#ifndef ACTION_H
#define ACTION_H

class Action{
public:
    virtual void operator()();
    virtual void operator()(const bool);
};

#endif
