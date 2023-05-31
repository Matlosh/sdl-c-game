#include "player.h"

void prepare_player() {
    Game_Object *player_rect = malloc(sizeof(Game_Object));
    player_rect->width = 64;
    player_rect->height = 64;
    player_rect->x = SCREEN_WIDTH / 2 - 64;
    player_rect->y = SCREEN_HEIGHT - 64;

    Player player_init = { .left_movement = 0, .right_movement = 0, .can_jump = 1,
        .max_health = 10, .health = 4, .stand_y = SCREEN_HEIGHT - player_rect->height };
    player_init.player_rect = player_rect;

    player = player_init;
}

int render_player() {
    SDL_Rect fill_rect = { .w = player.player_rect->width, .h = player.player_rect->height,
        .x = player.player_rect->x, .y = player.player_rect->y };
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
    int can_fall = 1;
    for(int i = 0; i < game_objects.length; i++) {
        Game_Object *object = game_objects.objects[i];

        if(object->type == BLOCK && (get_collision_direction(player.player_rect, object) == 1))
            can_fall = 0;

        if(object->type == BLOCK && are_objects_overlapping(player.player_rect, object)) {
            switch(get_collision_direction(player.player_rect, object)) {
                case COLLISION_TOP:
                    player.player_rect->y = object->y - player.player_rect->height;
                    player.stand_y = object->y - player.player_rect->height;
                    x = 0;
                    player.can_jump = 1;
                break;

                case COLLISION_RIGHT: break;

                case COLLISION_BOTTOM: break;

                case COLLISION_LEFT: break;

                default: break;
            }
        }

        // Using effects on collision/overlapping/etc.
        if(are_objects_overlapping(player.player_rect, object) && !object->did_use_effect) {
            for(int j = 0; j < object->interaction_effects.effects_count; j++)
                object->interaction_effects.custom_effects[j](object, &player);
            object->did_use_effect = 1;
        }
    }

    // left/right movement
    if(player.left_movement) {
        move_game_objects(-5, 0);
        camera_x += -5;
    }

    if(player.right_movement) {
        move_game_objects(5, 0);
        camera_x += 5;
    }

    if(player.can_jump && can_fall && player.player_rect->y + player.player_rect->height < SCREEN_HEIGHT) {
        player.player_rect->y += 6;
        player.stand_y += 6;
    }

    // jumping
    if(player.can_jump == 0) {
        if(player.player_rect->y >= SCREEN_HEIGHT) {
            player.can_jump = 1;
            x = 0;
        }

        x += 1;
        if(x == x_max) {
            player.can_jump = 1;
            x = 0;
        }

        player.player_rect->y = player.stand_y - get_velocity(x, x_max);
    }

}
// Uses quadratic function
static int get_velocity(int x, int x_max) {
    return (int) (-((double)1 / 25) * x * (x - x_max));
}

static int get_collision_direction(Game_Object *object_1, Game_Object *object_2) {
    if(object_1->y + object_1->height <= object_2->y + 4 && object_1->y + object_1->height >= object_2->y &&
        abs(object_2->x - object_1->x) < 64)
        return COLLISION_TOP;

    if(object_1->x >= object_2->x + object_2->width - 4 && object_1->x <= object_2->x + object_2->width + 4 &&
        (object_2->y - object_1->y < object_1->height &&
        object_1->y + object_1->height - object_2->y + object_2->height < object_1->height ))
        return COLLISION_RIGHT;

    if(object_1->y >= object_2->y + object_2->height - 4 && object_1->y <= object_2->y + object_2->height + 4 &&
        abs(object_2->x - object_1->x) < 64)
        return COLLISION_BOTTOM;

    if(object_1->x + object_1->width <= object_2->x + 4 && object_1->x + object_1->width >= object_2->x - 4 &&
        (object_2->y - object_1->y < object_1->height &&
        object_1->y + object_1->height - object_2->y + object_2->height < object_1->height ))
        return COLLISION_LEFT; 

    return NO_COLLISION;
}