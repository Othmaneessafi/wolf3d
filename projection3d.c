/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:40:01 by cnaour            #+#    #+#             */
/*   Updated: 2020/10/18 01:44:13 by cnaour           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		clearcolorbuffer(int *buffer, int color)
{
	int i;
	int j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			buffer[(WIDTH * j) + i] = color;
			j++;
		}
		i++;
	}
}

void		rendercolorbuffer(t_player *p, t_wolf *wolf)
{
	SDL_UpdateTexture(p->colorbuffertexture, NULL, wolf->colorbuffer,
			(int)(int)WIDTH * sizeof(int));
	SDL_RenderCopy(wolf->renderer, p->colorbuffertexture, NULL, NULL);
}

void		coloring(t_cords walltopandbottom, t_ray *rays, t_wolf *wolf, int i, t_projection *proj, t_player *p)
{
	int		j;
	t_texture	wall;
	t_texture	flor;
	t_texture   ceil;
	int disFromTop;

	j = 0;
	//printf("%f === %f\n", walltopandbottom.x, rays[i].distance);
	while (j < walltopandbottom.x)
	{
		
		ceil.ratio = (TILE_SIZE - p->height) / (CENTERY - j);
		ceil.diago_distance = floor(proj->distprojplane * ceil.ratio / cos(rays[i].rayangle - p->rotatangle));
		ceil.endx = floor(ceil.diago_distance * cos(rays[i].rayangle));
		ceil.endy = floor(ceil.diago_distance * sin(rays[i].rayangle));
		ceil.endy += p->y;
		ceil.endx += p->x;
		ceil.cellx = floor(ceil.endx / TILE_SIZE);
		ceil.celly = floor(ceil.endy / TILE_SIZE);

		if (ceil.cellx < COLS && ceil.celly < ROWS && ceil.cellx >= 0 && ceil.celly >= 0)
		{
			ceil.tilerow = (int)ceil.endy % TILE_SIZE;
			ceil.tilecol = (int)ceil.endx % TILE_SIZE;
			//if (flor.cellx == 7 && flor.celly == 8)
				//flor.color = wolf->walltex1[(TEX_W * flor.tilerow) + flor.tilecol];
			//else
			ceil.color = wolf->walltex1[(TEX_W * ceil.tilerow) + ceil.tilecol];
			wolf->colorbuffer[(WIDTH * j) + i] = ceil.color;
		}
		j++;
	}
	j = walltopandbottom.x;
	if (rays[i].hitver)
         wall.offx = (int)rays[i].wallhity % TILE_SIZE;
    else
        wall.offx = (int)rays[i].wallhitx % TILE_SIZE;
	while (j < walltopandbottom.y)
	{
        disFromTop = j + ((int)proj->wallprojheight/2) - (HEIGHT / 2);
        wall.offy = disFromTop * ((float)TEX_H / proj->wallprojheight);
        wall.color = wolf->walltex[(TEX_W * wall.offy) + wall.offx];
        wolf->colorbuffer[(WIDTH * j) + i] = wall.color;
		j++;
	}
	j = walltopandbottom.y;
	while (j < HEIGHT)
	{
		flor.ratio = p->height / (j - CENTERY);
		flor.diago_distance = floor(proj->distprojplane * flor.ratio / cos(rays[i].rayangle - p->rotatangle));
		flor.endy = floor(flor.diago_distance * sin(rays[i].rayangle));
		flor.endx = floor(flor.diago_distance * cos(rays[i].rayangle));
		flor.endy += p->y;
		flor.endx += p->x;
		flor.cellx = floor(flor.endx / TILE_SIZE);
		flor.celly = floor(flor.endy / TILE_SIZE);

		if (flor.cellx < COLS && flor.celly < ROWS && flor.cellx >= 0 && flor.celly >= 0)
		{
			flor.tilerow = (int)flor.endy % TILE_SIZE;
			flor.tilecol = (int)flor.endx % TILE_SIZE;
			//if (flor.cellx == 7 && flor.celly == 8)
				//flor.color = wolf->walltex1[(TEX_W * flor.tilerow) + flor.tilecol];
			//else
			flor.color = wolf->walltex2[(TEX_W * flor.tilerow) + flor.tilecol];
			wolf->colorbuffer[(WIDTH * j) + i] = flor.color;
		}
		//wolf->colorbuffer[(WIDTH * j) + i] = 0xFF333333;
		j++;
	}
}

void    tex2(t_wolf *wolf)
{
	wolf->walltex = (int*) malloc(sizeof(int) * TEX_H * TEX_W);
    wolf->surface = IMG_Load(wolf->pics[1]);
    wolf->walltex = (int*)wolf->surface->pixels;
	
	wolf->walltex1 = (int*) malloc(sizeof(int) * TEX_H * TEX_W);
    wolf->surface = IMG_Load(wolf->pics[5]);
    wolf->walltex1 = (int*)wolf->surface->pixels;

	wolf->walltex2 = (int*) malloc(sizeof(int) * TEX_H * TEX_W);
    wolf->surface = IMG_Load(wolf->pics[7]);
    wolf->walltex2 = (int*)wolf->surface->pixels;

}		

void		generate3dprojection(t_ray *rays, t_player *player, t_wolf *wolf)
{
	int				i;
	t_projection	*proj;
	t_cords			walltopandbottom;

	i = 0;
	proj = malloc(sizeof(t_projection));
	while (i < NUM_RAY)
	{
		if (rays[i].distance == 0)
			rays[i].distance = 0.0003;
		proj->perpdistance = rays[i].distance * cos(rays[i].rayangle -
				player->rotatangle);
		proj->distprojplane = (WIDTH / 2) / tan(FOVA / 2);
		proj->wallprojheight = (TILE_SIZE / proj->perpdistance) *
			proj->distprojplane;
		walltopandbottom.x = (HEIGHT / 2) - ((int)proj->wallprojheight / 2);
		walltopandbottom.x = walltopandbottom.x < 0 ? 0 : walltopandbottom.x;
		walltopandbottom.y = (HEIGHT / 2) + ((int)proj->wallprojheight / 2);
		walltopandbottom.y = walltopandbottom.y > HEIGHT ? HEIGHT :
			walltopandbottom.y;
		coloring(walltopandbottom, rays, wolf, i, proj, player);
		i++;
	}
}
