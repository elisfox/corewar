/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:19:09 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:47:31 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	lexical_error(t_parsedata *parser)
{
	ft_printf("Lexical error at [%03u:%03u]\n",
													parser->line,
													parser->column + 1);
	exit(1);
}

void	tocken_error(t_tocken *tocken)
{
	ft_printf("Unexpected token \"%s\" %s at [%03u:%03u]\n",
			tocken->content, g_type[tocken->type],
			tocken->line, tocken->column + 1);
	exit(1);
}

void	tag_error(t_tag *tag)
{
	t_quote	*quote;

	ft_printf("Undeclared tag \"%s\" is quoted at:\n", tag->name);
	quote = tag->quote;
	while (quote)
	{
		ft_printf("\t— [%03u:%03u]\n", quote->line, quote->column + 1);
		quote = quote->next;
	}
	exit(1);
}

void	operator_error(t_tocken *tocken)
{
	ft_printf("Unknown operator \"%s\"at [%03u:%03u]\n",
			tocken->content, tocken->line, tocken->column + 1);
	exit(1);
}

void	arg_type_error(t_op *op, int arg_num, t_tocken *tocken)
{
	ft_printf("Invalid type of parameter #%d for instruction \"%s\""\
						" at [%03u:%03u]\n", arg_num + 1,
						op->name, tocken->line, tocken->column + 1);
	exit(1);
}
