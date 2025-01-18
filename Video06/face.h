#ifndef FACE_H
#define FACE_H

#include "main.h"

struct Face {
        SDL_Renderer *renderer;
        SDL_Texture *image;
        SDL_Rect *src_rects;
        SDL_Rect dest_rect;
        unsigned columns;
};

bool face_new(struct Face **face, SDL_Renderer *renderer, unsigned columns);
void face_free(struct Face **face);
void face_draw(const struct Face *f);

#endif
