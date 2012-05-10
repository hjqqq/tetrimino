#include <algorithm>
#include "randomqueue.h"

RandomQueueData::RandomQueueData(Randomizer *_randomizer, int _length):
    randomizer(_randomizer),
    length(_length)
{
    for (int i = 0; i != length; ++i)
	randomData.push_back(randomizer->get());
}

RandomQueueData::~RandomQueueData()
{
    delete randomizer;
}

int RandomQueueData::addStartIndex()
{
    allStart.push_back(0);
    return allStart.size() - 1;
}

void RandomQueueData::pop(int startIndex)
{
    ++allStart[startIndex];
    int minStart = *std::min_element(allStart.begin(), allStart.end());
    if (minStart == 1){
	for (int i = 0; i != allStart.size(); ++i)
	    allStart[i] -= 1;
	randomData.pop_front();
    }
    
    int maxStart = *std::max_element(allStart.begin(), allStart.end());
    if (randomData.size() < maxStart + length)
	randomData.push_back(randomizer->get());
}

RandomQueueData::iterator RandomQueueData::begin(int startIndex)
{
    return randomData.begin() + allStart[startIndex];
}

RandomQueueData::iterator RandomQueueData::end(int startIndex)
{
    return randomData.begin() + allStart[startIndex] + length;
}


RandomQueue::RandomQueue(RandomQueueData *_randomQueueData):
    randomQueueData(_randomQueueData)
{
    startIndex = randomQueueData->addStartIndex();
}

RandomQueue::iterator RandomQueue::begin()
{
    return randomQueueData->begin(startIndex);
}

RandomQueue::iterator RandomQueue::end()
{
    return randomQueueData->end(startIndex);
}

void RandomQueue::pop()
{
    randomQueueData->pop(startIndex);
}

