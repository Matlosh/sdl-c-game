#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "variables.h"
#include "game_object.h"
#include "map.h"

typedef struct Player_s {
    Game_Object player_rect;
    // Movement variables
    short int left_movement, right_movement, can_jump;
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

#endif