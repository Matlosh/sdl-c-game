#include "variables.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
SDL_Window *main_window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL; // Initialized in init()
int camera_x = 0;
int camera_y = 0;