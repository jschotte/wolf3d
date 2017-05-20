#include "../includes/wolf.h"

void	ft_clear_win(t_env *env)
{
	int x, y;

	if(SDL_MUSTLOCK(env->screen)) 
		if(SDL_LockSurface(env->screen) < 0)
			return;
	for(y = 0; y < env->screen->h; y++ ) 
	{
		for( x = 0; x < env->screen->w; x++ ) 
		{
			setpixel(env->screen, x, y, ft_create_color(env, 255, 255, 255));
		}
	}
	if(SDL_MUSTLOCK(env->screen))
		SDL_UnlockSurface(env->screen);
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
	if (event.key.keysym.sym == SDLK_DOWN)
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
			if(env->map[(int)(env->player->x - env->dirX * env->moveSpeed)][(int)env->player->y] == 0)
				env->player->x -= env->dirX * env->moveSpeed;
			if(env->map[(int)env->player->x][(int)(env->player->y - env->dirY * env->moveSpeed)] == 0)
				env->player->y -= env->dirY * env->moveSpeed;
		}
	}
	if (event.key.keysym.sym == SDLK_UP)
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
			if(env->map[(int)(env->player->x + env->dirX * env->moveSpeed)][(int)env->player->y] == 0)
				env->player->x += env->dirX * env->moveSpeed;
			if(env->map[(int)env->player->x][(int)(env->player->y + env->dirY * env->moveSpeed)] == 0)
				env->player->y += env->dirY * env->moveSpeed;

		}

	}
	if (event.key.keysym.sym == SDLK_LEFT)
	{
		if (env->start == 1)
		{
			double oldDirX = env->dirX;
			env->dirX = env->dirX * cos(-1*env->rotSpeed) - env->dirY * sin(-1*env->rotSpeed);
			env->dirY = oldDirX * sin(-1*env->rotSpeed) + env->dirY * cos(-1*env->rotSpeed);
			double oldPlaneX = env->planeX;
			env->planeX = env->planeX * cos(-1*env->rotSpeed) - env->planeY * sin(-1*env->rotSpeed);
			env->planeY = oldPlaneX * sin(-1*env->rotSpeed) + env->planeY * cos(-1*env->rotSpeed);
		}
	}
	if (event.key.keysym.sym == SDLK_RIGHT)
	{
		if (env->start == 1)
		{
			double oldDirX = env->dirX;
			env->dirX = env->dirX * cos(env->rotSpeed) - env->dirY * sin(env->rotSpeed);
			env->dirY = oldDirX * sin(env->rotSpeed) + env->dirY * cos(env->rotSpeed);
			double oldPlaneX = env->planeX;
			env->planeX = env->planeX * cos(env->rotSpeed) - env->planeY * sin(env->rotSpeed);
			env->planeY = oldPlaneX * sin(env->rotSpeed) + env->planeY * cos(env->rotSpeed);
		}
	}	
	if (event.key.keysym.sym == SDLK_ESCAPE)
		env->quit = 1;
	if (event.key.keysym.sym == SDLK_f)
	{
		if (env->full == 1)
		{
			env->screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE);
			env->full = 0;
		}
		else
		{
			env->screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_FULLSCREEN|SDL_HWSURFACE);
			env->full = 1;
		}
	}
	if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER)
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
}

void	ft_joystick_button(t_env *env, SDL_Event event)
{
	switch(event.jbutton.button)
	{
		case 0 : // appui sur bouton 0
			printf("X\n");
			break;
		case 1 :		// A
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
			break;
		case 2 : // appui sur bouton 0
			printf("B\n");
			break;
		case 3 : // appui sur bouton 0
			printf("Y\n");
			break;
		case 4 : // appui sur bouton 0
			printf("L\n");
			break;
		case 5 : // appui sur bouton 0
			printf("R\n");
			break;
		case 7 : // appui sur bouton 0
			printf("7\n");
			break;
		case 8 : // appui sur bouton 0
			printf("START\n");
			break;
		case 9 : // appui sur bouton 0
			printf("SELECT\n");
			break;
	}
}

void	ft_joystick_axis(t_env *env, SDL_Event event)
{
	int axis = event.jaxis.axis;
	int value = event.jaxis.value;
	
	if (value == -129)
		return ;
	if (axis == 3)
	{
		if (value < 0)
			printf("LEFT\n");
		else
			printf("RIGHT\n");
	}
	else
	{
		if (value < 0)
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
			if(env->map[(int)(env->player->x + env->dirX * env->moveSpeed)][(int)env->player->y] == 0)
				env->player->x += env->dirX * env->moveSpeed;
			if(env->map[(int)env->player->x][(int)(env->player->y + env->dirY * env->moveSpeed)] == 0)
				env->player->y += env->dirY * env->moveSpeed;

		}
		}
		else
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
				if(env->map[(int)(env->player->x - env->dirX * env->moveSpeed)][(int)env->player->y] == 0)
					env->player->x -= env->dirX * env->moveSpeed;
				if(env->map[(int)env->player->x][(int)(env->player->y - env->dirY * env->moveSpeed)] == 0)
					env->player->y -= env->dirY * env->moveSpeed;
			}
		}
	}
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
			ft_joystick_axis(env, event);

	}
}
