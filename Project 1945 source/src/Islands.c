#include "Islands.h"


void CreateIslands(Scene* scene) {
    scene->island1 = CreateIsland("resources/map/island1.png", 50, 57);
    scene->island2 = CreateIsland("resources/map/island2.png", 68, 64);
    scene->island3 = CreateIsland("resources/map/island3.png", 46, 46);
}

Island* CreateIsland(char* island_texture_path, int w, int h) {
    Island* island = (Island*)malloc(sizeof(Island));
    island->texture = CreateTexture(island_texture_path);
    island->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

    Set_Island_Random_SpawnPoint(island->rect);
    Set_Island_Random_Size(island->rect);
    island->rect->w = w;
    island->rect->h = h;

    island->speed = 100;

    return island;
}


void Set_Island_Random_SpawnPoint(SDL_Rect* rect) {
    rect->x = Get_Random_Number(0, WINDOW_WIDTH);
    rect->y = -Get_Random_Number(0, WINDOW_HEIGHT * 4);
}

void Set_Island_Random_Size(SDL_Rect* rect) {
    rect->w = Get_Random_Number(1, 3)* 32;
    rect->h = rect->w;
}


void Update_Islands(Scene* scene) {
   scene->island1->rect->y += (int)(delta_time * scene->island1->speed);
   scene->island2->rect->y += (int)(delta_time * scene->island1->speed);
   scene->island3->rect->y += (int)(delta_time * scene->island1->speed);


   if (scene->island1->rect->y > WINDOW_HEIGHT) {
       Set_Island_Random_SpawnPoint(scene->island1->rect);
       Set_Island_Random_Size(scene->island1->rect);
   }
   if (scene->island2->rect->y > WINDOW_HEIGHT) {
       Set_Island_Random_SpawnPoint(scene->island2->rect);
       Set_Island_Random_Size(scene->island2->rect);
   }
   if (scene->island3->rect->y > WINDOW_HEIGHT) {
       Set_Island_Random_SpawnPoint(scene->island3->rect);
       Set_Island_Random_Size(scene->island3->rect);
   }
}
