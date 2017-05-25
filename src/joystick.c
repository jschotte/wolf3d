/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joystick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:04:32 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/24 18:27:31 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_clear_win(t_env *env)
{
	int x;
	int	y;

	if (SDL_MUSTLOCK(env->screen))
		if (SDL_LockSurface(env->screen) < 0)
			return ;
	y = 0;
	while (y < env->screen->h)
	{
		x = 0;
		while (x < env->screen->w)
		{
			setpixel(env->screen, x, y, ft_create_color(env, 0, 0, 0));
			x++;
		}
		y++;
	}
	if (SDL_MUSTLOCK(env->screen))
		SDL_UnlockSurface(env->screen);
}

void	ft_joystick_axis(t_env *env, int axis, int value)
{
	if (value == -129)
		return ;
	if (axis == 3)
	{
		if (value < 0)
			ft_left(env);
		else
			ft_right(env);
	}
	else
	{
		if (value < 0)
			ft_up(env);
		else
			ft_down(env);
	}
}

void	ft_joystick_axis2(t_env *env, SDL_Event event)
{
	int axis;
	int value;

	axis = event.jaxis.axis;
	value = event.jaxis.value;
	if (value == -129)
		return ;
	if (axis == 3)
	{
		if (value < 0)
			ft_left(env);
		else
			ft_right(env);
	}
	else
	{
		if (value < 0)
			ft_up(env);
		else
			ft_down(env);
	}
}

void	ft_joystick_button(t_env *env, SDL_Event event)
{
	if (event.jbutton.button == 1)
	{
		if (env->start == 0)
		{
			if (ft_strstr(env->img, "menu_2.bmp") != 0)
				env->quit = 1;
			else
			{
				env->start = 1;
				env->img = "";
				ft_clear_win(env);
			}
		}
	}
}
