/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:04:32 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/23 23:04:33 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_turn_right(t_env *env)
{
	double old_dirx;
	double old_planex;

	if (env->start == 1)
	{
		old_dirx = env->dirx;
		env->dirx = env->dirx * cos(-1 * env->rotspeed)
		- env->diry * sin(-1 * env->rotspeed);
		env->diry = old_dirx * sin(-1 * env->rotspeed)
		+ env->diry * cos(-1 * env->rotspeed);
		old_planex = env->planex;
		env->planex = env->planex * cos(-1 * env->rotspeed)
		- env->planey * sin(-1 * env->rotspeed);
		env->planey = old_planex * sin(-1 * env->rotspeed)
		+ env->planey * cos(-1 * env->rotspeed);
	}
}

void	ft_turn_left(t_env *env)
{
	double old_dirx;
	double old_planex;

	if (env->start == 1)
	{
		old_dirx = env->dirx;
		env->dirx = env->dirx * cos(env->rotspeed)
		- env->diry * sin(env->rotspeed);
		env->diry = old_dirx * sin(env->rotspeed)
		+ env->diry * cos(env->rotspeed);
		old_planex = env->planex;
		env->planex = env->planex * cos(env->rotspeed)
		- env->planey * sin(env->rotspeed);
		env->planey = old_planex * sin(env->rotspeed)
		+ env->planey * cos(env->rotspeed);
	}
}
