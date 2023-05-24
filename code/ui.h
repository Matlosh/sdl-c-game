#ifndef UI_H
#define UI_H

#include <SDL.h>
#include "variables.h"
#include "general.h"

SDL_Texture *text_texture;

// Creates and sets needed objects/texts/etc. for ui to work
void prepare_ui();
// Renders all of the ui elements
void render_ui();

#endif