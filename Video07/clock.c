#include "clock.h"
#include "load_media.h"

void clock_update_digits(struct Clock *c);

bool clock_new(struct Clock **clock, SDL_Renderer *renderer, unsigned columns,
               int scale) {
    *clock = calloc(1, sizeof(struct Clock));
    if (!*clock) {
        fprintf(stderr, "Error in calloc of new clock.\n");
        return false;
    }
    struct Clock *c = *clock;

    c->renderer = renderer;
    c->columns = columns;
    c->scale = scale;

    if (!load_media_sheet(c->renderer, &c->back_image, "images/digitback.png",
                          DIGIT_BACK_WIDTH, DIGIT_BACK_HEIGHT,
                          &c->back_src_rects)) {
        return false;
    }

    if (!load_media_sheet(c->renderer, &c->digit_image, "images/digits.png",
                          DIGIT_WIDTH, DIGIT_HEIGHT, &c->digit_src_rects)) {
        return false;
    }

    clock_set_scale(c, c->scale);

    return true;
}

void clock_free(struct Clock **clock) {
    if (*clock) {
        struct Clock *c = *clock;

        if (c->back_src_rects) {
            free(c->back_src_rects);
            c->back_src_rects = NULL;
        }

        if (c->back_image) {
            SDL_DestroyTexture(c->back_image);
            c->back_image = NULL;
        }

        if (c->digit_src_rects) {
            free(c->digit_src_rects);
            c->digit_src_rects = NULL;
        }

        if (c->digit_image) {
            SDL_DestroyTexture(c->digit_image);
            c->digit_image = NULL;
        }

        c->renderer = NULL;

        free(*clock);
        *clock = NULL;

        printf("clock clean.\n");
    }
}

void clock_set_scale(struct Clock *c, int scale) {
    c->scale = scale;
    c->back_dest_rect.x = (PIECE_SIZE * ((int)c->columns + 1) - BORDER_LEFT -
                           DIGIT_BACK_WIDTH - DIGIT_BACK_RIGHT) *
                          c->scale;
    c->back_dest_rect.y = DIGIT_BACK_TOP * c->scale;
    c->back_dest_rect.w = DIGIT_BACK_WIDTH * c->scale;
    c->back_dest_rect.h = DIGIT_BACK_HEIGHT * c->scale;
    c->digit_rect.x = c->back_dest_rect.x + c->scale;
    c->digit_rect.y = DIGIT_BACK_TOP * c->scale + c->scale;
    c->digit_rect.w = DIGIT_WIDTH * c->scale;
    c->digit_rect.h = DIGIT_HEIGHT * c->scale;
}

void clock_draw(const struct Clock *c) {
    SDL_RenderCopy(c->renderer, c->back_image, &c->back_src_rects[0],
                   &c->back_dest_rect);
    SDL_Rect dest_rect = {c->digit_rect.x, c->digit_rect.y, c->digit_rect.w,
                          c->digit_rect.h};
    for (int i = 0; i < 3; i++) {
        dest_rect.x = c->digit_rect.x + c->digit_rect.w * i;
        SDL_RenderCopy(c->renderer, c->digit_image, &c->digit_src_rects[0],
                       &dest_rect);
    }
}
