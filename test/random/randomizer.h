#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <cstdlib>

const int blockPackageSize = 7;

inline int randInt(int begin, int end)
{
    int length = end - begin;
    return std::rand() % length + begin;
}

//----------------------------------------------------------------------------------------------------
class Randomizer{
public:
    virtual int get() = 0;
};

class BagRandomizer : public Randomizer{
public:
    BagRandomizer();
    virtual int get();
private:
    int bag[blockPackageSize];
    int *current;
};

//----------------------------------------------------------------------------------------------------
template <int LENGTH = 4>
class HistoryRollRandomizer : public Randomizer{
public:
    HistoryRollRandomizer(int *_history);
    virtual int get();
private:
    int history[LENGTH];
    int *oldest;
};

template <int LENGTH>
HistoryRollRandomizer<LENGTH>::HistoryRollRandomizer(
    int *_history):
    oldest(history)
{
    std::copy_n(_history, LENGTH, history);
}

template <int LENGTH>
int HistoryRollRandomizer<LENGTH>::get()
{
    int randNum;
    int *result;
    while (true){
	randNum = randInt(0, blockPackageSize);
	result = std::find(history, history + LENGTH, randNum);
	if (result == history + LENGTH){
	    *oldest++ = randNum;
	    if (oldest == history + LENGTH)
		oldest = history;
	    return randNum;
	}
    }
}

#endif
