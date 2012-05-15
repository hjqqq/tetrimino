#include <iostream>

#include "SDL.h"

#include "sound.h"

#include <stdio.h>  
#include <SDL/SDL.h>  
#include <SDL/SDL_mixer.h>  

int main()
{
    //SDL_Init(SDL_INIT_EVERYTHING);
    Sound sound;
    
    SDL_Surface *display = SDL_SetVideoMode(400, 300, 0, SDL_SWSURFACE);

    sound.playChunk(Sound::Chunk(1));
    for (int i = 0; i != 10; ++i){
	sound.playMusic();
	SDL_Delay(3000);
    }

    //SDL_Quit();    
    return 0;
}
