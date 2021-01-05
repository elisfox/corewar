/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:19:46 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:44:40 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"

void	parsing_chars(t_parsedata *parsing,
					char *line,
					unsigned start,
					t_tocken *tocken)
{
	unsigned column;

	tocken->column = start;
	column = parsing->column;
	while (line[parsing->column]
			&& ft_strchr(LABEL_CHARS, line[parsing->column]))
		parsing->column++;
	if ((parsing->column - column) && line[parsing->column] == LABEL_CHAR
			&& ++parsing->column)
	{
		tocken->content = get_tocken_content(parsing, line, start);
		tocken->type = LABEL;
		add_tocken(&parsing->tockens, tocken);
	}
	else if ((parsing->column - column) \
			&& find_delimiter(line[parsing->column]))
	{
		tocken->content = get_tocken_content(parsing, line, start);
		if (tocken->type == INDIRECT)
			tocken->type = (find_register(tocken->content)) \
				? REGISTER : OPERATOR;
		add_tocken(&parsing->tockens, tocken);
	}
	else
		lexical_error(parsing);
}

void	parsing_numbers(t_parsedata *parsing,
						char *line,
						unsigned start,
						t_tocken *tocken)
{
	unsigned column;

	tocken->column = start;
	if (line[parsing->column] == '-')
		parsing->column++;
	column = parsing->column;
	while (ft_isdigit(line[parsing->column]))
		parsing->column++;
	if ((parsing->column - column)
		&& (tocken->type == DIRECT || find_delimiter(line[parsing->column])))
	{
		tocken->content = get_tocken_content(parsing, line, start);
		add_tocken(&parsing->tockens, tocken);
	}
	else if (tocken->type != DIRECT)
	{
		parsing->column = start;
		parsing_chars(parsing, line, start, tocken);
	}
	else
		lexical_error(parsing);
}

void	str_parsing(t_parsedata *parsing,
					char **line,
					unsigned start,
					t_tocken *tocken)
{
	char	*end;
	ssize_t	size;
	char	*str;

	tocken->column = start;
	size = 1;
	while (!(end = ft_strchr(&((*line)[start + 1]), '\"'))
		&& (size = get_line(parsing->fd, &str)) > 0)
		*line = join_str(line, &str);
	change_parser_pointer(parsing, *line);
	if (size == -1)
		stopped(ERR_READ_FILE);
	if (size == 0)
		lexical_error(parsing);
	if (!(tocken->content = ft_strsub(*line, start, \
	end + 1 - &((*line)[start]))))
		stopped(ERR_STR_INIT);
	if (end - parsing->column != *line)
		moving_line(line, end - parsing->column);
	parsing->column++;
	add_tocken(&parsing->tockens, tocken);
}

void	tocken_parsing(t_parsedata *parsing, char **line)
{
	if (*(*line + parsing->column) == SEPARATOR_CHAR && ++parsing->column)
		add_tocken(&parsing->tockens, init_tocken(parsing, SEPARATOR));
	else if (*(*line + parsing->column) == '\n' && ++parsing->column)
		add_tocken(&parsing->tockens, init_tocken(parsing, NEW_LINE));
	else if (*(*line + parsing->column) == '.')
		parsing_chars(parsing, *line, parsing->column++,
				init_tocken(parsing, COMMAND));
	else if (*(*line + parsing->column) == DIRECT_CHAR && ++parsing->column)
	{
		if (*(*line + parsing->column) == LABEL_CHAR && ++parsing->column)
			parsing_chars(parsing, *line, parsing->column - 2,
				init_tocken(parsing, DIRECT_LABEL));
		else
			parsing_numbers(parsing, *line, parsing->column - 1,
							init_tocken(parsing, DIRECT));
	}
	else if (*(*line + parsing->column) == '\"')
		str_parsing(parsing, line, parsing->column, \
				init_tocken(parsing, STRING));
	else if (*(*line + parsing->column) == LABEL_CHAR)
		parsing_chars(parsing, *line, parsing->column++,
				init_tocken(parsing, INDIRECT_LABEL));
	else
		parsing_numbers(parsing, *line, parsing->column, \
				init_tocken(parsing, INDIRECT));
}

void	asm_parsing(t_parsedata *parsing)
{
	ssize_t	size;
	char	*line;

	while (++parsing->line
		&& !(parsing->column = 0)
		&& (size = get_line(parsing->fd, &line)) > 0)
	{
		while (line[parsing->column])
		{
			pass_whitespaces(parsing, line);
			pass_comment(parsing, line);
			if (line[parsing->column])
				tocken_parsing(parsing, &line);
		}
		ft_strdel(&line);
	}
	if (size == -1)
		stopped(ERR_READ_FILE);
	add_tocken(&(parsing->tockens), init_tocken(parsing, END));
}
