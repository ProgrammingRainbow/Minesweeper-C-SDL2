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
        bool is_playing;
        unsigned rows;
        unsigned columns;
        int scale;
        int mine_count;
        double difficulty;
        char *size_str;
        char *diff_str;
};

bool game_new(struct Game **game);
void game_free(struct Game **game);
bool game_run(struct Game *g);

#endif
