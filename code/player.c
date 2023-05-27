#include "player.h"

void prepare_player() {
    Game_Object player_rect = {.width = 64, .height = 64, .x = SCREEN_WIDTH / 2 - 64,
        .y = SCREEN_HEIGHT - 64};

    Player player_init = { .left_movement = 0, .right_movement = 0, .can_jump = 1,
        .max_health = 100, .health = 47 };
    player_init.player_rect = player_rect;

    player = player_init;
}

int render_player() {
    SDL_Rect fill_rect = { .w = player.player_rect.width, .h = player.player_rect.height,
        .x = player.player_rect.x, .y = player.player_rect.y };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &fill_rect);
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
        for(int i = 0; i < game_objects.length; i++) {
            Game_Object *object = game_objects.objects[i];
            // if(object->type == BLOCK && are_objects_overlapping(&player.player_rect, object)) {
                
            // }
        }

        x += 1;
        if(x == x_max) {
            player.can_jump = 1;
            x = 0;
        }

        player.player_rect.y = (SCREEN_HEIGHT - player.player_rect.height) - get_velocity(x, x_max);
    }
}
// Uses quadratic function
static int get_velocity(int x, int x_max) {
    return (int) (-((double)1 / 25) * x * (x - x_max));
}