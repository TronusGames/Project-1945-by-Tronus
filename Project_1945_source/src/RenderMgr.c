#include "RenderMgr.h"


void CreateWindow() {
        window = SDL_CreateWindow(
        "Project 1945 by Tronus",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        0
    );

    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
            "Could not create window: %s", SDL_GetError());
        return;
    }


    // SET ICON
   /* Uint32 rmask, gmask, bmask, amask;
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;


    SDL_Surface* icon;
    SDL_RWops *rwop;

    rwop = SDL_RWFromFile("resources/ui/Icon.ico", "rb");
    Uint32 pixels[32 * 32 * 4 + 1];

    if (rwop != NULL) {
        rwop->read(rwop, pixels, sizeof (pixels), 1);
        rwop->close(rwop);
    }
    icon = SDL_CreateRGBSurfaceFrom(pixels, 32, 32, 32, 32 * 3, rmask, gmask, bmask, amask);  */

    SDL_Surface* icon = IMG_Load("resources/ui/Icon.png");

    SDL_SetWindowIcon(window, icon);

    SDL_FreeSurface(icon);
    //SDL_FreeRW(rwop);
}

void CreateRenderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
            "Could not create renderer: %s", SDL_GetError());
        return;
    }
}

SDL_Texture* CreateTexture(char* filePath) {
    //Load on RAM
    SDL_Surface* surface = IMG_Load(filePath);
    if (surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load surface: %s", SDL_GetError());
        return NULL;
    }

    //Load on GPU
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
       if (texture == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load texture: %s", SDL_GetError());
        return NULL;
    }

    //Free RAM
    SDL_FreeSurface(surface);

    return texture;
}