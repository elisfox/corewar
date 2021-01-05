/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:22:04 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:22:08 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"
#include <fcntl.h>
#include <unistd.h>

void		recode_to_byte(int fd, t_parsedata *parsing)
{
	int32_t	len;
	int32_t	index;
	char	*bytecode;

	index = 0;
	len = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 + parsing->index;
	if (!(bytecode = ft_strnew((size_t)len)))
		stopped(ERR_STR_INIT);
	from_int32_byte(bytecode, index, COREWAR_EXEC_MAGIC, 4);
	index += 4;
	ft_memcpy(&bytecode[index], parsing->name, ft_strlen(parsing->name));
	index += PROG_NAME_LENGTH;
	index += 4;
	from_int32_byte(bytecode, index, parsing->index, 4);
	index += 4;
	ft_memcpy(&bytecode[index], parsing->comment, ft_strlen(parsing->comment));
	index += COMMENT_LENGTH;
	index += 4;
	ft_memcpy(&bytecode[index], parsing->code, (size_t)parsing->index);
	write(fd, bytecode, (size_t)len);
	free(bytecode);
}
