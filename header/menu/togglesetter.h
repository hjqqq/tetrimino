#ifndef _TOGGLESETTER_H_
#define _TOGGLESETTER_H_

#include "action.h"
/**
   @file togglesetter.h
 */

/**
   @brief 更改传入bool对象的值
 */
class ToggleSetter : public Action{
public:
    /**
       @param _sys 关联的需要修改的bool变量引用
     */
    ToggleSetter(bool &_sys) : sys(_sys) {}

    /**
       @param value 用此状态值为关联变量赋值
     */
    inline void operator()(const bool &value);

private:
    bool &sys;
};

void ToggleSetter::operator()(const bool &value)
{
    sys = value;
}
#endif /* _TOGGLESETTER_H_ */
