#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "variables.h"
#include "game_object.h"
#include "map.h"

static enum COLLISION_DIRECTIONS {
    NO_COLLISION,
    COLLISION_TOP,
    COLLISION_RIGHT,
    COLLISION_BOTTOM,
    COLLISION_LEFT
};

typedef struct Player_s {
    Game_Object player_rect;
    // Movement variables
    short int left_movement, right_movement, can_jump;
    // stand_y is a position that the player now stands on (it changes when the player f.e. lands on a block
    // and is slightly different from the player_rect.y)
    int stand_y;
    // Gameplay related stats
    int max_health, health;
} Player;

Player player;
static int x, x_max;

// Sets Player object and sets all default (start) variables
void prepare_player();
// Sets and prepares player gameobject for rendering
int render_player();
// Checks for any keydown/up movement and makes player do things like movement etc.
void process_player_movement(SDL_Event *event);
// Moves player according to up, down, left, right movement and velocity
void move_player();
// Gets velocity (speed) in the x of the x_max
static int get_velocity(int x, int x_max);
// Checks on which direction of object_2 object_1 is collidiing with it
// Returns: 0 - no collision, 1 - collision on top, 2 - collision on right, 3  collision on bottom
// 4 - collision on right
static int get_collision_direction(Game_Object *object_1, Game_Object *object_2);

#endif