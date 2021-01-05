/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:18:46 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:18:51 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_tockens(t_tocken **list)
{
	t_tocken	*now;
	t_tocken	*del;

	now = *list;
	while (now)
	{
		del = now;
		now = now->next;
		ft_strdel(&(del->content));
		ft_memdel((void **)&del);
	}
	*list = NULL;
}

static void	free_quotes(t_quote **list)
{
	t_quote	*now;
	t_quote	*del;

	now = *list;
	while (now)
	{
		del = now;
		now = now->next;
		ft_memdel((void **)&del);
	}
	*list = NULL;
}

static void	free_tags(t_tag **list)
{
	t_tag	*now;
	t_tag	*del;

	now = *list;
	while (now)
	{
		del = now;
		now = now->next;
		ft_strdel(&(del->name));
		free_quotes(&(del->quote));
		ft_memdel((void **)&del);
	}
	*list = NULL;
}

void		free_asm_parser(t_parsedata **parsing)
{
	free_tockens(&((*parsing)->tockens));
	ft_strdel(&((*parsing)->name));
	ft_strdel(&((*parsing)->comment));
	ft_strdel(&((*parsing)->code));
	free_tags(&((*parsing)->tags));
	ft_memdel((void **)parsing);
}
