#ifndef SCENE_H_
#define SCENE_H_
#include <SDL_image.h>
#include <stdlib.h>
#include <RenderMgr.h>

typedef struct Scene Scene;

#include <FontMgr.h>
#include <Actors.h>
#include <Game_Actors.h>
#include <Islands.h>


short quit_game;

typedef struct {
    Sprite* sprite;
    float curr_time_waiting;
    float max_time_to_wait;
    short go_next_scene;
} SplashScreen;

SplashScreen* Create_SplashScreen();
void Destroy_SplashScreen(SplashScreen* splash);

void Update_SplashScreen(SplashScreen* splash, Scene* scene, Player* player);
void Draw_SplashScreen(SplashScreen* splash);

int SplashScreen_GameLoop(SplashScreen* splash, Scene* scene, Player* player);



struct Scene{
    SDL_Texture* bottom_texture;
    SDL_Texture* water_texture;

    SDL_Rect** bg_rects;
    int bg_rects_capacity;
    SDL_Rect* bottom_ui_rect;

    Island* island1;
    Island* island2;
    Island* island3;

    int enemies_count;
    SDL_Texture* enemy1_texture;
    SDL_Texture* enemy_expl_texture;
    Enemy** enemies;

    Sprite* life_sprite;
    SDL_Rect* hp_bar_rect;
    int max_hp_bar_width;
    int score;

    SDL_Texture* atlas;
    SDL_Rect* game_over_atlas_pos;
    SDL_Rect* game_over_rect;

    float curr_time_to_restart;
    float max_waittime_to_restart;

    int bullets_num;
    Bullet** bullets;
    SDL_Rect* bullet_text_rect;
    SDL_Texture* bullet1_texture;


    float curr_time_toSpawn_perk;
    float max_time_toSpawn_perk;

    int life_perks_num;
    Perk** life_perks;
    SDL_Rect* atlas_rect_life_perk;
    int bullet_perks_num;
    Perk** bullet_perks;
    SDL_Rect* atlas_rect_bullet_perk;

    int enemy_points;
    int bullet_points;
    int life_perk_points;
    int bullet_perk_points;
    int boss_kill_points;

    short curr_difficulty_distance_mul;
    float curr_difficulty_time;
    float max_difficulty_time;

    Enemy* boss;
    SDL_Rect* boss_hitted_explosion;
    int boss_hit_expl_dist_x;
    int boss_hit_expl_dist_y;
    float boss_coll_dmg_time;
    float max_boss_coll_dmg_time;
    float curr_timer_boss_advancing;
    float max_curr_timer_boss_advancing;
    int old_boss_advancing_pos_y;
};



Scene* Create_Scene();
void Scene_Init(Scene* scene);
void Scene_Restart(Scene* scene, Player* player);

void Scene_Update(SplashScreen* splash, Scene* Scene, Player* Player);

void Scene_Draw();
void Create_BG(Scene* scene);


#endif