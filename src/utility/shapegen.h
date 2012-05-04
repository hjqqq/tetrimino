#ifndef SHAPEGEN_H
#define SHAPEGEN_H

#include "blockdata.h"

class ShapeGenerator{
public:
    virtual BlockData::BlockShape getRandShape() = 0;
};

#endif

#ifndef

