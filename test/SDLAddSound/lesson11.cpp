/*This source code copyrighted by Lazy Foo' Productions (2004-2012)
 and may not be redestributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Sound.h"
#include <string>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

SDL_Surface *load_image(std::string filename) {
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized surface that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load(filename.c_str());

	//If the image loaded
	if (loadedImage != NULL) {
		//Create an optimized surface
		optimizedImage = SDL_DisplayFormat(loadedImage);

		//Free the old surface
		SDL_FreeSurface(loadedImage);

		//If the surface was optimized
		if (optimizedImage != NULL) {
			//Color key surface
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY,
					SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
		}
	}

	//Return the optimized surface
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination,
		SDL_Rect* clip = NULL) {
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit
	SDL_BlitSurface(source, clip, destination, &offset);
}

bool init() {
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	//Set up the screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
			SDL_SWSURFACE);

	//If there was an error in setting up the screen
	if (screen == NULL) {
		return false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1) {
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption("Monitor Music", NULL);

	//If everything initialized fine
	return true;
}

bool load_files() {
	//Load the background image
	background = load_image("background.png");

	//Open the font
	font = TTF_OpenFont("lazy.ttf", 30);

	//If there was a problem in loading the background
	if (background == NULL) {
		return false;
	}

	//If there was an error in loading the font
	if (font == NULL) {
		return false;
	}

	//If everything loaded fine
	return true;
}

void clean_up() {
	//Free the surfaces
	SDL_FreeSurface(background);

	//Close the font
	TTF_CloseFont(font);

	//Quit SDL_ttf
	TTF_Quit();

	//Quit SDL
	SDL_Quit();
}

int main(int argc, char* args[]) {
	//Quit flag
	bool quit = false;

	//Initialize
	if (init() == false) {
		return 1;
	}

	//Load the files
	if (load_files() == false) {
		return 1;
	}

	//Apply the background
	apply_surface(0, 0, background, screen);

	//Render the text
	message = TTF_RenderText_Solid(font,
			"Press effect c:cursor s:select ", textColor);

	//If there was an error in rendering the text
	if (message == NULL) {
		return 1;
	}

	//Show the message on the screen
	apply_surface((SCREEN_WIDTH - message->w) / 2, 80, message, screen);

	//Free the message
	SDL_FreeSurface(message);

	//Render the text
	message = TTF_RenderText_Solid(font, "f:finally e:explosion w:warn",
			textColor);

	//If there was an error in rendering the text
	if (message == NULL) {
		return 1;
	}

	//Show the message on the screen
	apply_surface((SCREEN_WIDTH - message->w) / 2, 160, message, screen);

	//Free the message
	SDL_FreeSurface(message);

	//Render the text
	message = TTF_RenderText_Solid(font, "Press Q to stop the music ",
			textColor);

	//If there was an error in rendering the text
	if (message == NULL) {
		return 1;
	}

	apply_surface((SCREEN_WIDTH - message->w) / 2, 230, message, screen);

		//Free the message
		SDL_FreeSurface(message);

		//Render the text
		message = TTF_RenderText_Solid(font, "b:blockmove r:ready P:play or pause.",
				textColor);

		//If there was an error in rendering the text
		if (message == NULL) {
			return 1;
		}



	//Update the screen
	if (SDL_Flip(screen) == -1) {
		return 1;
	}

	Sound mysound;

	//While the user hasn't quit
	while (quit == false) {
		//While there's events to handle
		while (SDL_PollEvent(&event)) {
			//If a key was pressed
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_c) {
					//change music
					mysound.playmus('c');
				}

				//If s was pressed
				else if (event.key.keysym.sym == SDLK_s) {
					//Play the scratch effect
					mysound.playmus('s');
				}
				//If h was pressed
				else if (event.key.keysym.sym == SDLK_e) {
					//Play the high hit effect
					mysound.playmus('e');
				}
				//If m was pressed
				else if (event.key.keysym.sym == SDLK_b) {
					//Play the medium hit effect
					mysound.playmus('b');
				}
				//If l was pressed
				else if (event.key.keysym.sym == SDLK_r) {
					//Play the low hit effect
					mysound.playmus('r');
				}

				else if (event.key.keysym.sym == SDLK_w) {
					mysound.playmus('w');
				}
				else if (event.key.keysym.sym == SDLK_f) {
					mysound.playmus('f');
				}
				else if (event.key.keysym.sym == SDLK_q) {
					//pause the music
					mysound.playmus('p');
				}
				else if (event.key.keysym.sym == SDLK_q) {
									//Stop the music
					mysound.playmus('q');
				}
			}
			//If the user has Xed out the window
			if (event.type == SDL_QUIT) {
				//Quit the program
				quit = true;
			}

		}
	}

	//Free surfaces, fonts and sounds
	//then quit SDL_mixer, SDL_ttf and SDL
	clean_up();

	return 0;
}
