/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:06:18 by asmall            #+#    #+#             */
/*   Updated: 2020/06/22 01:27:50 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void			push_info(t_vm *vm)
{
	push_char_text(vm->vis_pause ? "***Pause***" : "***Running***", 20, WHITE);
	push_int_text(vm->num_process, "Total processes: ", 40, WHITE);
	push_int_text(vm->cycle, "Current cycle: ", 60, WHITE);
	push_int_text(vm->cycles_to_die, "Cycle to die: ", 90, WHITE);
	push_int_text(CYCLE_DELTA, "Cycle delta: ", 110, WHITE);
	push_int_slash_data(130, vm->live_calls, NBR_LIVE, "NBR_live: ");
	push_int_slash_data(150, vm->checks, MAX_CHECKS, "MAX_checks: ");
	push_char_text("Live breakdown for now:", SCREEN_HEIGHT - 80, WHITE);
	push_live_breakdown(vm, SCREEN_HEIGHT - 60);
	push_char_text("Arena distribution: ", SCREEN_HEIGHT - 40, WHITE);
	push_distribution(vm->arena, SCREEN_HEIGHT - 20);
	push_players(vm, 180);
}

int				arena_play(t_vm *vm, SDL_Rect cell, unsigned i,
					int lines_count)
{
	unsigned	j;

	while (++i < MEM_SIZE / 64)
	{
		j = -1;
		while (++j < MEM_SIZE / 64)
		{
			cell.x = cell.w * j;
			cell.y = cell.h * i;
			SDL_SetRenderDrawColor(g_main_render,
				(vm->arena[i + j + lines_count].color & 0xff) +
					vm->arena[i + j + lines_count].write_cycles,
				(vm->arena[i + j + lines_count].color >> 8 & 0xff) +
					vm->arena[i + j + lines_count].write_cycles,
				(vm->arena[i + j + lines_count].color >> 16 & 0xff) +
					vm->arena[i + j + lines_count].write_cycles, 255);
			if (!vm->vis_pause && vm->arena[i + j + lines_count].write_cycles)
				vm->arena[i + j + lines_count].write_cycles--;
			SDL_RenderFillRect(g_main_render, &cell);
		}
		lines_count += j - 1;
	}
	return (j);
}

void			arena_play2(t_vm *vm, SDL_Rect cell)
{
	unsigned	i;
	unsigned	j;
	int			lines_count;

	i = -1;
	lines_count = 0;
	SDL_SetRenderDrawColor(g_main_render, 255, 255, 255, 255);
	while (++i < MEM_SIZE / 64)
	{
		j = -1;
		while (++j < MEM_SIZE / 64)
		{
			if (vm->arena[i + j + lines_count].cursors)
			{
				cell.x = cell.w * j;
				cell.y = cell.h * i;
				SDL_RenderDrawRect(g_main_render, &cell);
			}
		}
		lines_count += j - 1;
	}
}

void			push_to_render_battlefield(t_vm *vm)
{
	int			i;
	SDL_Rect	cell;

	cell.w = (SCREEN_WIDTH - INFORMATION_SIZE) / ARENA_WIDTH;
	cell.h = SCREEN_HEIGHT / ARENA_HEIGHT;
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	SDL_RenderClear(g_main_render);
	arena_play(vm, cell, -1, 0);
	i = -1;
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	while (++i < MEM_SIZE / 64)
	{
		SDL_RenderDrawLine(g_main_render, cell.w * i, 0,
			cell.w * i, SCREEN_HEIGHT);
		SDL_RenderDrawLine(g_main_render, 0, cell.h * i,
			SCREEN_WIDTH - INFORMATION_SIZE, cell.h * i);
	}
	arena_play2(vm, cell);
}
