/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:04:28 by asmall            #+#    #+#             */
/*   Updated: 2020/06/29 19:46:47 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	draw_arena(t_vm *vm)
{
	SDL_Rect	cell;
	int			i;

	cell.w = (SCREEN_WIDTH - MENU_WIDTH) / ARENA_WIDTH - 1;
	cell.h = SCREEN_HEIGHT / ARENA_HEIGHT - 1;
	i = -1;
	while (++i < MEM_SIZE)
	{
		cell.y = i / ARENA_WIDTH * (cell.h + 1) + 1;
		cell.x = i % ARENA_WIDTH * (cell.w + 1) + 1;
		SDL_SetRenderDrawColor(vm->renderer,
			(vm->arena[i].color & 0xff) + vm->arena[i].write_cycles,
			(vm->arena[i].color >> 8 & 0xff) + vm->arena[i].write_cycles,
			(vm->arena[i].color >> 16 & 0xff) + vm->arena[i].write_cycles, 255);
		SDL_RenderFillRect(vm->renderer, &cell);
		SDL_SetRenderDrawColor(vm->renderer, 255, 255, 255, 255);
		if (vm->arena[i].cursors)
			SDL_RenderDrawRect(vm->renderer, &cell);
		if (!vm->vis_pause && vm->arena[i].write_cycles)
			vm->arena[i].write_cycles--;
	}
}

void	draw_text(t_vm *vm, char *text, int y, SDL_Color color)
{
	SDL_Surface	*text_surface;
	SDL_Texture	*text_texture;
	SDL_Rect	coor;

	text_texture = NULL;
	coor.x = SCREEN_WIDTH - MENU_WIDTH + OFFSET;
	coor.y = y;
	TTF_SizeText(vm->font, text, &coor.w, &coor.h);
	if (!(text_surface = TTF_RenderText_Solid(vm->font, text, color)) ||
	!(text_texture = SDL_CreateTextureFromSurface(vm->renderer, text_surface)))
		error(SDL_GetError());
	SDL_RenderCopy(vm->renderer, text_texture, NULL, &coor);
	SDL_DestroyTexture(text_texture);
	SDL_FreeSurface(text_surface);
}

void	draw_process_bar(t_vm *vm, int y)
{
	int			i;
	double		sum;
	SDL_Rect	coor;

	coor.y = y;
	coor.x = SCREEN_WIDTH - MENU_WIDTH + OFFSET;
	coor.h = BAR_HEIGHT;
	sum = 0.0;
	i = vm->num_players;
	while (--i >= 0)
		sum += vm->players[i].num_cursors;
	if (sum == 0.0)
		return ;
	while (++i < vm->num_players - 1)
	{
		coor.w = vm->players[i].num_cursors * BAR_WIDTH / sum + 0.5;
		SDL_SetRenderDrawColor(vm->renderer, g_colors[i] & 0xff,
			g_colors[i] >> 8 & 0xff, g_colors[i] >> 16 & 0xff, 255);
		SDL_RenderFillRect(vm->renderer, &coor);
		coor.x += coor.w;
	}
	coor.w = SCREEN_WIDTH - MENU_WIDTH + OFFSET + BAR_WIDTH - coor.x;
	SDL_SetRenderDrawColor(vm->renderer, g_colors[i] & 0xff,
		g_colors[i] >> 8 & 0xff, g_colors[i] >> 16 & 0xff, 255);
	SDL_RenderFillRect(vm->renderer, &coor);
}

void	draw_live_bar(t_vm *vm, int y)
{
	int			i;
	double		sum;
	SDL_Rect	coor;

	coor.y = y;
	coor.x = SCREEN_WIDTH - MENU_WIDTH + OFFSET;
	coor.h = BAR_HEIGHT;
	sum = 0.0;
	i = vm->num_players;
	while (--i >= 0)
		sum += vm->players[i].lives_in_current_period;
	if (sum == 0.0)
		return ;
	while (++i < vm->num_players - 1)
	{
		coor.w = vm->players[i].lives_in_current_period * BAR_WIDTH / sum + 0.5;
		SDL_SetRenderDrawColor(vm->renderer, g_colors[i] & 0xff,
			g_colors[i] >> 8 & 0xff, g_colors[i] >> 16 & 0xff, 255);
		SDL_RenderFillRect(vm->renderer, &coor);
		coor.x += coor.w;
	}
	coor.w = SCREEN_WIDTH - MENU_WIDTH + OFFSET + BAR_WIDTH - coor.x;
	SDL_SetRenderDrawColor(vm->renderer, g_colors[i] & 0xff,
		g_colors[i] >> 8 & 0xff, g_colors[i] >> 16 & 0xff, 255);
	SDL_RenderFillRect(vm->renderer, &coor);
}
