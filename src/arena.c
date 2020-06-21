/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:22:33 by sscarecr          #+#    #+#             */
/*   Updated: 2020/06/22 01:04:24 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** All arena read and write operations.
** NB: Arena is big-endian!
*/

#include "corewar.h"
#include "visualizer.h"

static t_process	*new_process(t_process *next, unsigned num,
					unsigned player_num, int pc)
{
	t_process	*p;

	if (!(p = (t_process*)ft_memalloc(sizeof(t_process))))
		sys_error(NULL);
	p->next = next;
	p->player_num = player_num;
	p->color = choose_color(player_num);
	p->num = num;
	p->pc = pc;
	return (p);
}

/*
** Place champions' code in the arena and create initial processes.
*/

void				init_arena(t_vm *vm)
{
	unsigned	i;
	unsigned	j;
	int			step;

	step = MEM_SIZE / vm->num_players;
	i = 0;
	while (i < MEM_SIZE)
		vm->arena[i++].color = 0x6f6f6f;
	i = 0;
	while (i < vm->num_players)
	{
		j = 0;
		vm->start = new_process(vm->start, ++vm->num_process,
			vm->players[i].num - 1, i * step);
		vm->players[i].num_cursors++;
		vm->arena[i * step].cursors = 1;
		vm->start->reg[0] = -(i + 1);
		while (j < vm->players[i].header.prog_size)
		{
			vm->arena[i * step + j].code = vm->players[i].code[j];
			vm->arena[i * step + j].color = choose_color(i);
			++j;
		}
		free(vm->players[i++].code);
	}
}

/*
** Read an argument of T_DIR type.
*/

int					read_dir(int start, t_battlefield *arena)
{
	char		s[DIR_SIZE];
	int			i;

	start = cut(start);
	i = -1;
	while (++i < DIR_SIZE)
		s[DIR_SIZE - 1 - i] = arena[(start + i) % MEM_SIZE].code;
	return (*((int*)s));
}

/*
** Read an argument of T_IND type.
*/

int					read_ind(int start, t_battlefield *arena)
{
	char		s[IND_SIZE];
	int			i;

	start = cut(start);
	i = -1;
	while (++i < IND_SIZE)
		s[IND_SIZE - 1 - i] = arena[(start + i) % MEM_SIZE].code;
	return (*((short*)s));
}

/*
** Write an argument to the arena.
*/

void				write_bytes(int n, int start, t_battlefield *arena,
						int color)
{
	t_byte		*s;
	int			i;

	start = cut(start);
	s = (t_byte*)&n;
	i = -1;
	while (++i < REG_SIZE)
	{
		arena[(start + i) % MEM_SIZE].code = s[REG_SIZE - 1 - i];
		arena[(start + i) % MEM_SIZE].color = color;
		arena[(start + i) % MEM_SIZE].write_cycles = 100;
	}
}
