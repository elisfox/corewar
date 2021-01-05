/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhaired <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:42:02 by lhaired           #+#    #+#             */
/*   Updated: 2019/09/07 18:42:04 by lhaired          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*result;

	if ((result = ft_strnew(ft_strlen(s1))))
	{
		i = 0;
		while (s1[i])
		{
			result[i] = s1[i];
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}
