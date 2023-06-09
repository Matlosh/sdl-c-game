#include "game_object.h"

// All game objects
static const char *game_objects_paths[GAME_OBJECTS_TOTAL] = {
    "resources/test_object.png",
    "resources/platform_1_sprites.png",
    "resources/spike.png"
};

static void load_game_object_template(int template_name, int width, int height, int x,
    int y, int is_rendered, int type, int sprite_width, int sprite_height, int sprites_count,
    int effects_count, ...) {
    game_objects_templates[template_name].texture = load_texture(game_objects_paths[template_name]);
    game_objects_templates[template_name].width = width;
    game_objects_templates[template_name].height = height;
    game_objects_templates[template_name].x = x;
    game_objects_templates[template_name].y = y;
    game_objects_templates[template_name].is_rendered = is_rendered;
    game_objects_templates[template_name].type = type;
    // srcrect should/can be specifically set when making a copy of the object to use in f.e. map
    SDL_Rect srcrect = {.w = sprite_width / sprites_count, .h = sprite_height, .x = 0, .y = 0};
    game_objects_templates[template_name].srcrect = srcrect;

    Sprites_Info sprites_info = { .sprite_width = sprite_width, .sprite_height = sprite_height,
        .sprites_count = sprites_count };
    game_objects_templates[template_name].sprites_info = sprites_info;

    game_objects_templates[template_name].interaction_effects.effects_count = effects_count;
    game_objects_templates[template_name].interaction_effects.custom_effects = malloc(sizeof(void *) * effects_count);

    va_list vl;
    va_start(vl, effects_count);

    for(int i = 0; i < effects_count; i++)
        game_objects_templates[template_name].interaction_effects.custom_effects[i] = va_arg(vl, void *);

    va_end(vl);
}

int load_game_objects() {
    load_game_object_template(TEST_OBJECT, 64, 64, 0, 0, 1, BUTTON, 100, 100, 1, 1, &lose_hp);
    load_game_object_template(GRASS_PLATFORM, 64, 64, 0, 0, 1, BLOCK, 128, 32, 4, 0);
    load_game_object_template(SPIKE, 64, 64, 0, 0, 1, TRAP, 32, 32, 1, 0);

    game_objects.length = 0;
    game_objects.objects = calloc(0, sizeof(Game_Object));
    return 0;
}

void move_game_objects(int x, int y) {
    for(int i = 0; i < game_objects.length; i++) {
        game_objects.objects[i]->x -= x;
        game_objects.objects[i]->y -= y;
    }
}

void lose_hp(Game_Object *object, Player *player) {
    player->health--;
    object->is_rendered = 0;
    printf("lose_hp(...)\n");
}