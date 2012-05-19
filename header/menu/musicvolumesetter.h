#ifndef _MUSICVOLUMESETTER_H_
#define _MUSICVOLUMESETTER_H_

#include "action.h"
#include "resourcedata.h"
/**
   @file musicvolumesetter.h
 */

/**
   @brief 更改全局音乐大小
   
   提供一个double参数的函数更改该全局变量
 */
class MusicVolumeSetter : public Action{
public:
    /**
       @param _sys 初始化传入的数值引用，关联需要修改的音乐大小全局变量
     */
    MusicVolumeSetter( int &_sys) : sys(_sys) {}

    /**
       @param value 用此数值为关联的变量赋值
     */
    inline void operator()( const double & value );

private:
    int &sys;
};

void MusicVolumeSetter::operator()( const double &value )
{
    sys = (int)value;
    ResourceData::sound->setVolumeMusic(sys);
}
#endif /* _MUSICVOLUMESETTER_H_ */
