/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:21:19 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:21:23 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"

static void		handling_tag(t_parsedata *parser, t_tocken **now)
{
	t_tag	*tag;
	char	*name;

	if (!(name = ft_strsub((*now)->content,
				0, ft_strlen((*now)->content) - 1)))
		stopped(ERR_STR_INIT);
	if (!(tag = find_tag(parser->tags, name)))
		add_tag(&(parser->tags), init_tag(name, parser->op_index));
	if (tag && tag->op_pos == -1)
		tag->op_pos = parser->index;
	ft_strdel(&name);
}

static int8_t	handling_args(t_parsedata *parser, t_tocken **now, t_op *op)
{
	int		arg_num;
	int8_t	types_code;
	int8_t	type;

	arg_num = 0;
	types_code = 0;
	while (arg_num < op->args_num)
	{
		if ((*now)->type >= REGISTER && (*now)->type <= INDIRECT_LABEL)
		{
			type = translate_args(parser, now, op, arg_num);
			upd_types_code(&types_code, type, arg_num);
			(*now) = (*now)->next;
		}
		else
			tocken_error((*now));
		if (arg_num++ != op->args_num - 1)
		{
			if ((*now)->type != SEPARATOR)
				tocken_error((*now));
			(*now) = (*now)->next;
		}
	}
	return (types_code);
}

static void		handling_operator(t_parsedata *parser, t_tocken **now)
{
	t_op	*op;
	int8_t	types_code;

	if ((op = take_op((*now)->content)))
	{
		parser->code[parser->index++] = op->code;
		(*now) = (*now)->next;
		if (op->args_types_code)
			parser->index++;
		types_code = handling_args(parser, now, op);
		if (op->args_types_code)
			parser->code[parser->op_index + 1] = types_code;
	}
	else
		operator_error((*now));
}

void			work_to_asm_code(t_parsedata *parsing, t_tocken **now)
{
	while ((*now)->type != END)
	{
		if (parsing->index >= parsing->code_size)
			upd_code_buffer(parsing);
		parsing->op_index = parsing->index;
		if ((*now)->type == LABEL)
		{
			handling_tag(parsing, now);
			(*now) = (*now)->next;
		}
		if ((*now)->type == OPERATOR)
			handling_operator(parsing, now);
		if ((*now)->type == NEW_LINE)
			(*now) = (*now)->next;
		else
			tocken_error((*now));
	}
}
