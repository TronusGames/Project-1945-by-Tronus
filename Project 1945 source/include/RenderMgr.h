#ifndef RENDERMGR_H_
#define RENDERMGR_H_
#include <SDL.h>
#include <SDL_image.h>

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 640


SDL_Window* window;
SDL_Renderer* renderer;

typedef struct {
    SDL_Texture* texture;
    SDL_Rect* rect;
} Sprite;

void CreateWindow();
void CreateRenderer();
SDL_Texture* CreateTexture(char* filePath);


#endif