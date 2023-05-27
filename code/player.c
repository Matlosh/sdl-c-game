#include "player.h"

void prepare_player() {
    Player player_init = {.player_width = 64, .player_height = 64,
        .player_x_pos = SCREEN_WIDTH / 2 - (100 / 2),
        .player_y_pos = SCREEN_HEIGHT - 64,
        .left_movement = 0, .right_movement = 0, .can_jump = 1,
        .max_health = 100, .health = 47};
    player = player_init;
}

int render_player() {
    SDL_Rect fillRect = { player.player_x_pos, player.player_y_pos, player.player_width, player.player_height };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &fillRect);
}

void process_player_movement(SDL_Event *event) {
    // Process keys
    switch(event->type) {
        case SDL_KEYDOWN:
            switch(event->key.keysym.sym) {
                case SDLK_w:
                    player.can_jump = 0;
                break;

                case SDLK_a:
                    player.left_movement = 1;
                break;

                case SDLK_d:
                    player.right_movement = 1;
                break;
            }
        break;

        case SDL_KEYUP:
            switch(event->key.keysym.sym) {
                case SDLK_a:
                    player.left_movement = 0;
                break;

                case SDLK_d:
                    player.right_movement = 0;
                break;
            }
        break;
    }
}

static int x = 0;
static int x_max = 150;

void move_player() {
    // left/right movement
    if(player.left_movement) {
        // camera_x -= 5;
        // player_x_pos -= 5;
        move_game_objects(-5, 0);
    }
    if(player.right_movement) {
        // camera_x += 5;
        // player_x_pos += 5;
        // decide whether to use camera_x or moving game objects technique
        move_game_objects(5, 0);
    }

    // jumping
    if(player.can_jump == 0) {
        x += 1;
        if(x == x_max) {
            player.can_jump = 1;
            x = 0;
        }

        player.player_y_pos = (SCREEN_HEIGHT - player.player_height) - get_velocity(x, x_max);
    }
}
// Uses quadratic function
static int get_velocity(int x, int x_max) {
    return (int) (-((double)1 / 25) * x * (x - x_max));
}