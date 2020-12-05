/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3d1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 03:16:58 by cnaour            #+#    #+#             */
/*   Updated: 2020/12/05 03:29:11 by cnaour           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			clearcolorbuffer(int *buffer, int color)
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

void			rendercolorbuffer(t_player *p, t_wolf *wolf)
{
	SDL_UpdateTexture(p->colorbuffertexture, NULL, wolf->colorbuffer,
			(int)(int)WIDTH * sizeof(int));
	SDL_RenderCopy(wolf->renderer, p->colorbuffertexture, NULL, NULL);
}

int				get_color(int color, double dist)
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

int				get_color2(int color, double dist)
{
	int r;
	int g;
	int b;

	r = ((color >> 16) & 255);
	g = ((color >> 8) & 255);
	b = (color & 255);
	r = (r * dist > 0.0) ? r * dist : 0;
	g = (g * dist > 0.0) ? g * dist : 0;
	b = (b * dist > 0.0) ? b * dist : 0;
	return ((r << 16) | (g << 8) | b);
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
			wall.color1 = rays[proj->i].rayright ? wolf->walltex[9] :
				wolf->walltex[8];
		}
		wall.offx = (int)rays[proj->i].wallhity % TILE_SIZE;
	}
	else
	{
		if (wolf->t == 1)
		{
			wall.color1 = rays[proj->i].rayup ? wolf->walltex[0] :
				wolf->walltex[1];
		}
		wall.offx = (int)rays[proj->i].wallhitx % TILE_SIZE;
	}
	if (wolf->t != 1)
		wall.color1 = clr.wall;
	return (wall);
}
