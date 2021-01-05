/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:19:23 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:26:30 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"

t_parsedata	*start_asm_parse(int fd)
{
	t_parsedata	*parsing;

	if (!(parsing = (t_parsedata *)ft_memalloc(sizeof(t_parsedata))))
		stopped(ERR_PARSER_INIT);
	parsing->fd = fd;
	parsing->line = 0;
	parsing->column = 0;
	parsing->index = 0;
	parsing->op_index = 0;
	parsing->name = NULL;
	parsing->comment = NULL;
	parsing->code = NULL;
	parsing->code_size = 0;
	parsing->tags = NULL;
	return (parsing);
}

t_tag		*init_tag(char *name, int op_pos)
{
	t_tag	*tag;

	if (!(tag = (t_tag *)ft_memalloc(sizeof(t_tag))))
		stopped(ERR_LABEL_INIT);
	if (!(tag->name = ft_strdup(name)))
		stopped(ERR_STR_INIT);
	tag->op_pos = op_pos;
	tag->quote = NULL;
	tag->next = NULL;
	return (tag);
}

t_quote		*init_quote(t_parsedata *parsing, t_tocken *tocken, size_t size)
{
	t_quote	*quote;

	if (!(quote = (t_quote *)ft_memalloc(sizeof(t_quote))))
		stopped(ERR_QUOTE_INIT);
	quote->line = tocken->line;
	quote->column = tocken->column;
	quote->pos = parsing->index;
	quote->op_pos = parsing->op_index;
	quote->size = size;
	quote->next = NULL;
	return (quote);
}

t_tocken	*init_tocken(t_parsedata *parser, t_type type)
{
	t_tocken	*tocken;

	if (!(tocken = (t_tocken *)ft_memalloc(sizeof(t_tocken))))
		stopped(ERR_TOKEN_INIT);
	tocken->content = NULL;
	tocken->type = type;
	tocken->line = parser->line;
	if (type == SEPARATOR || type == NEW_LINE)
		tocken->column = parser->column - 1;
	else
		tocken->column = parser->column;
	tocken->next = NULL;
	return (tocken);
}
