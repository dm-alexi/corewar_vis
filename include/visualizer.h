/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 14:10:35 by asmall            #+#    #+#             */
/*   Updated: 2020/06/21 12:58:23 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# if __APPLE__
#  include "SDL.h"
#  include "SDL_ttf.h"
# else
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_ttf.h>
# endif

# include "corewar.h"
# include "libft.h"

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 700
# define SCREEN_FPS 244
# define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS
# define INFORMATION_SIZE 350
# define WHITE (SDL_Color){255, 255, 255, 255}

SDL_Window		*g_main_window;
SDL_Renderer	*g_main_render;
TTF_Font		*g_font;

int				choose_color(int n);
int				choose_reverse_color(t_battlefield *cell);
void			init_visualizer(t_vm *vm);

void			push_to_render_battlefield(t_vm *vm);
void			push_info(t_vm *vm, char *status);
void			push_int_text(int data, char *info_text,
					float y, SDL_Color color);
void			push_int_slash_data(float y, int data_1,
					int data_2, char *text);
void			push_char_text(char *text, float y, SDL_Color color);
void			push_live_breakdown(t_vm *vm, int y);
void			push_pause(void);
void			push_distribution(t_battlefield *arena, float y);
void			push_players(t_vm *vm, int start_y);
void			push_winner_vis(t_vm *vm);
void			set_render_draw_color(int color);
void			set_sdl_color(SDL_Color *color, int i);
void			put_text_texture(float y, char *temp_2,
					char *temp_3, SDL_Texture *text_texture);
void			key_pause_quite(t_vm *vm);
void			visualizer_event(t_vm *vm);
void			live_players(t_vm *vm, SDL_FRect coor, int sum);

#endif
