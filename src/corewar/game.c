/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojoseph <jojoseph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:06:23 by fjessi            #+#    #+#             */
/*   Updated: 2021/01/05 17:18:23 by jojoseph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	introduce_players(t_arena *arena)
{
	t_player *tmp;

	tmp = arena->players;	
	ft_printf("Introducing contestants...\n");
	while(tmp)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", tmp->num,
		reverse_bytes(tmp->header.prog_size), tmp->header.prog_name, tmp->header.comment);
		tmp = tmp->next;
	}
}

void	start_game(t_arena *arena)
{
	int fl;
	
	fl = 1;
	introduce_players(arena);
	while(fl)
	{
		if (arena->dump_nbr_cycles &&
		arena->dump_nbr_cycles == arena->num_cycles)
		{
			print_arena(arena->core);
			break ;
		}
		arena->num_cycles++;
	}
	
	
	
}
