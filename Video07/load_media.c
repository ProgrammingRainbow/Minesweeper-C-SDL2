#include "load_media.h"

bool load_media_sheet(SDL_Renderer *renderer, SDL_Texture **image,
                      const char *file_path, int width, int height,
                      SDL_Rect **rects) {

    SDL_Surface *source_surf = IMG_Load(file_path);
    if (!source_surf) {
        fprintf(stderr, "Error creating the source surface: %s\n",
                SDL_GetError());
        return false;
    }

    int max_rows = source_surf->h / height;
    int max_columns = source_surf->w / width;
    size_t rects_length = (size_t)(max_rows * max_columns);

    *image = SDL_CreateTextureFromSurface(renderer, source_surf);
    SDL_FreeSurface(source_surf);
    if (!*image) {
        fprintf(stderr, "Error creating a image texture: %s\n", SDL_GetError());
        return false;
    }

    if (*rects) {
        free(*rects);
        *rects = NULL;
    }

    *rects = calloc(rects_length, sizeof(SDL_Rect));
    if (!*rects) {
        fprintf(stderr, "Error in calloc of image array.\n");
        return false;
    }

    for (int row = 0; row < max_rows; row++) {
        for (int column = 0; column < max_columns; column++) {
            int index = row * max_columns + column;
            (*rects)[index].x = column * width;
            (*rects)[index].y = row * height;
            (*rects)[index].w = width;
            (*rects)[index].h = height;
        }
    }

    return true;
}
