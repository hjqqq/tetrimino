#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <string>

#include "SDL_mixer.h"

/**
   @file sound.h
 */

/**
   @brief 管理效果音以及音乐
   
   本游戏在使用 Sound 类时只会新建一个 ResourceData::sound 全局对象，使用该全局
   对象播放效果音 (chunk) 以及音乐 (music)   
 */

class Sound{
public:
    /**
       @brief 初始化所有声音有关资源

       - 效果音 (chunk) 放在 "res/sound/chunk"
       
       - 背景音乐 （music） 放在 "res/sound/music/"

       可以手动将背景音乐地放到这个文件夹中，要求 mp3，名字为英文。
    */
    Sound();
    ~Sound();

    /**
       使用于 Sound::playChunk 来播放效果音
     */
    enum Chunk{CURSOR, SELECT, MOVE, TURN,
	       HARDDROP, EXPLOSION, WARN, FINALLY};
    
    /**
       播放一段效果音，只播放一遍，可快速多次调用，使得效果音重叠。
       
       @param chunk 指定播放什么效果音
     */
    void playChunk(Chunk chunk);

    /**
       指定所有效果音音量大小
       
       @param volume
       设置范围 [0, 128]，如果 volume > 128 就会变成 128，如果
       volume < 0 则不会设置音量。
       @return 设置前的音量大小。
     */
    int setVolumeChunk(int volume = -1);


    /**
       获取现在音乐文件夹中有多少音乐文件。
     */
    int getMusicSize();

    /**
       根据编号播放音乐，编号是按照读入文件夹时的顺序编号的。
       @param num 音乐编号 范围 [0, Sound::getMusicSize())
       @param loops 指定循环播放次数
       - 0: 不播放
       - -1: 重复播放永不停止
       - others: 播放次数
     */
    void playMusic(int num, int loops = -1);

    /**
       根据音乐文件夹中的音乐文件名字播放音乐
       @param fileName 指定音乐文件名字，若没有该文件则什么也不播放
       @param loops 指定循环播放次数
       - 0: 不播放
       - -1: 重复播放永不停止
       - others: 播放次数
     */
    void playMusic(const std::string &fileName, int loops = -1);

    /**
       随机播放音乐

       内部会建立所有音乐文件的播放列表，打乱顺序之后，每一个文件播放一次，全部
       放完一遍就再打乱顺序，重新播放。
     */
    void randomPlayMusic();

    /**
       设置音乐的音量大小
       @param volume
       设置范围 [0, 128]，如果 volume > 128 就会变成 128，如果
       volume < 0 则不会设置音量。
       @return 设置前的音量大小。
     */
    int setVolumeMusic(int volume = -1);
private:
    static const int CHUNKSIZE = 8; ///< 效果音的总大小，用于新建效果音的资源数组
    void loadChunk();
    void loadMusic();

    static const std::string prefix; ///< 音乐的前缀目录 "res/sound/music"
    
    Mix_Chunk *chunkList[CHUNKSIZE];
    std::vector<Mix_Music*> allMusic;
    std::vector<std::string> allMusicFile;
    std::vector<int> index;
    int current;
    friend void next();
};

#endif
