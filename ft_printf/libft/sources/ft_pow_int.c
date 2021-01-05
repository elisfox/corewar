/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhaired <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:13:59 by lhaired           #+#    #+#             */
/*   Updated: 2019/09/06 20:14:03 by lhaired          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_pow_int(intmax_t num, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (num * (ft_pow_int(num, power - 1)));
}
