/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:28:57 by cnaour            #+#    #+#             */
/*   Updated: 2020/12/04 02:28:29 by oes-safi         ###   ########.fr       */
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
	if (e.key.keysym.sym == SDLK_SPACE)
		wolf->i = 1;
}

void		process_input(t_wolf *wolf, t_player *player)
{
	SDL_Event e;

	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT)
		wolf->loop = FALSE;
	else if (e.type == SDL_KEYDOWN)
		keyup_input(wolf, player, e);
	if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		input(wolf);
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
		if (e.key.keysym.sym == SDLK_SPACE)
			wolf->i = 1;
	}
}

void		input(t_wolf *wolf)
{
	if (wolf->i == 2 && wolf->p == 1)
		wolf->i = 5;
	else if (wolf->i == 3 && wolf->o == 1)
	{
		wolf->i = 6;
		wolf->o = 2;
	}
	else if (wolf->i == 4 && wolf->a == 1)
	{
		wolf->i = 7;
		wolf->a = 2;
	}
	else if (wolf->i == 6)
		input1(wolf);
}

void		input1(t_wolf *wolf)
{
	if (wolf->m == 1)
	{
		sounds(wolf, "sounds/mission.mp3");
		wolf->i = 1;
		wolf->t = 1;
	}
	if (wolf->m == 2)
	{
		sounds(wolf, "sounds/momen.mp3");
		wolf->i = 1;
		wolf->t = 2;
	}
	if (wolf->m == 3)
	{
		sounds(wolf, "sounds/hajib.mp3");
		wolf->i = 1;
		wolf->t = 3;
	}
}
