/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojoseph <jojoseph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:06:23 by jojoseph          #+#    #+#             */
/*   Updated: 2021/01/05 15:58:44 by jojoseph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		*init_flag_n(void)
{
	int *flag_n;
	int i;
	
	i = 0;
	if (!(flag_n = (int *)ft_memalloc(sizeof(MAX_PLAYERS))))
		ft_exit("ERROR", NULL);
	while (i < MAX_PLAYERS)
		flag_n[i++] = -1;
	return(flag_n);
	
}
t_arena		*init_arena(void)
{
	t_arena		*arena;

	if (!(arena = (t_arena *)ft_memalloc(sizeof(t_arena))))
		return (NULL);
	arena->dump_nbr_cycles = -1;
	arena->players = NULL;
	arena->count_players = 0;
	arena->flag_n = init_flag_n();
	ft_bzero(arena->core, MEM_SIZE);
	return(arena);
}