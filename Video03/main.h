#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL_FLAGS (SDL_INIT_VIDEO | SDL_INIT_AUDIO)
#define IMG_FLAGS IMG_INIT_PNG

#define WINDOW_TITLE "Minesweeper"
#define WINDOW_WIDTH 328
#define WINDOW_HEIGHT 414

#define PIECE_SIZE 16
#define BORDER_HEIGHT 55
#define BORDER_LEFT 4
#define BORDER_RIGHT 8
#define BORDER_BOTTOM 8

#endif
