/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 04:56:27 by cnaour            #+#    #+#             */
/*   Updated: 2020/10/18 04:57:14 by cnaour           ###   ########.fr       */
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

void		destroy_window(t_wolf *wolf)
{
	free(wolf->colorbuffer);
	SDL_DestroyRenderer(wolf->renderer);
	SDL_DestroyWindow(wolf->window);
	SDL_Quit();
}

float		normalizeangle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return (angle);
}

float		distancecalc(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void    imgs(t_wolf *wolf)
{
    wolf->pics = (char **)malloc(sizeof(char *) * 13);
    wolf->pics[0] = ft_strdup("./pics/wood.png");
    wolf->pics[1] = ft_strdup("./pics/colorstone.png");
    wolf->pics[2] = ft_strdup("./images/play.png");
    wolf->pics[3] = ft_strdup("./images/about.png");
    wolf->pics[4] = ft_strdup("./pics/graystone.png");
    wolf->pics[5] = ft_strdup("./images/info.png");
    wolf->pics[6] = ft_strdup("./images/option.png");
    wolf->pics[7] = ft_strdup("./images/menu1.png");
    wolf->pics[8] = ft_strdup("./images/ceil.png");
    wolf->pics[9] = ft_strdup("./pics/floortile.png");
    wolf->pics[10] = ft_strdup("./images/choose.png");
    wolf->pics[11] = ft_strdup("./images/bg.png");
    wolf->pics[12] = ft_strdup("./images/is1.png");
}

void    tex2(t_wolf *wolf)
{
	wolf->walltex = (int**) malloc(sizeof(int*) * 13);

	wolf->walltex[0] = (int*) malloc(sizeof(int) * TEX_H * TEX_W);
    wolf->surface = IMG_Load(wolf->pics[1]);
    wolf->walltex[0] = (int*)wolf->surface->pixels;
	
	wolf->walltex[1] = (int*) malloc(sizeof(int) * TEX_H * TEX_W);
    wolf->surface = IMG_Load(wolf->pics[4]);
    wolf->walltex[1] = (int*)wolf->surface->pixels;

	wolf->walltex[2] = (int*) malloc(sizeof(int) * TEX_H * TEX_W);
    wolf->surface = IMG_Load(wolf->pics[0]);
    wolf->walltex[2] = (int*)wolf->surface->pixels;

	wolf->walltex[3] = (int*) malloc(sizeof(int) * TEX_H * TEX_W);
    wolf->surface = IMG_Load(wolf->pics[9]);
    wolf->walltex[3] = (int*)wolf->surface->pixels;

	wolf->walltex[4] = (int*) malloc(sizeof(int) * TEX_H * TEX_W);
    wolf->surface = IMG_Load(wolf->pics[12]);
    wolf->walltex[4] = (int*)wolf->surface->pixels;

	wolf->walltex[5] = (int*) malloc(sizeof(int) * TEX_H * TEX_W);
    wolf->surface = IMG_Load(wolf->pics[8]);
    wolf->walltex[5] = (int*)wolf->surface->pixels;

	wolf->walltex[6] = (int*) malloc(sizeof(int) * TEX_H * TEX_W);
    wolf->surface = IMG_Load(wolf->pics[11]);
    wolf->walltex[6] = (int*)wolf->surface->pixels;


}

void	sounds(t_wolf *wolf)
{
	Mix_PauseMusic();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	//wolf->msc = Mix_LoadMUS("sounds/hajib.mp3");
	Mix_PlayMusic(wolf->msc, 1);
}

void background(t_wolf *wolf)
{
		int w, h;
		SDL_Texture *img = NULL;
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
		SDL_Rect tex;
		tex.x = 0;
		tex.y = 0;
		tex.w = WIDTH;
		tex.h = HEIGHT;
		SDL_RenderClear(wolf->renderer);
		SDL_RenderCopy(wolf->renderer, img, NULL, &tex);
		SDL_RenderPresent(wolf->renderer);
}

t_choose	choose_tex(t_wolf *wolf)
{
	t_choose choose;

	if (wolf->t == 1)
	{
		choose.flor = wolf->walltex[3];
		choose.ceiling = wolf->walltex[5];
		choose.wall = wolf->walltex[5];
	}
	if (wolf->t == 2)
	{
		choose.flor = wolf->walltex[4];
		choose.ceiling = wolf->walltex[5];
		choose.wall = wolf->walltex[2];
	}
	if (wolf->t == 3)
	{
		choose.flor = wolf->walltex[4];
		choose.ceiling = wolf->walltex[5];
		choose.wall = wolf->walltex[0];
	}
	return (choose);
	
}