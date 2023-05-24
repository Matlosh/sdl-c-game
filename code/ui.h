#ifndef UI_H
#define UI_H

#include <SDL.h>
#include "variables.h"
#include "general.h"
#include "player.h"

typedef struct In_Game_UI_s {
    SDL_Texture *health_bar_empty;
    SDL_Texture *health_bar;
    int is_visible;
} In_Game_UI;

In_Game_UI in_game_ui;
SDL_Texture *text_texture;

// Creates and sets needed objects/texts/etc. for ui to work
void prepare_ui();
// Updates ui (health bar, etc.)
void update_ui();
// Renders all of the ui elements
void render_ui();

#endif