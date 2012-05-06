#ifndef RANDOMQUEUE_H
#define RANDOMQUEUE_H

#include <deque>

#include "randomizer.h"

class RandomQueue{
public:
    typedef typename std::deque<int>::iterator iterator;
    
    RandomQueue(Randomizer *_randomizer, int _length = 4);
    ~RandomQueue();
    
    iterator begin();
    iterator end();
    
    void pop();
private:
    Randomizer *randomizer;
    std::deque<int> randomData;
};

#endif
