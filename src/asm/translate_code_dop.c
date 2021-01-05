/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_code_dop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:21:28 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:21:31 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"

void			upd_code_buffer(t_parsedata *parser)
{
	parser->code_size += CHAMP_MAX_SIZE;
	if (!(parser->code = (char *)realloc(parser->code,
				((size_t)parser->code_size + MAX_STATEMENT_SIZE))))
		stopped(ERR_STR_INIT);
}

t_op			*take_op(char *name)
{
	unsigned	i;

	i = 0;
	while (i < (sizeof(g_oper) / sizeof(t_op)))
	{
		if (!ft_strcmp(g_oper[i].name, name))
			return (&g_oper[i]);
		i++;
	}
	return (NULL);
}

static uint8_t	get_arg_code(int8_t type)
{
	if (type == T_DIR)
		return (DIR_CODE);
	else if (type == T_REG)
		return (REG_CODE);
	else
		return (IND_CODE);
}

void			upd_types_code(int8_t *types_code, int8_t type, int arg_num)
{
	(*types_code) |= (get_arg_code(type) << 2 * (4 - arg_num - 1));
}
