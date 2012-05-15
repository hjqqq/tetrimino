#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <string>

#include "SDL_mixer.h"


class Sound{
public:
    Sound();
    ~Sound();
    
    enum Chunk{CURSOR, SELECT, MOVE, TURN,
	       HARDDROP, EXPLOSION, WARN, FINALLY};
    static const int CHUNKSIZE = 8;
    void loadChunk();    
    void playChunk(Chunk chunk);

    static const std::string prefix;
    void loadMusic();    
    int getMusicSize();
    void playMusic(int num);
    void playMusic();
private:
    Mix_Chunk *chunkList[CHUNKSIZE];
    std::vector<Mix_Music*> allMusic;
    std::vector<std::string> allMusicFile;
};

#endif
