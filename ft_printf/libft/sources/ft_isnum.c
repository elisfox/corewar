/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhaired <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:20:55 by lhaired           #+#    #+#             */
/*   Updated: 2019/09/06 19:21:00 by lhaired          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_isnum(char *str, int base)
{
	size_t	i;
	size_t	digits;

	i = 0;
	digits = 0;
	while (ft_isspace(str[i]))
		i++;
	if (base != 10 && !ft_isprefix(&str[i], base))
		return (false);
	if (base == 2 || base == 16)
		i += 2;
	else if (base == 8)
		i++;
	else if (base == 10 && (str[i] == '-' || str[i] == '+'))
		i++;
	while (ft_isdigit_base(str[i], base) >= 0)
	{
		i++;
		digits++;
	}
	return ((!str[i] && digits) ? true : false);
}
