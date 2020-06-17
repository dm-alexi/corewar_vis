/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:06:18 by asmall            #+#    #+#             */
/*   Updated: 2020/06/17 22:32:42 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void			push_info(t_vm *vm, char *status)
{
	push_char_text(status, 20, WHITE);
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

int				arena_play(t_vm *vm, SDL_FRect cell, unsigned i,
					int lines_count)
{
	unsigned	j;

	while (++i < (float)MEM_SIZE / 64)
	{
		j = -1;
		while (++j < (float)MEM_SIZE / 64)
		{
			cell.x = cell.w * j;
			cell.y = cell.h * i;
			SDL_SetRenderDrawColor(g_main_render,
				vm->arena[i + j + lines_count].color_r +
					vm->arena[i + j + lines_count].write_cycles,
				vm->arena[i + j + lines_count].color_g +
					vm->arena[i + j + lines_count].write_cycles,
				vm->arena[i + j + lines_count].color_b +
					vm->arena[i + j + lines_count].write_cycles, 255);
			if (!vm->vis_pause && vm->arena[i + j +
				lines_count].write_cycles > 0)
				vm->arena[i + j + lines_count].write_cycles--;
			SDL_RenderFillRectF(g_main_render, &cell);
		}
		lines_count += j - 1;
	}
	return (j);
}

void			arena_play2(t_vm *vm, SDL_FRect cell)
{
	unsigned	i;
	unsigned	j;
	int			lines_count;

	i = -1;
	lines_count = 0;
	SDL_SetRenderDrawColor(g_main_render, 255, 255, 255, 255);
	while (++i < (float)MEM_SIZE / 64)
	{
		j = -1;
		while (++j < (float)MEM_SIZE / 64)
		{
			if (vm->arena[i + j + lines_count].cursor)
			{
				cell.x = cell.w * j;
				cell.y = cell.h * i;
				SDL_RenderDrawRectF(g_main_render, &cell);
			}
		}
		lines_count += j - 1;
	}
}

void			push_to_render_battlefield(t_vm *vm)
{
	unsigned	i;
	SDL_FRect	cell;

	cell.w = (float)(SCREEN_WIDTH - INFORMATION_SIZE) / 64;
	cell.h = (float)SCREEN_HEIGHT / 64;
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	SDL_RenderClear(g_main_render);
	arena_play(vm, cell, -1, 0);
	i = -1;
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	while (++i < (float)MEM_SIZE / 64)
	{
		SDL_RenderDrawLineF(g_main_render, cell.w * i, 0,
			cell.w * i, SCREEN_HEIGHT);
		SDL_RenderDrawLineF(g_main_render, 0, cell.h * i,
			SCREEN_WIDTH - INFORMATION_SIZE, cell.h * i);
	}
	arena_play2(vm, cell);
}

void			push_pause(void)
{
	SDL_Rect	pause;

	pause.h = 20;
	pause.w = 300;
	pause.y = 20;
	pause.x = SCREEN_WIDTH - INFORMATION_SIZE + 50;
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	SDL_RenderFillRect(g_main_render, &pause);
	push_char_text("**Pause**", 20, WHITE);
	SDL_RenderPresent(g_main_render);
}
