/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmodule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 17:49:33 by asmall            #+#    #+#             */
/*   Updated: 2020/06/17 22:26:14 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visualizer.h"

int		arena_players_module(t_vm *vm, unsigned i, int step, int byte)
{
	unsigned j;

	j = -1;
	vm->start = new_process_vm(vm->start, ++vm->num_process,
	vm->players[i].num - 1, i * step);
	vm->players[i].amount_cursors++;
	vm->arena[byte].cursor = 1;
	vm->start->reg[0] = -(i + 1);
	while (++j < vm->players[i].header.prog_size)
	{
		vm->arena[byte].code = vm->players[i].code[j];
		vm->arena[byte].write_cycles = 0;
		choose_color(&vm->arena[byte], i);
		byte++;
	}
	return (byte);
}

void	init_arena_module(t_vm *vm, int byte)
{
	vm->arena[byte].color_b = 111;
	vm->arena[byte].color_g = 111;
	vm->arena[byte].color_r = 111;
	vm->arena[byte].code = 0x0;
	vm->arena[byte].color = 'n';
	vm->arena[byte].write_cycles = 0;
}

void	battle_module(t_vm *vm)
{
	if (!vm->vis_quit)
		push_winner_vis(vm);
	TTF_CloseFont(g_font);
	TTF_Quit();
	SDL_DestroyRenderer(g_main_render);
	SDL_DestroyWindow(g_main_window);
	SDL_Quit();
}

void	run_pause_module(t_vm *vm, int flag)
{
	if (flag == 1)
	{
		push_to_render_battlefield(vm);
		push_info(vm, "***Running***");
		SDL_RenderPresent(g_main_render);
	}
	else
	{
		push_to_render_battlefield(vm);
		push_info(vm, "***Pause***");
		SDL_RenderPresent(g_main_render);
	}
}

void	exec_instr_module(t_process *cur, t_vm *vm)
{
	vm->arena[cur->pc].cursor = 0;
	cur->pc = cut(cur->pc + 1);
	vm->arena[cur->pc].cursor = 1;
}
