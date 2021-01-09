#ifndef ACTORS_H_
#define ACTORS_H_
#include <SDL_image.h>
#include <SDL.h>


typedef struct {
    SDL_Texture* texture;
    SDL_Rect* rect;
    SDL_Rect* anim_rect;
    int curr_anim_frame;
    int anim_frames;
    float anim_max_time;
    float anim_curr_time;
    float speed;
    int max_health;
    int health;
    int collision_damage;
} Actor;

typedef struct {
    SDL_Texture* texture;
    SDL_Rect* rect;
    float speed;
    short isEnabled;
} Perk;

typedef struct {
    Actor* actor;
    short isEnable;
} Bullet;

typedef struct {
    Actor* actor;
    SDL_Rect* collision_rect;
    int lifes;
    int max_lifes;
    short has_lost_HP;
    float curr_time_hitted_anim;
    float max_time_hitted_anim;

    int bullets_num;
    Bullet** bullets;
    SDL_Texture* bullet_texture;
    float curr_time_to_shoot;
    float max_time_to_wait_to_shoot;
    float normal_time_to_wait_to_shoot;

    short explosion_is_ended;
    SDL_Texture* explosion_texture;
    SDL_Rect* explosion_rect;
    int expl_curr_anim_frame;
    int expl_anim_frames;
    float expl_anim_max_time;
    float expl_anim_curr_time;
    float curr_blink_time;
    float blink_time_rate;

    short bullet_perk;
    float curr_bullet_perk_time;
    float max_bullet_perk_time;
    float bullet_perk_time_to_shoot;
} Player;

typedef struct {
    Actor* actor;
    short isDied;
    SDL_Rect* explosion_anim_rect;
    int expl_curr_anim_frame;
    int expl_anim_frames;
    float expl_anim_max_time;
    float expl_anim_curr_time;

    float curr_time_to_shoot;
    float max_time_to_wait_to_shoot;

    short direction;
    float curr_time_to_direction;
    float max_waitime_to_direction;
} Enemy;


#endif