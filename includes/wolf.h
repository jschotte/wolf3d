/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:20:11 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/24 19:35:32 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <SDL.h>
# include "../libft/libft.h"

# define WIDTH 1000
# define HEIGHT 800
# define HEIGHTIMG 800
# define DEPTH 16
# define BPP 4
# define SIZECASE 64
# define SIZECASEMAP 200
# define POSMAPX 750
# define POSMAPY 75
# define TEXTWIDTH 64
# define TEXTHEIGHT 64

typedef struct	s_player
{
	double		x;
	double		y;
}				t_player;

typedef	struct	s_env
{
	SDL_Surface		*screen;
	int				quit;
	char			*img;
	int				full;
	int				lowcost;
	int				start;
	int				ismap;
	int				**map;
	char			*map_path;
	int				mapw;
	int				maph;
	int				is_texture;
	t_player		*player;
	SDL_Joystick	*joystick;
	SDL_Surface		**texture;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			movespeed;
	double			rotspeed;
	double			oldtime;
	double			time;
	double			frametime;
	double			camerax;
	double			rayposx;
	double			rayposy;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				texnum;
	double			wallx;
	int				texx;
	int				texy;
}				t_env;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

void			ft_load_map(t_env *env);
void			ft_free_map(t_env *env);

void			setpixel(SDL_Surface *screen, int x, int y, Uint32 color);
void			ft_draw_square(t_env *env, t_point *point, int l, Uint32 color);
Uint32			ft_create_color(t_env *env, Uint8 r, Uint8 g, Uint8 b);
void			ft_mid_up(t_env *env);
void			ft_mid_down(t_env *env);

void			ft_key(t_env *env, SDL_Event event);
void			ft_event(t_env *env);
void			ft_clear_win(t_env *env);

void			ft_joystick_axis(t_env *env, int axis, int value);
void			ft_joystick_axis2(t_env *env, SDL_Event event);
void			ft_joystick_button(t_env *env, SDL_Event event);
void			ft_turn_left(t_env *env);
void			ft_turn_right(t_env *env);
void			ft_left(t_env *env);
void			ft_right(t_env *env);
void			ft_up(t_env *env);
void			ft_down(t_env *env);

void			ft_print_map(t_env *env);
void			ft_print_player(t_env *env);

void			ft_calc_ray(t_env *env, int x);
void			ft_check_dir(t_env *env);
void			ft_find_wall(t_env *env);
void			ft_calc_h(t_env *env);
void			ft_print_wall(t_env *env, int x);

void			generate_texture(t_env *env);
void			check_joy(t_env *env);
void			ft_cal_fps(t_env *env);

void			ft_init_player(t_env *env);
void			ft_print_player(t_env *env);
void			ft_img(t_env *env);
void			ft_setcolor(t_env *env, int x, int y);
void			ft_line(t_env *env, int x, int val);

int				ft_exit(char *str);
#endif
