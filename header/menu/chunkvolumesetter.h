#ifndef _CHUNKVOLUMESETTER_H_
#define _CHUNKVOLUMESETTER_H_

#include "action.h"
#include "sound.h"
#include "resourcedata.h"

/**
   @file chunkvolumesetter.h
 */

/**
   @brief 更改全局音效大小
   
   提供一个double参数的函数更改该全局变量
 */
class ChunkVolumeSetter : public Action{
public:
    /**
       @param _sys 初始化传入的数值引用，关联需要修改的音效大小全局变量
     */
    ChunkVolumeSetter( int &_sys) : sys(_sys) {}

    /**
       @param value 用此数值为关联的变量赋值
     */
    inline void operator()( const double & value );

private:
    int &sys;
};

void ChunkVolumeSetter::operator()( const double &value )
{
    sys = (int)value;
    ResourceData::sound->setVolumeChunk(sys);
    ResourceData::sound->playChunk(Sound::CURSOR);
}


#endif /* _CHUNKVOLUMESETTER_H_ */

