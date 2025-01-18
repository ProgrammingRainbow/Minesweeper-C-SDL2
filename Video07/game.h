#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "border.h"
#include "board.h"
#include "mines.h"
#include "clock.h"
#include "face.h"

struct Game {
        SDL_Event event;
        SDL_Window *window;
        SDL_Renderer *renderer;
        struct Border *border;
        struct Board *board;
        struct Mines *mines;
        struct Clock *clock;
        struct Face *face;
        bool is_running;
        unsigned rows;
        unsigned columns;
        int scale;
};

bool game_new(struct Game **game);
void game_free(struct Game **game);
void game_run(struct Game *g);

#endif
