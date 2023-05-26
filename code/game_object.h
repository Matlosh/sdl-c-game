#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <stdlib.h>
#include "general.h"
#include "player.h"

enum Game_Object_Type {
    BLOCK,
    BUTTON,
    EFFECT,
    GAME_OBJECT_TYPE_TOTAL
};

// All game objects available in the game
enum Game_Objects {
    TEST_OBJECT,
    GRASS_PLATFORM,
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
    // srcrect corresponds to the rect that is going to be clipped from the texture
    // f.e. this is useful when texture is a sprite
    SDL_Rect srcrect;
} Game_Object;

// Struct to help getting control of the all Game Objects
typedef struct Game_Objects_s {
    int length;
    Game_Object *objects;
} Game_Objects;

// All startup templates of the game objects (f.e. to clone and further use)
Game_Object game_objects_templates[GAME_OBJECTS_TOTAL];
// All currently available objects (not all visible/rendered on the screen, because
// some of them can be f.e. hidden)
Game_Objects game_objects;
static const char *game_objects_paths[GAME_OBJECTS_TOTAL];

// Loads single game object template to game_object_templates
// Parameters: game_object represent int of the object from the Game_Objects enum
static void load_game_object_template(int template_name, int width, int height, int x,
    int y, int is_rendered, int type);
// Loads all game objects' textures and returns 0 if successful, else 1
int load_game_objects();
// Moves all game objects in the x or y position
void move_game_objects(int x, int y);

#endif