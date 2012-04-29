#include <cmath>
#include <stdexcept>
#include "vector2.h"

void Vector2::setLength(double length)
{
    if (length == 0)
	x = y = 0;
    else{
	*this *= length / this->getLength();
    }
}


