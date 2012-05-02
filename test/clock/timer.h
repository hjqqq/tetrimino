#ifndef TIMER_H
#define TIMER_H

class Timer{
public:
    Timer(Uint32 _delay);
    void reset();
    bool checkTimeOut() const;
private:
    Uint32 delay;
    Uint32 start;
};

#endif
