#ifndef _TOGGLESETTER_H_
#define _TOGGLESETTER_H_

#include "action.h"

class ToggleSetter : public Action{
 public:
  ToggleSetter(bool &_sys);
  
  void operator()(const bool value);

 private:
  bool &sys;
};

#endif /* _TOGGLESETTER_H_ */
