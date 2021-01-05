/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhaired <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 14:41:44 by lhaired           #+#    #+#             */
/*   Updated: 2019/09/14 14:41:46 by lhaired          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	char *ptr;

	if ((ptr = ft_memchr(s, '\0', maxlen)))
		return (size_t)(ptr - s);
	return (maxlen);
}
