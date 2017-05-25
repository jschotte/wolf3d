/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:04:08 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/24 17:28:09 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	setpixel(SDL_Surface *screen, int x, int y, Uint32 color)
{
	Uint8	*pixmem32;
	int		bpp;

	bpp = screen->format->BytesPerPixel;
	pixmem32 = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;
	*(Uint16 *)pixmem32 = color;
}

void	ft_draw_square(t_env *env, t_point *point, int l, Uint32 color)
{
	int	x;
	int	y;

	y = point->y;
	while (y < point->y + l)
	{
		x = point->x;
		while (x < point->x + l)
		{
			setpixel(env->screen, x, y, color);
			x++;
		}
		y++;
	}
}

Uint32	ft_create_color(t_env *env, Uint8 r, Uint8 g, Uint8 b)
{
	Uint32 color;

	color = SDL_MapRGB(env->screen->format, r, g, b);
	return (color);
}

void	ft_mid_up(t_env *env)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHTIMG / 2)
	{
		x = 0;
		while (x < env->screen->w)
		{
			setpixel(env->screen, x, y, ft_create_color(env, 45, 47, 47));
			x++;
		}
		y++;
	}
}

void	ft_mid_down(t_env *env)
{
	int	x;
	int	y;

	y = HEIGHTIMG / 2;
	while (y < HEIGHTIMG)
	{
		x = 0;
		while (x < env->screen->w)
		{
			setpixel(env->screen, x, y, ft_create_color(env, 155, 157, 157));
			x++;
		}
		y++;
	}
}
