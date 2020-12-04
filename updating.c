/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 04:57:42 by cnaour            #+#    #+#             */
/*   Updated: 2020/10/18 05:07:26 by cnaour           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			mapwall(int **map, float x, float y)
{
	int		mapequx;
	int		mapequy;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return (TRUE);
	mapequx = floor(x / TILE_SIZE);
	mapequy = floor(y / TILE_SIZE);
	return (map[mapequy][mapequx] != 0);
}

void		playermove(int **map, float deltatime, t_player *player)
{
	float	movestep;
	float	newx;
	float	newy;

	player->rotatangle += player->turndirection *
		player->turnspeed * deltatime;
	movestep = player->walkdirection * player->walkspeed *
		deltatime;
	newx = round(player->x + movestep * cos(player->rotatangle));
	newy = round(player->y + movestep * sin(player->rotatangle));
	if (!mapwall(map, newx, newy))
	{
		player->x = (float)newx;
		player->y = (float)newy;
	}
}

void		update(int **map, float *ticks, t_player *player, t_ray *rays)
{
	float	deltatime;
	float	t;

	t = SDL_GetTicks();
	while (!SDL_TICKS_PASSED(t, *ticks + FRAME_TIME))
	{
		t = SDL_GetTicks();
	}
	deltatime = (SDL_GetTicks() - *ticks) / 1000.0f;
	*ticks = SDL_GetTicks();
	playermove(map, deltatime, player);
	castallrays(player, map, rays);
}
