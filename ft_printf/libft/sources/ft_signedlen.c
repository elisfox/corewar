/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signedlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhaired <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 14:54:13 by lhaired           #+#    #+#             */
/*   Updated: 2019/09/14 14:54:15 by lhaired          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_signedlen(intmax_t number, unsigned int base)
{
	size_t	size;

	size = ft_unsignedlen((uintmax_t)FT_ABS(number), base);
	return (size + ((number < 0 && size) ? 1 : 0));
}
