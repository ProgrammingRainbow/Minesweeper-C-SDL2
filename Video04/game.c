#include "game.h"
#include "init_sdl.h"

void game_events(struct Game *g);
void game_update(struct Game *g);
void game_draw(const struct Game *g);

bool game_new(struct Game **game) {
    *game = calloc(1, sizeof(struct Game));
    if (*game == NULL) {
        fprintf(stderr, "Error in calloc of new game.\n");
        return false;
    }
    struct Game *g = *game;

    g->is_running = true;
    g->rows = 9;
    g->columns = 9;

    if (!game_init_sdl(g)) {
        return false;
    }

    if (!border_new(&g->border, g->renderer, g->rows, g->columns)) {
        return false;
    }

    if (!board_new(&g->board, g->renderer, g->rows, g->columns)) {
        return false;
    }

    if (!mines_new(&g->mines, g->renderer)) {
        return false;
    }

    return true;
}

void game_free(struct Game **game) {
    if (*game) {
        struct Game *g = *game;

        border_free(&g->border);
        board_free(&g->board);
        mines_free(&g->mines);

        if (g->renderer) {
            SDL_DestroyRenderer(g->renderer);
            g->renderer = NULL;
        }

        if (g->window) {
            SDL_DestroyWindow(g->window);
            g->window = NULL;
        }

        IMG_Quit();
        SDL_Quit();

        g = NULL;

        free(*game);
        *game = NULL;

        printf("all clean!\n");
    }
}

void game_events(struct Game *g) {
    while (SDL_PollEvent(&g->event)) {
        switch (g->event.type) {
        case SDL_QUIT:
            g->is_running = false;
            break;
        case SDL_KEYDOWN:
            switch (g->event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                g->is_running = false;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void game_draw(const struct Game *g) {
    SDL_RenderClear(g->renderer);

    border_draw(g->border);
    board_draw(g->board);
    mines_draw(g->mines);

    SDL_RenderPresent(g->renderer);
}

void game_run(struct Game *g) {
    while (g->is_running) {

        game_events(g);

        game_draw(g);

        SDL_Delay(16);
    }
}
