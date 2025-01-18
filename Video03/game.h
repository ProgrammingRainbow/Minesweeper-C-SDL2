#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "border.h"
#include "board.h"

struct Game {
        SDL_Event event;
        SDL_Window *window;
        SDL_Renderer *renderer;
        struct Border *border;
        struct Board *board;
        bool is_running;
        unsigned rows;
        unsigned columns;
};

bool game_new(struct Game **game);
void game_free(struct Game **game);
void game_run(struct Game *g);

#endif
