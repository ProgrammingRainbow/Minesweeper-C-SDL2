#ifndef BOARD_H
#define BOARD_H

#include "main.h"

struct Board {
        SDL_Renderer *renderer;
        SDL_Texture *image;
        SDL_Rect *src_rects;
        unsigned **front_array;
        SDL_Rect rect;
        unsigned rows;
        unsigned columns;
        int scale;
        int piece_size;
};

bool board_new(struct Board **board, SDL_Renderer *renderer, unsigned rows,
               unsigned columns, int scale);
void board_free(struct Board **board);
bool board_reset(struct Board *b);
void board_set_scale(struct Board *b, int scale);
void board_draw(const struct Board *b);

#endif
