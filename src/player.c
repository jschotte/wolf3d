/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:16:20 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/24 18:18:07 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_img(t_env *env)
{
	SDL_Surface *test;
	SDL_Rect	positionfond;

	positionfond.x = 0;
	positionfond.y = 0;
	test = SDL_LoadBMP(env->img);
	SDL_BlitSurface(test, NULL, env->screen, &positionfond);
	SDL_FreeSurface(test);
	SDL_Flip(env->screen);
}

void	ft_print_player(t_env *env)
{
	t_point *p;

	if ((p = malloc(sizeof(t_point))) == NULL)
		ft_exit("Malloc Error\n");
	p->x = POSMAPX + ((SIZECASEMAP / env->mapw) * env->player->x);
	p->y = POSMAPY + ((SIZECASEMAP / env->maph) * env->player->y);
	ft_draw_square(env, p, SIZECASEMAP / (env->mapw + env->maph),
		ft_create_color(env, 255, 0, 0));
	free(p);
}

void	ft_init_player(t_env *env)
{
	t_player	*player;

	if ((player = malloc(sizeof(t_player))) == NULL)
		ft_exit("Malloc Error\n");
	env->player = player;
}
