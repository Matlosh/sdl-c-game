#include "game_object.h"

// All game objects
static const char *game_objects_paths[GAME_OBJECTS_TOTAL] = {
    "resources/test_object.png",
    "resources/platform_1_sprites.png"
};

static void load_game_object_template(int template_name, int width, int height, int x,
    int y, int is_rendered, int type) {
    game_objects_templates[template_name].texture = load_texture(game_objects_paths[template_name]);
    game_objects_templates[template_name].width = width;
    game_objects_templates[template_name].height = height;
    game_objects_templates[template_name].x = x;
    game_objects_templates[template_name].y = y;
    game_objects_templates[template_name].is_rendered = is_rendered;
    game_objects_templates[template_name].type = type;
}

int load_game_objects() {
    load_game_object_template(TEST_OBJECT, 100, 100, 0, 0, 0, BLOCK);

    game_objects.length = 0;
    game_objects.objects = calloc(0, sizeof(Game_Object));
    return 0;
}

void move_game_objects(int x, int y) {
    for(int i = 0; i < game_objects.length; i++) {
        game_objects.objects[i].x -= x;
        game_objects.objects[i].y -= y;
    }
}