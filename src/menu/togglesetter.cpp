#include "togglesetter.h"

ToggleSetter::ToggleSetter(bool &_sys) : sys(_sys)
{}

void ToggleSetter::operator()(const bool value)
{
  sys = value;
}
