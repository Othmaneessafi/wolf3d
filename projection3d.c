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

int			get_color(int color, double dist)
{
	int r;
	int g;
	int b;

	r = ((color >> 16) & 255);
	g = ((color >> 8) & 255);
	b = (color & 255);
	r = (r * (1.0 - dist / 4) > 0.0) ? r * (1.0 - dist / 4) : 0;
	g = (g * (1.0 - dist / 4) > 0.0) ? g * (1.0 - dist / 4) : 0;
	b = (b * (1.0 - dist / 4) > 0.0) ? b * (1.0 - dist / 4) : 0;
	return ((r << 16) | (g << 8) | b);
}

int			get_color2(int color, double dist)
{
	int r;
	int g;
	int b;

	r = ((color >> 16) & 255);
	g = ((color >> 8) & 255);
	b = (color & 255) ;
	r = (r * dist > 0.0) ? r * dist : 0;
	g = (g * dist > 0.0) ? g * dist : 0;
	b = (b * dist > 0.0) ? b * dist : 0;
	return ((r << 16) | (g << 8) | b);
}

void		coloring(t_cords walltopandbottom, t_ray *rays, t_wolf *wolf, int i, t_projection *proj, t_player *p)
{
	int		j;
	t_texture	wall;
	t_texture	flor;
	t_texture   ceil;
	t_choose	clr;	
	int disFromTop;
	int *color = NULL;
	int color1;

	j = 0;
	clr = choose_tex(wolf);
		
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
			double bright = HEIGHT / (2.0 * j - HEIGHT);
			ceil.color = clr.ceiling[(TEX_W * ceil.tilerow) + ceil.tilecol];
			color1 = get_color(ceil.color, -1.0 * bright);
			wolf->colorbuffer[(WIDTH * j) + i] = color1;
		}
		j++;
	}
	double light;
	j = walltopandbottom.x;
		if (rays[i].hitver)
		{
			if (wolf->t == 1)
			{
				if (rays[i].rayright)
					color = wolf->walltex[1];
				else if (rays[i].rayleft)
					color = wolf->walltex[3];
			}
			wall.offx = (int)rays[i].wallhity % TILE_SIZE;
		}
		else
		{
			if (wolf->t == 1)
			{
				if (rays[i].rayup)
					color = wolf->walltex[0];
				else if (rays[i].raydown)
					color = wolf->walltex[2];
			}
			wall.offx = (int)rays[i].wallhitx % TILE_SIZE;
		}
	if (wolf->t != 1)
		color = clr.wall;
	light = 180/rays[i].distance;
	if (light > 0.883948)
		light = 0.883948;
	while (j < walltopandbottom.y)
	{
        disFromTop = j + ((int)proj->wallprojheight/2) - (HEIGHT / 2);
        wall.offy = disFromTop * ((float)TEX_H / proj->wallprojheight);
		//printf("%d\n", wolf->t);
		wall.color = color[(TEX_W * wall.offy) + wall.offx];
		color1 = get_color2(wall.color, (light));
        wolf->colorbuffer[(WIDTH * j) + i] = color1;
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
			double bright = HEIGHT / (2.0 * j - HEIGHT);
			flor.color = clr.flor[(TEX_W * flor.tilerow) + flor.tilecol];
			color1 = get_color(flor.color, bright);
			wolf->colorbuffer[(WIDTH * j) + i] = color1;
		}
		j++;
	}
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
