#include "../includes/wolf.h"

void setpixel(SDL_Surface *screen, int x, int y, Uint32 color)
{
	Uint8 *pixmem32;
	int bpp = screen->format->BytesPerPixel;

	pixmem32 = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;
	*(Uint16 *)pixmem32 = color;
}

void	ft_draw_square(t_env *env, t_point *point, int l, Uint32 color)
{
	int x, y;

	for(y = point->y; y < point->y + l; y++ ) 
	{
		for( x = point->x; x < point->x + l; x++ ) 
		{
			setpixel(env->screen, x, y, color);
		}
	}
}

Uint32		ft_create_color(t_env *env, Uint8 r, Uint8 g, Uint8 b)
{
	Uint32 color;

	color = SDL_MapRGB(env->screen->format, r, g, b);
	return (color);
}

void	ft_mid_up(t_env *env)
{
	int x, y, ytimesw;

	//if(SDL_MUSTLOCK(env->screen)) 
	//	if(SDL_LockSurface(env->screen) < 0)
	//		return;
	for(y = 0; y < HEIGHTIMG / 2; y++ ) 
	{
		ytimesw = env->screen->pitch/BPP;
		for( x = 0; x < env->screen->w; x++ ) 
		{
			//if (env->ismap == 0 || ((x < POSMAPX || x >= POSMAPX + SIZECASEMAP)
			//		|| (y < POSMAPY || y >= POSMAPY + SIZECASEMAP)))
			setpixel(env->screen, x, y, ft_create_color(env, 0, 255, 0));
		}
	}
	//if(SDL_MUSTLOCK(env->screen))
	//	SDL_UnlockSurface(env->screen);
	//SDL_Flip(env->screen); 

}

void	ft_mid_down(t_env *env)
{
	int x, y, ytimesw;

	//if(SDL_MUSTLOCK(env->screen)) 
	//	if(SDL_LockSurface(env->screen) < 0)
	//		return;
	for(y = HEIGHTIMG / 2; y < HEIGHTIMG; y++ ) 
	{
		ytimesw = env->screen->pitch/BPP;
		for( x = 0; x < env->screen->w; x++ ) 
		{
			setpixel(env->screen, x, y, ft_create_color(env, 255, 0, 0));
		}
	}
	//if(SDL_MUSTLOCK(env->screen))
	//	SDL_UnlockSurface(env->screen);
	//SDL_Flip(env->screen); 

}
