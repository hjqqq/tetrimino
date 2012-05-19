#ifndef _NUMBERSETTER_H_
#define _NUMBERSETTER_H_

#include "action.h"
/**
   @file numbersetter.h
 */

/**
   @brief 绑定一个全局变量，提供一个double参数的函数更改该全局变量

   该模板只适应用于能够被强制转换为double的类型，如int等
 */
template <typename T>
class NumberSetter : public Action{
 public:
    /**
       @param _sys 初始化传入的数值引用，关联需要修改的变量
     */
 NumberSetter(T &_sys) : sys(_sys) {}

    /**
       param value 用此数值为关联的变量赋值
     */
  inline void operator()(const double & value);
  
 private:
  T &sys;
};

template <typename T>
void NumberSetter<T>::operator()(const double & value)
{
  sys = (T)value;
}

#endif /* _NUMBERSETTER_H_ */
