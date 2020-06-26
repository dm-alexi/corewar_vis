/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:06:18 by asmall            #+#    #+#             */
/*   Updated: 2020/06/26 20:00:19 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

const int	g_colors[] = {0x00009b, 0x009b9b, 0x008000, 0x9b0000,
	0x800080, 0x9b9b00, 0xa9a9a9, 0x323232, 0x6f6f6f};

static void	draw_arena(t_vm *vm)
{
	SDL_Rect	cell;
	int			i;

	cell.w = (SCREEN_WIDTH - INFORMATION_SIZE) / ARENA_WIDTH - 1;
	cell.h = SCREEN_HEIGHT / ARENA_HEIGHT - 1;
	i = -1;
	while (++i < MEM_SIZE)
	{
		cell.y = i / ARENA_WIDTH * (cell.h + 1) + 1;
		cell.x = i % ARENA_WIDTH * (cell.w + 1) + 1;
		SDL_SetRenderDrawColor(g_main_render,
			(vm->arena[i].color & 0xff) + vm->arena[i].write_cycles,
			(vm->arena[i].color >> 8 & 0xff) + vm->arena[i].write_cycles,
			(vm->arena[i].color >> 16 & 0xff) + vm->arena[i].write_cycles, 255);
		SDL_RenderFillRect(g_main_render, &cell);
		SDL_SetRenderDrawColor(g_main_render, 255, 255, 255, 255);
		if (vm->arena[i].cursors)
			SDL_RenderDrawRect(g_main_render, &cell);
		if (!vm->vis_pause && vm->arena[i].write_cycles)
			vm->arena[i].write_cycles--;
	}
}

static void	draw_winner(t_vm *vm, int y)
{
	SDL_Color	color;
	char		*full_line;

	if (!(full_line =
	ft_strjoin(vm->players[vm->winner - 1].header.prog_name, " won!")))
		sys_error(NULL);
	color.r = g_colors[vm->winner - 1] & 0xff;
	color.g = g_colors[vm->winner - 1] >> 8 & 0xff;
	color.b = g_colors[vm->winner - 1] >> 16 & 0xff;
	draw_text(full_line, y, color);
	free(full_line);
}

void		visualize(t_vm *vm)
{
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	SDL_RenderClear(g_main_render);
	draw_arena(vm);
	if (vm->winner < 0)
		draw_text(vm->vis_pause ? "***Pause***" : "***Running***", 20, WHITE);
	else
		draw_winner(vm, 20);
	draw_data(vm->num_process, "Total processes: ", 40);
	draw_data(vm->cycle, "Current cycle: ", 60);
	draw_data(vm->cycles_to_die, "Cycles to die: ", 90);
	draw_data(CYCLE_DELTA, "Cycle delta: ", 110);
	draw_double_data(130, vm->live_calls, NBR_LIVE, "NBR_live: ");
	draw_double_data(150, vm->checks, MAX_CHECKS, "MAX_checks: ");
	draw_text("Live breakdown:", SCREEN_HEIGHT - 80, WHITE);
	push_live_breakdown(vm, SCREEN_HEIGHT - 60);
	draw_text("Arena distribution:", SCREEN_HEIGHT - 40, WHITE);
	push_distribution(vm->arena, SCREEN_HEIGHT - 20);
	push_players(vm, 180);
	SDL_RenderPresent(g_main_render);
}
