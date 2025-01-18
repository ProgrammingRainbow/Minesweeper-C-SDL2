#ifndef CLOCK_H
#define CLOCK_H

#include "main.h"

struct Clock {
        SDL_Renderer *renderer;
        SDL_Texture *back_image;
        SDL_Texture *digit_image;
        SDL_Rect *back_src_rects;
        SDL_Rect *digit_src_rects;
        SDL_Rect back_dest_rect;
        SDL_Rect digit_rect;
        unsigned columns;
        int scale;
        unsigned digits[3];
        unsigned seconds;
        Uint32 last_time;
        unsigned back_theme;
        unsigned digit_theme;
};

bool clock_new(struct Clock **clock, SDL_Renderer *renderer, unsigned columns,
               int scale);
void clock_free(struct Clock **clock);
void clock_reset(struct Clock *c);
void clock_set_scale(struct Clock *c, int scale);
void clock_set_theme(struct Clock *c, unsigned theme);
void clock_set_size(struct Clock *c, unsigned columns);
void clock_update(struct Clock *c);
void clock_draw(const struct Clock *c);

#endif
