/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:04:32 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/23 23:04:33 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_down(t_env *env)
{
	if (env->start == 0)
	{
		if (env->lowcost == 0)
			env->img = "./img2/menu_2.bmp";
		else
			env->img = "./img/menu_2.bmp";
	}
	else
	{
		if (env->map[(int)(env->player->y - env->dirx * env->movespeed)]
			[(int)env->player->x] == 0)
			env->player->y -= env->dirx * env->movespeed;
		if (env->map[(int)env->player->y]
			[(int)(env->player->x - env->diry * env->movespeed)] == 0)
			env->player->x -= env->diry * env->movespeed;
	}
}

void	ft_up(t_env *env)
{
	if (env->start == 0)
	{
		if (env->lowcost == 0)
			env->img = "./img2/menu_1.bmp";
		else
			env->img = "./img/menu_1.bmp";
	}
	else
	{
		if (env->map[(int)(env->player->y + env->dirx * env->movespeed)]
			[(int)env->player->x] == 0)
			env->player->y += env->dirx * env->movespeed;
		if (env->map[(int)env->player->y]
			[(int)(env->player->x + env->diry * env->movespeed)] == 0)
			env->player->x += env->diry * env->movespeed;
	}
}

void	ft_left(t_env *env)
{
	if (env->start == 1)
	{
		if (env->map[(int)(env->player->y)]
			[(int)(env->player->x - env->planey * env->movespeed)] == 0)
			env->player->x -= env->planey * env->movespeed;
		if (env->map[(int)(env->player->y - env->planex * env->movespeed)]
			[(int)env->player->x] == 0)
			env->player->y -= env->planex * env->movespeed;
	}
}

void	ft_right(t_env *env)
{
	if (env->start == 1)
	{
		if (env->map[(int)(env->player->y)]
			[(int)(env->player->x + env->planey * env->movespeed)] == 0)
			env->player->x += env->planey * env->movespeed;
		if (env->map[(int)(env->player->y + env->planex * env->movespeed)]
			[(int)env->player->x] == 0)
			env->player->y += env->planex * env->movespeed;
	}
}
