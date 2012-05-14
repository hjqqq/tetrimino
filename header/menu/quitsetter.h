#ifndef _QUITSETTER_H_
#define _QUITSETTER_H_

#include "action.h"
#include "optiondata.h"

class QuitSetter : public Action {
 public:
  inline void operator()();
};

void QuitSetter::operator()()
{
  OptionData::menuHolderStatus = OptionData::QUITMENU;
  OptionData::tetriminoStatus = OptionData::QUIT;
}

#endif /* _QUITSETTER_H_ */
