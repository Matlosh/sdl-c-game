#include "player.h"

int player_width = 100;
int player_height = 100;
int player_x_pos = 450;
int player_y_pos = 600;
short int left_movement = 0;
short int right_movement = 0;
short int can_jump = 1;

int render_player() {
    SDL_Rect fillRect = { player_x_pos, player_y_pos, player_width, player_height };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &fillRect);
}

void process_player_movement(SDL_Event *event) {
    // Process keys
    switch(event->type) {
        case SDL_KEYDOWN:
            switch(event->key.keysym.sym) {
                case SDLK_w:
                    can_jump = 0;
                break;

                case SDLK_a:
                    left_movement = 1;
                break;

                case SDLK_d:
                    right_movement = 1;
                break;
            }
        break;

        case SDL_KEYUP:
            switch(event->key.keysym.sym) {
                case SDLK_a:
                    left_movement = 0;
                break;

                case SDLK_d:
                    right_movement = 0;
                break;
            }
        break;
    }
}

static int x = 0;
static int x_max = 130;

void move_player() {
    // left/right movement
    if(left_movement) {
        player_x_pos -= 5;
        // move_game_objects(-5, 0);
    }
    if(right_movement) {
        player_x_pos += 5;
        // move_game_objects(5, 0);
    }

    // jumping
    if(can_jump == 0) {
        x += 1;
        if(x == x_max) {
            can_jump = 1;
            x = 0;
        }

        player_y_pos = (SCREEN_HEIGHT - player_height) - get_velocity(x, x_max);
    }
}
// Uses quadratic function
static int get_velocity(int x, int x_max) {
    return (int) (-((double)1 / 25) * x * (x - x_max));
}