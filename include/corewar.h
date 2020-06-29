/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:28:58 by sscarecr          #+#    #+#             */
/*   Updated: 2020/06/29 23:27:29 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "op.h"

# if __APPLE__
#  include "SDL.h"
#  include "SDL_ttf.h"
# else
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_ttf.h>
# endif

/*
** In COPYCAT mode all the 'general' messages from zaz's Corewar are reproduced.
** NB: it doesn't comply with the subject!
*/

# define COPYCAT		0

# define OP_NUM			16
# define SHORT_DUMP		32
# define LONG_DUMP		64

/*
** Verbosity level constants
*/

# define LIVES			1
# define CYCLES			2
# define OPERATIONS		4
# define DEATHS			8
# define MOVES			16

/*
** Visualizations screen parameters must be adjusted manually if MEM_SIZE value
** is to be changed.
** Arena width and height are in cells.
*/

# define SCREEN_WIDTH	1311
# define SCREEN_HEIGHT	705
# define MENU_WIDTH		350
# define OFFSET			25
# define ARENA_WIDTH	64
# define ARENA_HEIGHT	64
# define BAR_WIDTH		300
# define BAR_HEIGHT		15

# define GREY			0x6f6f6f
# define RED			0x00009b
# define YELLOW			0x009b9b
# define GREEN			0x008000
# define BLUE			0x9b0000

typedef unsigned char	t_byte;

typedef struct	s_player
{
	t_header	header;
	t_byte		*code;
	int			num;
	int			last_alive;
	int			lives_in_current_period;
	int			num_cursors;
}				t_player;

typedef struct	s_process
{
	int					num;
	int					last_live;
	t_byte				carry;
	t_byte				op;
	int					pc;
	int					reg[REG_NUMBER];
	struct s_process	*next;
	int					player_num;
	int					exec_cycle;
	int					color;
}				t_process;

typedef struct	s_battlefield
{
	t_byte	code;
	int		color;
	int		write_cycles;
	int		cursors;
}				t_battlefield;

typedef struct	s_vm
{
	t_battlefield	arena[MEM_SIZE];
	int				num_players;
	t_player		*players;
	int				num_process;
	t_process		*start;
	int				cycle;
	int				cycles_to_die;
	int				checks;
	int				next_check;
	int				live_calls;
	int				last_alive;
	int				dump_cycle;
	int				dump_len;
	int				verbosity;
	int				winner;
	t_byte			visual;
	t_byte			vis_quit;
	t_byte			vis_pause;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
}				t_vm;

typedef struct	s_op
{
	void	(*func)(t_process*, t_vm*, t_byte *argtypes, int* args);
	t_byte	typebyte;
	int		argnum;
	char	args[3];
	int		dirsize;
	int		lag;
}				t_op;

extern const t_op	g_tab[];
extern const int	g_colors[];

void			sys_error(const char *s);
void			error(const char *s);
void			error2(const char *s, const char *t);
void			usage(void);
void			check_invariants(void);

void			input(t_vm *vm, int ac, char **av);
void			get_players(t_vm *vm, char **files);

void			introduce(t_vm *vm);
void			declare_winner(t_vm *vm);
void			print_movement(t_battlefield *arena, int pc, int n);
int				dump(t_vm *vm);

int				cut(int n);
void			init_arena(t_vm *vm);
int				read_dir(int start, t_battlefield *arena);
int				read_ind(int start, t_battlefield *arena);
void			write_bytes(int n, int start, t_battlefield *arena,
						int color);
void			battle(t_vm *vm);
void			read_instr(t_process *cur, t_vm *vm);
void			exec_instr(t_process *cur, t_vm *vm);
void			delete_vm(t_vm *vm);

void			live(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			ld(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			st(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			add(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			sub(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			and(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			or(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			xor(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			zjmp(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			ldi(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			sti(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			sfork(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			lld(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			lldi(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			lfork(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			aff(t_process *t, t_vm *vm, t_byte *argtypes, int *args);

void			init_visualizer(t_vm *vm);
void			visualize(t_vm *vm);
void			event_handler(t_vm *vm);
void			finish_visualization(t_vm *vm);
void			draw_arena(t_vm *vm);
void			draw_menu(t_vm *vm);
void			draw_text(t_vm *vm, char *text, int y, SDL_Color color);
void			draw_live_bar(t_vm *vm, int y);
void			draw_process_bar(t_vm *vm, int y);

#endif
