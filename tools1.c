/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oes-safi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 00:57:31 by oes-safi          #+#    #+#             */
/*   Updated: 2020/12/04 02:32:34 by oes-safi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			init_window(t_wolf *wolf)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Initialisation error\n");
		return (FALSE);
	}
	wolf->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (!wolf->window)
	{
		printf("Error creating window\n");
		return (FALSE);
	}
	wolf->renderer = SDL_CreateRenderer(wolf->window, -1, 0);
	if (!wolf->renderer)
	{
		printf("Error creating renderer\n");
		return (FALSE);
	}
	return (TRUE);
}

float		distancecalc(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void		imgs(t_wolf *wolf, t_player *player)
{
	if ((wolf->pics = (char **)malloc(sizeof(char *) * 20)) == NULL)
	{
		destroy_window(wolf, player);
		exit(0);
	}
	wolf->pics[0] = ft_strdup("./images/mossystone.png");
	wolf->pics[1] = ft_strdup("./images/colorstone.png");
	wolf->pics[2] = ft_strdup("./images/play.png");
	wolf->pics[3] = ft_strdup("./images/about.png");
	wolf->pics[4] = ft_strdup("./images/graystone.png");
	wolf->pics[5] = ft_strdup("./images/info.png");
	wolf->pics[6] = ft_strdup("./images/option.png");
	wolf->pics[7] = ft_strdup("./images/menu1.png");
	wolf->pics[8] = ft_strdup("./images/bluestone.png");
	wolf->pics[9] = ft_strdup("./images/redbrick.png");
	wolf->pics[10] = ft_strdup("./images/choose.png");
	wolf->pics[11] = ft_strdup("./images/bg.png");
	wolf->pics[12] = ft_strdup("./images/is1.png");
	wolf->pics[13] = ft_strdup("./images/purplestone.png");
	wolf->pics[14] = ft_strdup("./images/wood.png");
	wolf->pics[15] = ft_strdup("./images/floortile.png");
	wolf->pics[16] = ft_strdup("./images/is.png");
	wolf->pics[17] = ft_strdup("./images/khayma1.png");
	wolf->pics[18] = ft_strdup("./images/s9af1.png");
	wolf->pics[19] = NULL;
}

void		textures(t_wolf *wolf, t_player *player)
{
	int i;

	i = 0;
	if ((wolf->walltex = (int**)malloc(sizeof(int *) * 19)) == NULL)
	{
		destroy_window(wolf, player);
		exit(0);
	}
	while (i < 19)
	{
		if ((wolf->walltex[i] = (int *)malloc(sizeof(int))) == NULL)
		{
			destroy_window(wolf, player);
			exit(0);
		}
		wolf->surface = IMG_Load(wolf->pics[i]);
		wolf->walltex[i] = (int *)wolf->surface->pixels;
		i++;
	}
	wolf->walltex[i] = NULL;
}

t_choose	choose_tex(t_wolf *wolf)
{
	t_choose choose;

	if (wolf->t == 1)
	{
		choose.flor = wolf->walltex[4];
		choose.ceiling = wolf->walltex[13];
	}
	if (wolf->t == 2)
	{
		choose.flor = wolf->walltex[12];
		choose.ceiling = wolf->walltex[15];
		choose.wall = wolf->walltex[14];
	}
	if (wolf->t == 3)
	{
		choose.flor = wolf->walltex[16];
		choose.ceiling = wolf->walltex[18];
		choose.wall = wolf->walltex[17];
	}
	return (choose);
}
