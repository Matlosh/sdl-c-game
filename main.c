#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include "code/general.h"
#include "code/variables.h"
#include "code/player.h"
#include "code/game_object.h"
#include "code/ui.h"
#include "code/map.h"

int func(int a, int b) {
    return a + b;
}

int main(int argc, char *argv[]) {
    if(init(&main_window, &renderer)) return 1;
    if(load_game_objects()) return 1;
    prepare_map();
    if(load_map()) return 1;
    prepare_ui();
    prepare_player();

    // test
    // int (*functions[2])(int, int);
    // int (*custom_func)(int, int);
    // custom_func = &func;

    // printf("%d\n", custom_func(5, 4));
    //

    SDL_Event event;

    bool working = true;
    // Game loop
    while(working) {
        SDL_Delay(10);
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                working = false;
            }

            if(event.key.keysym.sym == SDLK_ESCAPE) {
                working = false;
            }

            process_player_movement(&event);
        }
        move_player();

        SDL_SetRenderDrawColor(renderer, 0xBB, 0xAA, 0xCC, 0xFF);

        // Clear screen
        SDL_RenderClear(renderer);
        render_map();
        render_player();
        render_ui();

        // Update screen
        SDL_RenderPresent(renderer);
    }

    close(main_window, renderer);
    return 0;
}