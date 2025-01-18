#ifndef FACE_H
#define FACE_H

#include "main.h"

struct Face {
        SDL_Renderer *renderer;
        SDL_Texture *image;
        SDL_Rect *src_rects;
        SDL_Rect dest_rect;
        unsigned columns;
        int scale;
        unsigned image_index;
        unsigned theme;
};

bool face_new(struct Face **face, SDL_Renderer *renderer, unsigned columns,
              int scale);
void face_free(struct Face **face);
void face_set_scale(struct Face *f, int scale);
bool face_mouse_click(struct Face *f, int x, int y, bool down);
void face_default(struct Face *f);
void face_won(struct Face *f);
void face_lost(struct Face *f);
void face_question(struct Face *f);
void face_set_theme(struct Face *f, unsigned theme);
void face_set_size(struct Face *f, unsigned columns);
void face_draw(const struct Face *f);

#endif
