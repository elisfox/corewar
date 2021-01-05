/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geting_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:18:58 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:19:02 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <unistd.h>

static int	separate_str(char **str, char **line)
{
	char	*new;
	char	*part;

	part = ft_strchrs(*str, '\n');
	part++;
	if (!(*line = ft_strsub(*str, 0, part - *str)))
		return (-1);
	if (!ft_strlen(part))
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	new = ft_strdup(part);
	free(*str);
	*str = new;
	return ((new) ? 1 : -1);
}

int			get_line(const int fd, char **line)
{
	static char		*str = NULL;
	char			buff[BUFF_SIZE + 1];
	ssize_t			size;
	char			*tmp;

	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	while (!ft_strchrs(str, '\n'))
	{
		if (!(size = read(fd, buff, BUFF_SIZE)))
		{
			if (!(*line = str))
				return (0);
			str = NULL;
			return (1);
		}
		buff[size] = '\0';
		tmp = str;
		str = ft_strjoin(str, buff);
		free(tmp);
		if (!str)
			return (-1);
	}
	return (separate_str(&str, line));
}
