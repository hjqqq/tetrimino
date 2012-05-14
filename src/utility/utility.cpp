#include <string>
#include <sstream>
#include "utility.h"

SDL_Surface *image_load_alpha( const char *file)
{
    SDL_Surface *image_orig = IMG_Load(file);
    SDL_Surface *image = SDL_DisplayFormatAlpha(image_orig);
    SDL_FreeSurface(image_orig);
    return image;
}
SDL_Surface *image_load(const char *file)
{
    SDL_Surface *image_orig = IMG_Load(file);
    SDL_Surface *image = SDL_DisplayFormat(image_orig);
    SDL_FreeSurface(image_orig);
    return image;
}

void doubleToString(double number, std::string &str)
{
  std::ostringstream ss;
  ss << number;
  str = ss.str();
}
