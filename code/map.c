#include "map.h"

int load_map() {
    game_objects.length = 1;
    game_objects.objects = realloc(game_objects.objects, sizeof(Game_Object) * game_objects.length);

    memcpy(&game_objects.objects[0], &game_objects_templates[TEST_OBJECT], sizeof(Game_Object));
    game_objects.objects[0].x = 100;
    return 0;
}

void render_map() {
    for(int i = 0; i < game_objects.length; i++) {
        Game_Object *current_object = &game_objects.objects[i];
        // Checks if element is off screen
        if(current_object->x > SCREEN_WIDTH ||
            current_object->x + current_object->width < 0 ||
            current_object->y > SCREEN_HEIGHT ||
            current_object->y + current_object->height < 0) {
            current_object->is_rendered = 0;
            continue;
        }

        SDL_Rect dstrect = { current_object->x, current_object->y,
            current_object->width, current_object->height };
        SDL_RenderCopy(renderer, current_object->texture, NULL, &dstrect);
        current_object->is_rendered = 1;
    }
}