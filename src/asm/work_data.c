/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:21:53 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:21:56 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"

static void	handling_name(t_parsedata *parser, t_tocken **now)
{
	if ((*now)->type == STRING)
	{
		if (!(parser->name = ft_strsub((*now)->content,
					1, ft_strlen((*now)->content) - 2)))
			stopped(ERR_STR_INIT);
		if (ft_strlen(parser->name) > PROG_NAME_LENGTH)
			name_error();
		(*now) = (*now)->next;
	}
	else
		tocken_error(*now);
}

static void	handling_comment(t_parsedata *parser, t_tocken **now)
{
	if ((*now)->type == STRING)
	{
		if (!(parser->comment = ft_strsub((*now)->content,
					1, ft_strlen((*now)->content) - 2)))
			stopped(ERR_STR_INIT);
		if (ft_strlen(parser->comment) > COMMENT_LENGTH)
			comment_error();
		(*now) = (*now)->next;
	}
	else
		tocken_error(*now);
}

void		work_data(t_parsedata *parser, t_tocken **now)
{
	while (!parser->name || !parser->comment)
	{
		if ((*now)->type == COMMAND
			&& !parser->name
			&& !ft_strcmp((*now)->content, NAME_CMD_STRING))
		{
			(*now) = (*now)->next;
			handling_name(parser, now);
			if ((*now)->type != NEW_LINE)
				tocken_error(*now);
		}
		else if ((*now)->type == COMMAND
			&& !parser->comment
			&& !ft_strcmp((*now)->content, COMMENT_CMD_STRING))
		{
			(*now) = (*now)->next;
			handling_comment(parser, now);
			if ((*now)->type != NEW_LINE)
				tocken_error(*now);
		}
		else
			tocken_error(*now);
		(*now) = (*now)->next;
	}
}
