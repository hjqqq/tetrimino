#ifndef _QUITSETTER_H_
#define _QUITSETTER_H_

#include "action.h"

class QuitSetter : public Action{
public:
    QuitSetter(bool &_sys) : sys(_sys) {}

    inline void operator()(const bool &);

private:
    bool &sys;
};

void QuitSetter::operator()(const bool &value)
{
    sys = value;
}
#endif /* _QUITSETTER_H_ */
