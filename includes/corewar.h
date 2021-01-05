/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojoseph <jojoseph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:00:08 by jojoseph          #+#    #+#             */
/*   Updated: 2021/01/05 17:15:54 by jojoseph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../ft_printf/include/ft_printf.h"
# include "../ft_printf/include/get_next_line.h"
# include "op.h"

# define DUMP_WIDTH 64

typedef struct			s_player
{
	int					num;
	t_header			header;
	void				*code;
	struct s_player		*next;
	struct s_player		*prev;
}						t_player;

typedef struct			s_carriage
{
	int					id;
	t_player			*owner;
	int					pc;
	int					wait_cmd;
	unsigned char		*core;
	int					reg[REG_NUMBER + 1];
	struct s_carriage	*next;
	struct s_carriage	*prev;
}						t_carriage;

typedef struct			s_arena
{
	int					dump_nbr_cycles;
	int					*flag_n;
	int					count_players;
	int					num_cycles;
	t_player			*players;
	t_carriage			*carriages;
	unsigned char		core[MEM_SIZE];
}						t_arena;

	
int				main(int argc, char **argv);
unsigned int	reverse_bytes(unsigned int value);
void			ft_exit(char *str, char *str2);
t_arena			*init_arena(void);
void			put_code_to_arena(t_arena *arena);
void			print(t_arena *arena);
void			start_game(t_arena *arena);
void			print_arena(void *core);


#endif