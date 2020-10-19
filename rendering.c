# include "wolf3d.h"

void    rendermap(int **map, wolf_t *wolf)
{
    int i;
    int j;
    int tilex;
    int tiley;
    int tilecolor;
    SDL_Rect maprect;

    i = 0;
    while (i < ROWS)
    {
        j = 0;
        while (j < COLS)
        {
            tilex = j * TILE_SIZE;
            tiley = i * TILE_SIZE;
            tilecolor = map[i][j] != 0 ? 255 : 0;
            SDL_SetRenderDrawColor(wolf->renderer, tilecolor,
                        tilecolor, tilecolor, 255);
            maprect = (SDL_Rect){MM_SCALE * tilex, MM_SCALE * tiley,
                        MM_SCALE * TILE_SIZE,MM_SCALE * TILE_SIZE};
            SDL_RenderFillRect(wolf->renderer, &maprect);
            j++;
        }
        i++;
    }

}

void    renderplayer(player_t *player, wolf_t *wolf)
{
    SDL_Rect p_rect;

    SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
    p_rect = (SDL_Rect){MM_SCALE * player->x, MM_SCALE * player->y,
                MM_SCALE * player->width, MM_SCALE * player->height};
    SDL_RenderFillRect(wolf->renderer, &p_rect);
    SDL_RenderDrawLine(wolf->renderer, MM_SCALE * player->x, MM_SCALE * player->y,
                    MM_SCALE * (player->x + cos(player->rotatangle) * 40),
                    MM_SCALE * (player->y + sin(player->rotatangle) * 40));
}

void    renderays(ray_t *rays, wolf_t *wolf, player_t *player)
{
    int i = 0;
    SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
    //loat rayangle = player->rotatangle - (FOVA / 2);
    while(i < NUM_RAY)
    {
        (void)rays;
        SDL_RenderDrawLine(wolf->renderer, MM_SCALE * player->x, MM_SCALE * player->y,
                MM_SCALE * rays[i].wallhitx, MM_SCALE * rays[i].wallhity);
        i++;
    }
}

void    clearcolorbuffer(Uint32 *buffer, Uint32 color)
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

void    rendercolorbuffer(player_t *p, wolf_t *wolf)
{
    SDL_UpdateTexture(p->colorbuffertexture, NULL, wolf->colorbuffer,
                    (int)(Uint32)WIDTH * sizeof(Uint32));
    SDL_RenderCopy(wolf->renderer, p->colorbuffertexture, NULL, NULL);
}


void    generate3dprojection(ray_t *rays, player_t *player, wolf_t *wolf)
{
    int i;
    int j;
    int offX;
    int offY;
    int disFromTop;
    i = 0;
    while(i < NUM_RAY)
    {
        float   perpdistance = rays[i].distance * cos(rays[i].rayangle - player->rotatangle);
        float   distprojplane = (WIDTH / 2) / tan(FOVA / 2);
        float   wallprojheight = (TILE_SIZE / perpdistance) * distprojplane;


        int     wallTopPixel = (HEIGHT / 2) - ((int)wallprojheight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (HEIGHT / 2) + ((int)wallprojheight / 2);
        wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;
        j = 0;
        while (j < wallTopPixel)
        {
            wolf->colorbuffer[(WIDTH * j) + i] = 0xFFface87;
            j++;
        }

        if (rays[i].hitver)
            offX = (int)rays[i].wallhity % TILE_SIZE;
        else
            offX = (int)rays[i].wallhitx % TILE_SIZE;
        
        j = wallTopPixel;
        while (j < wallBottomPixel)
        {
            disFromTop = j + ((int)wallprojheight/2) - (HEIGHT / 2);
            offY = disFromTop * ((float)tex_h / wallprojheight);
            unsigned int texClr = wolf->walltex[(tex_w * offY) + offX];
            wolf->colorbuffer[(WIDTH * j) + i] = texClr;
            j++;
        }

        j = wallBottomPixel;
        while (j < HEIGHT)
        {
            wolf->colorbuffer[(WIDTH * j) + i] = 0xFF777777;
            j++;
        }
        i++;
    }
}

void    render(wolf_t   *wolf, player_t *player, int **map, ray_t *rays)//[NUM_RAY])
{
    SDL_SetRenderDrawColor(wolf->renderer, 0, 0, 0, 255);
    SDL_RenderClear(wolf->renderer);

    generate3dprojection(rays, player, wolf);
    rendercolorbuffer(player, wolf);
    clearcolorbuffer(wolf->colorbuffer, 0xFF000000);
    rendermap(map, wolf);
    renderays(rays, wolf, player);
    renderplayer(player, wolf);
    SDL_RenderPresent(wolf->renderer);
}