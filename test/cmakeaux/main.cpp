#include <iostream>
#include "foo.h"
#include "bar.h"

int main()
{
    std::cout << foo() + bar() << std::endl;
    return 0;
}
