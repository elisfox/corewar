/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:20:19 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:46:23 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_whitetspc(int c)
{
	return (c == '\t' || c == '\v' ||
			c == '\f' || c == '\r' ||
			c == ' ');
}

t_bool	find_delimiter(int c)
{
	return (c == '\0'
			|| c == '\n' || find_whitetspc(c)
			|| c == COMMAND_CHAR || c == '\"'
			|| c == DIRECT_CHAR || c == SEPARATOR_CHAR
			|| c == COMMENT_CHAR || c == ALT_COMMENT_CHAR);
}

t_bool	find_register(const char *arg)
{
	int	i;

	i = 0;
	if (ft_strlen(arg) >= 2 && ft_strlen(arg) <= 3 && arg[i] == REG_CHAR)
	{
		i++;
		while (ft_isdigit(arg[i]))
			i++;
		return (!arg[i] && ft_atoi(&arg[1]) > 0);
	}
	return (false);
}

/*
 **  skipping function
*/

void	pass_whitespaces(t_parsedata *parser, const char *line)
{
	while (find_whitetspc(line[parser->column]))
		parser->column++;
}

void	pass_comment(t_parsedata *parser, const char *line)
{
	if (line[parser->column] == COMMENT_CHAR
		|| line[parser->column] == ALT_COMMENT_CHAR)
		while (line[parser->column] && line[parser->column] != '\n')
			parser->column++;
}
