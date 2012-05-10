#include <iostream>

class Base{
public:
    Base(){
	std::cerr << "create!!!\n";
    }
    ~Base(){
	std::cerr << "destroy!!!\n";
    }
} base;

class Ha{
public:
    Ha(){
	base = new Base();
    }
    static Base *base;
};

Base *Ha::base = NULL;

int main()
{
    Ha ha;
    return 0;
}
