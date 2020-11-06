#include "wolf3d.h"

int     mapwall(int **map, float x, float y)
{
    int mapequx;
    int mapequy;

    if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
        return(TRUE);
    mapequx = floor(x / TILE_SIZE);
    mapequy = floor(y / TILE_SIZE);
    return(map[mapequy][mapequx] != 0);
}

void    playermove(int **map, float deltatime, player_t *player)
{
    float   movestep;
    float   newx;
    float   newy;
    player->rotatangle += player->turndirection *
                player->turnspeed * deltatime;
    movestep = player->walkdirection * player->walkspeed *
                deltatime;
    newx = player->x + movestep * cos(player->rotatangle);
    newy = player->y + movestep * sin(player->rotatangle);
    if(!mapwall(map, newx, newy))
    {
        player->x = newx;
        player->y = newy;

    }
}

void    update(int **map, float *ticks, player_t *player, ray_t rays[NUM_RAY])
{
    //int i = 0;

    while(!SDL_TICKS_PASSED(SDL_GetTicks(), *ticks + FRAME_TIME));
    float   deltatime = (SDL_GetTicks() - *ticks) / 1000.0f;
    *ticks = SDL_GetTicks();
    playermove(map, deltatime, player);
    //(void)rays;
    //printf("dkhal");
    castallrays(player, map, rays);
    //printf("khrj");
    /*while (i < NUM_RAY)
    {
        printf("%f\n", rays[i].distance);
        i++;
    }*/
    //update geme objects delta
}

