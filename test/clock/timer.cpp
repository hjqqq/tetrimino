#include <iostream>

#include "SDL.h"

#include "timer.h"

Timer::Timer(Uint32 _delay):
    delay(_delay)
{
    start = SDL_GetTicks();
}

void Timer::reset()
{
    start = SDL_GetTicks();
}

bool Timer::checkTimeOut() const
{
    int diff = (int)SDL_GetTicks() - (int)start;
    return delay < diff;
}


