/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:20:00 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:49:34 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"

char	*get_tocken_content(t_parsedata *parsing, const char *line,
		unsigned strt)
{
	char	*content;

	if (!(content = ft_strsub(line, strt, parsing->column - strt)))
		stopped(ERR_STR_INIT);
	return (content);
}

char	*join_str(char **str1, char **str2)
{
	char *result;

	if (!(result = ft_strjoin(*str1, *str2)))
		stopped(ERR_STR_INIT);
	ft_strdel(str1);
	ft_strdel(str2);
	return (result);
}

void	change_parser_pointer(t_parsedata *parsing, const char *line)
{
	unsigned i;

	i = ++(parsing->column);
	while (line[i] && line[i] != '\"')
	{
		if (line[i] == '\n')
		{
			parsing->line++;
			parsing->column = 0;
		}
		else
			parsing->column++;
		i++;
	}
}

void	moving_line(char **line, char *ptr)
{
	char *new;

	if (!(new = ft_strdup(ptr)))
		stopped(ERR_STR_INIT);
	ft_strdel(line);
	*line = new;
}
