#ifndef FONT_MGR_H_
#define FONT_MGR_H_
#include <SDL.h>
#include <SDL_ttf.h>
#include <RenderMgr.h>
#include <Scene.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct
{
    TTF_Font* font;
    SDL_Color color_font;
    SDL_Texture* score_texture;
    SDL_Rect score_rect;
    int nDigits;

    SDL_Texture* you_won_texture;
    SDL_Rect you_won_rect;

    SDL_Texture* wave_texture;
    SDL_Rect wave_rect;

    SDL_Texture* e_texture;
    SDL_Rect e_rect;
    SDL_Texture* embark_texture;
    SDL_Rect embark_rect;

    SDL_Texture* q_texture;
    SDL_Rect q_rect;
    SDL_Texture* quit_texture;
    SDL_Rect quit_rect;

    SDL_Texture* best_score_texture;
    SDL_Rect best_score_rect;

    SDL_Texture* boss_kills_texture;
    SDL_Rect boss_kills_rect;
} FontMgr;

FontMgr fontMgr;


void Init_FontMgr(Scene* scene);
void Create_Menu();

void Change_Score_Text(Scene* scene);
void Change_Best_Score_Text(Scene* scene);
void Change_Boss_Kills(Scene* scene, int* kills_num);
void Change_Wave_Text(Scene* scene);

void Draw_Score();
void Draw_Wave();
void Draw_You_Won();

#endif