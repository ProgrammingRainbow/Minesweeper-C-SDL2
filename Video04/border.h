#ifndef BORDER_H
#define BORDER_H

#include "main.h"

struct Border {
        SDL_Renderer *renderer;
        SDL_Texture *image;
        SDL_Rect *src_rects;
        unsigned rows;
        unsigned columns;
        int piece_height;
        int piece_width;
        int left_offset;
};

bool border_new(struct Border **border, SDL_Renderer *renderer, unsigned rows,
                unsigned columns);
void border_free(struct Border **border);
void border_draw(const struct Border *b);

#endif
