/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojoseph <jojoseph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:42:04 by lhaired           #+#    #+#             */
/*   Updated: 2020/12/05 16:13:59 by jojoseph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 20
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"

int		get_next_line(const int fd, char **line);

#endif
