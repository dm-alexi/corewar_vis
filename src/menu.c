/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:05:44 by asmall            #+#    #+#             */
/*   Updated: 2020/06/29 23:39:00 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

static void		draw_data(t_vm *vm, int data, char *info_text, int y)
{
	static const SDL_Color	white = (SDL_Color){255, 255, 255, 255};
	char					*number;
	char					*full_line;

	full_line = NULL;
	if (!(number = ft_itoa(data)) ||
	!(full_line = ft_strjoin(info_text, number)))
		sys_error(NULL);
	free(number);
	draw_text(vm, full_line, y, white);
	free(full_line);
}

static char		*join_data(char *text, int data_1, int data_2)
{
	char	*tmp1;
	char	*tmp2;
	char	*full_line;

	tmp2 = NULL;
	full_line = NULL;
	if (!(tmp1 = ft_itoa(data_1)) ||
	!(tmp2 = ft_itoa(data_2)) ||
	!(full_line = (char*)ft_memalloc(ft_strlen(text)
	+ ft_strlen(tmp1) + ft_strlen(tmp2) + 2)))
		sys_error(NULL);
	ft_strcat(full_line, text);
	ft_strcat(full_line, tmp1);
	full_line[ft_strlen(full_line)] = '/';
	ft_strcat(full_line, tmp2);
	free(tmp1);
	free(tmp2);
	return (full_line);
}

static void		draw_players(t_vm *vm, int pos)
{
	int			i;
	SDL_Color	color;

	i = 0;
	while (i < vm->num_players)
	{
		draw_data(vm, i + 1, "Player # ", pos);
		color.r = g_colors[i] & 0xff;
		color.g = g_colors[i] >> 8 & 0xff;
		color.b = g_colors[i] >> 16 & 0xff;
		color.a = 255;
		draw_text(vm, vm->players[i].header.prog_name, pos + 20, color);
		draw_data(vm, vm->players[i].last_alive, "Last alive: ", pos + 40);
		draw_data(vm, vm->players[i].lives_in_current_period,
			"Lives in current period : ", pos + 60);
		draw_data(vm, vm->players[i].num_cursors,
			"Number of processes: ", pos + 80);
		pos += 110;
		++i;
	}
}

static void		draw_winner(t_vm *vm, int y)
{
	SDL_Color	color;
	char		*full_line;

	if (!(full_line =
	ft_strjoin(vm->players[vm->winner - 1].header.prog_name, " won!")))
		sys_error(NULL);
	color.r = g_colors[vm->winner - 1] & 0xff;
	color.g = g_colors[vm->winner - 1] >> 8 & 0xff;
	color.b = g_colors[vm->winner - 1] >> 16 & 0xff;
	color.a = 255;
	draw_text(vm, full_line, y, color);
	free(full_line);
}

void			draw_menu(t_vm *vm)
{
	static const SDL_Color	white = (SDL_Color){255, 255, 255, 255};
	char					*line;

	if (vm->winner < 0)
		draw_text(vm, vm->vis_pause ? "***Pause***" : "***Running***",
			20, white);
	else
		draw_winner(vm, 20);
	draw_data(vm, vm->num_process, "Total processes: ", 40);
	draw_data(vm, vm->cycle, "Current cycle: ", 60);
	draw_data(vm, vm->cycles_to_die, "Cycles to die: ", 90);
	draw_data(vm, CYCLE_DELTA, "Cycle delta: ", 110);
	draw_text(vm, (line = join_data("NBR_live: ", vm->live_calls, NBR_LIVE)),
		130, white);
	free(line);
	draw_text(vm, (line = join_data("MAX_checks: ", vm->checks, MAX_CHECKS)),
		150, white);
	free(line);
	draw_players(vm, 180);
	draw_text(vm, "Live breakdown:", SCREEN_HEIGHT - 80, white);
	draw_live_bar(vm, SCREEN_HEIGHT - 60);
	draw_text(vm, "Process breakdown:", SCREEN_HEIGHT - 40, white);
	draw_process_bar(vm, SCREEN_HEIGHT - 20);
}
