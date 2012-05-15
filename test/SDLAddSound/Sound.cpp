/*
 * Sound.cpp
 *
 *  Created on: 2012-4-27
 *      Author: zhangtao
 */

#include "Sound.h"

int Sound::playing_n = 0;

Sound::Sound():afn(){

	//afn.show();//show the musics
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	music = Mix_LoadMUS(("./musics/"+afn.get_name(0)).c_str());
	if (music == NULL) {
		fprintf(stderr, "Mix_LoadMUS: %s\n", Mix_GetError());
	}
	cursor = Mix_LoadWAV( "./effects/cursor.wav" );
	select = Mix_LoadWAV( "./effects/select.wav" );
	blockdown = Mix_LoadWAV( "./effects/blockdown.wav" );
	explosion = Mix_LoadWAV( "./effects/explosion.wav" );
	warn = Mix_LoadWAV( "./effects/warn.wav" );
	finally = Mix_LoadWAV( "./effects/finally.wav" );
	ready = Mix_LoadWAV( "./effects/ready.wav" );
	n_music = afn.num_musics();
}

Sound::~Sound() {
	Mix_FreeChunk(cursor);
	Mix_FreeChunk(select);
	Mix_FreeChunk(blockdown);
	Mix_FreeChunk(explosion);
	Mix_FreeChunk(warn);
	Mix_FreeChunk(finally);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	Mix_Quit();
}


void Sound::playmus(char ch) {
	switch (ch) {
	case 'c':
		Mix_PlayChannel( -1, cursor, 0);
		break;
	case 's':
		Mix_PlayChannel( -1, select, 0);
		break;
	case 'b':
		Mix_PlayChannel( -1, blockdown, 0);
		break;
	case 'e':
		Mix_PlayChannel( -1, explosion, 0);
		break;
	case 'w':
			Mix_PlayChannel( -1, warn, 0);
			break;
	case 'r':
			Mix_PlayChannel( -1, ready, 0);
			break;
	case 'f':
			Mix_PlayChannel( -1, finally, 0);
			break;
	case 'q':
		Mix_HaltMusic();
		break;
	case 'p':
		if (Mix_PlayingMusic() == 0)
			Mix_PlayMusic(music, -1);
		else if (Mix_PausedMusic() == 1)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
		break;
	}

}

bool Sound::change_mus(std::string str) {
	if (music != NULL)
		Mix_FreeMusic(music);
	music = Mix_LoadMUS(str.c_str());
	if (music == NULL)
		return false;
	return true;
}

void Sound::next_mus(){
	change_mus("./musics/"+afn.get_name(++playing_n%n_music));
}

