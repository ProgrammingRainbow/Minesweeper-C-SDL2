#include "face.h"
#include "load_media.h"

bool face_new(struct Face **face, SDL_Renderer *renderer, unsigned columns) {
    *face = calloc(1, sizeof(struct Face));
    if (!*face) {
        fprintf(stderr, "Error in calloc of new face.\n");
        return false;
    }
    struct Face *f = *face;

    f->renderer = renderer;
    f->columns = columns;

    f->dest_rect.x = ((PIECE_SIZE * (int)f->columns - FACE_SIZE) / 2 +
                      PIECE_SIZE - BORDER_LEFT) *
                     2;
    f->dest_rect.y = FACE_TOP * 2;
    f->dest_rect.w = FACE_SIZE * 2;
    f->dest_rect.h = FACE_SIZE * 2;

    if (!load_media_sheet(f->renderer, &f->image, "images/faces.png", FACE_SIZE,
                          FACE_SIZE, &f->src_rects)) {
        return false;
    }

    return true;
}

void face_free(struct Face **face) {
    if (*face) {
        struct Face *f = *face;

        if (f->src_rects) {
            free(f->src_rects);
            f->src_rects = NULL;
        }

        if (f->image) {
            SDL_DestroyTexture(f->image);
            f->image = NULL;
        }

        f->renderer = NULL;

        free(*face);
        *face = NULL;

        printf("face clean.\n");
    }
}

void face_draw(const struct Face *f) {
    SDL_RenderCopy(f->renderer, f->image, &f->src_rects[0], &f->dest_rect);
}
