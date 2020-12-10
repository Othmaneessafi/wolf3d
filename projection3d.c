/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:40:01 by cnaour            #+#    #+#             */
/*   Updated: 2020/12/05 04:15:27 by cnaour           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ceilingcast(t_projection *proj, t_wolf *wolf, t_ray *rays, t_player *p)
{
	int			j;
	t_choose	clr;
	t_texture	ceil;
	double		bright;

	j = -1;
	clr = choose_tex(wolf);
	while (++j < proj->walltopandbottom.x)
	{
		ceil.ratio = (TILE_SIZE - p->height) / (CENTERY - j);
		ceil.diago_distance = floor(proj->distprojplane * ceil.ratio /
				cos(rays[proj->i].rayangle - p->rotatangle));
		ceil.endx = floor(ceil.diago_distance * cos(rays[proj->i].rayangle));
		ceil.endy = floor(ceil.diago_distance * sin(rays[proj->i].rayangle));
		ceil.endy += p->y;
		ceil.endx += p->x;
		ceil.tilerow = (int)ceil.endy % TILE_SIZE;
		ceil.tilecol = (int)ceil.endx % TILE_SIZE;
		bright = HEIGHT / (2.0 * j - HEIGHT);
		ceil.color = clr.ceiling[(TEX_W * ceil.tilerow) + ceil.tilecol];
		wolf->colorbuffer[(WIDTH * j) + proj->i] =
			get_color(ceil.color, -1.0 * bright);
	}
}

void	floorcast(t_projection *proj, t_wolf *wolf, t_ray *rays, t_player *p)
{
	int			j;
	t_choose	clr;
	t_texture	flor;
	double		bright;

	clr = choose_tex(wolf);
	j = proj->walltopandbottom.y - 1;
	while (++j < HEIGHT)
	{
		flor.ratio = p->height / (j - CENTERY);
		flor.diago_distance = floor(proj->distprojplane * flor.ratio /
				cos(rays[proj->i].rayangle - p->rotatangle));
		flor.endy = floor(flor.diago_distance * sin(rays[proj->i].rayangle));
		flor.endx = floor(flor.diago_distance * cos(rays[proj->i].rayangle));
		flor.endy += p->y;
		flor.endx += p->x;
		flor.tilerow = (int)flor.endy % TILE_SIZE;
		flor.tilecol = (int)flor.endx % TILE_SIZE;
		bright = HEIGHT / (2.0 * j - HEIGHT);
		flor.color = clr.flor[(TEX_W * flor.tilerow) + flor.tilecol];
		wolf->colorbuffer[(WIDTH * j) + proj->i] =
			get_color(flor.color, bright);
	}
}

void	wallcast(t_projection *proj, t_wolf *wolf, t_ray *rays)
{
	double		light;
	int			disfromtop;
	int			color1;
	t_texture	wall;
	int			j;

	j = proj->walltopandbottom.x;
	wall = coloringwalls(wolf, rays, proj);
	light = 180 / rays[proj->i].distance;
	if (light > 0.883948)
		light = 0.883948;
	while (j < proj->walltopandbottom.y)
	{
		disfromtop = j + ((int)proj->wallprojheight / 2) - (HEIGHT / 2);
		wall.offy = disfromtop * ((float)TEX_H / proj->wallprojheight);
		color1 = get_color2(wall.color1[(TEX_W * wall.offy) + wall.offx],
				light);
		wolf->colorbuffer[(WIDTH * j) + proj->i] = color1;
		j++;
	}
}

void	coloring(t_ray *rays, t_wolf *wolf, t_projection *proj, t_player *p)
{
	ceilingcast(proj, wolf, rays, p);
	wallcast(proj, wolf, rays);
	floorcast(proj, wolf, rays, p);
}

void	generate3dprojection(t_ray *rays, t_player *player, t_wolf *wolf, int i)
{
	t_projection	*proj;

	if ((proj = malloc(sizeof(t_projection))) == NULL)
		destroy_window(wolf, player);
	while (++i < NUM_RAY)
	{
		rays[i].distance = rays[i].distance < 2 ? 2 : rays[i].distance;
		proj->perpdistance = rays[i].distance * cos(rays[i].rayangle -
				player->rotatangle);
		proj->distprojplane = (WIDTH / 2) / tan(FOVA / 2);
		proj->wallprojheight = (TILE_SIZE / proj->perpdistance) *
			proj->distprojplane;
		proj->walltopandbottom.x = (HEIGHT / 2) -
			((int)proj->wallprojheight / 2);
		proj->walltopandbottom.x = proj->walltopandbottom.x < 0 ? 0 :
			proj->walltopandbottom.x;
		proj->walltopandbottom.y = (HEIGHT / 2) +
			((int)proj->wallprojheight / 2);
		proj->walltopandbottom.y = proj->walltopandbottom.y > HEIGHT ? HEIGHT :
			proj->walltopandbottom.y;
		proj->i = i;
		coloring(rays, wolf, proj, player);
	}
	free(proj);
}
