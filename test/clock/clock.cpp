#include <functional>
#include <algorithm>
#include <iostream>
#include "clock.h"

Clock::Clock(Uint32 framerate):
    millisecondPerFrame(frame2Millisecond(framerate)),
    prev(0)
{}

Clock::~Clock()
{
    for (std::list<Counter*>::iterator iter = counterList.begin();
	 iter != counterList.end();
	 ++iter){
	delete *iter;
    }
}

void Clock::tick(){
    countCounterList();
    const Uint32 current = SDL_GetTicks();
    const int distance = current - prev;
    const int remain = millisecondPerFrame - distance;
    if (remain > 0)
	SDL_Delay(remain);
    prev = SDL_GetTicks();
}

Counter* Clock::addCounter(Uint32 num)
{
    Counter *counter = new Counter(num);
    counterList.push_back(counter);
    return counter;
}

void Clock::countCounterList()
{
    for_each(counterList.begin(), counterList.end(), std::mem_fun(&Counter::count));
}


