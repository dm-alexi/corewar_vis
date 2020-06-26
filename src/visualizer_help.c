/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:06:04 by asmall            #+#    #+#             */
/*   Updated: 2020/06/26 20:08:02 by sscarecr         ###   ########.fr       */
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

void	event_handler(t_vm *vm)
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
		SDL_SetRenderDrawColor(g_main_render, g_colors[i] & 0xff,
			g_colors[i] >> 8 & 0xff, g_colors[i] >> 16 & 0xff, 255);
		SDL_RenderFillRect(g_main_render, &coor);
		coor.x += coor.w;
		++i;
	}
}

void	finish_visualization(t_vm *vm)
{
	visualize(vm);
	while (!vm->vis_quit && !vm->vis_pause)
		event_handler(vm);
	TTF_CloseFont(g_font);
	TTF_Quit();
	SDL_DestroyRenderer(g_main_render);
	SDL_DestroyWindow(g_main_window);
	SDL_Quit();
}
