/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_help_pt2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:02:09 by asmall            #+#    #+#             */
/*   Updated: 2020/06/17 22:32:31 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void			set_sdl_color2(SDL_Color *color, int i)
{
	if (i == 3 || i == 'b')
	{
		color->r = 0;
		color->g = 0;
		color->b = 155;
	}
	else if (i == 4 || i == 'p')
	{
		color->r = 155;
		color->g = 0;
		color->b = 155;
	}
	else if (i == 5 || i == 'c')
	{
		color->r = 0;
		color->g = 155;
		color->b = 155;
	}
}

void			set_sdl_color3(SDL_Color *color, int i)
{
	if (i == 6 || i == 'e')
	{
		color->r = 155;
		color->g = 155;
		color->b = 155;
	}
	else if (i == 7 || i == 'l')
	{
		color->r = 50;
		color->g = 50;
		color->b = 50;
	}
	else if (i == 'n')
	{
		color->r = 111;
		color->g = 111;
		color->b = 111;
	}
}

void			set_sdl_color(SDL_Color *color, int i)
{
	if (i == 0 || i == 'r')
	{
		color->r = 155;
		color->g = 0;
		color->b = 0;
	}
	else if (i == 1 || i == 'y')
	{
		color->r = 155;
		color->g = 155;
		color->b = 0;
	}
	else if (i == 2 || i == 'g')
	{
		color->r = 0;
		color->g = 155;
		color->b = 0;
	}
	else
	{
		set_sdl_color2(color, i);
		set_sdl_color3(color, i);
	}
}

void			live_players(t_vm *vm, SDL_FRect coor, int sum)
{
	unsigned	i;
	float		k;

	i = -1;
	while (++i < vm->num_players)
		sum += vm->players[i].lives_in_current_period;
	k = 300 / (float)sum;
	i = -1;
	while (++i < vm->num_players)
	{
		coor.w = vm->players[i].lives_in_current_period * k;
		set_render_draw_color(choose_color_char(i));
		SDL_RenderFillRectF(g_main_render, &coor);
		coor.x += coor.w;
	}
}
