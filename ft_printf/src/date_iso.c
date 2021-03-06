/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   date_iso.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojoseph <jojoseph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:10:54 by fjessi            #+#    #+#             */
/*   Updated: 2020/12/03 19:25:16 by jojoseph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*data_iso(va_list *ap)
{
	int		data;
	char	*dd;
	char	*mm;
	char	*yy;

	data = va_arg(*ap, int);
	dd = ft_itoa(data % 100);
	data /= 100;
	mm = ft_itoa(data % 100);
	data /= 100;
	yy = ft_itoa(data);
	if (!(yy = ft_strjoin_free(yy, "-", 1)))
		return (NULL);
	if (!(yy = ft_strjoin_free(yy, mm, 3)))
		return (NULL);
	if (!(yy = ft_strjoin_free(yy, "-", 1)))
		return (NULL);
	if (!(yy = ft_strjoin_free(yy, dd, 3)))
		return (NULL);
	return (yy);
}
