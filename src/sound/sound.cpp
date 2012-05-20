#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "dirent.h"
#include "sound.h"
#include "utility.h"
#include "resourcedata.h"

Sound::Sound()
{
    int ret = Mix_Init(MIX_INIT_MP3);
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

int Sound::setVolumeChunk(int volume)
{
    return Mix_Volume(-1, volume);
}

const std::string Sound::prefix("res/sound/music/");

void Sound::loadMusic()
{
    DIR *dir = opendir(prefix.c_str());
    dirent *dirp;
    current = 0;
    while (dirp = readdir(dir)){
	std::string fileName = dirp->d_name;
	if (fileName != ".." && fileName != "."){
	    std::string fullFileName = prefix + fileName;
	    Mix_Music *music = Mix_LoadMUS(fullFileName.c_str());
	    allMusic.push_back(music);
	    allMusicFile.push_back(fileName);
	    index.push_back(current++);
	}
    }
    closedir(dir);
}

int Sound::getMusicSize()
{
    return allMusic.size();
}

void Sound::playMusic(int num, int loops)
{
    if(Mix_PlayMusic(allMusic[num], loops) == -1)
	printf("Mix_PlayMusic: %s\n", Mix_GetError());
}

void Sound::playMusic(const std::string &fileName, int loops)
{
    std::vector<std::string>::iterator result =
	std::find(allMusicFile.begin(), allMusicFile.end(), fileName);
    if (result != allMusicFile.end())
	playMusic(result - allMusicFile.begin(), loops);
}

/**
   为了 Mix_HookMusicFinished 而新建的用于回调函数，
   与 randomPlayMusic 一起，实现放完一首歌再放一首歌。
 */
void next();

void Sound::randomPlayMusic()
{
    if (current == index.size()){
	current = 0;
	std::random_shuffle(index.begin(), index.end());
    }
    playMusic(index[current], 1);
    Mix_HookMusicFinished(next);
}

int Sound::setVolumeMusic(int volume)
{
    return Mix_VolumeMusic(volume); 
}

using namespace ResourceData;

void next()
{
    ++sound->current;
    if (sound->current == sound->index.size()){
	sound->current = 0;
	std::random_shuffle(sound->index.begin(),
			    sound->index.end());
    }
    sound->playMusic(sound->index[sound->current], 1);
}
