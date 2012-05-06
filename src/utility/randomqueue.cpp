#include "randomqueue.h"

RandomQueue::RandomQueue(Randomizer *_randomizer, int _length):
    randomizer(_randomizer),
    randomData(std::deque<int>(_length))
{
    for (int i = 0; i != _length; ++i)
	randomData[i] = randomizer->get();
}

RandomQueue::~RandomQueue()
{
    delete randomizer;
}

RandomQueue::iterator RandomQueue::begin(){
    return randomData.begin();
}

RandomQueue::iterator RandomQueue::end(){
    return randomData.end();
}

void RandomQueue::pop()
{
    randomData.pop_front();
    randomData.push_back(randomizer->get());
}

