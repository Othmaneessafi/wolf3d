/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:44:54 by cnaour            #+#    #+#             */
/*   Updated: 2020/10/18 04:48:28 by cnaour           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		init_raycasting_results(t_results *res)
{
	res->foundhit = FALSE;
	res->wallhitx = 0;
	res->wallhity = 0;
	res->content = 0;
}

t_results	looping_hor_cast(t_cords intercept, t_cords step,
		t_ray *ray, int **map)
{
	t_cords		hortouch;
	t_results	res;
	t_cords		check;

	hortouch = (t_cords){.x = intercept.x, .y = intercept.y};
	init_raycasting_results(&res);
	while (hortouch.x >= 0 && hortouch.x <= WIDTH &&
			hortouch.y >= 0 && hortouch.y <= HEIGHT)
	{
		check = (t_cords){hortouch.x, hortouch.y + (ray->rayup ? -1 : 0)};
		if (mapwall(map, check.x, check.y))
		{
			res = (t_results){.wallhitx = hortouch.x, .wallhity = hortouch.y};
			res.content = map[(int)floor(check.y / TILE_SIZE)][(int)
				floor(check.x / TILE_SIZE)];
			res.foundhit = TRUE;
			break ;
		}
		else
		{
			hortouch.x += step.x;
			hortouch.y += step.y;
		}
	}
	return (res);
}

t_results	looping_ver_cast(t_cords intercept, t_cords step,
		t_ray *ray, int **map)
{
	t_cords		vertouch;
	t_results	res;
	t_cords		check;

	vertouch = (t_cords){.x = intercept.x, .y = intercept.y};
	init_raycasting_results(&res);
	while (vertouch.x >= 0 && vertouch.x <= WIDTH &&
			vertouch.y >= 0 && vertouch.y <= HEIGHT)
	{
		check = (t_cords){vertouch.x + (ray->rayleft ? -1 : 0), vertouch.y};
		if (mapwall(map, check.x, check.y))
		{
			res = (t_results){.wallhitx = vertouch.x, .wallhity = vertouch.y};
			res.content = map[(int)floor(check.y / TILE_SIZE)][(int)
				floor(check.x / TILE_SIZE)];
			res.foundhit = TRUE;
			break ;
		}
		else
		{
			vertouch.x += step.x;
			vertouch.y += step.y;
		}
	}
	return (res);
}
