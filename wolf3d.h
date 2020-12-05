/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnaour <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:11:30 by cnaour            #+#    #+#             */
/*   Updated: 2020/12/05 04:15:29 by cnaour           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define TRUE 1
# define FALSE 0
# define PI 3.14159265
# define TWO_PI 6.28318530
# define TILE_SIZE 64
# define ROWS 13
# define COLS 20
# define FOVA (60 * (PI / 180))
# define WIDTH (COLS * TILE_SIZE)
# define HEIGHT (ROWS * TILE_SIZE)
# define FPS 30
# define FRAME_TIME (1000/FPS)
# define WALL_STRIP_WIDTH 1
# define NUM_RAY WIDTH / WALL_STRIP_WIDTH
# define MM_SCALE 0.2
# define TEX_H 64
# define TEX_W 64
# define CENTERY HEIGHT / 2


# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include "SDL/SDL2.framework/Headers/SDL.h"
# include "SDL/SDL2_image.framework/Headers/SDL_image.h"
# include "SDL/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include "Get_Next_Line/get_next_line.h"
# include "Get_Next_Line/libft/libft.h"

typedef struct			s_player
{
	float				x;
	float				y;
	float			width;
	float			height;
	int				turndirection;
	int				walkdirection;
	float			rotatangle;
	float			walkspeed;
	float			turnspeed;
	SDL_Texture		*colorbuffertexture;
}						t_player;

typedef struct			s_wolf
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Surface     *surface;
	int				loop;
	float			tickslastframe;
	int				*colorbuffer;
	int				**map;
	char 			**pics;
	int 			**walltex;
	Mix_Music 		*msc;
	int				i;
	int				p;
	int				o;
	int				a;
	int				m;
	int				t;
}						t_wolf;


typedef struct			s_texture
{
	int				offx;
	int 			offy;
	int 	color;
	float			ratio;
	int				diago_distance;
	float			endx;
	float			endy;
	int				cellx;
	int				celly;
	int				tilerow;
	int				tilecol;
	int				*color1;
}						t_texture;

typedef struct			s_ray
{
	int		stripid;
	float	rayangle;
	float	wallhitx;
	float	wallhity;
	float	distance;
	int		hitver;
	int		rayup;
	int		raydown;
	int		rayleft;
	int		rayright;
	int		wallhitcontent;
}						t_ray;

typedef struct			s_results
{
	int		foundhit;
	float	wallhitx;
	float	wallhity;
	int		content;
}						t_results;

typedef struct			s_cords
{
	float		x;
	float		y;
}						t_cords;

typedef struct			s_projection
{
	float	perpdistance;
	float	distprojplane;
	float	wallprojheight;
	int		i;
	t_cords	walltopandbottom;

}						t_projection;

typedef struct			s_choose
{
	int	*flor;
	int	*wall;
	int	*ceiling;

}						t_choose;

void                    clearcolorbuffer(int *buffer, int color);
void                    rendercolorbuffer(t_player *p, t_wolf *wolf);
int                     get_color(int color, double dist);
int                     get_color2(int color, double dist);
t_texture               coloringwalls(t_wolf *wolf, t_ray *rays, t_projection *proj);

int						init_window(t_wolf *wolf);
void					destroy_window(t_wolf *wolf, t_player *player);
void					process_input(t_wolf *wolf, t_player *player);
void					render(t_wolf *wolf, t_player *player, int **map,
		t_ray *rays);
void					update(int **map, float *ticks, t_player *player,
		t_ray *rays);
float					normalizeangle(float angle);
float					distancecalc(float x1, float y1, float x2, float y2);
int						mapwall(int **map, float x, float y);
void					castallrays(t_player *player, int **map, t_ray *ray);
int						ft_check(char **av, t_wolf *wolf, int i, int j);
void					clearcolorbuffer(int *buffer, int color);
void					rendercolorbuffer(t_player *p, t_wolf *wolf);
void					generate3dprojection(t_ray *rays, t_player *player,
		t_wolf *wolf, int i);
void					init_raycasting_results(t_results *res);
t_results				looping_hor_cast(t_cords intercept, t_cords step,
		t_ray *ray, int **map);
t_results				looping_ver_cast(t_cords intercept, t_cords step,
		t_ray *ray, int **map);
void    				imgs(t_wolf *wolf, t_player *player);
void					textures(t_wolf *wolf, t_player *player);
void					convert_data_img(int *tab, int range);
void					sounds(t_wolf *wolf, char *music);
void 					background(t_wolf *wolf);
t_choose				choose_tex(t_wolf *wolf);
void					ft_free_tab(char **tab);
void					ft_free_int_tab(int **tab, int k);
void 					menu(t_wolf *wolf, t_player *player, t_ray *rays);
void 					menu1(t_wolf *wolf, int x, int y);
void 					menu2(t_wolf *wolf, int x, int y);
void					input(t_wolf *wolf);
void					input1(t_wolf *wolf);
#endif
