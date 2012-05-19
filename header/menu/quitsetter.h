#ifndef _QUITSETTER_H_
#define _QUITSETTER_H_

#include "action.h"
#include "optiondata.h"
/**
   @file quitsetter.h
 */

/**
   @brief 更改游戏全局状态，退出游戏，只在菜单做特殊用处
 */
class QuitSetter : public Action {
 public:
  inline void operator()();
};

/**
   更改游戏菜单状态为退出状态，整个程序的状态也为退出状态
 */
void QuitSetter::operator()()
{
  OptionData::menuHolderStatus = OptionData::QUITMENU;
  OptionData::tetriminoStatus = OptionData::QUIT;
}

#endif /* _QUITSETTER_H_ */
