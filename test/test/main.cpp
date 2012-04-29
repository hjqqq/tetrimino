#include <iostream>

int main()
{
    typedef int intarr[4];
    const intarr arr = {1, 2, 3, 4};
    std::cout << arr[3] << std::endl;
    return 0;
}
