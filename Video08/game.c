#include "game.h"
#include "init_sdl.h"

bool game_reset(struct Game *g);
void game_set_scale(struct Game *g);
void game_toggel_scale(struct Game *g);
void game_mouse_down(struct Game *g, int x, int y, Uint8 button);
bool game_mouse_up(struct Game *g, int x, int y, Uint8 button);
bool game_events(struct Game *g);
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
    g->scale = 2;
    g->mine_count = 7;

    if (!game_init_sdl(g)) {
        return false;
    }

    if (!border_new(&g->border, g->renderer, g->rows, g->columns, g->scale)) {
        return false;
    }

    if (!board_new(&g->board, g->renderer, g->rows, g->columns, g->scale,
                   g->mine_count)) {
        return false;
    }

    if (!mines_new(&g->mines, g->renderer, g->scale)) {
        return false;
    }

    if (!clock_new(&g->clock, g->renderer, g->columns, g->scale)) {
        return false;
    }

    if (!face_new(&g->face, g->renderer, g->columns, g->scale)) {
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
        clock_free(&g->clock);
        face_free(&g->face);

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

bool game_reset(struct Game *g) {

    if (!board_reset(g->board)) {
        return false;
    }

    return true;
}

void game_set_scale(struct Game *g) {
    border_set_scale(g->border, g->scale);
    board_set_scale(g->board, g->scale);
    mines_set_scale(g->mines, g->scale);
    clock_set_scale(g->clock, g->scale);
    face_set_scale(g->face, g->scale);

    int window_width =
        (PIECE_SIZE * ((int)g->columns + 1) - BORDER_LEFT + BORDER_RIGHT) *
        g->scale;
    int window_height =
        (PIECE_SIZE * ((int)g->rows) + BORDER_HEIGHT + BORDER_BOTTOM) *
        g->scale;
    SDL_SetWindowSize(g->window, window_width, window_height);
    SDL_SetWindowPosition(g->window, SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED);
}

void game_toggel_scale(struct Game *g) {
    g->scale = (g->scale == 1) ? 2 : (g->scale == 2) ? 3 : 1;
    game_set_scale(g);
}

void game_mouse_down(struct Game *g, int x, int y, Uint8 button) {
    if (button == SDL_BUTTON_LEFT) {
        face_mouse_click(g->face, x, y, true);
    }
}

bool game_mouse_up(struct Game *g, int x, int y, Uint8 button) {
    if (button == SDL_BUTTON_LEFT) {
        if (face_mouse_click(g->face, x, y, false)) {
            if (!game_reset(g)) {
                return false;
            }
        }
    }

    face_default(g->face);

    return true;
}

bool game_events(struct Game *g) {
    while (SDL_PollEvent(&g->event)) {
        switch (g->event.type) {
        case SDL_QUIT:
            g->is_running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            game_mouse_down(g, g->event.button.x, g->event.button.y,
                            g->event.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            if (!game_mouse_up(g, g->event.button.x, g->event.button.y,
                               g->event.button.button)) {
                return false;
            }
            break;
        case SDL_KEYDOWN:
            switch (g->event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                g->is_running = false;
                break;
            case SDL_SCANCODE_B:
                game_toggel_scale(g);
                break;
            case SDL_SCANCODE_N:
                if (!game_reset(g)) {
                    return false;
                }
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    return true;
}

void game_draw(const struct Game *g) {
    SDL_RenderClear(g->renderer);

    border_draw(g->border);
    board_draw(g->board);
    mines_draw(g->mines);
    clock_draw(g->clock);
    face_draw(g->face);

    SDL_RenderPresent(g->renderer);
}

bool game_run(struct Game *g) {
    while (g->is_running) {

        if (!game_events(g)) {
            return false;
        }

        game_draw(g);

        SDL_Delay(16);
    }

    return true;
}
