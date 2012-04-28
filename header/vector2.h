#ifndef VECTOR2_H
#define VECTOR2_H

#include <ostream>
#include <cmath>

struct Vector2{
    inline Vector2(double _x = 0, double _y = 0);
    inline double getLength() const;
    void setLength(double length);
    inline void normalize();

    inline Vector2& operator+=(const Vector2 &rhs);
    inline Vector2& operator-=(const Vector2 &rhs);
    inline Vector2& operator*=(double scalar);
    inline Vector2& operator/=(double scalar);

    friend inline const Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs);
    friend inline const Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs);
    friend inline const Vector2 operator-(const Vector2 &value);
    friend inline const Vector2 operator*(const Vector2 &value, double scalar);
    friend inline const Vector2 operator*(double scalar, const Vector2 &value);
    friend inline const Vector2 operator/(const Vector2 &value, double scalar);

    friend inline std::ostream& operator<<(std::ostream &stream, const Vector2 &value);
    
    double x, y;
};

Vector2::Vector2(double _x, double _y):
    x(_x), y(_y)
{};

double Vector2::getLength() const
{
    return std::sqrt(x * x + y * y);	
}

void Vector2::normalize()
{
    *this /= this->getLength();
}

Vector2& Vector2::operator+=(const Vector2 &rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vector2& Vector2::operator*=(double scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator/=(double scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

const Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs)
{
    return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

const Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs)
{
    return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

const Vector2 operator-(const Vector2 &value)
{
    return Vector2(-value.x, -value.y);
}

const Vector2 operator*(const Vector2 &value, double scalar)
{
    return Vector2(value.x * scalar, value.y * scalar);
}

const Vector2 operator*(double scalar, const Vector2 &value)
{
    return Vector2(scalar * value.x, scalar * value.y);
}

const Vector2 operator/(const Vector2 &value, double scalar)
{
    return Vector2(value.x / scalar, value.y / scalar);
}

std::ostream& operator<<(std::ostream &stream, const Vector2 &value)
{
    return stream << "(" << value.x << ", " << value.y << ")";
}



#endif
