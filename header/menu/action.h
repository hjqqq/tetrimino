#ifndef ACTION_H
#define ACTION_H

#include "SDL.h"
class Action{
public:
    virtual void operator()();
    virtual void operator()(const bool &);
    virtual void operator()(const double &);
};

#endif
