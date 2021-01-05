/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:20:52 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:31:30 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"

static int8_t	search_arg_type(t_type type)
{
	if (type == DIRECT || type == DIRECT_LABEL)
		return (T_DIR);
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return (T_IND);
	else if (type == REGISTER)
		return (T_REG);
	else
		return (0);
}

static void		translate_quote(t_parsedata *parser, t_tocken *now, t_op *op)
{
	t_tag		*tag;
	char		*name;
	unsigned	start;
	size_t		size;

	start = (now->type == DIRECT_LABEL) ? 2 : 1;
	size = (now->type == DIRECT_LABEL) ? op->t_dir_size : IND_SIZE;
	if (!(name = ft_strsub(now->content,
					start, ft_strlen(now->content) - start)))
		stopped(ERR_STR_INIT);
	if (!(tag = find_tag(parser->tags, name)))
	{
		tag = init_tag(name, -1);
		add_tag(&(parser->tags), tag);
	}
	ft_strdel(&name);
	add_quote(&tag->quote, init_quote(parser, now, size));
	parser->index += size;
}

static void		translate_num(t_parsedata *parsing, t_tocken *now, t_op *oper)
{
	unsigned	start;
	size_t		size;

	start = (now->type == DIRECT) ? 1 : 0;
	size = (now->type == DIRECT) ? oper->t_dir_size : IND_SIZE;
	if (size == 2)
		from_int32_byte(parsing->code,
						parsing->index,
						(int16_t)ft_atoi32(&now->content[start]),
						size);
	else
		from_int32_byte(parsing->code,
						parsing->index,
						ft_atoi32(&now->content[start]),
						size);
	parsing->index += size;
}

static void		translate_register(t_parsedata *parser, t_tocken *now)
{
	from_int32_byte(parser->code,
					parser->index,
					(int8_t)ft_atoi(&now->content[1]), 1);
	parser->index += 1;
}

int8_t			translate_args(t_parsedata *parser,
							t_tocken **now,
							t_op *op,
							int arg_num)
{
	int8_t	type;

	type = search_arg_type((*now)->type);
	if (!(op->args_types[arg_num] & type))
		arg_type_error(op, arg_num, *now);
	if ((*now)->type == INDIRECT_LABEL
		|| (*now)->type == DIRECT_LABEL)
		translate_quote(parser, *now, op);
	else if ((*now)->type == INDIRECT
		|| (*now)->type == DIRECT)
		translate_num(parser, *now, op);
	else
		translate_register(parser, *now);
	return (type);
}
