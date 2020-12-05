/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 04:50:13 by cnaour            #+#    #+#             */
/*   Updated: 2020/12/05 04:14:10 by cnaour           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		rendermap(int **map, t_wolf *wolf)
{
	int			i;
	int			j;
	t_cords		tile;
	int			tilecolor;
	SDL_Rect	maprect;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			tile.x = j * TILE_SIZE;
			tile.y = i * TILE_SIZE;
			tilecolor = map[i][j] != 0 ? 255 : 0;
			SDL_SetRenderDrawColor(wolf->renderer, tilecolor,
					tilecolor, tilecolor, 255);
			maprect = (SDL_Rect){MM_SCALE * tile.x, MM_SCALE * tile.y,
				MM_SCALE * TILE_SIZE, MM_SCALE * TILE_SIZE};
			SDL_RenderFillRect(wolf->renderer, &maprect);
			j++;
		}
		i++;
	}
}

void		renderplayer(t_player *player, t_wolf *wolf)
{
	SDL_Rect	p_rect;

	SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
	p_rect = (SDL_Rect){MM_SCALE * player->x, MM_SCALE * player->y,
		MM_SCALE * player->width, MM_SCALE * player->height};
	SDL_RenderFillRect(wolf->renderer, &p_rect);
	SDL_RenderDrawLine(wolf->renderer, MM_SCALE * player->x, MM_SCALE *
			player->y, MM_SCALE * (player->x + cos(player->rotatangle) * 40),
			MM_SCALE * (player->y + sin(player->rotatangle) * 40));
}

void		renderays(t_ray *rays, t_wolf *wolf, t_player *player)
{
	int		i;

	i = 0;
	SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
	while (i < NUM_RAY)
	{
		SDL_RenderDrawLine(wolf->renderer, MM_SCALE * player->x,
				MM_SCALE * player->y,
				MM_SCALE * rays[i].wallhitx,
				MM_SCALE * rays[i].wallhity);
		i++;
	}
}

void		render(t_wolf *wolf, t_player *player, int **map, t_ray *rays)
{
	SDL_SetRenderDrawColor(wolf->renderer, 0, 0, 0, 255);
	SDL_RenderClear(wolf->renderer);
	generate3dprojection(rays, player, wolf, -1);
	rendercolorbuffer(player, wolf);
	clearcolorbuffer(wolf->colorbuffer, 0xFF000000);
	rendermap(map, wolf);
	renderays(rays, wolf, player);
	renderplayer(player, wolf);
	SDL_RenderPresent(wolf->renderer);
}
