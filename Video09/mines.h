#ifndef MINES_H
#define MINES_H

#include "main.h"

struct Mines {
        SDL_Renderer *renderer;
        SDL_Texture *back_image;
        SDL_Texture *digit_image;
        SDL_Rect *back_src_rects;
        SDL_Rect *digit_src_rects;
        SDL_Rect back_dest_rect;
        SDL_Rect digit_rect;
        int scale;
};

bool mines_new(struct Mines **mines, SDL_Renderer *renderer, int scale);
void mines_free(struct Mines **mines);
void mines_set_scale(struct Mines *m, int scale);
void mines_draw(const struct Mines *m);

#endif
