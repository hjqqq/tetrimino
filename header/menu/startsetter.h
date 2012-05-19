#ifndef _STARTSETTER_H_
#define _STARTSETTER_H_

#include "action.h"
#include "optiondata.h"
/**
   @file startsetter.h
 */
/**
   @brief 设置退出菜单，开始游戏的状态，只在菜单处作特别作用
 */
class StartSetter : public Action {
 public:
  inline void operator()();
};

/**
   更改菜单状态为退出状态，更改程序状态为游戏状态，进入游戏循环
 */
void StartSetter::operator()()
{
  OptionData::menuHolderStatus = OptionData::QUITMENU;
  OptionData::tetriminoStatus = OptionData::GAMELOOP;
}
#endif /* _STARTSETTER_H_ */
