#ifndef VARIABLES_H
#define VARIABLES_H

// Global variables that should be available in all files

#include <SDL.h>
#include <SDL_ttf.h>

const int SCREEN_WIDTH, SCREEN_HEIGHT;
SDL_Window *main_window;
SDL_Renderer *renderer;
TTF_Font *font;
int camera_x, camera_y;

#endif