#ifndef CIRCLEQUEUE_H
#define CIRCLEQUEUE_H

#include <iostream>
#include <cmath>
#include <cstddef>
#include <iterator>

template <typename T = int>
class CircleIterator{
public:
//    typedef std::bidirectional_iterator_tag iterator_category;
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
    
    inline CircleIterator(pointer _start,
			  pointer _finish);

    template <typename T2>
    friend bool operator==(const CircleIterator<T2> &lhs,
			   const CircleIterator<T2> &rhs);
    template <typename T2>
    friend bool operator!=(const CircleIterator<T2> &lhs,
			   const CircleIterator<T2> &rhs);
        
    inline CircleIterator<T>& operator++();
    inline CircleIterator<T> operator++(int);
    CircleIterator<T>& operator+=(difference_type rhs);

    inline CircleIterator<T>& operator--();
    inline CircleIterator<T> operator--(int);
    CircleIterator<T>& operator-=(difference_type rhs);

    template <typename T2>
    friend ptrdiff_t operator-(const CircleIterator<T2> &lhs,
			       const CircleIterator<T2> &rhs);

    inline reference operator*();

private:
    const pointer start;
    const pointer finish;
    pointer current;
};

template <typename T>
CircleIterator<T>::CircleIterator(pointer _start, pointer _finish):
    start(_start), finish(_finish), current(_start)
{}

template <typename T2>
bool operator==(const CircleIterator<T2> &lhs,
		const CircleIterator<T2> &rhs)
{
    return lhs.current == rhs.current;
}

template <typename T2>
bool operator!=(const CircleIterator<T2> &lhs,
	       const CircleIterator<T2> &rhs)
{
    return lhs.current != rhs.current;
}

template <typename T>
CircleIterator<T>& CircleIterator<T>::operator++()
{
    ++current;
    if (current == finish)
	current = start;
    return *this;
}

template <typename T>
CircleIterator<T> CircleIterator<T>::operator++(int)
{
    const CircleIterator<T> iter(*this);
    ++*this;
    return iter;
}

template <typename T>
CircleIterator<T>& CircleIterator<T>::operator+=(difference_type rhs)
{
    const difference_type distance = (current - start) + rhs;
    const difference_type length = finish - start;
    const difference_type quotient =
	(difference_type)std::floor((double)distance / length);
    const difference_type remainder =
	distance - quotient * length;
    current = start + remainder;
    return *this;
}

template <typename T>
CircleIterator<T> operator+(const CircleIterator<T> &lhs,
			    ptrdiff_t rhs)
{
    CircleIterator<T> result = lhs;
    result += rhs;
    return result; 
}

template <typename T>
CircleIterator<T> operator+(ptrdiff_t lhs,
			    const CircleIterator<T> &rhs)
{
    CircleIterator<T> result = rhs;
    result += lhs;
    return result;
}

template <typename T>
CircleIterator<T>& CircleIterator<T>::operator--()
{
    if (current == start)
	current = finish;
    --current;
    return *this;
}

template <typename T>
CircleIterator<T> CircleIterator<T>::operator--(int)
{
    const CircleIterator<T> iter(*this);
    --*this;
    return iter;
}

template <typename T>
CircleIterator<T>& CircleIterator<T>::operator-=(
    difference_type rhs)
{
    return *this += -rhs;
}

template <typename T>
CircleIterator<T> operator-(const CircleIterator<T> &lhs,
			    ptrdiff_t rhs)
{
    CircleIterator<T> result = lhs;
    result -= rhs;
    return result; 
}

template <typename T2>
ptrdiff_t operator-(const CircleIterator<T2> &lhs,
		    const CircleIterator<T2> &rhs)
{
    return lhs.current - rhs.current; 
}

template <typename T>
typename CircleIterator<T>::reference
CircleIterator<T>::operator*()
{
    return *current;
}

#endif
