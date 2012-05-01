#include <iostream>

#include "rect.h"

int main()
{
    Rect<double> rect(10, 10, 10, 10);
    std::cout << rect << "\n";
    return 0;
}
