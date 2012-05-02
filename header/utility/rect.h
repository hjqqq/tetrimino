#ifndef RECT_H
#define RECT_H

#include "SDL.h"
#include "vector2.h"

/**
   @file rect.h
 */

/**
   存储了一个矩形的类，使用的坐标的原点是左上角，x 轴水平向右，存储的是矩形左上
   角的坐标 pos 和从左上角指向右下角的向量 diagonal。
 */

template <typename T>
class Rect;

template <typename T>
std::ostream& operator<<(std::ostream &stream, const Rect<T> &rect);

template <typename T>
struct Rect{
    Rect(T posX, T posY, T width, T height);
    Rect(const Vector2<T> &_pos = Vector2<T>(), const Vector2<T> &_diagonal = Vector2<T>());
    Rect(const SDL_Rect &rect);

    inline const SDL_Rect getSDL_Rect() const;
    inline bool isNormal() const;
    
    inline const Vector2<T> getTopLeft() const;
    inline void setTopLeft(const Vector2<T> &value);
    inline const Vector2<T> getBottomLeft() const;
    inline void setBottomLeft(const Vector2<T> &value);
    inline const Vector2<T> getBottomRight() const;
    inline void setBottomRight(const Vector2<T> &value);    
    inline const Vector2<T> getTopRight() const;
    inline void setTopRight(const Vector2<T> &value);

    inline const Vector2<T> getMidTop() const;
    inline void setMidTop(const Vector2<T> &value);
    inline const Vector2<T> getMidLeft() const;
    inline void setMidLeft(const Vector2<T> &value);
    inline const Vector2<T> getMidBottom() const;
    inline void setMidBottom(const Vector2<T> &value);
    inline const Vector2<T> getMidRight() const;
    inline void setMidRight(const Vector2<T> &value);

    inline const Vector2<T> getCenter() const;
    inline void setCenter(const Vector2<T> &value);

    inline void move(T x, T y);
    inline void move(const Vector2<T> &direction);
    void clipRect(const Rect<T> &rect);
    void unionRect(const Rect<T> &rect);

    friend std::ostream& operator<< <>(std::ostream &stream, const Rect<T> &rect);
    
    Vector2<T> pos, diagonal;
};

template <typename T>
Rect<T>::Rect(T posX, T posY, T width, T height):
    pos(Vector2<T>(posX, posY)), diagonal(Vector2<T>(width, height))
{
    if (!this->isNormal())
	pos = diagonal = Vector2<T>();
}

template <typename T>
Rect<T>::Rect(const Vector2<T> &_pos, const Vector2<T> &_diagonal):
    pos(_pos), diagonal(_diagonal)
{
    if (!this->isNormal())
	pos = diagonal = Vector2<T>();
}

template <typename T>
Rect<T>::Rect(const SDL_Rect &rect):
    pos(rect.x, rect.y), diagonal(rect.w, rect.h)
{
    if (!this->isNormal())
	pos = diagonal = Vector2<T>();
}

template <typename T>
const SDL_Rect Rect<T>::getSDL_Rect() const
{
    const SDL_Rect result = {
	(Sint16)pos.x, (Sint16)pos.y,
	(Uint16)diagonal.x, (Uint16)diagonal.y
    };
    return result;
}

template <typename T>
bool Rect<T>::isNormal() const
{
    return (0 <= diagonal.x) && (0 <= diagonal.y);
}

template <typename T>
const Vector2<T> Rect<T>::getTopLeft() const
{
    return pos;
}

template <typename T>
void Rect<T>::setTopLeft(const Vector2<T> &value)
{
    pos = value;
}

template <typename T>
const Vector2<T> Rect<T>::getBottomLeft() const
{
    return Vector2<T>(pos.x, pos.y + diagonal.y);
}

template <typename T>
void Rect<T>::setBottomLeft(const Vector2<T> &value)
{
    const Vector2<T> currentBottomLeft = getBottomLeft();
    const Vector2<T> direction = value - currentBottomLeft;
    move(direction);
}

template <typename T>
const Vector2<T> Rect<T>::getBottomRight() const
{
    return pos + diagonal;
}

template <typename T>
void Rect<T>::setBottomRight(const Vector2<T> &value)
{
    const Vector2<T> currentBottomRight = getBottomRight();
    const Vector2<T> direction = value - currentBottomRight;
    move(direction);
}

template <typename T>
const Vector2<T> Rect<T>::getTopRight() const
{
    return Vector2<T>(pos.x + diagonal.x, pos.y);
}

template <typename T>
void Rect<T>::setTopRight(const Vector2<T> &value)
{
    const Vector2<T> currentTopRight = getTopRight();
    const Vector2<T> direction = value - currentTopRight;
    move(direction);
}

template <typename T>
const Vector2<T> Rect<T>::getMidTop() const
{
    return Vector2<T>(pos.x + diagonal.x / 2, pos.y);
}

template <typename T>
void Rect<T>::setMidTop(const Vector2<T> &value)
{
    const Vector2<T> currentMidTop = getMidTop();
    const Vector2<T> direction = value - currentMidTop;
    move(direction);
}

template <typename T>
const Vector2<T> Rect<T>::getMidLeft() const
{
    return Vector2<T>(pos.x, pos.y + diagonal.y / 2);
}

template <typename T>
void Rect<T>::setMidLeft(const Vector2<T> &value)
{
    const Vector2<T> currentMidLeft = getMidLeft();
    const Vector2<T> direction = value - currentMidLeft;
    move(direction);    
}

template <typename T>
const Vector2<T> Rect<T>::getMidBottom() const
{
    return Vector2<T>(pos.x + diagonal.x / 2, pos.y + diagonal.y);
}

template <typename T>
void Rect<T>::setMidBottom(const Vector2<T> &value)
{
    const Vector2<T> currentMidBottom = getMidBottom();
    const Vector2<T> direction = value - currentMidBottom;
    move(direction);
}

template <typename T>
const Vector2<T> Rect<T>::getMidRight() const
{
    return Vector2<T>(pos.x + diagonal.x, pos.y + diagonal.y / 2);
}

template <typename T>
void Rect<T>::setMidRight(const Vector2<T> &value)
{
    const Vector2<T> currentMidRight = getMidRight();
    const Vector2<T> direction = value - currentMidRight;
    move(direction);
}

template <typename T>
const Vector2<T> Rect<T>::getCenter() const
{
    return Vector2<T>(pos.x + diagonal.x / 2, pos.y + diagonal.y / 2);
}

template <typename T>
void Rect<T>::setCenter(const Vector2<T> &value)
{
    const Vector2<T> currentCenter = getCenter();
    const Vector2<T> direction = value - currentCenter;
    move(direction);
}

template <typename T>
void Rect<T>::move(T x, T y){
    move(Vector2<T>(x, y));
}

template <typename T>
void Rect<T>::move(const Vector2<T> &direction)
{
    pos += direction;
}


template <typename T>
void Rect<T>::clipRect(const Rect<T> &rect)
{
    const Vector2<T> topLeft = getTopLeft(),
	          bottomRight = getBottomRight(),
	          clipTopLeft = rect.getTopLeft(),
	          clipBottomRight = rect.getBottomRight();
	
    const Vector2<T> newTopLeft = Vector2<T>(
	std::max(topLeft.x, clipTopLeft.x),
	std::max(topLeft.y, clipTopLeft.y));
    const Vector2<T> newBottomRight = Vector2<T>(
	std::min(bottomRight.x, clipBottomRight.x),
	std::min(bottomRight.y, clipBottomRight.y));

    pos = newTopLeft;
    diagonal = newBottomRight - newTopLeft;
    if (!isNormal())
	pos = diagonal = Vector2<T>();
}

template <typename T>
void Rect<T>::unionRect(const Rect<T> &rect)
{
    const Vector2<T> topLeft = getTopLeft(),
	          bottomRight = getBottomRight(),
	          unionTopLeft = rect.getTopLeft(),
	          unionBottomRight = rect.getBottomRight();
	
    const Vector2<T> newTopLeft = Vector2<T>(
	std::min(topLeft.x, unionTopLeft.x),
	std::min(topLeft.y, unionTopLeft.y));
    const Vector2<T> newBottomRight = Vector2<T>(
	std::max(bottomRight.x, unionBottomRight.x),
	std::max(bottomRight.y, unionBottomRight.y));

    pos = newTopLeft;
    diagonal = newBottomRight - newTopLeft;
}

template <typename T>
std::ostream& operator<<(std::ostream &stream, const Rect<T> &rect)
{
    return stream << "[" << rect.pos << ", " << rect.diagonal << "]";
}

#endif
