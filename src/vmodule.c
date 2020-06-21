/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmodule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 17:49:33 by asmall            #+#    #+#             */
/*   Updated: 2020/06/21 11:53:33 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visualizer.h"

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
