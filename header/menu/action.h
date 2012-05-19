#ifndef ACTION_H
#define ACTION_H

#include "SDL.h"

/**
   @file action.h
*/

/**
   @brief 所有setter的基类，用来修改全局变量

   每个Widget都有一个Action对象指针，告诉Widget应该执行的操作
*/
class Action{
public:
    /**
       无参数的operator()，一般用来重载更改游戏状态(enum类型)
    */
    virtual void operator()();

    /**
       一般用来更改bool型的全局变量

       @param bool 传入游戏的全局变量(bool)，传入的值会被改变
    */
    virtual void operator()(const bool &);

    /**
       一般用来更改数值型的全局变量(double)

       @param double 传入游戏的全局变量(double)，传入的值会被改变
    */
    virtual void operator()(const double &);
};

#endif
