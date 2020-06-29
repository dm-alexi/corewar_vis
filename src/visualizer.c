/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:06:18 by asmall            #+#    #+#             */
/*   Updated: 2020/06/29 19:47:05 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

const int	g_colors[MAX_PLAYERS] = {RED, YELLOW, GREEN, BLUE};

void	init_visualizer(t_vm *vm)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error2("SDL could not initialize. SDL error: ", SDL_GetError());
	if (!(vm->window = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
		error2("SDL could not create window. SDL error: ", SDL_GetError());
	if (!(vm->renderer = SDL_CreateRenderer(vm->window, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		error2("SDL could not create renderer. SDL error: ", SDL_GetError());
	if (TTF_Init() < 0)
		error2("SDL_ttf could not initialize. SDL error: ", TTF_GetError());
	if (!(vm->font = TTF_OpenFont("resource/InputMono-Regular.ttf", 15)))
		error(TTF_GetError());
}

void	visualize(t_vm *vm)
{
	SDL_SetRenderDrawColor(vm->renderer, 0, 0, 0, 255);
	SDL_RenderClear(vm->renderer);
	draw_arena(vm);
	draw_menu(vm);
	SDL_RenderPresent(vm->renderer);
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

void	finish_visualization(t_vm *vm)
{
	visualize(vm);
	while (!vm->vis_quit && !vm->vis_pause)
		event_handler(vm);
	TTF_CloseFont(vm->font);
	TTF_Quit();
	SDL_DestroyRenderer(vm->renderer);
	SDL_DestroyWindow(vm->window);
	SDL_Quit();
}
