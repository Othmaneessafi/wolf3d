/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:30:51 by cnaour            #+#    #+#             */
/*   Updated: 2020/10/18 01:38:49 by cnaour           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			found_distance(t_results *hor, t_results *ver, t_ray *ray,
		t_player *player)
{
	float	horzhitdistance;
	float	verthitdistance;

	horzhitdistance = hor->foundhit
		? distancecalc(player->x, player->y, hor->wallhitx, hor->wallhity)
		: INT_MAX;
	verthitdistance = ver->foundhit
		? distancecalc(player->x, player->y, ver->wallhitx, ver->wallhity)
		: INT_MAX;
	if (verthitdistance < horzhitdistance)
	{
		ray->distance = verthitdistance;
		ray->wallhitx = ver->wallhitx;
		ray->wallhity = ver->wallhity;
		ray->wallhitcontent = ver->content;
		ray->hitver = TRUE;
	}
	else
	{
		ray->distance = horzhitdistance;
		ray->wallhitx = hor->wallhitx;
		ray->wallhity = hor->wallhity;
		ray->wallhitcontent = hor->content;
		ray->hitver = FALSE;
	}
}

t_results		horz_cast(t_ray *ray, t_player *player, int **map)
{
	t_cords		intercept;
	t_cords		step;
	t_results	res;

	init_raycasting_results(&res);
	intercept.y = floor(player->y / TILE_SIZE) * TILE_SIZE;
	intercept.y += ray->raydown ? TILE_SIZE : 0;
	intercept.x = player->x + (intercept.y - player->y) / tan(ray->rayangle);
	step.y = TILE_SIZE;
	step.y *= ray->rayup ? -1 : 1;
	step.x = TILE_SIZE / tan(ray->rayangle);
	step.x *= (ray->rayleft && step.x > 0) ? -1 : 1;
	step.x *= (ray->rayright && step.x < 0) ? -1 : 1;
	res = looping_hor_cast(intercept, step, ray, map);
	return (res);
}

t_results		ver_cast(t_ray *ray, t_player *player, int **map)
{
	t_cords		intercept;
	t_cords		step;
	t_results	res;

	init_raycasting_results(&res);
	intercept.x = floor(player->x / TILE_SIZE) * TILE_SIZE;
	intercept.x += ray->rayright ? TILE_SIZE : 0;
	intercept.y = player->y + (intercept.x - player->x) * tan(ray->rayangle);
	step.x = TILE_SIZE;
	step.x *= ray->rayleft ? -1 : 1;
	step.y = TILE_SIZE * tan(ray->rayangle);
	step.y *= (ray->rayup && step.y > 0) ? -1 : 1;
	step.y *= (ray->raydown && step.y < 0) ? -1 : 1;
	res = looping_ver_cast(intercept, step, ray, map);
	return (res);
}

void			castray(int stripid, t_player *player, int **map, t_ray *rays)
{
	t_results horresult;
	t_results verresult;

	rays[stripid].raydown = rays[stripid].rayangle > 0 &&
		rays[stripid].rayangle < PI;
	rays[stripid].rayup = !rays[stripid].raydown;
	rays[stripid].rayright = rays[stripid].rayangle < 0.5 * PI ||
		rays[stripid].rayangle > 1.5 * PI;
	rays[stripid].rayleft = !rays[stripid].rayright;
	init_raycasting_results(&horresult);
	horresult = horz_cast(&rays[stripid], player, map);
	init_raycasting_results(&verresult);
	verresult = ver_cast(&rays[stripid], player, map);
	found_distance(&horresult, &verresult, &rays[stripid], player);
}

void			castallrays(t_player *player, int **map, t_ray *rays)
{
	float	rayangle;
	int		col_id;

	rayangle = player->rotatangle - (FOVA / 2);
	col_id = 0;
	while (col_id < NUM_RAY)
	{
		rays[col_id].rayangle = normalizeangle(rayangle);
		castray(col_id, player, map, rays);
		rayangle += FOVA / NUM_RAY;
		col_id++;
	}
}
