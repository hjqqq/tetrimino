/*
 * playmus.h
 *
 *  Created on: 2012-4-27
 *      Author: zhangtao
 */

#ifndef SOUND_H_
#define SOUDN_H_
#include "SDL/SDL_mixer.h"
#include "filena.h"
#include <string>
#include <iostream>


class Sound{
private:
	static int playing_n;
	int n_music;
	Mix_Music *music;
	Mix_Chunk *cursor;
	Mix_Chunk *select;
	Mix_Chunk *blockdown;
	Mix_Chunk *explosion;
	Mix_Chunk *warn;
	Mix_Chunk *ready;
	Mix_Chunk *finally;

	Allfilename afn;
public:
	Sound();
	~Sound();
	bool change_mus(std::string);
	void playmus(char ch);
	void next_mus();
};



#endif /* SOUDN_H_ */
