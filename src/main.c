/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:16:20 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/20 11:19:03 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	return (EXIT_FAILURE);
}

void	ft_img(t_env *env)
{
	SDL_Surface *test;
	SDL_Rect	positionFond;

	positionFond.x = 0;
	positionFond.y = 0;
	test = SDL_LoadBMP(env->img);
	SDL_BlitSurface(test, NULL, env->screen, &positionFond);
	SDL_FreeSurface(test);
	SDL_Flip(env->screen);
}

void	ft_print_player(t_env *env)
{
	t_point *p;

	p = malloc(sizeof(t_point));
	p->x = POSMAPX + ((SIZECASEMAP / env->mapw) * env->player->x);
	p->y = POSMAPY + ((SIZECASEMAP / env->maph) * env->player->y); 
	ft_draw_square(env, p, 5, ft_create_color(env, 255, 0, 0));
	free(p);
}

void	ft_print_map(t_env *env)
{
	int i;
	int j;
	t_point *p;

	if(SDL_MUSTLOCK(env->screen)) 
		if(SDL_LockSurface(env->screen) < 0)
			return;
	p = malloc(sizeof(t_point));
	p->x = POSMAPX;
	p->y = POSMAPY;
	ft_draw_square(env, p, SIZECASEMAP, ft_create_color(env, 255, 255, 255));
	i = 0;
	while (i < env->maph)
	{
		j = 0;
		p->x = POSMAPX;
		while (j < env->mapw)
		{
			if (env->map[i][j] != 0)
				ft_draw_square(env, p, 100 / env->mapw, ft_create_color(env, 0, 0, 0));
			p->x += 100 / env->mapw;
			j++;	
		}
		p->y += 100 / env->maph;
		i++;
	}
	ft_print_player(env);
	free(p);
}

void	ft_load_size(t_env *env, char *str)
{
	char **split;
	int		index = 0;
	split = ft_strsplit(str, ' ');
	env->mapw = ft_atoi(split[0]);
	env->maph = ft_atoi(split[1]);
	while (split[index])
	{
		free(split[index]);
		split[index] = NULL;
		index++;
	}
	free(split);
	split = NULL;
	env->map = malloc(sizeof(int*) * (env->maph) + 1);
}

void	ft_free_map(t_env *env)
{
	int i;

	i = 0;
	while (i < env->maph)
	{
		free(env->map[i]);
		env->map[i] = NULL;
		i++;
	}
	free(env->map);
	env->map = NULL;
	env->mapw = 0;
	env->maph = 0;
}

void	ft_load_map(t_env *env)
{
	char *line;
	int fd;
	int i;
	int x;
	int y;

	i = 0;
	y = 0;
	fd = open(env->map_path, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (i == 0)
			ft_load_size(env, line);
		else
		{
			x = 0;
			env->map[y] = malloc(sizeof(int) * (env->mapw) + 1);
			while (x < env->mapw)
			{
				env->map[y][x] = line[x] - '0';
				x++;
			}
			y++;
		}
		i++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	env->player->x = 1.3;
	env->player->y = 1.3;
	env->player->angle = 0.0f;
}

void	verLine(t_env *env, int w, int sh, int eh, Uint32 color)
{
	while (sh < eh)
	{
		setpixel(env->screen, w, sh, color);
		sh++;
	}

}

void	ft_start(t_env *env)
{
	t_player	*player;
	int x;

	player = malloc(sizeof(t_player));
	player->x = 1.3;
	player->y = 1.3;
	player->angle = 0.0f;
	env->player = player;
	ft_load_map(env);
	env->dirX = -1;
	env->dirY = 0;
	env->planeX = 0;
	env->planeY = 0.66;
	double time = 0;
	double oldTime = 0;
	while (env->quit == 0)
	{
		ft_clear_win(env);
		//ft_mid_up(env);
		//ft_mid_down(env);
		x = 0;
		while (x < WIDTH)
		{
			double cameraX = 2 * x / WIDTH - 1; //x-coordinate in camera space
			double rayPosX = env->player->x;
			double rayPosY = env->player->y;
			double rayDirX = env->dirX + env->planeX * cameraX;
			double rayDirY = env->dirY + env->planeY * cameraX;

			int mapX = (int)rayPosX;
			int mapY = (int)rayPosY;

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
			double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (rayPosX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (rayPosY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
			}
			while (hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (env->map[mapX][mapY] > 0)
					hit = 1;
			}
			if (side == 0)
				perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

			int lineHeight = (int)(HEIGHT / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + HEIGHT / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + HEIGHT / 2;
			if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;

			Uint32 color;
			if (env->map[mapX][mapY] == 1)
				color = SDL_MapRGB(env->screen->format, 0, 0, 255);
			else if (env->map[mapX][mapY] == 2)
				color = SDL_MapRGB(env->screen->format, 0, 255, 0);
			else if (env->map[mapX][mapY] == 3)
				color = SDL_MapRGB(env->screen->format, 255, 0, 0);
			else if (env->map[mapX][mapY] == 4)
				color = SDL_MapRGB(env->screen->format, 0, 255, 255);

			//give x and y sides different brightness
			//if (side == 1)
			//	color = color / 2;

			//draw the pixels of the stripe as a vertical line
			//printf("%d %d %d\n", x, drawStart, drawEnd);
			if (env->map[mapX][mapY] != 0)
				verLine(env, x, drawStart, drawEnd, color);
			x++;
		}
		oldTime = time;
		time = SDL_GetTicks();
		double frameTime = (time - oldTime) / 1000.0;

		env->moveSpeed = frameTime * 0.5; //the constant value is in squares/second
		env->rotSpeed = frameTime * 1.0; //the constant value is in radians/second
		//printf("%f %f %f %f\n", env->dirX, env->dirY, env->planeX, env->planeY);
		//printf("%d\n", env->ismap);
		if (env->ismap == 1)
			ft_print_map(env);
		if(SDL_MUSTLOCK(env->screen))
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
	tmp->maph = 1;
	tmp->mapw = 1;
	tmp->player = NULL;
	return (tmp);
}

int main(int argc, char* argv[])
{
	SDL_Surface *screen;
	t_env		*env;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
		return (ft_exit("SDL can't init !\n"));
	if ((screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE)) < 0)
	{
		SDL_Quit();
		return (ft_exit("SDL can't open \n"));
	}
	
	SDL_Joystick *joystick; // on crée le joystick
	joystick = SDL_JoystickOpen(0); // on l'assigne au numéro 0
	SDL_JoystickEventState(SDL_ENABLE);	
	SDL_EnableKeyRepeat(10, 10);
	SDL_WM_SetCaption("WOFL3D", NULL);
	env = init_env(screen);
	ft_menu(env);
	SDL_Quit();
	return (0);
}
