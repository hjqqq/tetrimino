#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include <vector>

class BlockData{
public:
    BlockData(int size, std::vector<int> data);
private:
    std::vector<int> blockData[4];
};

#endif
