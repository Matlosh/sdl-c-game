#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <stdlib.h>
#include <string.h>
#include "game_object.h"

// Loads all needed map elements; Returns 0 if successful, else 1
int load_map();
// Renders the current map onto the screen
void render_map();

#endif