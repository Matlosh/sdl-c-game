#include "ui.h"

void prepare_ui() {
    SDL_Color color = {0, 0, 0};
    text_texture = create_text_texture("Henlo ;)", color);

    in_game_ui.health_bar_empty = load_texture("resources/hp_bar_empty.png");
    in_game_ui.health_bar = load_texture("resources/hp_bar.png");
    in_game_ui.is_visible = 1;
}

void update_ui() {

}

void render_ui() {
    SDL_Rect text_rect = {SCREEN_WIDTH - 300, SCREEN_HEIGHT - 100, 300, 100};
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    if(in_game_ui.is_visible) {
        // below must be done better - should this inner/outer be created here?
        SDL_Rect health_bar_outer = {.w = 200, .h = 3, .x = SCREEN_WIDTH - 210, .y = 10};
        SDL_Rect health_bar_inner = {.w = 200 * (double)player.health / player.max_health,
            .h = 3, .x = SCREEN_WIDTH - 210, .y = 10};
        SDL_RenderCopy(renderer, in_game_ui.health_bar_empty, NULL, &health_bar_outer);
        SDL_RenderCopy(renderer, in_game_ui.health_bar, NULL, &health_bar_inner);
    }
}