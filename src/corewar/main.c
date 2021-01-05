/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojoseph <jojoseph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:07:33 by jojoseph          #+#    #+#             */
/*   Updated: 2021/01/05 16:39:32 by jojoseph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	is_flag(char *av, char *av2)
{
	if (ft_strequ(av, "-n") && ft_atoi(av2))
		return (1);
	else if (ft_strequ(av, "-dump") && ft_atoi(av2))
		return (1);
	else
		return (0);
}

t_bool	is_avname(const char *name_av, const char *ext)
{
	if (name_av && ext && ft_strlen(name_av) >= ft_strlen(ext))
		return (!ft_strcmp(ft_strchr(name_av, '\0') - ft_strlen(ext), ext));
	else
		return (false);
}

void	help(void)
{
	ft_printf("Usage: ./corewar [-dump N] [[-n N] champion.cor]...\n");
	ft_printf("    champion.cor   — bytecode from asm\n");
	ft_printf("    -dump N	: Dumps memory after N cycles then exits\n");
	ft_printf("    -n N : Set unic champion number\n");
	exit (1);
}

int	get_num_player(t_arena *arena)
{
	int i;
	int j;

	if (arena->flag_n[arena->count_players] != -1)
		return(arena->flag_n[arena->count_players]);
	else
	{
		i = 0;
		j = 1;
		while (i < MAX_PLAYERS)
		{
			if (arena->flag_n[i] == -1)
				i++;
			else if (j == arena->flag_n[i])
			{
				j++;
				i = 0;
			}
			else if (j != arena->flag_n[i])
				i++;
		}
		arena->flag_n[arena->count_players] = j;
		return (j);		
	}
	
}

unsigned int	reverse_bytes(unsigned int value)
{
	return (value & 0x000000FFU) << 24 | (value & 0x0000FF00U) << 8 |
	(value & 0x00FF0000U) >> 8 | (value & 0xFF000000U) >> 24;
}

t_header	read_header(char *av, int *fd)
{
	t_header header;

	if ((*fd = open(av, O_RDONLY)) < 0)
		ft_exit("ERROR", NULL);
	if (read(*fd, &header, sizeof(header)) != sizeof(header))
		ft_exit("ERROR: reading header in file ", av);
	if (reverse_bytes(header.magic) != COREWAR_EXEC_MAGIC)
		ft_exit("ERROR: magic in header in file ", av);
	if (header.prog_name[PROG_NAME_LENGTH] != 0)
		ft_exit("ERROR: no string terminator found in champion name in file ", av);
	if (header.comment[COMMENT_LENGTH] != 0)
		ft_exit("ERROR: no string terminator found in comments in file ", av);
	if (reverse_bytes(header.prog_size) > CHAMP_MAX_SIZE)
		ft_exit("ERROR: champion prog_size too big in file ", av);
	if (reverse_bytes(header.prog_size) <= 0)
		ft_exit("ERROR: no champion prog found in file ", av);
	return (header);
}

void	*read_code(int *fd, char *av, int size)
{
	void *code;

	if (!(code = ft_memalloc(size)))
		ft_exit("ERROR", NULL);
	if (read(*fd, code, size) != size)
		ft_exit("ERROR reading champion programm incorrect program size in", av);
	if (read(*fd, code, 1) == 1)
	{
		close(*fd);
		ft_exit("ERROR: some data found after champion programm in ", av);
	}
	close (*fd);
	return (code);
}

t_player *get_new_player(t_arena *arena, char *av)
{
	t_player	*player;
	int			fd;
	
	if (!(player = (t_player *)ft_memalloc(sizeof(*player))))
		ft_exit("ERROR", NULL);
	player->num = get_num_player(arena);
	arena->count_players++;
	if (arena->count_players > MAX_PLAYERS)
		ft_exit("ERROR: ", "too many players");
	//ft_printf("player->num = %d\n", player->num);
	player->header = read_header(av, &fd);
	player->code = read_code(&fd, av, reverse_bytes(player->header.prog_size));
	player->prev = NULL;
	player->next = NULL;
	return (player);
}

void read_champ(t_arena *arena, char *av)
{
	t_player	*player;
	t_player	*tmp;
	t_player	*tmp_prev;
	int			fd;

	if (arena->players == NULL)
	{
		if (!(player = (t_player *)ft_memalloc(sizeof(*player))))
			ft_exit("ERROR", NULL);
		player->num = get_num_player(arena);
		arena->count_players++;
		//ft_printf("player->num = %d\n", player->num);
		player->header = read_header(av, &fd);
		player->code = read_code(&fd, av, reverse_bytes(player->header.prog_size));
		player->prev = NULL;
		player->next = NULL;
		arena->players = player;
	}
	else
	{
		tmp = arena->players;
		while (tmp->next)
			tmp = tmp->next;
		tmp_prev = tmp;
		tmp->next = get_new_player(arena, av);
		tmp = tmp->next;
		tmp->prev = tmp_prev;
	}
	//printf("champ = %d\n", arena->count_players);
}

int		check_num_flag(int num, t_arena *arena)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (num == arena->flag_n[i] || num > MAX_PLAYERS)
			return (0);
		i++;
	}
	return (1);
}

void	check_num_player(char *flag, t_arena *arena, int count)
{
	if (ft_strequ(flag, "-n"))
	{
		if (arena->flag_n[arena->count_players] <= count \
			&& arena->flag_n[arena->count_players] > 0)
			return ;
		else
			ft_exit("ERROR", ": Wrong number(s) for flag [-n].");
	}
}

void	get_num_flag(char *flag, char *num, t_arena *arena)
{
	if (ft_strequ(flag, "-n"))
	{
		if (check_num_flag(ft_atoi(num), arena))
			arena->flag_n[arena->count_players] = ft_atoi(num);
		else
			ft_exit("ERROR", ": Wrong number(s) for flag [-n].");
	}
	else if (ft_strequ(flag, "-dump"))
		arena->dump_nbr_cycles = ft_atoi(num);
}

void get_arg(int ac, char **av, t_arena *arena)
{
	int i;
	int count;

	i = 0;
	count = arena->count_players;
	arena->count_players = 0;
	while(++i < ac)
	{
		if (is_avname(av[i], ".cor"))
			read_champ(arena, av[i]);
		else if (av[i + 1] && is_flag(av[i], av[i + 1]) && is_avname(av[i], ".cor"))
			ft_printf("ok21\n");
		else if (ft_atoi(av[i]) && is_flag(av[i - 1], av[i]) && is_avname(av[i + 2], ".cor"))
			check_num_player(av[i - 1], arena, count);
			//ft_printf("ok22\n");
			//get_num_flag(av[i - 1], av[i], arena);
	}
	put_code_to_arena(arena);
	//print(arena);
}

int		main(int ac, char **av)
{
	int i;
	t_arena *arena;

	arena = NULL;
	arena = init_arena();
	if (ac >= 2)
	{
		i = 0;
		while(++i < ac)
		{
			if (is_avname(av[i], ".cor"))
				arena->count_players++;
				//ft_printf("ok11\n");
			else if (av[i + 1] && is_flag(av[i], av[i + 1]) && is_avname(av[i + 2], ".cor"))
				ft_printf("ok12\n");
			else if (ft_atoi(av[i]) && is_flag(av[i - 1], av[i]))
				get_num_flag(av[i - 1], av[i], arena);
			else
				help();
		}
		get_arg(ac, av, arena);
		start_game(arena);
	}
	else
		help();
	return(0);
}