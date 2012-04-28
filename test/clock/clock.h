#ifndef CLOCK_H
#define CLOCK_H

#include <list>

#include "SDL.h"

#include "counter.h"

class Clock{
public:
    Clock(Uint32 framerate);
    ~Clock();
    void tick();
    Counter* addCounter(Uint32 num);
    
    inline static Uint32 frame2Millisecond(Uint32 framerate);
private:
    void countCounterList();
    Uint32 prev;
    const Uint32 millisecondPerFrame;
    std::list<Counter*> counterList; 
};

Uint32 Clock::frame2Millisecond(Uint32 framerate)
{
    return 1000 / framerate;
}

#endif
