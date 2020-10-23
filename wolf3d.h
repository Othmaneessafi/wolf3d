#ifndef WOLF3D_H
# define WOLF3D_H

//constants
# define TRUE 1
# define FALSE 0
# define PI 3.14159265
# define TWO_PI 6.28318530
//map
# define TILE_SIZE 64
# define ROWS 13
# define COLS 20
//angle
# define FOVA (60 * (PI / 180))
//window
# define WIDTH (COLS * TILE_SIZE)
# define HEIGHT (ROWS * TILE_SIZE)
//time and frames
# define FPS 30
# define FRAME_TIME (1000/FPS)
//rays
# define WALL_STRIP_WIDTH 1
# define NUM_RAY WIDTH / WALL_STRIP_WIDTH
//scaling
# define MM_SCALE 0.2

//textures
# define tex_w 64
# define tex_h 64

//includes
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include "SDL/SDL2.framework/Headers/SDL.h"
# include "SDL/SDL2_image.framework/Headers/SDL_image.h"
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include "Get_Next_Line/get_next_line.h"
# include "Get_Next_Line/libft/libft.h"
# include "libpng/upng.h"

//game struct
typedef struct      wolf_s
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    int             loop;
    float           tickslastframe;
    uint32_t*       colorbuffer;
    uint32_t*       walltex;
    upng_t*         pngTex;
    char            **pics;
    //SDL_Texture     *colorbuffertexture;

}                   wolf_t;

//player struct
typedef struct      player_s
{
    float           x;
    float           y;
    float           width;
    float           height;
    int             turndirection;//-1 left. 1 right
    int             walkdirection;
    float           rotatangle;
    float           walkspeed;
    float           turnspeed;
    SDL_Texture     *colorbuffertexture;
}                   player_t;

//ray struct
typedef struct      ray_s
{
    int     stripId;
    float   rayangle;
    float   wallhitx;
    float   wallhity;
    float   distance;
    int     hitver;
    int     rayup;
    int     raydown;
    int     rayleft;
    int     rayright;
    int     wallhitcontent;
}                   ray_t;

//raycast results
typedef struct      results_s 
{
    int     foundhit;
    float   wallhitx;
    float   wallhity;
    int     content;  
}                   results_t;


int     init_window(wolf_t *wolf);
void    destroy_window(wolf_t *wolf);
void    process_input(wolf_t *wolf, player_t *player);
void    render(wolf_t   *wolf, player_t *player, int **map, ray_t *rays);//[NUM_RAY]);
void    update(int **map, float *ticks, player_t *player, ray_t *rays);//[NUM_RAY]);
float   normalizeangle(float angle);
float   distancecalc(float x1, float y1, float x2, float y2);
int     mapwall(int **map, float x, float y);
void    castallrays(player_t *player, int **map, ray_t *ray);//[NUM_RAY]);
int     **ft_check(int ac, char **av);
void    tex(wolf_t *wolf);
void    imgs(wolf_t *wolf);

#endif