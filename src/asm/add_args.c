/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:18:19 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:27:20 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_tag(t_tag **list, t_tag *new)
{
	t_tag	*now;

	if (list)
	{
		if (*list)
		{
			now = *list;
			while (now->next)
				now = now->next;
			now->next = new;
		}
		else
			*list = new;
	}
}

void	add_quote(t_quote **list, t_quote *new)
{
	t_quote	*now;

	if (list)
	{
		if (*list)
		{
			now = *list;
			while (now->next)
				now = now->next;
			now->next = new;
		}
		else
			*list = new;
	}
}

t_tag	*find_tag(t_tag *list, char *name)
{
	t_tag	*tag;

	tag = list;
	while (tag)
	{
		if (!ft_strcmp(tag->name, name))
			return (tag);
		tag = tag->next;
	}
	return (tag);
}

void	replace_quotes(t_parsedata *file)
{
	t_tag		*tag;
	t_quote		*quote;

	tag = file->tags;
	while (tag)
	{
		if (tag->op_pos == -1)
			tag_error(tag);
		else
		{
			quote = tag->quote;
			while (quote)
			{
				if (quote->size == 2)
					from_int32_byte(file->code, quote->pos,
									(int16_t)(tag->op_pos - quote->op_pos),
									quote->size);
				else
					from_int32_byte(file->code, quote->pos,
									tag->op_pos - quote->op_pos, quote->size);
				quote = quote->next;
			}
		}
		tag = tag->next;
	}
}

void	add_tocken(t_tocken **list, t_tocken *new)
{
	t_tocken	*now;

	if (list)
	{
		if (*list)
		{
			now = *list;
			while (now->next)
				now = now->next;
			if (now->type == NEW_LINE && new->type == NEW_LINE)
				ft_memdel((void **)&new);
			else
				now->next = new;
		}
		else
		{
			if (new->type == NEW_LINE)
				ft_memdel((void **)&new);
			else
				*list = new;
		}
	}
}
