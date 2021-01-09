#include "Scene.h"

SplashScreen* Create_SplashScreen(){
    SplashScreen* splash = (SplashScreen*)malloc(sizeof(SplashScreen));
    splash->curr_time_waiting = 0;
    splash->max_time_to_wait = 4;
    splash->go_next_scene = 0;

    splash->sprite = (Sprite*)malloc(sizeof(Sprite));
    splash->sprite->texture = CreateTexture("resources/extra/Title.bmp");

    splash->sprite->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    splash->sprite->rect->x = 0;
    splash->sprite->rect->y = 0;
    splash->sprite->rect->w = WINDOW_WIDTH;
    splash->sprite->rect->h = WINDOW_HEIGHT;

    Create_Menu();

    return splash;
}

void Destroy_SplashScreen(SplashScreen* splash){
    free(splash->sprite->rect);
    SDL_DestroyTexture(splash->sprite->texture);
    free(splash->sprite);
    free(splash);
}

void Update_SplashScreen(SplashScreen* splash, Scene* scene, Player* player){

    if(splash->curr_time_waiting < splash->max_time_to_wait){
        splash->curr_time_waiting += delta_time;
    }
    else{
        if(fontMgr.embark_rect.y > WINDOW_HEIGHT / 2){
            fontMgr.e_rect.y -= (int)(delta_time * 110);
            fontMgr.embark_rect.y -= (int)(delta_time * 110);
            fontMgr.q_rect.y -= (int)(delta_time * 110);
            fontMgr.quit_rect.y -= (int)(delta_time * 110);
            fontMgr.best_score_rect.y -= (int)(delta_time * 110);
            fontMgr.boss_kills_rect.y -= (int)(delta_time * 110);
        }
        else{
            // INPUTS
            if (keyboard_state[SDL_SCANCODE_E]) {
                Mix_PlayChannel(-1, audio_mgr.expl1, 0);
                splash->go_next_scene = 1;
                Scene_Restart(scene, player);
                return;
            }
            else if (keyboard_state[SDL_SCANCODE_Q]) {
                Mix_PlayChannel(-1, audio_mgr.expl1, 0);
                quit_game = 1;
                return;
            }
        }        
    }   
}

void Draw_SplashScreen(SplashScreen* splash){
    SDL_RenderCopy(renderer, splash->sprite->texture, NULL, splash->sprite->rect);

    // MENU
    SDL_RenderCopy(renderer, fontMgr.e_texture, NULL, &fontMgr.e_rect);
    SDL_RenderCopy(renderer, fontMgr.embark_texture, NULL, &fontMgr.embark_rect);
    SDL_RenderCopy(renderer, fontMgr.q_texture, NULL, &fontMgr.q_rect);
    SDL_RenderCopy(renderer, fontMgr.quit_texture, NULL, &fontMgr.quit_rect);

    SDL_RenderCopy(renderer, fontMgr.best_score_texture, NULL, &fontMgr.best_score_rect);
    SDL_RenderCopy(renderer, fontMgr.boss_kills_texture, NULL, &fontMgr.boss_kills_rect);
}

int SplashScreen_GameLoop(SplashScreen* splash, Scene* scene, Player* player){
    if(splash->go_next_scene == 0 && quit_game == 0) {
        // UPDATES
        Update_InputEvents();
        Update_DeltaTime();
        Update_SplashScreen(splash, scene, player);

        // DRAWS
        SDL_Delay(11);
        Draw_SplashScreen(splash);
        SDL_RenderPresent(renderer);

        return 1;
    } 

    return 0;
}



Scene* Create_Scene() {
    Scene* s = (Scene*)malloc(sizeof(Scene));
    Scene_Init(s);
    return s;
}

void Scene_Init(Scene* scene) {
    Create_BG(scene);


    // DIFFICULTY
    scene->curr_difficulty_distance_mul = 11;
    scene->curr_difficulty_time = 0;
    scene->max_difficulty_time = 12;


    // ENEMIES CREATION
    scene->enemies_count = 32;
    scene->enemies = malloc(scene->enemies_count * sizeof(Enemy*));
    for (int i = 0; i < scene->enemies_count; i++)
    {
        scene->enemies[i] = Create_Enemy(scene->enemy1_texture, scene);
    }

    // ENEMY BULLETS CREATION
    scene->bullets_num = 22;
    scene->bullets = malloc(scene->bullets_num * sizeof(Bullet*));
    for (int i = 0; i < scene->bullets_num; i++)
    {
        scene->bullets[i] = Create_Bullet(scene->bullet1_texture);
        scene->bullets[i]->actor->speed = 255;
    }

    // BOSS
    scene->boss = Create_Boss(CreateTexture("resources/enemy/enemy2_strip3.png"), scene);
    scene->boss_coll_dmg_time = 0;
    scene->max_boss_coll_dmg_time = 2.2f;
    scene->curr_timer_boss_advancing = 0;
    scene->max_curr_timer_boss_advancing = 10;


    // PERKS CREATION

    // LIFE PERKS
    scene->life_perks_num = 3;
    scene->life_perks = malloc(scene->life_perks_num * sizeof(Perk*));
    scene->atlas_rect_life_perk = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    scene->atlas_rect_life_perk->w = 32;
    scene->atlas_rect_life_perk->h = 32;
    scene->atlas_rect_life_perk->x = 202;
    scene->atlas_rect_life_perk->y = 268;

    for (int i = 0; i < scene->life_perks_num; i++)
    {
        scene->life_perks[i] = Create_Perk(scene->atlas, scene);
        scene->life_perks[i]->speed = Get_Random_Number(100, 200);
    }

    // BULLET PERKS
    scene->bullet_perks_num = 3;
    scene->bullet_perks = malloc(scene->life_perks_num * sizeof(Perk*));
    scene->atlas_rect_bullet_perk = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    scene->atlas_rect_bullet_perk->w = 32;
    scene->atlas_rect_bullet_perk->h = 32;
    scene->atlas_rect_bullet_perk->x = 103;
    scene->atlas_rect_bullet_perk->y = 268;

    for (int i = 0; i < scene->bullet_perks_num; i++)
    {
        scene->bullet_perks[i] = Create_Perk(scene->atlas, scene);
        scene->bullet_perks[i]->speed = Get_Random_Number(100, 200);
    }


    // POINTS
    scene->enemy_points = 10;
    scene->bullet_points = 2;
    scene->life_perk_points = 100;
    scene->bullet_perk_points = 60;
    scene->boss_kill_points = 1200;

    scene->score = 0;
    scene->curr_time_to_restart = 0;
    scene->max_waittime_to_restart = 3.5f;
    scene->curr_time_toSpawn_perk = 0;
    scene->max_time_toSpawn_perk = 5;
    quit_game = 0;
}

void Scene_Restart(Scene* scene, Player* player) {
    // SAVE DATA
    Save_Data(scene);      


    // DIFFICULTY
    scene->curr_difficulty_distance_mul = 11;
    scene->curr_difficulty_time = 0;


    Player_Reset(player);
    Boss_Reset(scene->boss);
    scene->boss_coll_dmg_time = 0;
    scene->curr_timer_boss_advancing = 0;
    scene->boss_hitted_explosion->x = -200;
    scene->boss_hitted_explosion->y = -400;
    scene->old_boss_advancing_pos_y = 0;
    scene->boss_hit_expl_dist_x = 3000;
    scene->boss_hit_expl_dist_y = 3000;


    // ENEMIES RESET
    for (int i = 0; i < scene->enemies_count; i++)
    {
        Set_Enemy_Random_SpawnPoint(scene->enemies[i]->actor->rect, scene);
    }
    // BULLETS RESET
    for (int i = 0; i < scene->bullets_num; i++)
    {
        Set_Enemy_Random_SpawnPoint(scene->bullets[i]->actor->rect, scene);
    }
    // PERKS RESET
    for (int i = 0; i < scene->life_perks_num; i++)
    {
        Set_Enemy_Random_SpawnPoint(scene->life_perks[i]->rect, scene);
    }
    for (int i = 0; i < scene->bullet_perks_num; i++)
    {
        Set_Enemy_Random_SpawnPoint(scene->bullet_perks[i]->rect, scene);
    }


    scene->score = 0;
    scene->curr_time_to_restart = 0;
    scene->hp_bar_rect->w = scene->max_hp_bar_width;
    scene->curr_time_toSpawn_perk = 0;

    quit_game = 0;
    Change_Score_Text(scene);
    Change_Wave_Text(scene);
}


void Scene_Update(SplashScreen* splash, Scene* Scene, Player* Player){
    // INPUTS
    if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
        Mix_PlayChannel(-1, audio_mgr.player_expl, 0);
        splash->go_next_scene = 0;
        return;
    }

    if(Player->lifes <= 0){
        Scene->curr_time_to_restart += delta_time;

        if(Scene->curr_time_to_restart >= Scene->max_waittime_to_restart){
            Scene_Restart(Scene, Player);
        }
    }   
    else{
        if(Scene->boss->isDied == 1){
            Scene->curr_time_to_restart += delta_time;

            if(Scene->curr_time_to_restart >= Scene->max_waittime_to_restart * 4){
                Scene_Restart(Scene, Player);
            }

            return;
        }


        // INCREASE DIFFICULTY
        if(Scene->curr_difficulty_distance_mul <= 1){
            Update_Boss(Scene);

            return;
        }

        Scene->curr_difficulty_time += delta_time;

        if(Scene->curr_difficulty_time >= Scene->max_difficulty_time){
            Scene->curr_difficulty_time = 0;

            if(Scene->curr_difficulty_distance_mul > 1){
                Scene->curr_difficulty_distance_mul -= 1;
                Change_Wave_Text(Scene);
            }
        }
    }   
}


void Scene_Draw(Scene* scene, Player* player, Enemy* enemy) {
    // RENDER WATER
    for (int i = 0; i < scene->bg_rects_capacity; i++)
    {
        SDL_RenderCopy(renderer, scene->water_texture, NULL, scene->bg_rects[i]);
    }

    // RENDER ISLANDS
    SDL_RenderCopy(renderer, scene->island1->texture, NULL, scene->island1->rect);
    SDL_RenderCopy(renderer, scene->island2->texture, NULL, scene->island2->rect);
    SDL_RenderCopy(renderer, scene->island3->texture, NULL, scene->island3->rect);

    // ENEMY
    for (int i = 0; i < scene->enemies_count; i++)
    {
        Draw_Enemy(scene, scene->enemies[i]);
    }

    // BULLETS
    Draw_Player_Bullets(player);
    Draw_Enemy_Bullets(scene);

    // PERKS
    Draw_Perks(scene);

    // BOSS
    Draw_Boss(scene, scene->boss);


    // RENDER UI
    SDL_RenderCopy(renderer, scene->bottom_texture, NULL, scene->bottom_ui_rect);
    // frame red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, scene->bottom_ui_rect);
    // hp bar
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   
    SDL_RenderFillRect(renderer, scene->hp_bar_rect);
    

    // draw lifes
    if(player->lifes >= player->max_lifes){
        scene->life_sprite->rect->x -= 17;
    }

    for (int i = 0; i < player->lifes; i++)
    {
        SDL_RenderCopy(renderer, scene->life_sprite->texture, NULL, scene->life_sprite->rect);
        scene->life_sprite->rect->x += 32;
    }

    if(player->lifes >= player->max_lifes){
        scene->life_sprite->rect->x += 17;
    }
    scene->life_sprite->rect->x -= 32 * player->lifes;



    // Score Wave Lifes YouWon
    Draw_Score();
    Draw_Wave();

    if(player->lifes <= 0 && player->explosion_is_ended == 1)
        SDL_RenderCopy(renderer, scene->atlas, scene->game_over_atlas_pos, scene->game_over_rect);


    if(scene->boss->isDied == 1)
        Draw_You_Won();
}


void Create_BG(Scene* scene) {
    scene->water_texture = CreateTexture("resources/map/water.png");
    CreateIslands(scene);
    //ui
    scene->bottom_texture = CreateTexture("resources/ui/bottom.png");
    scene->life_sprite = (Sprite*)malloc(sizeof(Sprite));
    scene->life_sprite->texture = CreateTexture("resources/ui/life.png");
    scene->atlas = CreateTexture("resources/1945_atlas.bmp");

    // ENEMIES
    scene->enemy1_texture = CreateTexture("resources/enemy/enemy1_strip3.png");
    scene->enemy_expl_texture = CreateTexture("resources/enemy/explosion1_strip6.png");

    // RECTS
    int width_cells = WINDOW_WIDTH / 32;
    int height_cells = WINDOW_HEIGHT / 32;
    scene->bg_rects_capacity = width_cells * height_cells;

    scene->life_sprite->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    scene->hp_bar_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    scene->bg_rects = malloc(scene->bg_rects_capacity * sizeof(SDL_Rect*));
    scene->boss_hitted_explosion = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    scene->boss_hitted_explosion->w = 32;
    scene->boss_hitted_explosion->h = 32;
    scene->boss_hitted_explosion->x = -100;
    scene->boss_hitted_explosion->y = -300;


    // BULLETS
    scene->bullet1_texture = CreateTexture("resources/enemy/enemybullet1.png");
    scene->bullet_text_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    scene->bullet_text_rect->w = 32;
    scene->bullet_text_rect->h = 32;
    scene->bullet_text_rect->x = 268;
    scene->bullet_text_rect->y = 169;


    // UI 
    scene->bottom_ui_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect)); 
    scene->bottom_ui_rect->w = WINDOW_WIDTH;
    scene->bottom_ui_rect->h = 76;
    scene->bottom_ui_rect->x = 0;
    scene->bottom_ui_rect->y = WINDOW_HEIGHT - 76;


    // GAME OVER
    scene->game_over_atlas_pos = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    scene->game_over_atlas_pos->w = 100;
    scene->game_over_atlas_pos->h = 18;
    scene->game_over_atlas_pos->x = 301;
    scene->game_over_atlas_pos->y = 500;
    scene->game_over_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    scene->game_over_rect->w = 200;
    scene->game_over_rect->h = 48;
    scene->game_over_rect->x = WINDOW_WIDTH / 2 - scene->game_over_rect->w / 2;
    scene->game_over_rect->y = WINDOW_HEIGHT / 2 - scene->game_over_rect->h / 2 - scene->bottom_ui_rect->h;


    scene->hp_bar_rect->h = 9;
    scene->hp_bar_rect->w = 126;
    scene->hp_bar_rect->x = scene->bottom_ui_rect->x + 12;
    scene->hp_bar_rect->y = scene->bottom_ui_rect->y + 45;
    scene->max_hp_bar_width = scene->hp_bar_rect->w;

    scene->life_sprite->rect->x = scene->bottom_ui_rect->x + 30;
    scene->life_sprite->rect->y = scene->bottom_ui_rect->y + 5;
    scene->life_sprite->rect->w = 32;
    scene->life_sprite->rect->h = 32;


    int curr_index = 0;

    for (int curr_y = 0; curr_y < height_cells; curr_y++)
    {
        for (int curr_x = 0; curr_x < width_cells; curr_x++)
        {
            curr_index = curr_x + curr_y * width_cells;

            SDL_Rect* curr_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect)); 
            curr_rect->h = 32;
            curr_rect->w = 32;
            curr_rect->x = curr_x * 32;
            curr_rect->y = curr_y * 32;

            scene->bg_rects[curr_index] = curr_rect;
        }
    } 
}