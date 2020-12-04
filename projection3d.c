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

void		ceilingcast(t_projection *proj, t_wolf *wolf, t_ray *rays, t_player *p)
{
	int			j;
	t_choose	clr;	
	t_texture   ceil;
	int color1;


	j = 0;
	clr = choose_tex(wolf);
	while (j < proj->walltopandbottom.x)
	{
		
		ceil.ratio = (TILE_SIZE - p->height) / (CENTERY - j);
		ceil.diago_distance = floor(proj->distprojplane * ceil.ratio / cos(rays[proj->i].rayangle - p->rotatangle));
		ceil.endx = floor(ceil.diago_distance * cos(rays[proj->i].rayangle));
		ceil.endy = floor(ceil.diago_distance * sin(rays[proj->i].rayangle));
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
			wolf->colorbuffer[(WIDTH * j) + proj->i] = color1;
		}
		j++;
	}

}

void		floorcast(t_projection *proj, t_wolf *wolf, t_ray *rays, t_player *p)
{
	int			j;
	t_choose	clr;	
	t_texture   flor;
	int color1;


	clr = choose_tex(wolf);
	j = proj->walltopandbottom.y;
	while (j < HEIGHT)
	{
		flor.ratio = p->height / (j - CENTERY);
		flor.diago_distance = floor(proj->distprojplane * flor.ratio / cos(rays[proj->i].rayangle - p->rotatangle));
		flor.endy = floor(flor.diago_distance * sin(rays[proj->i].rayangle));
		flor.endx = floor(flor.diago_distance * cos(rays[proj->i].rayangle));
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
			wolf->colorbuffer[(WIDTH * j) + proj->i] = color1;
		}
		j++;
	}

}

t_texture		coloringwalls(t_wolf *wolf, t_ray *rays, t_projection *proj)
{
	t_choose	clr;
	t_texture	wall;

	clr = choose_tex(wolf);
	if (rays[proj->i].hitver)
	{
		if (wolf->t == 1)
		{
			if (rays[proj->i].rayright)
				wall.color1 = wolf->walltex[9];
			else if (rays[proj->i].rayleft)
				wall.color1 = wolf->walltex[8];
		}
		wall.offx = (int)rays[proj->i].wallhity % TILE_SIZE;
	}
	else
	{
		if (wolf->t == 1)
		{
			if (rays[proj->i].rayup)
				wall.color1 = wolf->walltex[0];
			else if (rays[proj->i].raydown)
				wall.color1 = wolf->walltex[1];
		}
		wall.offx = (int)rays[proj->i].wallhitx % TILE_SIZE;
	}
	if (wolf->t != 1)
		wall.color1 = clr.wall;
	return (wall);
}

void		wallcast(t_projection *proj, t_wolf *wolf, t_ray *rays)
{
	double light;
	int disFromTop;
	int color1;
	t_texture	wall;
	int j;
	
	j = proj->walltopandbottom.x;
	wall = coloringwalls(wolf, rays, proj);
	light = 180/rays[proj->i].distance;
	if (light > 0.883948)
		light = 0.883948;
	while (j < proj->walltopandbottom.y)
	{
        disFromTop = j + ((int)proj->wallprojheight/2) - (HEIGHT / 2);
        wall.offy = disFromTop * ((float)TEX_H / proj->wallprojheight);
		color1 = get_color2(wall.color1[(TEX_W * wall.offy) + wall.offx], (light));
        wolf->colorbuffer[(WIDTH * j) + proj->i] = color1;
		j++;
	}

}

void		coloring(t_ray *rays, t_wolf *wolf, t_projection *proj, t_player *p)
{
	ceilingcast(proj, wolf, rays, p);
	wallcast(proj, wolf, rays);
	floorcast(proj, wolf, rays, p);
}	

void		generate3dprojection(t_ray *rays, t_player *player, t_wolf *wolf)
{
	int				i;
	t_projection	*proj;

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
		proj->walltopandbottom.x = (HEIGHT / 2) - ((int)proj->wallprojheight / 2);
		proj->walltopandbottom.x = proj->walltopandbottom.x < 0 ? 0 : proj->walltopandbottom.x;
		proj->walltopandbottom.y = (HEIGHT / 2) + ((int)proj->wallprojheight / 2);
		proj->walltopandbottom.y = proj->walltopandbottom.y > HEIGHT ? HEIGHT :
			proj->walltopandbottom.y;
		proj->i = i;
		coloring(rays, wolf, proj, player);
		i++;
	}
}
