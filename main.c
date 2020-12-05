/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:24:42 by cnaour            #+#    #+#             */
/*   Updated: 2020/10/18 01:27:18 by cnaour           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		init_wolf(t_wolf *wolf, t_player *player)
{
	wolf->window = NULL;
	wolf->renderer = NULL;
	wolf->loop = 0;
	wolf->tickslastframe = 0;
	if ((wolf->colorbuffer = (int *)malloc(sizeof(int)
					* WIDTH * HEIGHT)) == NULL)
	{
		destroy_window(wolf, player);
		exit(0);
	}
	wolf->i = 0;
	wolf->p = 0;
	wolf->o = 0;
	wolf->a = 0;
	wolf->m = 0;
	wolf->t = 1;
	wolf->msc = NULL;
}

void		init_player(t_player *player, t_wolf *wolf)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->width = 2;
	player->height = 32;
	player->turndirection = 0;
	player->walkdirection = 0;
	player->rotatangle = PI;
	player->walkspeed = 200;
	player->turnspeed = 70 * (PI / 180);
	player->colorbuffertexture = SDL_CreateTexture(wolf->renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING
			, WIDTH, HEIGHT);
}

void		init_tab(t_ray *rays)
{
	int j;

	j = 0;
	while (j < NUM_RAY)
	{
		rays[j].distance = 0;
		rays[j].hitver = 0;
		rays[j].rayangle = 0;
		rays[j].raydown = 0;
		rays[j].rayleft = 0;
		rays[j].rayright = 0;
		rays[j].rayup = 0;
		rays[j].wallhitcontent = 0;
		rays[j].wallhitx = 0;
		rays[j].wallhity = 0;
		j++;
	}
}

int			main(int ac, char **av)
{
	t_wolf		wolf;
	t_player	player;
	t_ray		rays[NUM_RAY];

	if (ft_check(av, &wolf, 0, 0) == 0 || ac != 2)
	{
		printf("map is invalid !!!\n");
		return (0);
	}
	init_wolf(&wolf, &player);
	wolf.loop = init_window(&wolf);
	imgs(&wolf, &player);
	init_tab(rays);
	textures(&wolf, &player);
	init_player(&player, &wolf);
	sounds(&wolf, "sounds/intro.mp3");
	while (wolf.loop)
	{
		process_input(&wolf, &player);
		menu(&wolf, &player, rays);
	}
	destroy_window(&wolf, &player);
}

