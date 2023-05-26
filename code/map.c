#include "map.h"

static void set_single_chunk_elements(int chunk_type, int max_elements, int diff_game_objects_length, ...) {
    va_list vl;
    va_start(vl, diff_game_objects_length);

    chunk_elements[chunk_type].chunk_type = chunk_type;
    chunk_elements[chunk_type].max_elements = max_elements;
    
    Chunk_Element *chunk_object_elements = malloc(sizeof(Chunk_Element) * diff_game_objects_length);

    int game_object;
    for(int i = 0; i < diff_game_objects_length; i++) {
        game_object = va_arg(vl, int);
        chunk_object_elements[i] = chunk_element_arr[game_object];
    }

    chunk_elements[chunk_type].chunk_object_elements = chunk_object_elements;
    va_end(vl);
}

void prepare_map() {
    chunk_element_arr[TEST_OBJECT].priority = 2;
    chunk_element_arr[GRASS_PLATFORM].priority = 1;

    set_single_chunk_elements(PARKOUR, 8, 2, TEST_OBJECT, GRASS_PLATFORM);
}

int load_map() {
    game_objects.length = 2;
    game_objects.objects = realloc(game_objects.objects, sizeof(Game_Object) * game_objects.length);

    memcpy(&game_objects.objects[0], &game_objects_templates[TEST_OBJECT], sizeof(Game_Object));
    game_objects.objects[0].x = 300;

    memcpy(&game_objects.objects[1], &game_objects_templates[GRASS_PLATFORM], sizeof(Game_Object));
    SDL_Rect srcrect = {.w = 32, .h = 32, .x = 64, .y = 0};
    game_objects.objects[1].srcrect = srcrect;
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
        SDL_RenderCopy(renderer, current_object->texture, &current_object->srcrect, &dstrect);
        current_object->is_rendered = 1;
    }
}

Chunk *generate_chunk() {
    Chunk *chunk = malloc(sizeof(Chunk));

    
}