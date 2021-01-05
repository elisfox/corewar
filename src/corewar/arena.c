/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojoseph <jojoseph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:06:23 by fjessi            #+#    #+#             */
/*   Updated: 2021/01/05 16:28:02 by jojoseph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_carriage	*create_carriage(t_arena *arena, t_player *player)
{
    t_carriage	*carriage;

	if (!(carriage = (t_carriage*)ft_memalloc(sizeof(*carriage))))
		ft_exit("ERROR", NULL);
    carriage->core = arena->core;
	carriage->wait_cmd = 1;
    carriage->owner = player;
    carriage->next = NULL;
    carriage->prev = NULL;    
    return (carriage);
}

t_carriage	*get_new_carriage(t_arena *arena, t_player *tmp, int pc)
{
    t_carriage	*carriage;

	carriage = create_carriage(arena, tmp);
    carriage->pc = pc;
    carriage->id = tmp->num;
    carriage->reg[1] = reverse_bytes(-(tmp->num));
    return (carriage);
}

void    put_code_to_arena(t_arena *arena)
{
    t_carriage	*carriage;
    t_carriage  *tmp_car;
    t_carriage  *tmp_car_prev;
    t_player *tmp;
    int			pc;

	pc = 0;
    tmp = arena->players;
    while(tmp)
    {
        if(arena->carriages == NULL)
        {
            carriage = create_carriage(arena, tmp);
            carriage->pc = pc;
            carriage->id = tmp->num;
            carriage->reg[1] = reverse_bytes(-(tmp->num));
            arena->carriages = carriage;
        }            
        else
        {
            tmp_car = arena->carriages;
            while(tmp_car->next)
               tmp_car = tmp_car->next;
		tmp_car_prev = tmp_car;
		tmp_car->next = get_new_carriage(arena, tmp, pc);
		tmp_car = tmp_car->next;
		tmp_car->prev = tmp_car_prev;
        }
        ft_memmove(arena->core + pc, tmp->code, reverse_bytes(tmp->header.prog_size));
        pc += MEM_SIZE / arena->count_players;
        tmp = tmp->next;
    }
    print(arena);
}
