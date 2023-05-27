#include "map.h"

static void set_single_chunk_elements(int chunk_type, int max_elements, int diff_game_objects_length, ...) {
    va_list vl;
    va_start(vl, diff_game_objects_length);

    chunk_elements[chunk_type].chunk_type = chunk_type;
    chunk_elements[chunk_type].max_elements = max_elements;
    chunk_elements[chunk_type].object_elements_count = diff_game_objects_length;
    
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
    chunk_element_arr[TEST_OBJECT].priority = 1;
    chunk_element_arr[TEST_OBJECT].game_object_template = TEST_OBJECT;
    chunk_element_arr[GRASS_PLATFORM].priority = 2;
    chunk_element_arr[GRASS_PLATFORM].game_object_template = GRASS_PLATFORM;

    set_single_chunk_elements(PARKOUR, 16, 2, TEST_OBJECT, GRASS_PLATFORM);
}

int load_map() {
    generate_chunk(PARKOUR, 0, 0);
    return 0;
}

void render_map() {
    for(int i = 0; i < game_objects.length; i++) {
        Game_Object *current_object = game_objects.objects[i];
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

int are_objects_overlapping(Game_Object *object_1, Game_Object *object_2) {
    if(object_1->x < object_2->x &&
        object_1->x + object_1->width <= object_2->x) return 0;

    if(object_1->x >= object_2->x + object_2->width) return 0;

    if(object_1->y < object_2->y &&
        object_1->y + object_1->height <= object_2->y) return 0;

    if(object_1->y >= object_2->y + object_2->height) return 0;

    return 1;
}

static int are_objects_in_area(Game_Object *object_1, Game_Object *object_2) {
    Game_Object area_1 = {.width = 64 * 3, .height = 64 * 3, .x = object_1->x - 64, .y = object_1->y - 64};
    Game_Object area_2 = {.width = 64 * 3, .height = 64 * 3, .x = object_2->x - 64, .y = object_2->y - 64};

    if(!are_objects_overlapping(&area_1, &area_2)) return 0;
    return 1;
}

static int check_generated_if_overlapping(Game_Object *current_object, Game_Object **generated_objects,
    int max_elements) {
    for(int l = 0; l < max_elements; l++) {
        if(generated_objects[l] == NULL) return 0;
        if(are_objects_overlapping(current_object, generated_objects[l])) return 1;
    }

    return 0;
}

static int generating_near_method(int generated_objects_count, Game_Object **generated_objects,
    Game_Object *current_object, int start_x, int start_y) {
    for(int l = 0; l < generated_objects_count; l++) {
        // Checking if object templates are of the same type (they share the same textures)
        if(generated_objects[l]->texture == current_object->texture && rand() % 100 >= 90) {
            current_object->x = generated_objects[l]->x + generated_objects[l]->width;
            current_object->y = generated_objects[l]->y;

            if(current_object->x + current_object->width > start_x + SCREEN_WIDTH) return 1;

            if(!check_generated_if_overlapping(current_object, generated_objects, generated_objects_count))
                return 0;
        }
    }

    return 1;
}

static int generating_random_method(int generated_objects_count, Game_Object **generated_objects,
    Game_Object *current_object, int start_x, int start_y) {
    int x_pos = rand() % (SCREEN_WIDTH / 64);
    int y_pos = rand() % (SCREEN_HEIGHT / 64);

    current_object->x = x_pos * 64 + start_x;
    current_object->y = y_pos * 64 + start_y;

    if(!check_generated_if_overlapping(current_object, generated_objects, generated_objects_count)) {
        for(int l = 0; l < generated_objects_count; l++) {
            if(are_objects_in_area(current_object, generated_objects[l])) return 1;
        }

        return 0;
    }

    return 1;
}

Chunk *generate_chunk(int chunk_type, int start_x, int start_y) {
    Chunk *chunk = malloc(sizeof(Chunk));

    Chunk_Elements *element = &chunk_elements[chunk_type];
    int priorities_sum = 0;
    int object_templates[element->object_elements_count];

    for(int i = 0; i < element->object_elements_count; i++) {
        Chunk_Element *object_element = &chunk_elements[chunk_type].chunk_object_elements[i];
        priorities_sum += object_element->priority;
        object_templates[i] = object_element->game_object_template;
    }

    // Ratio for how many blocks of some type should be generated on this chunk 
    // int priority_ratio = (int)((double)priorities_sum / element->object_elements_count);
    Game_Object *generated_objects[element->max_elements];
    int generated_objects_current = 0;

    // NULLing generated_objects for further convenience
    for(int i = 0; i < element->max_elements; i++) generated_objects[i] = NULL;

    for(int i = 0; i < element->object_elements_count; i++) {
        int object_template = object_templates[i];

        int objects_count = (int)(element->max_elements / (double)priorities_sum
            * element->chunk_object_elements[object_template].priority * (rand() / (double)RAND_MAX + 0.5));
        if(objects_count > element->max_elements) objects_count = element->max_elements;

        for(int j = 0; j < objects_count; j++) {
            Game_Object *object = malloc(sizeof(Game_Object));
            memcpy(object, &game_objects_templates[object_template], sizeof(Game_Object));

            int counter = 0;
            while(counter < 10) {
                if(!generating_near_method(generated_objects_current, generated_objects, object,
                    start_x, start_y)) break;
                if(!generating_random_method(generated_objects_current, generated_objects, object, start_x, start_y)) break;
                // To prevent from possible endless loop under certain conditions try to generate 10 times
                counter++;
            }

            game_objects.length = game_objects.length + 1;
            game_objects.objects = realloc(game_objects.objects, sizeof(Game_Object *) * game_objects.length);

            game_objects.objects[game_objects.length - 1] = object;

            generated_objects[generated_objects_current] = object;
            generated_objects_current++;
        }
    }
}