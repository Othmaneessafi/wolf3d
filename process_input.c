/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:28:57 by cnaour            #+#    #+#             */
/*   Updated: 2020/10/18 01:29:59 by cnaour           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		keyup_input(t_wolf *wolf, t_player *player, SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_ESCAPE)
		wolf->loop = FALSE;
	if (e.key.keysym.sym == SDLK_w)
		player->walkdirection = +1;
	if (e.key.keysym.sym == SDLK_s)
		player->walkdirection = -1;
	if (e.key.keysym.sym == SDLK_d)
		player->turndirection = +1;
	if (e.key.keysym.sym == SDLK_a)
		player->turndirection = -1;
}

void		process_input(t_wolf *wolf, t_player *player)
{
	SDL_Event e;

	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT)
	{
		wolf->loop = FALSE;
	}
	else if (e.type == SDL_KEYDOWN)
	{
		keyup_input(wolf, player, e);
	}
	else if (e.type == SDL_KEYUP)
	{
		if (e.key.keysym.sym == SDLK_w)
			player->walkdirection = 0;
		if (e.key.keysym.sym == SDLK_s)
			player->walkdirection = 0;
		if (e.key.keysym.sym == SDLK_d)
			player->turndirection = 0;
		if (e.key.keysym.sym == SDLK_a)
			player->turndirection = 0;
	}
}
