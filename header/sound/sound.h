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
    void setVolumeChunk(int volume = -1);

    static const std::string prefix;
    void loadMusic();    
    int getMusicSize();

    enum PlayStyle{};
    void playMusic(int num, int loops = -1);
    void playMusic(const std::string &fileName);
    void playMusic();
    void randomPlayMusic();
    int setVolumeMusic(int volume = -1);
private:
    Mix_Chunk *chunkList[CHUNKSIZE];
    std::vector<Mix_Music*> allMusic;
    std::vector<std::string> allMusicFile;
    std::vector<int> index;
    int current;
    friend void next();
};

#endif
