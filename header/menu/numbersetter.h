#ifndef _NUMBERSETTER_H_
#define _NUMBERSETTER_H_

#include "action.h"

template <typename T>
class NumberSetter : public Action{
 public:
 NumberSetter(T &_sys) : sys(_sys) {}
  
  void operator()(const double);

 private:
  T &sys;
};

template <typename T>
void NumberSetter<T>::operator()(const double value)
{
  sys = (T)value;
}
#endif /* _NUMBERSETTER_H_ */
