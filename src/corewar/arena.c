/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojoseph <jojoseph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:06:23 by fjessi            #+#    #+#             */
/*   Updated: 2021/01/05 14:27:09 by jojoseph         ###   ########.fr       */
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
    arena->carriages = carriage;    
    return (carriage);
}

void    put_code_to_arena(t_arena *arena)
{
    t_carriage	*carriage;
    t_player *tmp;
    int			pc;

	pc = 0;
    tmp = arena->players;
    while(tmp)
    {
        if(arena->carriages = NULL)
            carriage = create_carriage(arena, tmp);
        else
        {
                
        }
        
        carriage->pc = pc;
        carriage->id = tmp->num;
        carriage->reg[1] = reverse_bytes(-(tmp->num));
        
        
        
        
        
    }
}
