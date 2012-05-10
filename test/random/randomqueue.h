#ifndef RANDOMQUEUE_H
#define RANDOMQUEUE_H

#include <deque>
#include <vector>
#include <iostream>

#include "randomizer.h"

class RandomQueueData{
public:
    typedef std::deque<int>::iterator iterator;
    RandomQueueData(Randomizer *_randomizer, int _length = 4);
    ~RandomQueueData();

    int addStartIndex();
    void pop(int startIndex);
    iterator begin(int startIndex);
    iterator end(int startIndex);
    void print(){
	for (int i = 0; i != randomData.size(); ++i){
	    std::cout << randomData[i] << " ";
	}
	std::cout << "\n";
    }
    
private:
    Randomizer *randomizer;
    int length;    
    std::deque<int> randomData;
    std::vector<int> allStart;
};

class RandomQueue{
public:
    typedef std::deque<int>::iterator iterator;
    RandomQueue(RandomQueueData *_randomQueueData);
    iterator begin();
    iterator end();
    void pop();

private:
    RandomQueue(const RandomQueue &randomQueue);
    RandomQueue operator=(const RandomQueue &randomQueue);
    RandomQueueData *randomQueueData;
    int startIndex;
};

#endif
