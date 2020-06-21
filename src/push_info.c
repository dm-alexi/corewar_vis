/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:05:44 by asmall            #+#    #+#             */
/*   Updated: 2020/06/22 01:42:59 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	push_distribution(t_battlefield *arena, int y)
{
	int			colors[9];
	int			i;
	float		k;
	SDL_Rect	coor;

	k = 300 / (float)MEM_SIZE;
	i = -1;
	while (++i < 9)
		colors[i] = 0;
	i = -1;
	while (++i < MEM_SIZE)
		colors[choose_reverse_color(&arena[i])]++;
	i = -1;
	coor.y = y;
	coor.x = SCREEN_WIDTH - INFORMATION_SIZE + 25;
	while (++i < 9)
	{
		coor.h = 15;
		coor.w = colors[i] * k;
		set_render_draw_color(choose_color(i));
		SDL_RenderFillRect(g_main_render, &coor);
		coor.x += coor.w;
	}
}

void	push_live_breakdown(t_vm *vm, int y)
{
	int			sum;
	SDL_Rect	coor;

	coor.y = y;
	coor.x = SCREEN_WIDTH - INFORMATION_SIZE + 25;
	coor.h = 15;
	sum = 0;
	if (vm->live_calls > 0)
		live_players(vm, coor, sum);
	else
	{
		SDL_SetRenderDrawColor(g_main_render, 255, 255, 255, 255);
		coor.w = INFORMATION_SIZE - OFFSET;
		SDL_RenderDrawRect(g_main_render, &coor);
	}
}

void	put_text_texture(int y, char *temp_2, char *temp_3,
			SDL_Texture *text_texture)
{
	SDL_Rect	coor;

	(temp_2) ? (TTF_SizeText(g_font, temp_2, &coor.w, &coor.h)) :
		TTF_SizeText(g_font, temp_3, &coor.w, &coor.h);
	coor.x = SCREEN_WIDTH - INFORMATION_SIZE + OFFSET;
	coor.y = y;
	SDL_RenderCopy(g_main_render, text_texture, NULL, &coor);
	SDL_DestroyTexture(text_texture);
}

void	push_int_text(int data, char *info_text, int y, SDL_Color color)
{
	char		*temp_1;
	char		*temp_2;
	SDL_Surface	*text_surface;
	SDL_Texture	*text_texture;

	text_surface = NULL;
	text_texture = NULL;
	temp_1 = ft_itoa(data);
	temp_2 = ft_strjoin(info_text, temp_1);
	ft_strdel(&temp_1);
	text_surface = TTF_RenderText_Solid(g_font, temp_2, color);
	if (text_surface)
	{
		text_texture = SDL_CreateTextureFromSurface(g_main_render,
			text_surface);
		SDL_FreeSurface(text_surface);
		if (text_texture)
			put_text_texture(y, temp_2, 0, text_texture);
	}
	ft_strdel(&temp_2);
}

void	key_pause_quite(t_vm *vm)
{
	SDL_Event	event;

	while (!vm->vis_pause && !vm->vis_quit)
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
				&& event.key.keysym.sym == SDLK_ESCAPE))
				vm->vis_quit = 1;
			if (event.type == SDL_KEYDOWN
				&& event.key.keysym.sym == SDLK_SPACE)
				vm->vis_pause = 1;
		}
}
