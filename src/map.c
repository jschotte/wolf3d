/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:16:20 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/23 22:55:43 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_print_map(t_env *env)
{
	int		i;
	int		j;
	t_point	p;

	p.x = POSMAPX;
	p.y = POSMAPY;
	ft_draw_square(env, &p, SIZECASEMAP, ft_create_color(env, 0, 0, 0));
	i = 0;
	while (i < env->maph)
	{
		j = 0;
		p.x = POSMAPX;
		while (j < env->mapw)
		{
			if (env->map[i][j] == 0)
				ft_draw_square(env, &p, SIZECASEMAP / env->mapw,
					ft_create_color(env, 255, 255, 255));
			p.x += SIZECASEMAP / env->mapw;
			j++;
		}
		p.y += SIZECASEMAP / env->maph;
		i++;
	}
	ft_print_player(env);
}

void	ft_load_size(t_env *env, char *str)
{
	char	**split;
	int		index;

	index = 0;
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
	if ((env->map = malloc(sizeof(int*) * (env->maph) + 1)) == NULL)
		ft_exit("Malloc Error\n");
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

void	fill_line(t_env *env, char *line, int y)
{
	int	x;

	x = 0;
	if ((env->map[y] = malloc(sizeof(int) * (env->mapw) + 1)) == NULL)
		ft_exit("Malloc Error\n");
	while (x < env->mapw)
	{
		env->map[y][x] = line[x] - '0';
		x++;
	}
}

void	ft_load_map(t_env *env)
{
	char	*line;
	int		fd;
	int		i;
	int		y;

	i = 0;
	y = 0;
	fd = open(env->map_path, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (i == 0)
			ft_load_size(env, line);
		else
		{
			fill_line(env, line, y);
			y++;
		}
		i++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	env->player->x = 1.3;
	env->player->y = 1.3;
}
