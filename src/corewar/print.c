#include "corewar.h"

void    print(t_arena *arena)
{
    int  i;
    /*t_player *pl;

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
        
    }*/

    t_carriage *car;

    car = arena->carriages;
    i = 0;
    while(car)
    {
        printf("pc = %d\n", car->pc);
        car = car->next;
    }
}

void    print_arena(void *core)
{
    int	i;
	int	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("0x%0.4x : ", i);
		j = 0;
		while (j++ < DUMP_WIDTH)
		{
			ft_printf("%02x ", ((unsigned char*)(core))[i]);
			++i;
		}
		ft_printf("\n");
	}
}