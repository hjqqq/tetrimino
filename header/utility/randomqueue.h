#ifndef RANDOMQUEUE_H
#define RANDOMQUEUE_H

#include <deque>
#include <vector>
#include <iostream>

#include "randomizer.h"

/**
   @file randomqueue.h
 */

/**
   @brief 提供方块中随机数的抽象。
   
   提供方块形状的随机数的抽象，这是一个“多指针”的队列，所存数据是整数[0,
   blockPackageSize) (blockPackageSize 来自 blockdata.h 值为 7，对应
   BlockShape)。具体的数据生成使用 Randomizer类。另外这个队列可以有任意多个指针
   指向其中的数据，只有在最前面的指针 pop() 的时候整个队列才会 pop() , 只有最后
   一个指针的后面的预览块不够大的时候才会利用 Randomizer 新建新的整数 push() 进
   来。多指针队列的目的是生成所有玩家都一样的随机数队列，并且提供每一个玩家的预
   览块。其中的每一个指针就由一个 RandomQueue 类进行封装。

   @see Randomizer
   @see RandomQueue
 */
class RandomQueueData{
public:
    typedef std::deque<int>::iterator iterator;
    RandomQueueData(Randomizer *_randomizer, int _length = 4);
    ~RandomQueueData();

    int addStartIndex();
    void pop(int startIndex);
    void erase(int startIndex);
    iterator begin(int startIndex);
    iterator end(int startIndex);
      
private:
    Randomizer *randomizer;
    int length;    
    std::deque<int> randomData;
    std::vector<int> allStart;
};

/**
   @brief 提供给 Game 类的 RandomQueueData 多指针队列的指针的抽象。 
   
   RandomQueue 封装起 RandomQueueData 多指针队列中的指针并且使其看起来就像是一
   个普通的队列。为 Game 类的编写带来方便。需要注意的是，新建 RandomQueue 对象
   需要在构造函数中告诉它是从那个 RandomQueueData 中新建的一个指针，新建的指针
   只能指向 RandomQueueData 的头部。
 */

class RandomQueue{
public:
    typedef std::deque<int>::iterator iterator;
    RandomQueue(RandomQueueData *_randomQueueData);
    iterator begin();
    iterator end();
    void pop();
    void erase();

private:
    RandomQueue(const RandomQueue &randomQueue);
    RandomQueue operator=(const RandomQueue &randomQueue);
    RandomQueueData *randomQueueData;
    int startIndex;
};

#endif
