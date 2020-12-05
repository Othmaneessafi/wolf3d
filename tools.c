/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 04:56:27 by cnaour            #+#    #+#             */
/*   Updated: 2020/12/04 02:22:36 by oes-safi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		background(t_wolf *wolf)
{
	int			w;
	int			h;
	SDL_Rect	tex;
	SDL_Texture	*img;

	if (wolf->i == 0)
		img = IMG_LoadTexture(wolf->renderer, wolf->pics[11]);
	if (wolf->i == 1)
		img = IMG_LoadTexture(wolf->renderer, wolf->pics[7]);
	if (wolf->i == 2)
		img = IMG_LoadTexture(wolf->renderer, wolf->pics[2]);
	if (wolf->i == 3)
		img = IMG_LoadTexture(wolf->renderer, wolf->pics[6]);
	if (wolf->i == 4)
		img = IMG_LoadTexture(wolf->renderer, wolf->pics[3]);
	if (wolf->i == 6)
		img = IMG_LoadTexture(wolf->renderer, wolf->pics[10]);
	if (wolf->i == 7)
		img = IMG_LoadTexture(wolf->renderer, wolf->pics[5]);
	SDL_QueryTexture(img, NULL, NULL, &w, &h);
	tex = (SDL_Rect){.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
	SDL_RenderClear(wolf->renderer);
	SDL_RenderCopy(wolf->renderer, img, NULL, &tex);
	SDL_RenderPresent(wolf->renderer);
	SDL_DestroyTexture(img);
}

void		menu(t_wolf *wolf, t_player *player, t_ray *rays)
{
	int x;
	int y;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);
	if (wolf->i == 0 || wolf->i == 1 || wolf->i == 2 || wolf->i == 3 ||
			wolf->i == 4 || wolf->i == 6 || wolf->i == 7)
	{
		menu0(wolf, x, y);
	}
	else if (wolf->i == 5)
	{
		update(wolf->map, &wolf->tickslastframe, player, rays);
		render(wolf, player, wolf->map, rays);
	}
}

void		menu0(t_wolf *wolf, int x, int y)
{
	background(wolf);
	if (wolf->i == 0)
	{
		SDL_Delay(3000);
		wolf->i = 1;
	}
	else
		menu1(wolf, x, y);
	if (wolf->i == 6)
		menu2(wolf, x, y);
	if (wolf->i == 1)
	{
		wolf->p = 0;
		wolf->o = 0;
		wolf->a = 0;
		wolf->m = 0;
	}
}

void		menu1(t_wolf *wolf, int x, int y)
{
	if ((x >= 835 && x <= 1222) && (y >= 529 && y <= 564) &&
			wolf->i != 6 && wolf->i != 7)
	{
		wolf->p = 1;
		wolf->i = 2;
	}
	else
		wolf->p = 0;
	if ((x >= 835 && x <= 1131) && (y >= 603 && y <= 634) &&
			wolf->o != 2 && wolf->i != 6 && wolf->i != 7)
	{
		wolf->o = 1;
		wolf->i = 3;
	}
	else
		wolf->o = wolf->o != 2 ? 0 : 2;
	if ((x >= 835 && x <= 1084) && (y >= 675 && y <= 713) &&
			wolf->a != 2 && wolf->i != 7 && wolf->i != 6)
	{
		wolf->a = 1;
		wolf->i = 4;
	}
	else
		wolf->a = wolf->a != 2 ? 0 : 2;
}

void		menu2(t_wolf *wolf, int x, int y)
{
	if ((x >= 791 && x <= 1260) && (y >= 500 && y <= 530) &&
			(wolf->m == 3 || wolf->m == 2 || wolf->m == 0))
	{
		wolf->m = 1;
	}
	else if ((x >= 791 && x <= 1195) && (y >= 575 && y <= 602) &&
			(wolf->m == 1 || wolf->m == 3 || wolf->m == 0))
	{
		wolf->m = 2;
	}
	else if ((x >= 791 && x <= 1200) && (y >= 645 && y <= 680) &&
			(wolf->m == 1 || wolf->m == 2 || wolf->m == 0))
	{
		wolf->m = 3;
	}
}
