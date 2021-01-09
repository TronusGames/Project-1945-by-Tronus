#ifndef GAME_ACTORS_H_
#define GAME_ACTORS_H_
#include <SDL_image.h>
#include <SDL.h>
#include <RenderMgr.h>
#include <Utility.h>
#include <Inputs.h>
#include <Actors.h>
#include <Scene.h>
#include <FontMgr.h>
#include <AudioMgr.h>


Player* Create_Player();
void Player_Reset(Player* player);
Enemy* Create_Enemy(SDL_Texture* texture_ptr, Scene* scene);
Enemy* Create_Boss(SDL_Texture* texture_ptr, Scene* scene);
void Enemy_Reset(Enemy* enemy, Scene* scene);
void Boss_Reset(Enemy* enemy);
void Set_Enemy_Direction(Enemy* enemy);

Bullet* Create_Bullet(SDL_Texture* texture_ptr);
Perk* Create_Perk(SDL_Texture* texture_ptr, Scene* scene);


void Set_Enemy_Random_SpawnPoint(SDL_Rect* rect, Scene* Scene);

void Update_PlayerInputs(Player* player);
void Player_Shoot(Player* player);
void Check_PlayerBounds(SDL_Rect* player_rect);

void Check_Player_Collisions(Scene* scene, Player* player);
void Check_Player_Bullets_Collisions(Scene* scene, Player* player);
void Check_Enemy_Bullets_Collisions(Scene* scene, Player* player);
void Check_Perks_Collisions(Scene* scene, Player* player);


void Player_Lose_HP(Scene* scene, Player* player, int* damage);
void Player_Check_Ishitted(Player* player);

short Animate_Rect(SDL_Rect* anim_rect, int* max_frames, int* curr_frame, float* time_max, float* time_curr);
short Animate_Rect_Atlas(int offset, SDL_Rect* anim_rect, int* max_frames, int* curr_frame, float* time_max, float* time_curr);

void Enemy_Tries_To_Shoot(Scene* scene, Enemy* enemy);

void Update_Boss(Scene* scene);
void Update_Enemy(Scene* scene, Enemy* enemy);
void Update_Player(Player* player, Scene* scene);
void Update_Bullets(Player* player);
void Update_Enemy_Bullets(Scene* scene);
void Update_Perks(Scene* scene);

void Spawn_Perks(Scene* scene);

void Draw_Player(Scene* scene, Player* player);
void Draw_Player_Bullets(Player* player);
void Draw_Enemy_Bullets(Scene* scene);
void Draw_Enemy(Scene* scene, Enemy* enemy);
void Draw_Boss(Scene* scene, Enemy* enemy);
void Draw_Boss_Hitted_Explosion(Scene* scene);
void Draw_Perks(Scene* scene);


void Player_AddScorePoints(Scene* scene, int points);

#endif