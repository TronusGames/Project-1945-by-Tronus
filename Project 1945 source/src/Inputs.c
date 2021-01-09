#include "Inputs.h"


void Update_InputEvents() {
        while (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_QUIT) {
                quit_game = 1;
                break;
            }
        }
}