#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include "general.h"
#include "player.h"

enum Game_Object_Type {
    BLOCK,
    BUTTON,
    EFFECT,
    GAME_OBJECT_TYPE_TOTAL
};

enum Game_Objects {
    TEST_OBJECT,
    GAME_OBJECTS_TOTAL
};

typedef struct Game_Object_s {
    int type;
    SDL_Texture *texture;
    // x and y are the coordinates where the game object is/should be
    // currently rendered 
    int width, height, x, y;
    // 0 -> is not rendered; 1 -> is rendered
    int is_rendered;
} Game_Object;

Game_Object game_objects[GAME_OBJECTS_TOTAL];
static const char *game_objects_paths[GAME_OBJECTS_TOTAL];

// Loads all game objects' textures and returns 0 if successful, else 1
int load_game_objects();
// Renders all game objects onto the screen
void render_game_objects();
// Moves all game objects in the x or y position
void move_game_objects(int x, int y);

#endif