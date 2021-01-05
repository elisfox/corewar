/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:19:34 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:48:33 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"
#include <fcntl.h>
#include <errno.h>

void	to_assemble(char *name)
{
	int			fd;
	t_parsedata	*parsing;
	t_tocken	*now;

	if ((fd = open(name, O_RDONLY)) == -1)
		stopped(ERR_OPEN_FILE);
	parsing = start_asm_parse(fd);
	asm_parsing(parsing);
	now = parsing->tockens;
	work_data(parsing, &now);
	work_to_asm_code(parsing, &now);
	replace_quotes(parsing);
	name = change_extens(name, ".s", ".cor");
	if ((fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		stopped(ERR_CREATE_FILE);
	recode_to_byte(fd, parsing);
	ft_printf("Writing output program to %s\n", name);
	ft_strdel(&name);
	free_asm_parser(&parsing);
}

t_bool	is_filename(const char *name_file, const char *ext)
{
	if (name_file && ext && ft_strlen(name_file) >= ft_strlen(ext))
		return (!ft_strcmp(ft_strchr(name_file, '\0') - ft_strlen(ext), ext));
	else
		return (false);
}

void	help(void)
{
	ft_printf("Usage: ./asm (champion.s)\n");
	ft_printf("    champion.s   — from assemble to bytecode\n");
}

int		main(int argc, char **argv)
{
	errno = 0;
	if (argc == 2 && is_filename(*(argv + 1), ".s"))
		to_assemble(*(argv + 1));
	else
		help();
	return (0);
}
