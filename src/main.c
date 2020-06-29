/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:29:39 by sscarecr          #+#    #+#             */
/*   Updated: 2020/06/29 23:32:36 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int	main(int ac, char **av)
{
	t_vm	vm;

	check_invariants();
	ft_bzero(&vm, sizeof(t_vm));
	input(&vm, ac, av);
	vm.cycles_to_die = CYCLE_TO_DIE;
	vm.next_check = vm.cycles_to_die;
	vm.last_alive = vm.num_players;
	vm.winner = -1;
	init_arena(&vm);
	introduce(&vm);
	battle(&vm);
	declare_winner(&vm);
	delete_vm(&vm);
	return (0);
}
