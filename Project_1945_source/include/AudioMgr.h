#ifndef AUDIO_MGR_H_
#define AUDIO_MGR_H_
#include <SDL.h>
#include <SDL_mixer.h>


typedef struct 
{
    Mix_Music* music;
    Mix_Chunk* expl1;
    Mix_Chunk* player_expl;
} AudioMgr;

AudioMgr audio_mgr;


void Init_AudioMgr(AudioMgr* audioMgr);



#endif