#ifndef _TOGGLESETTER_H_
#define _TOGGLESETTER_H_

#include "action.h"

class ToggleSetter : public Action{
 public:
 ToggleSetter(bool &_sys) : sys(_sys) {}

  inline void operator()(const bool &);

 private:
  bool &sys;
};

void ToggleSetter::operator()(const bool &value)
{
  sys = value;
}
#endif /* _TOGGLESETTER_H_ */
