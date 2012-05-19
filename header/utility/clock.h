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
    void removeCounter(Counter *counter);
    void clearCounter();
    
    inline static Uint32 frame2Millisecond(Uint32 framerate);
    inline static Uint32 millisecond2Frame(Uint32 millisecond);
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

Uint32 Clock::millisecond2Frame(Uint32 millisecond){
    return 1000/ millisecond;
}

#endif
