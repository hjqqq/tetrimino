#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "resourcedata.h"
#include "optiondata.h"

SDL_Surface *image_load_alpha( const char *file);
SDL_Surface *image_load(const char *file);
void doubleToString(double, std::string &);
Uint32 getPixel(SDL_Surface *surface, int x, int y);
void putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
    
inline const SDL_Rect get_rect(const SDL_Surface *surface);
inline Uint32 SDL_Color2Uint32(const SDL_Color &color);
inline SDL_Color Uint322SDL_Color(Uint32 pixel);

inline SDL_Color alpha_translate(const SDL_Color &orig,
				 const SDL_Color &back,
				 double alpha);
inline SDL_Color multiply_translate(const SDL_Color &orig,
				    const SDL_Color &back);
inline SDL_Color screen_translate(const SDL_Color &orig,
				  const SDL_Color &back);

inline double lerp(double a, double b, double t);
inline SDL_Surface *create_surface(Uint16 x, Uint16 y);

const SDL_Rect get_rect(const SDL_Surface *surface)
{
    const SDL_Rect rect = {0, 0, (Uint16)surface->w, (Uint16)surface->h};
    return rect;
}

Uint32 SDL_Color2Uint32(const SDL_Color &color)
{
    return SDL_MapRGB(ResourceData::display->format,
		      color.r,
		      color.g,
		      color.b);
}

SDL_Color Uint322SDL_Color(Uint32 pixel)
{
    SDL_Color color;
    SDL_GetRGB(pixel,
	       ResourceData::display->format,
	       &color.r,
	       &color.g,
	       &color.b);
    return color;
}

SDL_Color alpha_translate(const SDL_Color &orig,
			  const SDL_Color &back,
			  double alpha){
    SDL_Color color;
    color.r = (double)orig.r * alpha + (double)back.r * (1 - alpha);
    color.g = (double)orig.g * alpha + (double)back.g * (1 - alpha);
    color.b = (double)orig.b * alpha + (double)back.b * (1 - alpha);
    return color;
}

SDL_Color multiply_translate(const SDL_Color &orig,
			     const SDL_Color &back){
    SDL_Color color;
    color.r = (double)orig.r * back.r / 255;
    color.g = (double)orig.g * back.g / 255;
    color.b = (double)orig.b * back.b / 255;    
    return color;
}

SDL_Color screen_translate(const SDL_Color &orig,
			   const SDL_Color &back){
    SDL_Color color;
    color.r = 255 - (double)(255 - orig.r) * (255 - back.r) / 255;
    color.g = 255 - (double)(255 - orig.g) * (255 - back.g) / 255;
    color.b = 255 - (double)(255 - orig.b) * (255 - back.b) / 255;
    return color;
}

inline int randInt(int begin, int end)
{
    int length = end - begin;
    return std::rand() % length + begin;
}

double lerp(double a, double b, double t)
{
    return a + (b - a) * t;
}

SDL_Surface *create_surface(Uint16 x, Uint16 y)
{
    return SDL_CreateRGBSurface(
	ResourceData::display->flags,
	x,
	y,
	ResourceData::display->format->BitsPerPixel,
	ResourceData::display->format->Rmask,
	ResourceData::display->format->Gmask,
	ResourceData::display->format->Bmask,
	ResourceData::display->format->Amask);
}

#endif 
