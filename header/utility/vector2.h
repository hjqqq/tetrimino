#ifndef VECTOR2_H
#define VECTOR2_H

#include <ostream>
#include <cmath>

template <typename T>
class Vector2;

template <typename T>
inline const Vector2<T> operator+(const Vector2<T> &lhs, const Vector2<T> &rhs);

template <typename T>
inline const Vector2<T> operator-(const Vector2<T> &lhs, const Vector2<T> &rhs);

template <typename T>
inline const Vector2<T> operator-(const Vector2<T> &value);

template <typename T>
inline const Vector2<T> operator*(const Vector2<T> &value, T scalar);

template <typename T>
inline const Vector2<T> operator*(T scalar, const Vector2<T> &value);

template <typename T>
inline const Vector2<T> operator/(const Vector2<T> &value, T scalar);

template <typename T>
inline std::ostream& operator<<(std::ostream &stream, const Vector2<T> &value);

template <typename T>
inline const bool operator==(const Vector2<T> &lhs, const Vector2<T> rhs);

template <typename T>
inline const bool operator!=(const Vector2<T> &lhs, const Vector2<T> rhs);    

template <typename T = int>
struct Vector2{
    inline Vector2(T _x = 0, T _y = 0);
    inline double getLength() const;
    void setLength(double length);
    inline void normalize();

    inline Vector2& operator+=(const Vector2 &rhs);
    inline Vector2& operator-=(const Vector2 &rhs);
    inline Vector2& operator*=(T scalar);
    inline Vector2& operator/=(T scalar);

    friend const Vector2<T> operator+<>(const Vector2<T> &lhs, const Vector2<T> &rhs);
    friend const Vector2<T> operator-<>(const Vector2<T> &lhs, const Vector2<T> &rhs);
    friend const Vector2<T> operator-<>(const Vector2<T> &value);
    friend const Vector2<T> operator*<>(const Vector2<T> &value, T scalar);
    friend const Vector2<T> operator*<>(T scalar, const Vector2<T> &value);
    friend const Vector2<T> operator/<>(const Vector2<T> &value, T scalar);

    friend const bool operator==<>(const Vector2<T> &lhs, const Vector2<T> rhs);
    friend const bool operator!=<>(const Vector2<T> &lhs, const Vector2<T> rhs);

    friend std::ostream& operator<< <>(std::ostream &stream, const Vector2<T> &value);
    
    T x, y;
};

template <typename T>
Vector2<T>::Vector2(T _x, T _y):
    x(_x), y(_y)
{};

template <typename T>
double Vector2<T>::getLength() const
{
    return std::sqrt(x * x + y * y);	
}

template <typename T>
void Vector2<T>::setLength(double length)
{
    if (length == 0)
	x = y = 0;
    else{
	*this *= length / this->getLength();
    }
}

template <typename T>
void Vector2<T>::normalize()
{
    *this /= this->getLength();
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T> &rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T> &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(T scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(T scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}
template <typename T>
const Vector2<T> operator+(const Vector2<T> &lhs, const Vector2<T> &rhs)
{
    return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename T>
const Vector2<T> operator-(const Vector2<T> &lhs, const Vector2<T> &rhs)
{
    return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename T>
const Vector2<T> operator-(const Vector2<T> &value)
{
    return Vector2<T>(-value.x, -value.y);
}

template <typename T>
const Vector2<T> operator*(const Vector2<T> &value, T scalar)
{
    return Vector2<T>(value.x * scalar, value.y * scalar);
}

template <typename T>
const Vector2<T> operator*(T scalar, const Vector2<T> &value)
{
    return Vector2<T>(scalar * value.x, scalar * value.y);
}

template <typename T>
const Vector2<T> operator/(const Vector2<T> &value, T scalar)
{
    return Vector2<T>(value.x / scalar, value.y / scalar);
}

template <typename T>
std::ostream& operator<<(std::ostream &stream, const Vector2<T> &value)
{
    return stream << "(" << value.x << ", " << value.y << ")";
}

template <typename T>
const bool operator==(const Vector2<T> &lhs, const Vector2<T> rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <typename T>
const bool operator!=(const Vector2<T> &lhs, const Vector2<T> rhs)
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

#endif
