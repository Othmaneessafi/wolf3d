/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oes-safi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 00:52:54 by oes-safi          #+#    #+#             */
/*   Updated: 2020/12/05 03:57:16 by cnaour           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
	return (1);
}

void	ft_free_int_tab(int **tab, int k)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
		{
			if (k)
				free(tab[i]);
			tab[i] = NULL;
			i++;
		}
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	sounds(t_wolf *wolf, char *music)
{
	Mix_PauseMusic();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	if (wolf->msc)
		Mix_FreeMusic(wolf->msc);
	wolf->msc = Mix_LoadMUS(music);
	Mix_PlayMusic(wolf->msc, 1);
}

void	destroy_window(t_wolf *wolf, t_player *player)
{
	if (wolf->colorbuffer)
		free(wolf->colorbuffer);
	if (wolf->pics)
		ft_free_tab(wolf->pics);
	if (wolf->map)
		ft_free_int_tab(wolf->map, 1);
	if (wolf->walltex)
		ft_free_int_tab(wolf->walltex, 0);
	if (wolf->renderer)
		SDL_DestroyRenderer(wolf->renderer);
	if (wolf->window)
		SDL_DestroyWindow(wolf->window);
	if (player->colorbuffertexture)
		SDL_DestroyTexture(player->colorbuffertexture);
	if (wolf->msc)
		Mix_FreeMusic(wolf->msc);
	SDL_Quit();
}

float	normalizeangle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return (angle);
}
