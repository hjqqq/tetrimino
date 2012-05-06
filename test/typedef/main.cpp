#include <iostream>
#include <iterator>

template <typename T>
class Base{
public:
    typedef T value_type;
};

class Derived : public Base<int>{
public:
    value_type data;
};

template <typename T>
class MyIter :
    public std::iterator<std::random_access_iterator_tag, T>{
public:
    value_type foo(pointer point);
    value_type data;
    
};

template <typename T>
typename MyIter<T>::value_type MyIter<T>::foo(
    pointer point)
{
    return *point;
}

int main()
{
    Derived derived;
    derived.data = 100;
    std::cout << derived.data << std::endl;

    MyIter<int> myIter;
    myIter.data = 200;
    std::cout << myIter.data << std::endl;

    int n = 300;
    std::cout << myIter.foo(&n) << std::endl;
    return 0;
}
