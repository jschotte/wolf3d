/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:16:20 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/24 18:39:16 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_calc_ray(t_env *env, int x)
{
	env->camerax = 2 * x / (float)WIDTH - 1;
	env->rayposy = env->player->x;
	env->rayposx = env->player->y;
	env->raydirx = env->dirx + env->planex * env->camerax;
	env->raydiry = env->diry + env->planey * env->camerax;
	env->mapx = (int)env->rayposx;
	env->mapy = (int)env->rayposy;
	env->deltadistx = sqrt(1 + (env->raydiry * env->raydiry)
			/ (env->raydirx * env->raydirx));
	env->deltadisty = sqrt(1 + (env->raydirx * env->raydirx)
			/ (env->raydiry * env->raydiry));
}

void	ft_check_dir(t_env *env)
{
	env->hit = 0;
	if (env->raydirx < 0)
	{
		env->stepx = -1;
		env->sidedistx = (env->rayposx - env->mapx) * env->deltadistx;
	}
	else
	{
		env->stepx = 1;
		env->sidedistx = (env->mapx + 1.0 - env->rayposx) * env->deltadistx;
	}
	if (env->raydiry < 0)
	{
		env->stepy = -1;
		env->sidedisty = (env->rayposy - env->mapy) * env->deltadisty;
	}
	else
	{
		env->stepy = 1;
		env->sidedisty = (env->mapy + 1.0 - env->rayposy) * env->deltadisty;
	}
}

void	ft_find_wall(t_env *env)
{
	while (env->hit == 0)
	{
		if (env->sidedistx < env->sidedisty)
		{
			env->sidedistx += env->deltadistx;
			env->mapx += env->stepx;
			env->side = 0;
		}
		else
		{
			env->sidedisty += env->deltadisty;
			env->mapy += env->stepy;
			env->side = 1;
		}
		if (env->map[env->mapx][env->mapy] > 0)
			env->hit = 1;
	}
	if (env->side == 0)
		env->perpwalldist = (env->mapx - env->rayposx + (1 - env->stepx)
				/ 2) / env->raydirx;
	else
		env->perpwalldist = (env->mapy - env->rayposy + (1 - env->stepy)
				/ 2) / env->raydiry;
}

void	ft_calc_h(t_env *env)
{
	env->lineheight = (int)(HEIGHT / env->perpwalldist);
	env->drawstart = -env->lineheight / 2 + HEIGHT / 2;
	if (env->drawstart < 0)
		env->drawstart = 0;
	env->drawend = env->lineheight / 2 + HEIGHT / 2;
	if (env->drawend >= HEIGHT)
		env->drawend = HEIGHT - 1;
	env->texnum = env->map[env->mapx][env->mapy] - 1;
	if (env->side == 0)
		env->wallx = env->rayposy + env->perpwalldist * env->raydiry;
	else
		env->wallx = env->rayposx + env->perpwalldist * env->raydirx;
	env->wallx -= floor((env->wallx));
	env->texx = (int)(env->wallx * (double)TEXTWIDTH);
	if (env->side == 1 && env->raydiry < 0)
		env->texx = TEXTWIDTH - env->texx - 1;
	if (env->side == 0 && env->raydirx > 0)
		env->texx = TEXTWIDTH - env->texx - 1;
}

void	ft_print_wall(t_env *env, int x)
{
	int		y;
	int		d;

	y = env->drawstart;
	if (env->is_texture == 1)
	{
		while (y < env->drawend)
		{
			d = y * 256 - HEIGHT * 128 + env->lineheight * 128;
			env->texy = ((d * 64) / env->lineheight) / (256);
			ft_setcolor(env, x, y);
			y++;
		}
	}
	else
		ft_line(env, x, env->map[env->mapx][env->mapy]);
}
