#ifndef GENERAL_H
#define GENERAL_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <time.h>
#include "variables.h"

// Initializes the app - Returns 0 on success, otherwise 1
int init(SDL_Window **window, SDL_Renderer **renderer);
// Clears the resources
void close(SDL_Window **window, SDL_Renderer **renderer);
// Loads texture from the given path
SDL_Texture *load_texture(char *path);
// Creates text texture from the given path
SDL_Texture *create_text_texture(char *text, SDL_Color text_color);

#endif