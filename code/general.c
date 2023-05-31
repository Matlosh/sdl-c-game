#include "general.h"

int init(SDL_Window **window, SDL_Renderer **renderer) {
    srand(time(NULL));

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize: %s\n", SDL_GetError());
        return 1;
    }

    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        printf("SDL_image could not initialize: %s\n", IMG_GetError());
        return 1;
    }

    if(TTF_Init()) {
        printf("SDL_ttf could not initialize: %s\n", TTF_GetError());
        return 1;
    }
    font = TTF_OpenFont("resources/RobotoSlab.ttf", 64);

    *window = SDL_CreateWindow("Mine app", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(*window == NULL) {
        printf("Window could not be created: %s\n", SDL_GetError());
        return 1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(*renderer == NULL) {
        printf("Renderer could not be fetched: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

void close(SDL_Window **window, SDL_Renderer **renderer) {
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);

    // Implement destroying all available textures (texts, game objects, etc.)
    // Implement freeing memory of game objects and chunks

    // Player
    free(player.player_rect);

    // Information about chunk types
    for(int i = 0; i < GAME_OBJECTS_TOTAL; i++)
        free(chunk_elements[i].chunk_object_elements);

    // Generated chunks
    for(int i = 0; i < generated_chunks.generated_chunks_count; i++) {
        for(int j = 0; j < generated_chunks.generated_chunks[i]->objects_in_chunk; j++)
            free(generated_chunks.generated_chunks[i]->objects[j]);
        free(generated_chunks.generated_chunks[i]->objects);
        free(generated_chunks.generated_chunks[i]);
    }
    free(generated_chunks.generated_chunks);

    // Loaded textures
    for(int i = 0; i < GAME_OBJECTS_TOTAL; i++) {
        SDL_DestroyTexture(game_objects_templates[i].texture);
    }

    // for(int i = 0; i < game_objects.length; i++) {
    //     printf("???\n");
    //     printf("%p\n", game_objects.objects[i]);
    //     // printf("%p\n", game_objects.objects[i]->texture);
    //     // free(game_objects.objects[i]->interaction_effects);
    //     free(game_objects.objects[i]);
    // }

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture *load_texture(char *path) {
    SDL_Texture *texture;
    texture = IMG_LoadTexture(renderer, path);
    if(!texture) {
        printf("Texture from %s could not be loaded.\n", path);
        return NULL;
    }

    return texture;
}

SDL_Texture *create_text_texture(char *text, SDL_Color text_color) {
    SDL_Surface *surface_text = TTF_RenderText_Solid(font, text, text_color);
    SDL_Texture *texture_text = SDL_CreateTextureFromSurface(renderer, surface_text);
    SDL_FreeSurface(surface_text);
    return texture_text;
}