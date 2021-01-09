#include "AudioMgr.h"


void Init_AudioMgr(AudioMgr* audioMgr){
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 2048);

    audioMgr->music = Mix_LoadMUS("resources/audio/background.mp3");
    audioMgr->expl1 = Mix_LoadWAV("resources/audio/snd_explosion1.wav");
    audioMgr->player_expl = Mix_LoadWAV("resources/audio/snd_explosion2.wav");

    Mix_PlayMusic(audioMgr->music, -1);
}