#include "Game_Actors.h"


Player* Create_Player() {
    Player* player = (Player*)malloc(sizeof(Player));
    player->actor = (Actor*)malloc(sizeof(Actor));
    player->actor->texture = CreateTexture("resources/player/myplane_strip3.png");
    player->actor->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    player->actor->anim_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    player->collision_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    player->explosion_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    player->explosion_texture = CreateTexture("resources/player/explosion2_strip7.png");

    Player_Reset(player);

    //create bullets
    player->bullets = malloc(sizeof(Bullet*) * player->bullets_num);
    player->bullet_texture = CreateTexture("resources/player/bullet.png");
    for (int i = 0; i < player->bullets_num; i++)
    {
        player->bullets[i] = Create_Bullet(player->bullet_texture);
    }


    return player;
}

void Player_Reset(Player* player) {
    player->actor->rect->w = 65;
    player->actor->rect->h = 65;
    player->actor->rect->x = WINDOW_WIDTH / 2 - player->actor->rect->w / 2;
    player->actor->rect->y = (WINDOW_HEIGHT - WINDOW_HEIGHT / 6);

    player->actor->anim_rect->w = 65;
    player->actor->anim_rect->h = 65;
    player->actor->anim_rect->x = 0;
    player->actor->anim_rect->y = 0;

    // ANIM
    player->actor->curr_anim_frame = 0;
    player->actor->anim_frames = 3;
    player->actor->anim_max_time = 0.08f;
    player->actor->anim_curr_time = 0;

    player->explosion_rect->w = 64;
    player->explosion_rect->h = 64;
    //player->explosion_rect->x = 4;
    //player->explosion_rect->y = 301;
    player->explosion_rect->x = 0;
    player->explosion_rect->y = 0;


    player->explosion_is_ended = 0;
    player->expl_curr_anim_frame = 0;
    player->expl_anim_frames = 7;
    player->expl_anim_max_time= 0.1f;
    player->expl_anim_curr_time = 0;

    // OTHERS
    player->collision_rect->w = 45;
    player->collision_rect->h = 45;
    player->collision_rect->x = 0;
    player->collision_rect->y = 0;

    // SHOOT
    player->curr_time_to_shoot = 0;
    player->normal_time_to_wait_to_shoot = 0.4f;
    player->max_time_to_wait_to_shoot = player->normal_time_to_wait_to_shoot;

    player->lifes = 2;
    player->max_lifes = 4;
    player->bullets_num = 10;
    player->actor->speed = 300;
    player->actor->max_health = 50;
    player->actor->health = player->actor->max_health;

    // player hitted anim
    player->actor->collision_damage = 500;
    player->has_lost_HP = 0;
    player->curr_time_hitted_anim = 0;
    player->max_time_hitted_anim = 3;
    player->curr_blink_time = 0;
    player->blink_time_rate = 0.1;

    // perks
    player->bullet_perk = 0;
    player->curr_bullet_perk_time = 0;
    player->max_bullet_perk_time = 12.2f;
    player->bullet_perk_time_to_shoot = 0.01f;
}

Enemy* Create_Enemy(SDL_Texture* texture_ptr, Scene* scene) {
    Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
    enemy->actor = (Actor*)malloc(sizeof(Actor));
    enemy->actor->texture = texture_ptr;
    enemy->actor->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    enemy->actor->anim_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    enemy->explosion_anim_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

    enemy->actor->rect->w = 32;
    enemy->actor->rect->h = 32;
    Set_Enemy_Random_SpawnPoint(enemy->actor->rect, scene);

    enemy->actor->anim_rect->w = 32;
    enemy->actor->anim_rect->h = 32;
    enemy->actor->anim_rect->x = 0;
    enemy->actor->anim_rect->y = 0;

    // ANIM
    enemy->actor->curr_anim_frame = 0;
    enemy->actor->anim_frames = 3;
    enemy->actor->anim_max_time = 0.1f;
    enemy->actor->anim_curr_time = 0;

    enemy->explosion_anim_rect->w = 32;
    enemy->explosion_anim_rect->h = 32;
    //enemy->explosion_anim_rect->x = 70;
    //enemy->explosion_anim_rect->y = 169;
    enemy->explosion_anim_rect->x = 0;
    enemy->explosion_anim_rect->y = 0;

    enemy->expl_curr_anim_frame = 0;
    enemy->expl_anim_frames = 6;
    enemy->expl_anim_max_time= 0.12f;
    enemy->expl_anim_curr_time = 0;

    // OTHERS
    enemy->actor->collision_damage = 20;
    enemy->actor->speed = Get_Random_Number(100, 200);
    enemy->actor->max_health = 50;
    enemy->actor->health = enemy->actor->max_health;
    enemy->isDied = 0;

    // SHOOT
    enemy->curr_time_to_shoot = 0;
    enemy->max_time_to_wait_to_shoot = Get_Random_Number(4, 16);

    // DIRECTION
    Set_Enemy_Direction(enemy);


    return enemy;
}

Enemy* Create_Boss(SDL_Texture* texture_ptr, Scene* scene) {
    Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
    enemy->actor = (Actor*)malloc(sizeof(Actor));
    enemy->actor->texture = texture_ptr;
    enemy->actor->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    enemy->actor->anim_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    enemy->explosion_anim_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

    enemy->actor->rect->w = 128;
    enemy->actor->rect->h = 128;
    enemy->actor->rect->x = WINDOW_WIDTH / 2;
    enemy->actor->rect->y = -212;

    enemy->actor->anim_rect->w = 32;
    enemy->actor->anim_rect->h = 32;
    enemy->actor->anim_rect->x = 0;
    enemy->actor->anim_rect->y = 0;

    // ANIM
    enemy->actor->curr_anim_frame = 0;
    enemy->actor->anim_frames = 3;
    enemy->actor->anim_max_time = 0.1f;
    enemy->actor->anim_curr_time = 0;

    enemy->explosion_anim_rect->w = 32;
    enemy->explosion_anim_rect->h = 32;
    //enemy->explosion_anim_rect->x = 70;
    //enemy->explosion_anim_rect->y = 169;
    enemy->explosion_anim_rect->x = 0;
    enemy->explosion_anim_rect->y = 0;

    enemy->expl_curr_anim_frame = 0;
    enemy->expl_anim_frames = 6;
    enemy->expl_anim_max_time= 0.12f;
    enemy->expl_anim_curr_time = 0;

    // OTHERS
    enemy->actor->collision_damage = 40;
    enemy->actor->speed = Get_Random_Number(110, 120);
    enemy->actor->max_health = 550;
    enemy->actor->health = enemy->actor->max_health;
    enemy->isDied = 0;

    // SHOOT
    enemy->curr_time_to_shoot = 0;
    enemy->max_time_to_wait_to_shoot = (float)Get_Random_Number(10, 30) / 29.f;

    // DIRECTION
    if(Get_Random_Number(0, 1) == 0){
        enemy->direction = 1;
    }
    else{
        enemy->direction = -1;
    }


    return enemy;
}

void Enemy_Reset(Enemy* enemy, Scene* scene) {
    Set_Enemy_Random_SpawnPoint(enemy->actor->rect, scene);

    if(scene->curr_difficulty_distance_mul <= 1)
    {
        enemy->actor->rect->y = -100;
        return;
    }

    enemy->actor->anim_rect->x = 0;
    enemy->actor->anim_rect->y = 0;

    // ANIM
    enemy->actor->curr_anim_frame = 0;
    enemy->actor->anim_curr_time = 0;

    enemy->expl_curr_anim_frame = 0;
    enemy->expl_anim_curr_time = 0;

    // OTHERS
    enemy->actor->collision_damage = 20;
    enemy->actor->speed = Get_Random_Number(100, 200);
    enemy->actor->max_health = 50;
    enemy->actor->health = enemy->actor->max_health;
    enemy->isDied = 0;

    
    // SHOOT
    enemy->curr_time_to_shoot = 0;
    enemy->max_time_to_wait_to_shoot = Get_Random_Number(4, 16);

    // DIRECTION
    Set_Enemy_Direction(enemy);
}

void Boss_Reset(Enemy* enemy) {
    enemy->actor->rect->x = WINDOW_WIDTH / 2;
    enemy->actor->rect->y = -212;


    // ANIM
    enemy->actor->curr_anim_frame = 0;
    enemy->actor->anim_curr_time = 0;

    enemy->expl_curr_anim_frame = 0;
    enemy->expl_anim_curr_time = 0;

    // OTHERS
    enemy->actor->collision_damage = 40;
    enemy->actor->speed = Get_Random_Number(110, 120);
    enemy->actor->max_health = 550;
    enemy->actor->health = enemy->actor->max_health;
    enemy->isDied = 0;

    
    // SHOOT
    enemy->curr_time_to_shoot = 0;
    enemy->max_time_to_wait_to_shoot = (float)Get_Random_Number(10, 30) / 29.f;

    // DIRECTION
    if(Get_Random_Number(0, 1) == 0){
        enemy->direction = 1;
    }
    else{
        enemy->direction = -1;
    }
}

void Set_Enemy_Direction(Enemy* enemy){
    // DIRECTION
    enemy->direction = Get_Random_Number(0, 4);
    if(enemy->direction == 4){
        enemy->direction = 1;

        enemy->curr_time_to_direction = 0;
        enemy->max_waitime_to_direction = Get_Random_Number(1, 4);
    }
    else if (enemy->direction == 3){
        enemy->direction = -1;

        enemy->curr_time_to_direction = 0;
        enemy->max_waitime_to_direction = Get_Random_Number(1, 4);
    }
    else{
        enemy->direction = 0;
    }
}

Bullet* Create_Bullet(SDL_Texture* texture_ptr) {
    Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
    bullet->actor = (Actor*)malloc(sizeof(Actor));
    bullet->actor->texture = texture_ptr;
    bullet->actor->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    bullet->actor->anim_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

    bullet->actor->rect->w = 32;
    bullet->actor->rect->h = 32;

    bullet->actor->anim_rect->w = 32;
    bullet->actor->anim_rect->h = 32;
    bullet->actor->anim_rect->x = 0;
    bullet->actor->anim_rect->y = 0;

    // ANIM
    bullet->actor->curr_anim_frame = 0;
    bullet->actor->anim_frames = 1;
    bullet->actor->anim_max_time = 0;
    bullet->actor->anim_curr_time = 0;

    // OTHERS
    bullet->actor->collision_damage = 10;
    bullet->actor->speed = 500;
    bullet->actor->max_health = 10;
    bullet->actor->health = bullet->actor->max_health;
    bullet->isEnable = 0;

    return bullet;
}

Perk* Create_Perk(SDL_Texture* texture_ptr, Scene* scene) {
    Perk* perk = (Perk*)malloc(sizeof(Perk));
    perk->texture = texture_ptr;
    perk->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

    perk->isEnabled = 0;

    perk->rect->w = 32;
    perk->rect->h = 32;
    Set_Enemy_Random_SpawnPoint(perk->rect, scene);


    return perk;
}


void Set_Enemy_Random_SpawnPoint(SDL_Rect* rect, Scene* Scene) {
    rect->x = Get_Random_Number(32, WINDOW_WIDTH - 32);
    rect->y = -Get_Random_Number(0, WINDOW_HEIGHT * Scene->curr_difficulty_distance_mul);
}

void Update_PlayerInputs(Player* player) {   
    if(player->lifes > 0 && player->has_lost_HP == 0) {
        if (keyboard_state[SDL_SCANCODE_LEFT]) {
            player->actor->rect->x -= (int)(player->actor->speed * delta_time);

       /* if (keyboard_state[SDL_SCANCODE_UP]) {
            player->actor->rect->y -= (int)(player->actor->speed * delta_time);
        }
        else if (keyboard_state[SDL_SCANCODE_DOWN]) {
            player->actor->rect->y += (int)(player->actor->speed * delta_time);
        }*/
        } 
        if (keyboard_state[SDL_SCANCODE_RIGHT]) {
            player->actor->rect->x += (int)(player->actor->speed * delta_time);

       /* if (keyboard_state[SDL_SCANCODE_UP]) {
            player->actor->rect->y -= (int)(player->actor->speed * delta_time);
        }
        else if (keyboard_state[SDL_SCANCODE_DOWN]) {
            player->actor->rect->y += (int)(player->actor->speed * delta_time);
        }*/
        }
        
        if (keyboard_state[SDL_SCANCODE_UP]) {
            player->actor->rect->y -= (int)(player->actor->speed * delta_time);
        }
        if (keyboard_state[SDL_SCANCODE_DOWN]) {
            player->actor->rect->y += (int)(player->actor->speed * delta_time);
        }   


        Check_PlayerBounds(player->actor->rect);
        player->collision_rect->x = player->actor->rect->x + 10;
        player->collision_rect->y = player->actor->rect->y + 10;


        // SHOOT
        if (keyboard_state[SDL_SCANCODE_SPACE]){
            if(player->curr_time_to_shoot >= player->max_time_to_wait_to_shoot){
                Player_Shoot(player);
            }
        }
        else
        {
            player->curr_time_to_shoot += delta_time;
        }  
    }
}

void Player_Shoot(Player* player){
    player->curr_time_to_shoot = 0;

    for (int i = 0; i < player->bullets_num; i++)
    {
        if(player->bullets[i]->isEnable == 0){
            player->bullets[i]->actor->rect->x = player->actor->rect->x + player->actor->rect->w / 2 - player->bullets[i]->actor->rect->w / 2;
            player->bullets[i]->actor->rect->y = player->actor->rect->y - 10;

            player->bullets[i]->isEnable = 1;
            return;
        }
    }  
}


void Check_PlayerBounds(SDL_Rect* player_rect) {
    if(player_rect->x < 0){
        player_rect->x = 0;
    }
    else if(player_rect->x > WINDOW_WIDTH - player_rect->w)
    {
        player_rect->x = WINDOW_WIDTH - player_rect->w;
    }

    if(player_rect->y < 0){
        player_rect->y = 0;
    }
    else if(player_rect->y > WINDOW_HEIGHT - player_rect->h - 76) // 76 is the ui height
    {
        player_rect->y = WINDOW_HEIGHT - player_rect->h - 76;
    }
}


void Check_Player_Collisions(Scene* scene, Player* player) {
    if(player->lifes > 0 && player->has_lost_HP == 0) {
        // PLAYER - ENEMIES
        for (int i = 0; i < scene->enemies_count; i++)
        {
            if(scene->enemies[i]->isDied == 0 && SDL_HasIntersection(scene->enemies[i]->actor->rect, player->collision_rect)) {
                Player_Lose_HP(scene, player, &scene->enemies[i]->actor->collision_damage);
                scene->enemies[i]->isDied = 1;

                Mix_PlayChannel(-1, audio_mgr.expl1, 0);
            }
        }

        // PLAYER - BOSS
        if(scene->curr_difficulty_distance_mul <= 1 && scene->boss->isDied == 0){
            if(scene->boss_coll_dmg_time >= scene->max_boss_coll_dmg_time){
                scene->boss_coll_dmg_time = 0;

                if(SDL_HasIntersection(scene->boss->actor->rect, player->collision_rect)) {
                    Player_Lose_HP(scene, player, &scene->boss->actor->collision_damage);

                    Mix_PlayChannel(-1, audio_mgr.expl1, 0);
                }
            }
            else{
                scene->boss_coll_dmg_time += delta_time;
            }       
        }
    }
}

void Check_Player_Bullets_Collisions(Scene* scene, Player* player) {
    if(player->lifes > 0) { 
        // PLAYER BULLETS - ENEMIES
        for (int i = 0; i < scene->enemies_count; i++)
        {
            for (int h = 0; h < player->bullets_num; h++)
            {
                if(player->bullets[h]->isEnable == 1 && scene->enemies[i]->isDied == 0 && SDL_HasIntersection(scene->enemies[i]->actor->rect, player->bullets[h]->actor->rect)) {
                    player->bullets[h]->isEnable = 0;
                    Player_AddScorePoints(scene, scene->enemy_points);
                    scene->enemies[i]->isDied = 1;

                    Mix_PlayChannel(-1, audio_mgr.expl1, 0);
                }
            }
        }

        // PLAYER BULLETS - ENEMY BULLETS
        for (int i = 0; i < scene->bullets_num; i++)
        {
            for (int h = 0; h < player->bullets_num; h++)
            {
                if(player->bullets[h]->isEnable == 1 && scene->bullets[i]->isEnable == 1 && SDL_HasIntersection(scene->bullets[i]->actor->rect, player->bullets[h]->actor->rect)) {
                    player->bullets[h]->isEnable = 0;
                    scene->bullets[i]->isEnable = 0;
                    Player_AddScorePoints(scene, scene->bullet_points);
                }
            }
        }

        // PLAYER BULLETS - BOSS
        if(scene->curr_difficulty_distance_mul <= 1 && scene->boss->isDied == 0){
            for (int h = 0; h < player->bullets_num; h++)
            {
                if(player->bullets[h]->isEnable == 1 && SDL_HasIntersection(player->bullets[h]->actor->rect, scene->boss->actor->rect)) {
                    player->bullets[h]->isEnable = 0;
                    scene->boss->actor->health -= player->bullets[h]->actor->collision_damage;

                    // SET BOSS MINI EXPL ANIM
                    if(player->bullets[h]->actor->rect->y >= scene->boss->actor->rect->y + 92){
                        if(player->bullets[h]->actor->rect->x >= scene->boss->actor->rect->x + scene->boss->actor->rect->w - 2){
                            scene->boss_hitted_explosion->x = scene->boss->actor->rect->x + scene->boss->actor->rect->w - 2 - player->bullets[h]->actor->rect->w;
                            scene->boss_hit_expl_dist_x = scene->boss_hitted_explosion->x - scene->boss->actor->rect->x;
                        }
                        else if(player->bullets[h]->actor->rect->x < scene->boss->actor->rect->x + 2){
                            scene->boss_hitted_explosion->x = scene->boss->actor->rect->x + 2;
                            scene->boss_hit_expl_dist_x = scene->boss_hitted_explosion->x - scene->boss->actor->rect->x;
                        }
                        else{
                            scene->boss_hitted_explosion->x = player->bullets[h]->actor->rect->x;
                            scene->boss_hit_expl_dist_x = player->bullets[h]->actor->rect->x - scene->boss->actor->rect->x;
                        }              

                        scene->boss_hitted_explosion->y = player->bullets[h]->actor->rect->y;
                        scene->boss_hit_expl_dist_y = player->bullets[h]->actor->rect->y - scene->boss->actor->rect->y;
                    }
                    else{
                        if(player->bullets[h]->actor->rect->x >= scene->boss->actor->rect->x + scene->boss->actor->rect->w - 2){
                            scene->boss_hitted_explosion->x = scene->boss->actor->rect->x + scene->boss->actor->rect->w - 2 - player->bullets[h]->actor->rect->w;
                            scene->boss_hit_expl_dist_x = scene->boss_hitted_explosion->x - scene->boss->actor->rect->x;
                        }
                        else if(player->bullets[h]->actor->rect->x < scene->boss->actor->rect->x + 2){
                            scene->boss_hitted_explosion->x = scene->boss->actor->rect->x + 2;
                            scene->boss_hit_expl_dist_x = scene->boss_hitted_explosion->x - scene->boss->actor->rect->x;
                        }
                        else{
                            scene->boss_hitted_explosion->x = player->bullets[h]->actor->rect->x;
                            scene->boss_hit_expl_dist_x = player->bullets[h]->actor->rect->x - scene->boss->actor->rect->x;
                        }   

                        scene->boss_hitted_explosion->y = scene->boss->actor->rect->y + 92;
                        scene->boss_hit_expl_dist_y = (scene->boss->actor->rect->y + 92) - scene->boss->actor->rect->y;
                    }
                    


                    if(scene->boss->actor->health <= 0){
                        Player_AddScorePoints(scene, scene->boss_kill_points);
                        scene->boss->isDied = 1;

                        Mix_PlayChannel(-1, audio_mgr.player_expl, 0);
                        return;
                    }

                    Mix_PlayChannel(-1, audio_mgr.expl1, 0);
                }
            }
        }
    }
}

void Check_Enemy_Bullets_Collisions(Scene* scene, Player* player) {
    if(player->lifes > 0 && player->has_lost_HP == 0) { // ENEMY BULLETS AND PLAYER
        for (int i = 0; i < scene->bullets_num; i++)
        {
            if(scene->bullets[i]->isEnable == 1 && SDL_HasIntersection(scene->bullets[i]->actor->rect, player->actor->rect)) {
                scene->bullets[i]->isEnable = 0;
                Player_Lose_HP(scene, player, &scene->bullets[i]->actor->collision_damage);
                
                Mix_PlayChannel(-1, audio_mgr.expl1, 0);
            }        
        }
    }
}

void Check_Perks_Collisions(Scene* scene, Player* player) {
    if(player->lifes > 0 && player->has_lost_HP == 0) { // PERKS AND PLAYER


        // LIFE PERKS
        for (int i = 0; i < scene->life_perks_num; i++)
        {
            if(scene->life_perks[i]->isEnabled == 1 && SDL_HasIntersection(scene->life_perks[i]->rect, player->actor->rect)) {
                scene->life_perks[i]->isEnabled = 0;
                Player_AddScorePoints(scene, scene->life_perk_points);
                if(player->lifes < player->max_lifes)
                    player->lifes += 1;

                Mix_PlayChannel(-1, audio_mgr.expl1, 0);
            }        
        }

        // BULLET PERKS
        for (int i = 0; i < scene->bullet_perks_num; i++)
        {
            if(scene->bullet_perks[i]->isEnabled == 1 && SDL_HasIntersection(scene->bullet_perks[i]->rect, player->actor->rect)) {
                scene->bullet_perks[i]->isEnabled = 0;
                player->bullet_perk = 1;
                player->max_time_to_wait_to_shoot = player->bullet_perk_time_to_shoot;
                player->curr_bullet_perk_time = 0;
                Player_AddScorePoints(scene, scene->bullet_perk_points);

                Mix_PlayChannel(-1, audio_mgr.expl1, 0);
            }        
        }
    }
}



void Player_Lose_HP(Scene* scene, Player* player, int* damage) {
    player->actor->health -= *damage;
    scene->hp_bar_rect->w = (scene->max_hp_bar_width * player->actor->health) / player->actor->max_health;

    if(player->actor->health <= 0 && player->has_lost_HP == 0) {

        if(player->lifes > 1){
            player->lifes -= 1;
            player->has_lost_HP = 1;
            player->actor->health = player->actor->max_health;
            scene->hp_bar_rect->w = scene->max_hp_bar_width;
        }
        else
        {
            player->lifes = 0;
            player->has_lost_HP = 1;
            player->actor->health = 0;
            scene->hp_bar_rect->w = 0;

            Mix_PlayChannel(-1, audio_mgr.player_expl, 0);
        }        
    }
}

void Player_Check_Ishitted(Player* player) {
    if(player->has_lost_HP == 1) {
        player->curr_time_hitted_anim += delta_time;

        if(player->curr_time_hitted_anim >= player->max_time_hitted_anim){
            player->curr_time_hitted_anim = 0;
            player->has_lost_HP = 0;
        }
    }
}


short Animate_Rect(SDL_Rect* anim_rect, int* max_frames, int* curr_frame, float* time_max, float* time_curr) {
    if(*time_curr >= *time_max){     
        *time_curr = 0;
        *curr_frame += 1;

        if(*curr_frame >= *max_frames){
            *curr_frame = 0;
            anim_rect->x = 0;
            return 1;
        }
        else
        {
            anim_rect->x += anim_rect->w;
        }
    }
    else
    {
        *time_curr += delta_time;
    }   

    return 0;
}

short Animate_Rect_Atlas(int offset, SDL_Rect* anim_rect, int* max_frames, int* curr_frame, float* time_max, float* time_curr) {
    if(*time_curr >= *time_max){     
        *time_curr = 0;
        *curr_frame += 1;

        if(*curr_frame >= *max_frames){
            *curr_frame = 0;
            anim_rect->x -= *max_frames - offset + (*max_frames - offset) * anim_rect->w;
            return 1;
        }
        else
        {
            anim_rect->x += anim_rect->w + offset;
        }
    }
    else
    {
        *time_curr += delta_time;
    }   

    return 0;
}

void Enemy_Tries_To_Shoot(Scene* scene, Enemy* enemy){
    enemy->curr_time_to_shoot += delta_time;

    if(enemy->curr_time_to_shoot >= enemy->max_time_to_wait_to_shoot){

        enemy->curr_time_to_shoot = 0;

        for (int i = 0; i < scene->bullets_num; i++)
        {
            if(scene->bullets[i]->isEnable == 0){
                scene->bullets[i]->actor->rect->x = enemy->actor->rect->x + enemy->actor->rect->w / 2 - scene->bullets[i]->actor->rect->w / 2;
                scene->bullets[i]->actor->rect->y = enemy->actor->rect->y + enemy->actor->rect->h + 4;

                scene->bullets[i]->isEnable = 1;
                return;
            }
        } 
    }
}

void Update_Boss(Scene* scene) {
    if(scene->boss->isDied == 0){
        scene->curr_timer_boss_advancing += delta_time;
        if(scene->curr_timer_boss_advancing >= scene->max_curr_timer_boss_advancing){
            scene->curr_timer_boss_advancing = 0;
            scene->boss->direction = 0;
            scene->old_boss_advancing_pos_y = scene->boss->actor->rect->y;
        }


        if(scene->boss->actor->rect->y < 4){
            scene->boss->actor->rect->y += (int)(delta_time * scene->boss->actor->speed * 2);
            return;
        }

        if(scene->boss->direction == 0){
            scene->boss->actor->rect->y += (int)(delta_time * scene->boss->actor->speed);

            if(scene->boss->actor->rect->y >= scene->old_boss_advancing_pos_y + 32){
                scene->boss->actor->rect->y = scene->old_boss_advancing_pos_y + 32;

                // DIRECTION
                if(Get_Random_Number(0, 1) == 0){
                    scene->boss->direction = 1;
                }
                else{
                     scene->boss->direction = -1;
                }
            }
        }
        else if(scene->boss->direction == 1){

            if(scene->boss->curr_time_to_direction >= scene->boss->max_waitime_to_direction){
                scene->boss->actor->rect->x += (int)(delta_time * scene->boss->actor->speed);

                if(scene->boss->actor->rect->x > WINDOW_WIDTH - scene->boss->actor->rect->w){
                    scene->boss->actor->rect->x = WINDOW_WIDTH - scene->boss->actor->rect->w;
                    scene->boss->direction = -1;
                    scene->boss->curr_time_to_direction = 0;
                }
            }
            else{
                scene->boss->curr_time_to_direction += delta_time;
            }           
        }
        else if(scene->boss->direction == -1){
            if(scene->boss->curr_time_to_direction >= scene->boss->max_waitime_to_direction){
                scene->boss->actor->rect->x -= (int)(delta_time * scene->boss->actor->speed);

                if(scene->boss->actor->rect->x < 0){
                    scene->boss->actor->rect->x = 0;
                    scene->boss->direction = 1;
                    scene->boss->curr_time_to_direction = 0;
                }
            }
            else{
                scene->boss->curr_time_to_direction += delta_time;
            }    
        }

        // SHOOT UPDATE
        Enemy_Tries_To_Shoot(scene, scene->boss);
    }
}

void Update_Enemy(Scene* scene, Enemy* enemy) {
    if(enemy->isDied == 0){

        if(enemy->direction == 0){
            enemy->actor->rect->y += (int)(delta_time * enemy->actor->speed);
        }
        else if(enemy->direction == 1){

            if(enemy->curr_time_to_direction >= enemy->max_waitime_to_direction && enemy->actor->rect->y > 32){
                enemy->actor->rect->x += (int)(delta_time * enemy->actor->speed);
            }
            else{
                if(enemy->actor->rect->y > 32)
                    enemy->curr_time_to_direction += delta_time;

                enemy->actor->rect->y += (int)(delta_time * enemy->actor->speed);
            }           
        }
        else if(enemy->direction == -1){
            if(enemy->curr_time_to_direction >= enemy->max_waitime_to_direction && enemy->actor->rect->y > 32){
                enemy->actor->rect->x -= (int)(delta_time * enemy->actor->speed);
            }
            else{
                if(enemy->actor->rect->y > 32)
                    enemy->curr_time_to_direction += delta_time;

                enemy->actor->rect->y += (int)(delta_time * enemy->actor->speed);
            }    
        }

        // SHOOT UPDATE
        Enemy_Tries_To_Shoot(scene, enemy);
    }

   if (enemy->actor->rect->y > WINDOW_HEIGHT || enemy->actor->rect->x > WINDOW_WIDTH + 64 || enemy->actor->rect->x < -64) {
       Enemy_Reset(enemy, scene);
   }
}

void Update_Player(Player* player, Scene* scene) {
    if(player->lifes > 0) {
        Player_Check_Ishitted(player);

        if(player->bullet_perk == 1){
            player->curr_bullet_perk_time += delta_time;

            if(player->curr_bullet_perk_time >= player->max_bullet_perk_time){
                player->curr_bullet_perk_time = 0;
                player->bullet_perk = 0;
                player->max_time_to_wait_to_shoot = player->normal_time_to_wait_to_shoot;
            }
        }
    }

    if(scene->curr_difficulty_distance_mul <= 1 && scene->boss->isDied == 1){
        // PLAYER ANIM BOSS DEFEATED
        player->actor->rect->y -= (int)(delta_time * (player->actor->speed / 2));
    }
}

void Update_Bullets(Player* player){
    for (int i = 0; i < player->bullets_num; i++)
    {
        if(player->bullets[i]->isEnable == 1){
            player->bullets[i]->actor->rect->y -= (int)(delta_time * player->bullets[i]->actor->speed);

            if(player->bullets[i]->actor->rect->y < 0){
                player->bullets[i]->isEnable = 0;
            }
        }
    }   
}

void Update_Enemy_Bullets(Scene* scene){
    for (int i = 0; i < scene->bullets_num; i++)
    {
        if(scene->bullets[i]->isEnable == 1){
            scene->bullets[i]->actor->rect->y += (int)(delta_time * scene->bullets[i]->actor->speed);

            if(scene->bullets[i]->actor->rect->y > WINDOW_HEIGHT){
                scene->bullets[i]->isEnable = 0;
            }
        }
    }   
}

void Update_Perks(Scene* scene){
    Spawn_Perks(scene);

    // LIFE PERKS
    for (int i = 0; i < scene->life_perks_num; i++)
    {
        if(scene->life_perks[i]->isEnabled == 1){
            scene->life_perks[i]->rect->y += (int)(delta_time * scene->life_perks[i]->speed);

            if(scene->life_perks[i]->rect->y > WINDOW_HEIGHT){
                scene->life_perks[i]->isEnabled = 0;
            }
        }
    } 

    // BULLET PERKS
    for (int i = 0; i < scene->bullet_perks_num; i++)
    {
        if(scene->bullet_perks[i]->isEnabled == 1){
            scene->bullet_perks[i]->rect->y += (int)(delta_time * scene->bullet_perks[i]->speed);

            if(scene->bullet_perks[i]->rect->y > WINDOW_HEIGHT){
                scene->bullet_perks[i]->isEnabled = 0;
            }
        }
    }     
}

void Spawn_Perks(Scene* scene){
    if(scene->boss->isDied == 1)
        return;

    scene->curr_time_toSpawn_perk += delta_time;

    if(scene->curr_time_toSpawn_perk >= scene->max_time_toSpawn_perk)
    {
        if(Get_Random_Number(0, 7) == 0){
            scene->curr_time_toSpawn_perk = 0;

            // LIFE PERKS
            for (int i = 0; i < scene->life_perks_num; i++)
            {
                if(scene->life_perks[i]->isEnabled == 0){
                    Set_Enemy_Random_SpawnPoint(scene->life_perks[i]->rect, scene);
                    scene->life_perks[i]->isEnabled = 1;
                    return;
                }
            } 
        }

        if(Get_Random_Number(0, 1) == 0){
            scene->curr_time_toSpawn_perk = 0;

            // BULLET PERKS
            for (int i = 0; i < scene->bullet_perks_num; i++)
            {
                if(scene->bullet_perks[i]->isEnabled == 0){
                    Set_Enemy_Random_SpawnPoint(scene->bullet_perks[i]->rect, scene);
                    scene->bullet_perks[i]->isEnabled = 1;
                    return;
                }
            }  
        }   

        scene->curr_time_toSpawn_perk = 0;
    }
}


void Draw_Player(Scene* scene, Player* player) {
    if(player->lifes > 0) {
        if(player->has_lost_HP == 1){
            Animate_Rect(player->actor->anim_rect, &player->actor->anim_frames, &player->actor->curr_anim_frame, &player->actor->anim_max_time, &player->actor->anim_curr_time);

            player->curr_blink_time += delta_time;
            if(player->curr_blink_time >= player->blink_time_rate)
            {
                SDL_RenderCopy(renderer, player->actor->texture, player->actor->anim_rect, player->actor->rect);

                if(player->curr_blink_time >= player->blink_time_rate * 2)
                    player->curr_blink_time = 0;
            }

            return;
    }
        Animate_Rect(player->actor->anim_rect, &player->actor->anim_frames, &player->actor->curr_anim_frame, &player->actor->anim_max_time, &player->actor->anim_curr_time);
        SDL_RenderCopy(renderer, player->actor->texture, player->actor->anim_rect, player->actor->rect);
    }
    else
    {
        /*if(player->explosion_is_ended == 0){
            player->explosion_is_ended = Animate_Rect_Atlas(2, player->explosion_rect, &player->expl_anim_frames, &player->expl_curr_anim_frame, &player->expl_anim_max_time, &player->expl_anim_curr_time);
            
            if(player->explosion_is_ended == 0)
                SDL_RenderCopy(renderer, scene->atlas, player->explosion_rect, player->actor->rect);
        }*/

        if(player->explosion_is_ended == 0){
            player->explosion_is_ended = Animate_Rect(player->explosion_rect, &player->expl_anim_frames, &player->expl_curr_anim_frame, &player->expl_anim_max_time, &player->expl_anim_curr_time);

            if(player->explosion_is_ended == 0)
                SDL_RenderCopy(renderer, player->explosion_texture, player->explosion_rect, player->actor->rect);
        }   
    }
}

void Draw_Player_Bullets(Player* player){
    for (int i = 0; i < player->bullets_num; i++)
    {
        if(player->bullets[i]->isEnable == 1){
            SDL_RenderCopy(renderer, player->bullet_texture, NULL, player->bullets[i]->actor->rect);
        }
    }   
}

void Draw_Enemy_Bullets(Scene* scene){
    for (int i = 0; i < scene->bullets_num; i++)
    {
        if(scene->bullets[i]->isEnable == 1){
           // SDL_RenderCopy(renderer, scene->atlas, scene->bullet_text_rect, scene->bullets[i]->actor->rect);
           SDL_RenderCopy(renderer, scene->bullet1_texture, NULL, scene->bullets[i]->actor->rect);
        }
    }   
}


void Draw_Enemy(Scene* scene, Enemy* enemy) {
    if(enemy->isDied == 0){
        Animate_Rect(enemy->actor->anim_rect, &enemy->actor->anim_frames, &enemy->actor->curr_anim_frame, &enemy->actor->anim_max_time, &enemy->actor->anim_curr_time);
        SDL_RenderCopy(renderer, enemy->actor->texture, enemy->actor->anim_rect, enemy->actor->rect);
    }
    else{
        /*if(Animate_Rect_Atlas(1, enemy->explosion_anim_rect, &enemy->expl_anim_frames, &enemy->expl_curr_anim_frame, &enemy->expl_anim_max_time, &enemy->expl_anim_curr_time) == 1){
            Enemy_Reset(enemy);
            return;
        }*/
        //SDL_RenderCopy(renderer, scene->atlas, enemy->explosion_anim_rect, enemy->actor->rect);


        if(Animate_Rect(enemy->explosion_anim_rect, &enemy->expl_anim_frames, &enemy->expl_curr_anim_frame, &enemy->expl_anim_max_time, &enemy->expl_anim_curr_time) == 1){
            Enemy_Reset(enemy, scene);
            return;
        }
        SDL_RenderCopy(renderer, scene->enemy_expl_texture, enemy->explosion_anim_rect, enemy->actor->rect);
    }    
}

void Draw_Boss(Scene* scene, Enemy* enemy) {
    if(enemy->isDied == 0){
        Animate_Rect(enemy->actor->anim_rect, &enemy->actor->anim_frames, &enemy->actor->curr_anim_frame, &enemy->actor->anim_max_time, &enemy->actor->anim_curr_time);
        SDL_RenderCopy(renderer, enemy->actor->texture, enemy->actor->anim_rect, enemy->actor->rect);
    }
    else{
        Animate_Rect(enemy->explosion_anim_rect, &enemy->expl_anim_frames, &enemy->expl_curr_anim_frame, &enemy->expl_anim_max_time, &enemy->expl_anim_curr_time);   
        SDL_RenderCopy(renderer, scene->enemy_expl_texture, enemy->explosion_anim_rect, enemy->actor->rect);
    }    

    Draw_Boss_Hitted_Explosion(scene);
}

void Draw_Boss_Hitted_Explosion(Scene* scene) {
    scene->boss_hitted_explosion->x = scene->boss->actor->rect->x + scene->boss_hit_expl_dist_x;
    scene->boss_hitted_explosion->y = scene->boss->actor->rect->y + scene->boss_hit_expl_dist_y - 48;

    Animate_Rect(scene->boss->explosion_anim_rect, &scene->boss->expl_anim_frames, &scene->boss->expl_curr_anim_frame, &scene->boss->expl_anim_max_time, &scene->boss->expl_anim_curr_time);   
    SDL_RenderCopy(renderer, scene->enemy_expl_texture, scene->boss->explosion_anim_rect, scene->boss_hitted_explosion);
}

void Draw_Perks(Scene* scene) {
    // LIFE PERKS
    for (int i = 0; i < scene->life_perks_num; i++)
    {
        if(scene->life_perks[i]->isEnabled == 1){
           SDL_RenderCopy(renderer, scene->life_perks[i]->texture, scene->atlas_rect_life_perk, scene->life_perks[i]->rect);
        }
    }   

    // BULLET PERKS
    for (int i = 0; i < scene->bullet_perks_num; i++)
    {
        if(scene->bullet_perks[i]->isEnabled == 1){
           SDL_RenderCopy(renderer, scene->bullet_perks[i]->texture, scene->atlas_rect_bullet_perk, scene->bullet_perks[i]->rect);
        }
    }   
}


void Player_AddScorePoints(Scene* scene, int points) {
    scene->score += points;
    Change_Score_Text(scene);
}