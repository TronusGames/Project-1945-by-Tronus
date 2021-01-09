#include <Utility.h>


void Init_Utility() {
    curr_count = SDL_GetPerformanceCounter();
    last_count = 0;
    update_time = 0;
    keyboard_state = SDL_GetKeyboardState(NULL);
}

void Update_DeltaTime() {
    last_count = curr_count;
    curr_count = SDL_GetPerformanceCounter();
    freq = SDL_GetPerformanceFrequency();
    delta_time = (float)(curr_count - last_count) / (float)freq;
    fps = (int)(1.f / delta_time);
    update_time += delta_time;


    if (update_time >= 1.f) {
        time_passed += update_time;
        sprintf_s(title, sizeof(title), "Project 1945 by Tronus      Time:  %.2f  -  FPS:  %d", time_passed, fps);
        SDL_SetWindowTitle(window, title);
        update_time -= 1.f;
    }  
}

int Get_Random_Number(int num_min, int num_max){
    return rand() % (num_max + 1 - num_min) + num_min;
}


int Get_Best_Score(){

    FILE *fp;
    char str[50];
    int best_score = 0;
    char* filename = "resources\\data.txt";
    fp = fopen(filename, "r");
 
    if (fp == NULL){
        printf("Could not open file %s", filename);
        return 0;
    }


    for(int i=0; i<1; i++) {
        fscanf(fp,"%s %d\n", &str, &best_score);
	}
    fclose(fp);


    /*while (fgets(str, 50, fp) != NULL)
        //printf("%s", str);
    fclose(fp);*/
    //int best_score = atoi(str);


    return best_score;
}

int Get_Boss_Kills(){

    FILE *fp;
    char str[50];
    int kills = 0;
    char* filename = "resources\\data.txt";
    fp = fopen(filename, "r");
 
    if (fp == NULL){
        printf("Could not open file %s", filename);
        return 0;
    }


    for(int i=0; i<2; i++) {
        fscanf(fp,"%s %d\n", &str, &kills);
	}
    fclose(fp);


    return kills;
}


int Save_Data(Scene* scene){
    short is_new_best_score = 0;

    int old_score = Get_Best_Score();
    if(scene->score > old_score){
        is_new_best_score = 1;
        Change_Best_Score_Text(scene);
    }


    if(is_new_best_score == 1 || scene->boss->isDied == 1){
        int kills = scene->boss->isDied + Get_Boss_Kills();
        Change_Boss_Kills(scene, &kills);


        FILE * fp;
    
        char* filename = "resources\\data.txt";
        fp = fopen(filename, "w");
        if (fp == NULL){
            printf("Could not open file %s", filename);
            return 0;
        }

        if(is_new_best_score == 0)
            fprintf (fp, "BestScore: %d\nBossKills: %d", old_score, kills);
        else
           fprintf (fp, "BestScore: %d\nBossKills: %d", scene->score, kills); 


        fclose (fp);
    }

     

    return 1;
}