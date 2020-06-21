/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:04:28 by asmall            #+#    #+#             */
/*   Updated: 2020/06/21 11:42:34 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		choose_color(int n)
{
	static const int	colors[] = {0x00009b, 0x009b9b, 0x008000, 0x9b0000,
		0x800080, 0x9b9b00, 0xa9a9a9, 0x323232, 0x6f6f6f};

	return (colors[n]);
}

int		choose_reverse_color(t_battlefield *cell)
{
	static const int	colors[] = {0x00009b, 0x009b9b, 0x008000, 0x9b0000,
		0x800080, 0x9b9b00, 0xa9a9a9, 0x323232, 0x6f6f6f};
	int					i;

	i = -1;
	while (++i < 8)
		if (colors[i] == cell->color)
			break ;
	return (i);
}
