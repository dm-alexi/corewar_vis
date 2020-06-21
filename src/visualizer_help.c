/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:06:04 by asmall            #+#    #+#             */
/*   Updated: 2020/06/22 00:18:07 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	init_visualizer(t_vm *vm)
{
	(void)vm; // check later
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error2("SDL could not initialize. SDL error: ", SDL_GetError());
	if (!(g_main_window = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
		error2("SDL could not create window. SDL error: ", SDL_GetError());
	if (!(g_main_render = SDL_CreateRenderer(g_main_window, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		error2("SDL could not create renderer. SDL error: ", SDL_GetError());
	if (TTF_Init() < 0)
		error2("SDL_ttf could not initialize. SDL error: ", TTF_GetError());
	if (!(g_font = TTF_OpenFont("resource/InputMono-Regular.ttf", 15)))
		error(TTF_GetError());
}

void	set_render_draw_color(int color)
{
	SDL_SetRenderDrawColor(g_main_render, color & 0xff, color >> 8 & 0xff,
		color >> 16 & 0xff, 255);
}

void	visualizer_event(t_vm *vm)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
			vm->vis_pause = !vm->vis_pause;
		else if (event.type == SDL_QUIT ||
		(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			vm->vis_quit = 1;
	}
}

void	set_sdl_color(SDL_Color *color, int i)
{
	static const int	colors[] = {0x00009b, 0x009b9b, 0x008000, 0x9b0000,
		0x800080, 0x9b9b00, 0xa9a9a9, 0x323232, 0x6f6f6f};

	color->r = colors[i] & 0xff;
	color->g = colors[i] >> 8 & 0xff;
	color->b = colors[i] >> 16 & 0xff;
}

void	live_players(t_vm *vm, SDL_Rect coor, int sum)
{
	unsigned	i;
	float		k;

	i = 0;
	while (i < vm->num_players)
		sum += vm->players[i++].lives_in_current_period;
	k = 300 / (float)sum;
	i = 0;
	while (i < vm->num_players)
	{
		coor.w = vm->players[i].lives_in_current_period * k;
		set_render_draw_color(choose_color(i));
		SDL_RenderFillRect(g_main_render, &coor);
		coor.x += coor.w;
		++i;
	}
}
