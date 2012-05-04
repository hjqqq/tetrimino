#ifndef COUNTER_H
#define COUNTER_H

class Counter{
public:
    inline Counter(Uint32 num);
    inline Uint32 getRemain() const;
    inline void setRemain(Uint32 newRemain);
    inline void reset();
    inline void count();
private:
    const Uint32 orig;
    Uint32 remain;
};

Counter::Counter(Uint32 num):
    orig(num), remain(num)
{}

Uint32 Counter::getRemain() const
{
    return remain;
}

void Counter::setRemain(Uint32 newRemain)
{
    remain = newRemain;
}

void Counter::reset()
{
    remain = orig;
}

void Counter::count()
{
    if (remain > 0)
	--remain;
}

#endif

