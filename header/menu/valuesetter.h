#ifndef VALUESETTER
#define VALUESETTER

#include "action.h"

template <typename T>
class ValueSetter : public Action{
public:
    ValueSetter(T &_ref, const T &_defaultValue = T()):
	ref(_ref), defaultValue(_defaultValue)
    {}
    
    virtual void operator()();
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
