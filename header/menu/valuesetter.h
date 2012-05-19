#ifndef VALUESETTER
#define VALUESETTER

#include "action.h"

/**
   @file valuesetter.h
 */

/**
   @brief 设置传入全局变量的值

   初始化需要关联的全局变量和全局变量的默认值
 */
template <typename T>
class ValueSetter : public Action{
public:
    /**
       @param _ref 指定关联的全局变量
       @param _defaultValue 指定该全局变量给定的默认值
     */
    ValueSetter(T &_ref, const T &_defaultValue = T()):
	ref(_ref), defaultValue(_defaultValue)
    {}

    /**
       设置全局变量为默认值
     */
    virtual void operator()();

    /**
       @param value 用此值为关联的全局变量赋值
     */
    virtual void operator()(const T &value);
private:
    T &ref;
    T defaultValue;
};

template <typename T>
void ValueSetter<T>::operator()(){
    ref = defaultValue;
}

template <typename T>
void ValueSetter<T>::operator()(const T &value){
    ref = value;
}

#endif
