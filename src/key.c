/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:04:32 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/24 19:24:29 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_keynext3(t_env *env, SDL_Event event)
{
	if (env->start == 1 && event.key.keysym.sym == SDLK_t)
	{
		if (env->is_texture == 1)
			env->is_texture = 0;
		else
			env->is_texture = 1;
	}
}

void	ft_keynext2(t_env *env, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_RETURN
		|| event.key.keysym.sym == SDLK_KP_ENTER)
	{
		if (env->start == 0)
		{
			if (ft_strstr(env->img, "menu_2.bmp") != 0)
				env->quit = 1;
			else
				env->start = 1;
		}
	}
	if (env->start == 1 && event.key.keysym.sym == SDLK_KP1)
	{
		ft_free_map(env);
		if (ft_strcmp(env->map_path, "./maps/map1") == 0)
			env->map_path = "./maps/map2";
		else if (ft_strcmp(env->map_path, "./maps/map2") == 0)
			env->map_path = "./maps/map3";
		else
			env->map_path = "./maps/map1";
		ft_load_map(env);
	}
	ft_keynext3(env, event);
}

void	ft_keynext(t_env *env, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_f)
	{
		if (env->full == 1)
		{
			env->screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE);
			env->full = 0;
		}
		else
		{
			env->screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH,
				SDL_FULLSCREEN | SDL_HWSURFACE);
			env->full = 1;
		}
	}
	if (event.key.keysym.sym == SDLK_m)
	{
		if (env->start == 1)
		{
			if (env->ismap == 1)
				env->ismap = 0;
			else
				env->ismap = 1;
		}
	}
	ft_keynext2(env, event);
}

void	ft_key(t_env *env, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_l)
	{
		if (env->lowcost == 0)
			env->lowcost = 1;
		else
			env->lowcost = 0;
	}
	if (event.key.keysym.sym == SDLK_s)
		ft_down(env);
	if (event.key.keysym.sym == SDLK_w)
		ft_up(env);
	if (event.key.keysym.sym == SDLK_a)
		if (env->start == 1)
			ft_left(env);
	if (event.key.keysym.sym == SDLK_d)
		if (env->start == 1)
			ft_right(env);
	if (event.key.keysym.sym == SDLK_RIGHT)
		ft_turn_right(env);
	if (event.key.keysym.sym == SDLK_LEFT)
		ft_turn_left(env);
	if (event.key.keysym.sym == SDLK_ESCAPE)
		env->quit = 1;
	ft_keynext(env, event);
}

void	ft_event(t_env *env)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			env->quit = 1;
		if (event.type == SDL_KEYDOWN)
			ft_key(env, event);
		if (event.type == SDL_JOYBUTTONDOWN)
			ft_joystick_button(env, event);
		if (event.type == SDL_JOYAXISMOTION)
			ft_joystick_axis2(env, event);
	}
}
