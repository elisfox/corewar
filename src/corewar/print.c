#include "corewar.h"

void    print(t_arena *arena)
{
    int  i;
    t_player *pl;

    pl = arena->players;
    i = 0;
    // while (i < 4)
    // {
    //     printf("i = %d     flag = %d\n", i, arena->flag_n[i]);
    //     i++;
    // }
    while (pl)
    {
        printf("player = %d\n", pl->num);
        printf("name = %s\n", pl->header.prog_name);
        pl = pl->next;
        
    }
}