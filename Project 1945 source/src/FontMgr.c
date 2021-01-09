#include "FontMgr.h"


void Init_FontMgr(Scene* scene) {
    TTF_Init();

    fontMgr.font = TTF_OpenFont("resources/font/atari.ttf", 100);

    fontMgr.color_font.r = 255;
    fontMgr.color_font.g = 228;
    fontMgr.color_font.b = 0;
    fontMgr.color_font.a = 255;

    fontMgr.nDigits = 1;

    Change_Score_Text(scene);
    Change_Wave_Text(scene);


    // YOU WON
    SDL_Surface* won_surface = TTF_RenderText_Solid(fontMgr.font, "BOSS DEFEATED!", fontMgr.color_font);
    fontMgr.you_won_texture = SDL_CreateTextureFromSurface(renderer, won_surface);

    fontMgr.you_won_rect.w = 200;
    fontMgr.you_won_rect.h = 48;
    fontMgr.you_won_rect.x = WINDOW_WIDTH / 2 - fontMgr.you_won_rect.w / 2;
    fontMgr.you_won_rect.y = WINDOW_HEIGHT / 2 - fontMgr.you_won_rect.h / 2 - scene->bottom_ui_rect->h;

    SDL_FreeSurface(won_surface);
}

void Create_Menu(){
    // E mbark
    SDL_Color colorBlack = {0, 0, 0, 255};

    SDL_Surface* surf1 = TTF_RenderText_Solid(fontMgr.font, "E", colorBlack);
    fontMgr.e_texture = SDL_CreateTextureFromSurface(renderer, surf1);

    fontMgr.e_rect.w = 24;
    fontMgr.e_rect.h = 48;
    fontMgr.e_rect.x = WINDOW_WIDTH / 2 + 4;
    fontMgr.e_rect.y = WINDOW_HEIGHT + 112;

    SDL_FreeSurface(surf1);

    SDL_Surface* surf = TTF_RenderText_Solid(fontMgr.font, " mbark", fontMgr.color_font);
    fontMgr.embark_texture = SDL_CreateTextureFromSurface(renderer, surf);

    fontMgr.embark_rect.w = 144;
    fontMgr.embark_rect.h = 48;
    fontMgr.embark_rect.x = WINDOW_WIDTH / 2 + 4;
    fontMgr.embark_rect.y = WINDOW_HEIGHT + 112;

    SDL_FreeSurface(surf);


    // Q uit
    SDL_Surface* surf3 = TTF_RenderText_Solid(fontMgr.font, "Q", colorBlack);
    fontMgr.q_texture = SDL_CreateTextureFromSurface(renderer, surf3);

    fontMgr.q_rect.w = 24;
    fontMgr.q_rect.h = 48;
    fontMgr.q_rect.x = WINDOW_WIDTH / 2 + 4;
    fontMgr.q_rect.y = WINDOW_HEIGHT + 164;

    SDL_FreeSurface(surf3);

    SDL_Surface* surf2 = TTF_RenderText_Solid(fontMgr.font, " uit", fontMgr.color_font);
    fontMgr.quit_texture = SDL_CreateTextureFromSurface(renderer, surf2);

    fontMgr.quit_rect.w = 96;
    fontMgr.quit_rect.h = 48;
    fontMgr.quit_rect.x = WINDOW_WIDTH / 2 + 4;
    fontMgr.quit_rect.y = WINDOW_HEIGHT + 164;

    SDL_FreeSurface(surf2);


    // BEST SCORE
    int b_score = Get_Best_Score();

    char text[60] = "Best Score: ";
    char char_score[10];
    sprintf(char_score, "%d", b_score);
    strcat(text, char_score);


    SDL_Surface* bs_surf = TTF_RenderText_Solid(fontMgr.font, text, fontMgr.color_font);
    fontMgr.best_score_texture = SDL_CreateTextureFromSurface(renderer, bs_surf);

    /*fontMgr.nDigits = floor(log10(abs(b_score))) + 1;   
    if(fontMgr.nDigits <= 0)
        fontMgr.nDigits = 1;*/

    fontMgr.best_score_rect.w = 24 * (11);
    fontMgr.best_score_rect.h = 48;
    fontMgr.best_score_rect.x = WINDOW_WIDTH / 2 + 4;
    fontMgr.best_score_rect.y = WINDOW_HEIGHT + 228;

    SDL_FreeSurface(bs_surf);


    // BOSS KILLS
    int b_score2 = Get_Boss_Kills();

    char text2[60] = "Boss Kills: ";
    char char_score2[10];
    sprintf(char_score2, "%d", b_score2);
    strcat(text2, char_score2);


    SDL_Surface* kills = TTF_RenderText_Solid(fontMgr.font, text2, fontMgr.color_font);
    fontMgr.boss_kills_texture = SDL_CreateTextureFromSurface(renderer, kills);

    fontMgr.boss_kills_rect.w = 24 * (10);
    fontMgr.boss_kills_rect.h = 48;
    fontMgr.boss_kills_rect.x = WINDOW_WIDTH / 2 + 4;
    fontMgr.boss_kills_rect.y = WINDOW_HEIGHT + 280;

    SDL_FreeSurface(kills);
}


void Change_Score_Text(Scene* scene) {
    fontMgr.nDigits = floor(log10(abs(scene->score))) + 1;   
    if(fontMgr.nDigits <= 0)
        fontMgr.nDigits = 1;

    char str[99];
    sprintf(str, "%d", scene->score);

    SDL_Surface* score_surface = TTF_RenderText_Solid(fontMgr.font, str, fontMgr.color_font);
    if(fontMgr.score_texture != NULL){
        SDL_DestroyTexture(fontMgr.score_texture);
    }
    fontMgr.score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);

    fontMgr.score_rect.x = scene->hp_bar_rect->x + scene->max_hp_bar_width + 40;
    fontMgr.score_rect.y = scene->hp_bar_rect->y - 10;
    fontMgr.score_rect.w = 9 * fontMgr.nDigits;
    fontMgr.score_rect.h = 18;


    SDL_FreeSurface(score_surface);
}

void Change_Best_Score_Text(Scene* scene){
    char text[60] = "Best Score: ";
    char char_score[10];
    sprintf(char_score, "%d", scene->score);
    strcat(text, char_score);

    SDL_Surface* bs_surf = TTF_RenderText_Solid(fontMgr.font, text, fontMgr.color_font);
    SDL_DestroyTexture(fontMgr.best_score_texture);
    fontMgr.best_score_texture = SDL_CreateTextureFromSurface(renderer, bs_surf);

    /*fontMgr.nDigits = floor(log10(abs(b_score))) + 1;   
    if(fontMgr.nDigits <= 0)
        fontMgr.nDigits = 1;*/

    SDL_FreeSurface(bs_surf);
}

void Change_Boss_Kills(Scene* scene, int* kills_num){
    // BOSS KILLS

    char text2[60] = "Boss Kills: ";
    char char_score2[10];
    sprintf(char_score2, "%d", *kills_num);
    strcat(text2, char_score2);


    SDL_Surface* kills = TTF_RenderText_Solid(fontMgr.font, text2, fontMgr.color_font);
    SDL_DestroyTexture(fontMgr.boss_kills_texture);
    fontMgr.boss_kills_texture = SDL_CreateTextureFromSurface(renderer, kills);

    SDL_FreeSurface(kills);
}

void Change_Wave_Text(Scene* scene){
    fontMgr.nDigits = floor(log10(abs(scene->curr_difficulty_distance_mul))) + 1;   
    if(fontMgr.nDigits <= 0)
        fontMgr.nDigits = 1;

    char str[3];


    if(scene->curr_difficulty_distance_mul > 1)
        sprintf(str, "%d", scene->curr_difficulty_distance_mul);
    else
        sprintf(str, "%d", 0);
    

    SDL_Surface* surface = TTF_RenderText_Solid(fontMgr.font, str, fontMgr.color_font);
    if(fontMgr.wave_texture != NULL){
        SDL_DestroyTexture(fontMgr.wave_texture);
    }
    fontMgr.wave_texture = SDL_CreateTextureFromSurface(renderer, surface);

    fontMgr.wave_rect.x = 12;
    fontMgr.wave_rect.y = 12;
    fontMgr.wave_rect.w = 16 * fontMgr.nDigits;
    fontMgr.wave_rect.h = 32;


    SDL_FreeSurface(surface);
}


void Draw_Score(){
    SDL_RenderCopy(renderer, fontMgr.score_texture, NULL, &fontMgr.score_rect);
}

void Draw_Wave(){
    SDL_RenderCopy(renderer, fontMgr.wave_texture, NULL, &fontMgr.wave_rect);
}

void Draw_You_Won(){
    SDL_RenderCopy(renderer, fontMgr.you_won_texture, NULL, &fontMgr.you_won_rect);
}