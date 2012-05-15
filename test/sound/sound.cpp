#include <iostream>
#include <cstdlib>

#include "dirent.h"
#include "sound.h"

int randInt(int begin, int end)
{
    int length = end - begin;
    return std::rand() % length + begin;
}

Sound::Sound()
{
    int ret = Mix_Init(MIX_INIT_MP3);
    if(ret & MIX_INIT_MP3 != MIX_INIT_MP3){  
        perror("failed to initialize mp3 module.");  
        exit(1);  
    }  
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    loadChunk();
    loadMusic();
}

Sound::~Sound()
{
    for (int i = 0; i != CHUNKSIZE; ++i)
	Mix_FreeChunk(chunkList[i]);
    for (int i = 0; i != allMusic.size(); ++i)
	Mix_FreeMusic(allMusic[i]);
    Mix_CloseAudio();
    Mix_Quit();
}

const int Sound::CHUNKSIZE;

void Sound::loadChunk()
{
    chunkList[0] = Mix_LoadWAV("res/sound/chunk/cursor.wav");
    chunkList[1] = Mix_LoadWAV("res/sound/chunk/select.wav");
    chunkList[2] = Mix_LoadWAV("res/sound/chunk/move.wav");
    chunkList[3] = Mix_LoadWAV("res/sound/chunk/turn.wav");
    chunkList[4] = Mix_LoadWAV("res/sound/chunk/harddrop.wav");
    chunkList[5] = Mix_LoadWAV("res/sound/chunk/explosion.wav");
    chunkList[6] = Mix_LoadWAV("res/sound/chunk/warn.wav");
    chunkList[7] = Mix_LoadWAV("res/sound/chunk/finally.wav");    
}

void Sound::playChunk(Chunk chunk)
{
    Mix_PlayChannel(-1, chunkList[chunk], 0);
}

const std::string Sound::prefix("res/sound/music/");

void Sound::loadMusic()
{
    DIR *dir = opendir(prefix.c_str());
    dirent *dirp;
    while (dirp = readdir(dir)){
	std::string fileName = dirp->d_name;
	if (fileName != ".." && fileName != "."){
	    std::string fullFileName = prefix + fileName;
	    Mix_Music *music = Mix_LoadMUS(fullFileName.c_str());
	    allMusic.push_back(music);
	    allMusicFile.push_back(fullFileName);
	}
    }
}

int Sound::getMusicSize()
{
    return allMusic.size();
}

void Sound::playMusic(int num)
{
    if(Mix_PlayMusic(allMusic[num], -1) == -1)
	printf("Mix_PlayMusic: %s\n", Mix_GetError());
}

void Sound::playMusic()
{
    int num = randInt(0, allMusic.size());
    playMusic(num);
}
