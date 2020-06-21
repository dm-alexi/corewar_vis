/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmodule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 17:49:33 by asmall            #+#    #+#             */
/*   Updated: 2020/06/21 21:51:42 by sscarecr         ###   ########.fr       */
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

void	run_module(t_vm *vm)
{
	push_to_render_battlefield(vm);
	push_info(vm);
	SDL_RenderPresent(g_main_render);
}
