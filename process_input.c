#include "wolf3d.h"

void    process_input(wolf_t *wolf, player_t *player)
{
    SDL_Event e;

    SDL_PollEvent(&e);
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
    if (e.type == SDL_QUIT)
    {
            wolf->loop = FALSE;
    }
    else if(e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_ESCAPE)
            wolf->loop = FALSE;
        if (e.key.keysym.sym == SDLK_w)
            player->walkdirection = +1;
        if (e.key.keysym.sym == SDLK_s)
            player->walkdirection = -1;
        if (e.key.keysym.sym == SDLK_d)
            player->turndirection = +1;
        if (e.key.keysym.sym == SDLK_a)
            player->turndirection = -1;
        if (keyboard_state_array[SDL_SCANCODE_W] && (keyboard_state_array[SDL_SCANCODE_LSHIFT]))
            player->walkdirection = +2;
    }
    else if (e.type == SDL_KEYUP)
    {
        if (e.key.keysym.sym == SDLK_w)
            player->walkdirection = 0;
        if (e.key.keysym.sym == SDLK_LSHIFT)
            player->walkdirection = 0;
        if (e.key.keysym.sym == SDLK_s)
            player->walkdirection = 0;
        if (e.key.keysym.sym == SDLK_d)
            player->turndirection = 0;
        if (e.key.keysym.sym == SDLK_a)
            player->turndirection = 0;
    }
}