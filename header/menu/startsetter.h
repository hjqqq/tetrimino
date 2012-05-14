#ifndef _STARTSETTER_H_
#define _STARTSETTER_H_

#include "action.h"
#include "optiondata.h"

class StartSetter : public Action {
 public:
  inline void operator()();
};

void StartSetter::operator()()
{
  OptionData::menuHolderStatus = OptionData::QUITMENU;
  OptionData::tetriminoStatus = OptionData::GAMELOOP;
}
#endif /* _STARTSETTER_H_ */
