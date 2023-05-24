#include "game_object.h"

// All game objects
static const char *game_objects_paths[GAME_OBJECTS_TOTAL] = {
    "resources/test_object.png"
};

int load_game_objects() {
    game_objects[TEST_OBJECT].texture = load_texture(game_objects_paths[TEST_OBJECT]);
    game_objects[TEST_OBJECT].width = 100;
    game_objects[TEST_OBJECT].height = 100;
    game_objects[TEST_OBJECT].x = 0;
    game_objects[TEST_OBJECT].y = 0;
    game_objects[TEST_OBJECT].is_rendered = 0;
    game_objects[TEST_OBJECT].type = BLOCK;

    return 0;
}

void render_game_objects() {
    for(int i = 0; i < GAME_OBJECTS_TOTAL; i++) {
        // Checks if element is off screen
        if(game_objects[i].x > SCREEN_WIDTH ||
            game_objects[i].x + game_objects[i].width < 0 ||
            game_objects[i].y > SCREEN_HEIGHT ||
            game_objects[i].y + game_objects[i].height < 0) {
            game_objects[i].is_rendered = 0;
            continue;
        }

        SDL_Rect dstrect = { game_objects[i].x, game_objects[i].y,
            game_objects[i].width, game_objects[i].height };
        SDL_RenderCopy(renderer, game_objects[i].texture, NULL, &dstrect);
        game_objects[i].is_rendered = 1;
    }

    printf("%d %d\n", player_x_pos, player_y_pos);
}

void move_game_objects(int x, int y) {
    for(int i = 0; i < GAME_OBJECTS_TOTAL; i++) {
        game_objects[i].x += x;
        game_objects[i].y += y;
    }
}