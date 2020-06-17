/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_dynamic_buffer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:07:10 by asmall            #+#    #+#             */
/*   Updated: 2020/05/10 17:07:14 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_dynamic_buffer	make_new_dynamic_buffer(void)
{
	t_dynamic_buffer	buffer;

	buffer.amount_chars = 0;
	buffer.size_for_malloc = 50;
	buffer.overflow_counter = 1;
	return (buffer);
}
