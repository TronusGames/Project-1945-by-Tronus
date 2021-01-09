#ifndef ISLANDS_H_
#define ISLANDS_H_
#include <SDL_image.h>
#include <RenderMgr.h>

typedef struct  Island Island;

struct Island{
    SDL_Texture* texture;
    SDL_Rect* rect;
    float speed;
};

#include <Utility.h>
#include "Scene.h"


void CreateIslands(Scene* scene);
Island* CreateIsland(char* island_texture_path, int w, int h);
void Set_Island_Random_SpawnPoint(SDL_Rect* rect);
void Set_Island_Random_Size(SDL_Rect* rect);
void Update_Islands(Scene* scene);

#endif