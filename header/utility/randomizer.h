#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <algorithm>
#include <cstdlib>

#include "utility.h"
#include "blockdata.h"

/**
   @file randomizer.h
 */

/**
   @brief 随机数产生器

   使用 get() 函数返回一个表示形状的整数。范围 [0, blockPackageSize)
   (blockPackageSize = 7 blockdata.h) 按照标准有两种随机数产生器。

   - random bag，对应 BagRandomizer。random bag 一次生成 7 个随机数，保证7种方
   块每一个出现一次。

   - history4，对应 HistoryRollRandomizer。保证新出现的方块形状不跟前4个一样。
   最开始的方块也有4个方块的历史，他们是StableData::history4Roll[4] = {5, 3,
   5, 3}; 对应形状 ZSZS，也就是一开始不可以出现 Z 或 S。接下来的第二个方块不能
   出现 Z 或 S 或 刚刚生成的方块。
 */

class Randomizer{
public:
    virtual int get() = 0;
};

/**
   @see Randomizer
 */

class BagRandomizer : public Randomizer{
public:
    BagRandomizer();
    virtual int get();
private:
    int bag[blockPackageSize];
    int *current;
};

/**
   @see Randomizer
 */
template <int LENGTH = 4>
class HistoryRollRandomizer : public Randomizer{
public:
    HistoryRollRandomizer(const int *_history);
    virtual int get();
private:
    int history[LENGTH];
    int *oldest;
};

template <int LENGTH>
HistoryRollRandomizer<LENGTH>::HistoryRollRandomizer(
    const int *_history):
    oldest(history)
{
    std::copy(_history, _history + LENGTH, history);
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
