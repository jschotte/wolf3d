/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:16:20 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/24 19:24:33 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	return (EXIT_FAILURE);
}

void	ft_start(t_env *env)
{
	int			x;

	ft_init_player(env);
	ft_load_map(env);
	while (env->quit == 0)
	{
		check_joy(env);
		x = 0;
		while (x < WIDTH)
		{
			ft_calc_ray(env, x);
			ft_check_dir(env);
			ft_find_wall(env);
			ft_calc_h(env);
			ft_print_wall(env, x);
			x++;
		}
		ft_cal_fps(env);
		if (env->ismap == 1)
			ft_print_map(env);
		if (SDL_MUSTLOCK(env->screen))
			SDL_UnlockSurface(env->screen);
		SDL_Flip(env->screen);
		ft_event(env);
	}
}

void	ft_menu(t_env *env)
{
	while (env->quit == 0 && env->start == 0)
	{
		ft_img(env);
		ft_event(env);
	}
	if (env->start != 0)
		ft_start(env);
}

t_env	*init_env(SDL_Surface *screen)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	if (tmp == NULL)
		ft_exit("Malloc Error\n");
	tmp->screen = screen;
	tmp->quit = 0;
	tmp->img = "./img2/menu_1.bmp";
	tmp->full = 0;
	tmp->lowcost = 0;
	tmp->start = 0;
	tmp->ismap = 1;
	tmp->map_path = "./maps/map1";
	tmp->map = NULL;
	tmp->player = NULL;
	tmp->dirx = -1;
	tmp->diry = 0;
	tmp->planex = 0;
	tmp->planey = 0.66;
	tmp->time = 0;
	tmp->oldtime = 0;
	tmp->frametime = 0;
	tmp->is_texture = 1;
	generate_texture(tmp);
	return (tmp);
}

int		main(int argc, char **argv)
{
	SDL_Surface		*screen;
	t_env			*env;
	SDL_Joystick	*joystick;

	(void)argc;
	(void)argv;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
		return (ft_exit("SDL can't init !\n"));
	if ((screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE)) < 0)
	{
		SDL_Quit();
		return (ft_exit("SDL can't open \n"));
	}
	joystick = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);
	SDL_EnableKeyRepeat(10, 10);
	SDL_WM_SetCaption("WOFL3D", NULL);
	env = init_env(screen);
	env->joystick = joystick;
	ft_menu(env);
	SDL_Quit();
	return (0);
}
