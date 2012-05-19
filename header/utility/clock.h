#ifndef CLOCK_H
#define CLOCK_H

#include <list>

#include "SDL.h"

#include "counter.h"

/**
   @file clock.h
 */

/**
   @brief 控制游戏 fps 时间。

   通过游戏主循环中每一帧调用一次 tick() 函数可以自动延迟相应的时间。可以
   addCounter。可以增加一个 counter。counter 在每一次 tick() 是会自动减1。通过
   addCounter 返回的 counter 由 Clock 管理内存，也可以使用 removeCounter()，先
   删掉。
 */

class Clock{
public:
    Clock(Uint32 framerate);
    ~Clock();
    void tick();

    /**
       @param num 计数器 (counter) 的计数次数
       @return 新增计数器指针，由 Clock 类自己管理内存
     */
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
