#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "game_object.h"
#include "player.h"

// Chunk is a SCREEN_WIDTH x SCREEN_HEIGHT place where some type of "room" is generated
// Depending on the type of "room" some specific objects/items/etc. must be spawned within it

enum Chunk_Type {
    PARKOUR,
    CHUNK_TYPE_TOTAL
};

typedef struct Chunk_s {
    int chunk_type, start_x, start_y, objects_in_chunk;
    // pointers to Game Objects added to the general Game_Objects array
    // game objects that were genereted within that chunk  
    Game_Object **objects;
} Chunk;

typedef struct Chunk_Manager_s {
    int generated_chunks_count;
    // REMEMBER TO FREE generated_chunks MEMORY at the end of the game
    Chunk **generated_chunks;
} Chunk_Manager;

// Chunk_Element contains game object (from enum Game_Objects) and its priority
// priority - the higher number is given the lower the chance that game object will be spawned (or lesser amount)
// of that game object will appear when rendering a chunk 
typedef struct Chunk_Element_s {
    int game_object_template, priority;
} Chunk_Element;

// Chunk_Elements contains what elements and how many of them can a chunk of a certain type contain
typedef struct Chunk_Elements_s {
    int chunk_type, max_elements, object_elements_count;
    Chunk_Element *chunk_object_elements;
} Chunk_Elements;

Chunk_Element chunk_element_arr[GAME_OBJECTS_TOTAL];
// Note: REMEMBER TO FREE chunk_elements MEMORY after it is not needed anymore  
Chunk_Elements chunk_elements[CHUNK_TYPE_TOTAL];
Chunk_Manager generated_chunks;
static Chunk *current_chunk;

// Sets one position of "chunk_elements" array with given parameters
// "diff_game_objects_length" is a number of different Game_Objects (enum) elements that will appear
// after that argument
static void set_single_chunk_elements(int chunk_type, int max_elements, int diff_game_objects_length, ...);
// Prepares all chunk elements for further use
void prepare_map();
// Loads all needed map elements; Returns 0 if successful, else 1
int load_map();
// Renders the current map onto the screen
void render_map();
// Checks if objects are overlapping; Returns 0 if no, else 1
int are_objects_overlapping(Game_Object *object_1, Game_Object *object_2);
// Checks if objects are in each others area (check Chunk Notes); Returns 0 if no, else 1
static int are_objects_in_area(Game_Object *object_1, Game_Object *object_2);
// Simply uses are_objects_overlapping function to check if current_object is overlapping
// with any of the generated_objects
// Returns: 0 if object isn't overlapping with any generated, else 1
static int check_generated_if_overlapping(Game_Object *current_object, Game_Object **generated_objects,
    int max_elements);
// Generating possiibility no.1: On game object of BLOCK type - only for TRAP and similar types | 5% chance
// Returns: 0 if object can be generated, else 1
static int generating_on_method(int generated_objects_count, Game_Object **generated_objects,
    Game_Object *current_object, int start_x, int start_y);
// Generating possibility no.2: Spawning near block of the same type | 50% chance
// Returns: 0 if object can be generated, else 1
static int generating_near_method(int generated_objects_count, Game_Object **generated_objects,
    Game_Object *current_object, int start_x, int start_y);
// Generating possibility no.3: On random x, y
// Returns: 0 if object can be generated, else 1
static int generating_random_method(int generated_objects_count, Game_Object **generated_objects,
    Game_Object *current_object, int start_x, int start_y);
// Generates chunk and returns it - REMEMBER TO FREE Chunk MEMORY after it is not needed anymore
// Note: generated game objects of Chunk are automatically added to the "global" Game_Objects array
// Note 2: start_x and start_y are the start x/y position of the chunk - where it begins, so
// full chunk screen size equals start_x + SCREEN_WIDTH and start_y + SCREEN_HEIGHT
Chunk *generate_chunk(int chunk_type, int start_x, int start_y);
// Get chunk at x and y position
// Returns: pointer to chunk if chunk was found, else NULL
static Chunk *get_chunk(int x, int y);
// Selects random sprite from the all possible ones in the given Game_Object and sets it
static void select_random_sprite(Game_Object *current_object);

// Chunk Notes:
// - Chunk consists of SCREEN_WIDTH / 64 x SCREEN_HEIGHT / 64 areas
// - In each area there can be generated one block/item/etc.
// - Near each generated block there can't be any block of other type:
// AAA  where A - area unavailable to other blocks
// ABA        B - generated block
// AAA

#endif