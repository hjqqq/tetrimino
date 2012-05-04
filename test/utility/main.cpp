#include <iostream>

#include "vector2.h"

int main()
{
    Vector2<int> vec1(10, 10);
    Vector2<int> vec2(10, 11);
    std::cout << std::boolalpha
	      << (vec1 == vec2)
	      << "\n";
    return 0;
}
