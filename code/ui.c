#include "ui.h"

void prepare_ui() {
    SDL_Color color = {0, 0, 0};
    text_texture = create_text_texture("Henlo ;)", color);
}

void render_ui() {
    SDL_Rect text_rect = {SCREEN_WIDTH - 300, SCREEN_HEIGHT - 100, 300, 100};
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
}