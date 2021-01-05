/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:21:43 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:28:21 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_error.h"
#include <stdio.h>
#include <errno.h>

void	stopped(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

char	*change_extens(char *name_file, char *old, char *new)
{
	char	*basename;

	basename = ft_strsub(name_file, 0, ft_strlen(name_file) - ft_strlen(old));
	if (!basename)
		stopped(ERR_STR_INIT);
	if (!(name_file = ft_strjoin(basename, new)))
		stopped(ERR_STR_INIT);
	ft_strdel(&basename);
	return (name_file);
}

t_bool	is_name(const char *name, const char *type)
{
	if (name && type && ft_strlen(name) >= ft_strlen(type))
		return (!ft_strcmp(ft_strchr(name, '\0') - ft_strlen(type), type));
	else
		return (false);
}

void	from_int32_byte(char *data,
						int32_t index,
						int32_t value,
						size_t size)
{
	int8_t		i;

	i = 0;
	while (size)
	{
		data[index + size - 1] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}
