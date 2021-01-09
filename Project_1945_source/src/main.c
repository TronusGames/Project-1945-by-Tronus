#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include <Utility.h>
#include <RenderMgr.h>
#include <Inputs.h>
#include <Islands.h>
#include <Scene.h>
#include <Actors.h>
#include <Game_Actors.h>
#include <FontMgr.h>
#include <AudioMgr.h>


void UpdateMgr(SplashScreen* splash, Scene* scene, Player* player){
    Update_DeltaTime();

    Update_Islands(scene);
    // Update enemies
    for (int i = 0; i < scene->enemies_count; i++)
    {
        Update_Enemy(scene, scene->enemies[i]);
    }

    Update_Player(player, scene);

    // Update Bullets
    Update_Bullets(player);
    Update_Enemy_Bullets(scene);

    // Update perks
    Update_Perks(scene);

    // Update Scene
    Scene_Update(splash, scene, player);
}

void DrawMgr(Scene* scene, Player* player) {
    // PRE RENDER
     SDL_SetRenderDrawColor(renderer, 0, 0, 55, 255);
     SDL_RenderClear(renderer);

     // FINAL RENDER
     Scene_Draw(scene, player);
     Draw_Player(scene, player);

     SDL_RenderPresent(renderer);
}

void CollisionsMgr(Scene* scene, Player* player) {
    if(scene->boss->isDied == 0){
        Check_Player_Collisions(scene, player);
        Check_Player_Bullets_Collisions(scene, player);
        Check_Enemy_Bullets_Collisions(scene, player);
        Check_Perks_Collisions(scene, player);
    }
}


int WinMain() {
    SDL_Init(SDL_INIT_VIDEO);
    CreateWindow();
    CreateRenderer();
    Init_Utility();
    Init_AudioMgr(&audio_mgr);


    Scene* scene = Create_Scene();
    Player* player = Create_Player();
    Init_FontMgr(scene);
    // SPLASH SCREEN
    SplashScreen* splash = Create_SplashScreen();
    

    // GAME SCENE GAME LOOP
    while(!quit_game) {
        if(SplashScreen_GameLoop(splash, scene, player) == 1){
            continue;
        }

        // INPUTS
        Update_InputEvents();
        if(scene->boss->isDied == 0)
            Update_PlayerInputs(player);


        // UPDATES
        UpdateMgr(splash, scene, player);
        CollisionsMgr(scene, player);

        // DRAWS
        SDL_Delay(11);
        DrawMgr(scene, player);
    } 



    Destroy_SplashScreen(splash);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
