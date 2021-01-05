/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:53:39 by gdoze             #+#    #+#             */
/*   Updated: 2020/11/07 16:31:05 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "../ft_printf/include/ft_printf.h"
# include "../ft_printf/include/get_next_line.h"
# include "op.h"
# include "asm_op.h"

# define BUFF_SIZE 2048

# define MAX_STATEMENT_SIZE 14

# define REG_CHAR 'r'

# define COMMAND_CHAR '.'

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	OPERATOR,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}	t_type;

static char				*g_type[] = {

	"COMMAND",
	"STRING",
	"LABEL",
	"OPERATOR",
	"REGISTER",
	"DIRECT",
	"DIRECT_LABEL",
	"INDIRECT",
	"INDIRECT_LABEL",
	"SEPARATOR",
	"NEW_LINE",
	"END"
};

/*
** Token
*/

/*
** content — content of token
** type    — type of token
** line     — line, where token is placed
** column  — column, where token is placed
** next    — pointer to the next token
*/

typedef struct			s_tocken
{
	char				*content;
	t_type				type;
	unsigned			line;
	unsigned			column;
	struct s_tocken		*next;
}						t_tocken;

/*
** Mention
*/

/*
** line    — line, where mention was found in assemble-file
** column — column, where mention was found in to_assemble-file
** index    — number of byte where mention is placed
** op_index — number of byte where operator code is placed
** size   — number of bytes which store a value of mention at index
** next   — pointer to the next mention
*/

typedef struct			s_quote
{
	unsigned			line;
	unsigned			column;
	int32_t				pos;
	int32_t				op_pos;
	size_t				size;
	struct s_quote		*next;
}						t_quote;

/*
** Label
*/

/*
** name     — name of label
** op_index   — number of byte, at which label points
** gons — list of quote
** next     — pointer to the next label
*/

typedef struct			s_tag
{
	char				*name;
	int32_t				op_pos;
	t_quote				*quote;
	struct s_tag		*next;
}						t_tag;

/*
** Assembler parse Data
*/

/*
** fd        — file descriptor of assemble-file
** line       — line of assemble-file, which parser processes now
** column    — column of to_assemble-file, which parser processes now
** tokens    — list of tokens
** index       — number of byte, at which parser writes now
** op_index    — number of byte, at which op_code of current statement is placed
** name      — name of champion
** comment   — comment of champion
** code      — executable code of champion
** code_size — size of champion's executable code
** tags    — list of tags
*/

typedef struct			s_data
{
	int					fd;
	unsigned			line;
	unsigned			column;
	t_tocken			*tockens;
	int32_t				index;
	int32_t				op_index;
	char				*name;
	char				*comment;
	char				*code;
	int32_t				code_size;
	t_tag				*tags;
}						t_parsedata;

t_parsedata				*start_asm_parse(int fd);
t_tocken				*init_tocken(t_parsedata *parser, t_type type);
t_tag					*init_tag(char *name, int op_pos);
t_quote					*init_quote(t_parsedata *parsing,
								t_tocken *tocken, size_t size);
int						get_line(int fd, char **line);
void					asm_parsing(t_parsedata *parsing);
int						find_whitetspc(int c);
t_bool					find_delimiter(int c);
t_bool					find_register(const char *arg);
char					*get_tocken_content(t_parsedata *parsing,
											const char *line,
											unsigned strt);
char					*join_str(char **str1, char **str2);
void					change_parser_pointer(t_parsedata *parsing,
									const char *line);
void					moving_line(char **line, char *ptr);
void					pass_whitespaces(t_parsedata *parser, const char *line);
void					pass_comment(t_parsedata *parser, const char *line);
void					add_tocken(t_tocken **list, t_tocken *new);
void					add_tag(t_tag **list, t_tag *new);
void					add_quote(t_quote **list, t_quote *new);
t_tag					*find_tag(t_tag *list, char *name);
void					replace_quotes(t_parsedata *file);
void					work_data(t_parsedata *parser, t_tocken **now);
void					work_to_asm_code(t_parsedata *parsing, t_tocken **now);
int8_t					translate_args(t_parsedata *parser,
										t_tocken **now,
										t_op *op,
										int arg_num);
void					upd_code_buffer(t_parsedata *parser);
t_op					*take_op(char *name);
void					upd_types_code(int8_t *types_code,
										int8_t type,
										int arg_num);
void					recode_to_byte(int fd, t_parsedata *parsing);
void					free_asm_parser(t_parsedata **parsing);
void					lexical_error(t_parsedata *parser);
void					tocken_error(t_tocken *tocken);
void					name_error(void);
void					comment_error(void);
void					tag_error(t_tag *tag);
void					operator_error(t_tocken *tocken);
void					arg_type_error(t_op *op, int arg_num, t_tocken *tocken);
void					from_int32_byte(char *data,
										int32_t index,
										int32_t value,
										size_t size);
void					to_assemble(char *name);
t_bool					is_filename(const char *name_file, const char *ext);
char					*change_extens(char *name_file, char *old, char *new);
void					help(void);
void					stopped(char *s);

#endif
