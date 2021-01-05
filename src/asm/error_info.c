/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoze <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:18:34 by gdoze             #+#    #+#             */
/*   Updated: 2020/10/25 15:23:06 by gdoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	name_error(void)
{
	ft_printf("Champion name too long (Max length %u)\n", PROG_NAME_LENGTH);
	exit(1);
}

void	comment_error(void)
{
	ft_printf("Champion comment too long (Max length %u)\n",
																COMMENT_LENGTH);
	exit(1);
}
