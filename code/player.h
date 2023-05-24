#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "variables.h"
#include "game_object.h"

int player_width, player_height, player_x_pos, player_y_pos;
// Movement variables
short int left_movement, right_movement, can_jump;
static int x, x_max;

// Sets and prepares player gameobject for rendering
int render_player();
// Checks for any keydown/up movement and makes player do things like movement etc.
void process_player_movement(SDL_Event *event);
// Moves player according to up, down, left, right movement and velocity
void move_player();
// Gets velocity (speed) in the x of the x_max
static int get_velocity(int x, int x_max);

#endif