/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:20:11 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/18 21:53:36 by jschotte         ###   ########.fr       */
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
# define SIZECASEMAP 100

# define POSMAPX 850
# define POSMAPY 75

typedef struct	s_player
{
	double		x;
	double		y;
	float		angle;
}				t_player;

typedef	struct	s_env
{
	SDL_Surface	*screen;
	int			quit;
	char		*img;
	int 		full;
	int			lowcost;
	int			start;
	int			ismap;
	int			**map;
	char		*map_path;
	int			mapw;
	int			maph;
	t_player	*player;


	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double moveSpeed;
	double rotSpeed;
}				t_env;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

void	ft_load_map(t_env *env);
void	ft_free_map(t_env *env);

void 	setpixel(SDL_Surface *screen, int x, int y, Uint32 color);
void 	ft_draw_square(t_env *env, t_point *point, int l, Uint32 color);
Uint32	ft_create_color(t_env *env, Uint8 r, Uint8 g, Uint8 b);
void	ft_mid_up(t_env *env);
void	ft_mid_down(t_env *env);

void	ft_key(t_env *env, SDL_Event event);
void	ft_event(t_env *env);
void	ft_clear_win(t_env *env);

#endif
