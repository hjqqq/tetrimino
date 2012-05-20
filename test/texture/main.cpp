#include "SDL.h"
#include "SDL_image.h"

inline double lerp(double a, double b, double t)
{
    return a + (b - a) * t;
}

Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

int main()
{
    const int displayX = 500, displayY = 300;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *display = SDL_SetVideoMode(displayX, displayY, 0, SDL_SWSURFACE);

    SDL_Surface *picture = IMG_Load("haha.jpg");

    SDL_Surface *halfPicture =
	SDL_CreateRGBSurface(
	    display->flags,
	    800,
	    600,
	    display->format->BitsPerPixel,
	    display->format->Rmask,
	    display->format->Gmask,
	    display->format->Bmask,
	    display->format->Amask);

    SDL_LockSurface(picture);
    SDL_LockSurface(halfPicture);
    Uint32 pixel;
    for (int j = 0; j != displayY; ++j){
	for (int i = 0; i != displayX; ++i){
	    pixel = getPixel(picture,
			     lerp(0, i, (double)picture->w / displayX),
			     lerp(0, j, (double)picture->h / displayY));
	    putPixel(halfPicture, i, j, pixel);
	}
    }
    SDL_UnlockSurface(picture);
    SDL_UnlockSurface(halfPicture);

    SDL_BlitSurface(halfPicture, NULL, display, NULL);
    
    SDL_Event event;
    while (true){
	while (SDL_PollEvent(&event)){
	    switch (event.type){
	    case SDL_QUIT:
		SDL_FreeSurface(picture);
		SDL_FreeSurface(halfPicture);
		SDL_Quit();
		return 0;
	    }
	}
	SDL_UpdateRect(display, 0, 0, 0, 0);
    }
    return 0;
}
