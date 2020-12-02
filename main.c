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

void		init_wolf(t_wolf *wolf)
{
	wolf->window = NULL;
	wolf->renderer = NULL;
	wolf->loop = 0;
	wolf->tickslastframe = 0;
	wolf->colorbuffer = (int *)malloc(sizeof(int)
					* WIDTH * HEIGHT);
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
	int x, y;

	wolf.map = ft_check(ac, av);
	if (wolf.map == 0)
	{
		printf("map is invalid !!!\n");
		return (0);
	}
	init_wolf(&wolf);
	wolf.loop = init_window(&wolf);
	imgs(&wolf);
	init_tab(rays);
	tex2(&wolf);
	init_player(&player, &wolf);
	// wolf.msc = NULL;
	//wolf.msc = Mix_LoadMUS("sounds/intro.mp3");
	sounds(&wolf, "sounds/intro.mp3");
	while (wolf.loop)
	{
		process_input(&wolf, &player);
		if (wolf.i == 0 || wolf.i == 1 || wolf.i == 2 || wolf.i == 3 || wolf.i == 4 || wolf.i == 6 || wolf.i == 7)
		{
			background(&wolf);
			if (wolf.i == 0)
			{
				SDL_Delay(3000);
				wolf.i = 1;
			}
			else
			{
				SDL_GetMouseState(&x, &y);
				if ((x >= 835 && x <= 1222) && (y >= 529 && y <= 564) && wolf.i != 6 && wolf.i != 7)
				{
					wolf.p = 1;
					wolf.i = 2;
				}
				else
					wolf.p = 0;
				if ((x >= 835 && x <= 1131) && (y >= 603 && y <= 634) && wolf.o != 2 && wolf.i != 6 && wolf.i != 7)
				{
					wolf.o = 1;
					wolf.i = 3;
				}
				else
					wolf.o = wolf.o != 2 ? 0 : 2;
				if ((x >= 835 && x <= 1084) && (y >= 675 && y <= 713) && wolf.a != 2 && wolf.i != 7 && wolf.i != 6)
				{
					wolf.a = 1;
					wolf.i = 4;
				}
				else
					wolf.a = wolf.a != 2 ? 0 : 2;
			}

			if (wolf.i == 6)
			{
				if ((x >= 791 && x <= 1260) && (y >= 500 && y <= 530) && (wolf.m == 3 || wolf.m == 2 || wolf.m == 0))
				{
					wolf.m = 1;
				}
				else if ((x >= 791 && x <= 1195) && (y >= 575 && y <= 602) && (wolf.m == 1 || wolf.m == 3 || wolf.m == 0))
				{
					wolf.m = 2;
				}
				else if ((x >= 791 && x <= 1200) && (y >= 645 && y <= 680) && (wolf.m == 1 || wolf.m == 2 || wolf.m == 0))
				{
					wolf.m = 3;
				}
				//printf("%d\n", wolf.m);
			}
			if (wolf.i == 1)
			{
				wolf.p = 0;
				wolf.o = 0;
				wolf.a = 0;
				wolf.m = 0;
			}
		}
		else if (wolf.i == 5)
		{
			update(wolf.map, &wolf.tickslastframe, &player, rays);
			render(&wolf, &player, wolf.map, rays);
		}
	}
	destroy_window(&wolf);
}