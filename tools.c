#include "wolf3d.h"

int   init_window(wolf_t *wolf)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Initialisation error\n");
        return (FALSE);
    }
    wolf->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (!wolf->window)
    {
        printf("Error creating window\n");
        return (FALSE);
    }
    wolf->renderer = SDL_CreateRenderer(wolf->window, -1, 0);
    if (!wolf->renderer)
    {
        printf("Error creating renderer\n");
        return (FALSE);
    }
    return (TRUE);
}

void    destroy_window(wolf_t *wolf)
{
    free(wolf->walltex);
    free (wolf->colorbuffer);
    SDL_DestroyRenderer(wolf->renderer);
    SDL_DestroyWindow(wolf->window);
    SDL_Quit();
}

float   normalizeangle(float angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0)
    {
        angle = TWO_PI + angle;
    }
    return (angle);
}

float   distancecalc(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void    tex(wolf_t *wolf)
{
    if (wolf->pngTex != NULL)
    {
        upng_decode(wolf->pngTex);
        if (upng_get_error(wolf->pngTex) == UPNG_EOK)
            wolf->walltex = (uint32_t *)upng_get_buffer(wolf->pngTex);
        
    }
}
