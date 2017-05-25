/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:16:20 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/24 19:25:33 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_line(t_env *env, int x, int value)
{
	Uint32 color;

	if (value == 1)
		color = SDL_MapRGB(env->screen->format, 0, 0, 255);
	else if (value == 2)
		color = SDL_MapRGB(env->screen->format, 0, 255, 0);
	else if (value == 3)
		color = SDL_MapRGB(env->screen->format, 255, 0, 0);
	else if (value == 4)
		color = SDL_MapRGB(env->screen->format, 0, 255, 255);
	else if (value == 5)
		color = SDL_MapRGB(env->screen->format, 255, 255, 0);
	else if (value == 6)
		color = SDL_MapRGB(env->screen->format, 255, 0, 255);
	else
		color = SDL_MapRGB(env->screen->format, 150, 64, 200);
	if (env->side == 1)
		color = color / 2;
	while (env->drawstart < env->drawend)
	{
		setpixel(env->screen, x, env->drawstart, color);
		env->drawstart++;
	}
}

void	ft_setcolor(t_env *env, int x, int y)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	Uint32	color;
	Uint32	*pixels;

	pixels = (Uint32 *)env->texture[env->texnum]->pixels;
	SDL_GetRGB(pixels[64 * env->texy + env->texx],
			env->texture[env->texnum]->format, &r, &g, &b);
	color = SDL_MapRGB(env->screen->format, r, g, b);
	setpixel(env->screen, x, y, color);
}

void	generate_texture(t_env *env)
{
	SDL_Surface **texture;

	if ((texture = malloc(sizeof(SDL_Surface) * 8)) == NULL)
		ft_exit("Malloc Errorn\n");
	texture[0] = SDL_LoadBMP("./textures/bluestone.bmp");
	texture[1] = SDL_LoadBMP("./textures/eagle.bmp");
	texture[2] = SDL_LoadBMP("./textures/redbrick.bmp");
	texture[3] = SDL_LoadBMP("./textures/wood.bmp");
	texture[4] = SDL_LoadBMP("./textures/mossy.bmp");
	texture[5] = SDL_LoadBMP("./textures/colorstone.bmp");
	texture[6] = SDL_LoadBMP("./textures/purplestone.bmp");
	texture[7] = SDL_LoadBMP("./textures/greystone.bmp");
	env->texture = texture;
}

void	check_joy(t_env *env)
{
	ft_mid_up(env);
	ft_mid_down(env);
	if (env->joystick != NULL)
	{
		if (SDL_JoystickGetButton(env->joystick, 4) == 1)
			ft_turn_left(env);
		if (SDL_JoystickGetButton(env->joystick, 5) == 1)
			ft_turn_right(env);
		ft_joystick_axis(env, 3, SDL_JoystickGetAxis(env->joystick, 3));
		ft_joystick_axis(env, 4, SDL_JoystickGetAxis(env->joystick, 4));
	}
}

void	ft_cal_fps(t_env *env)
{
	env->oldtime = env->time;
	env->time = SDL_GetTicks();
	env->frametime = (env->time - env->oldtime) / 1000.0;
	env->movespeed = env->frametime * 5.0;
	env->rotspeed = env->frametime * 3.0;
}
