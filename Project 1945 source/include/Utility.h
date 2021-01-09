#ifndef UTILITY_H_
#define UTILITY_H_
#include <SDL.h>
#include <RenderMgr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Scene.h>


char title[100];
int freq;
int curr_count;
int last_count;
float delta_time;
float update_time;
float time_passed;
int fps;
const Uint8* keyboard_state;


void Init_Utility();
void Update_DeltaTime();
int Get_Random_Number(int num_min, int num_max);

int Get_Best_Score();
int Get_Boss_Kills();
int Save_Data(Scene* scene);

#endif