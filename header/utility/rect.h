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
struct Rect{
    Rect(double posX, double posY, double width, double height);
    Rect(const Vector2 &_pos = Vector2(), const Vector2 &_diagonal = Vector2());
    Rect(const SDL_Rect &rect);

    inline const SDL_Rect getSDL_Rect() const;
    inline bool isNormal() const;
    
    inline const Vector2 getTopLeft() const;
    inline void setTopLeft(const Vector2 &value);
    inline const Vector2 getBottomLeft() const;
    inline void setBottomLeft(const Vector2 &value);
    inline const Vector2 getBottomRight() const;
    inline void setBottomRight(const Vector2 &value);    
    inline const Vector2 getTopRight() const;
    inline void setTopRight(const Vector2 &value);

    inline const Vector2 getMidTop() const;
    inline void setMidTop(const Vector2 &value);
    inline const Vector2 getMidLeft() const;
    inline void setMidLeft(const Vector2 &value);
    inline const Vector2 getMidBottom() const;
    inline void setMidBottom(const Vector2 &value);
    inline const Vector2 getMidRight() const;
    inline void setMidRight(const Vector2 &value);

    inline const Vector2 getCenter() const;
    inline void setCenter(const Vector2 &value);
    
    inline void move(const Vector2 &direction);
    void clipRect(const Rect &rect);
    void unionRect(const Rect &rect);

    friend std::ostream& operator<<(std::ostream &stream, const Rect &rect);
    
    Vector2 pos, diagonal;
};


const SDL_Rect Rect::getSDL_Rect() const
{
    const SDL_Rect result = {
	(Sint16)pos.x, (Sint16)pos.y,
	(Uint16)diagonal.x, (Uint16)diagonal.y
    };
    return result;
}

bool Rect::isNormal() const
{
    return (0 <= diagonal.x) && (0 <= diagonal.y);
}

const Vector2 Rect::getTopLeft() const
{
    return pos;
}

void Rect::setTopLeft(const Vector2 &value)
{
    pos = value;
}

const Vector2 Rect::getBottomLeft() const
{
    return Vector2(pos.x, pos.y + diagonal.y);
}

void Rect::setBottomLeft(const Vector2 &value)
{
    const Vector2 currentBottomLeft = getBottomLeft();
    const Vector2 direction = value - currentBottomLeft;
    move(direction);
}

const Vector2 Rect::getBottomRight() const
{
    return pos + diagonal;
}

void Rect::setBottomRight(const Vector2 &value)
{
    const Vector2 currentBottomRight = getBottomRight();
    const Vector2 direction = value - currentBottomRight;
    move(direction);
}

const Vector2 Rect::getTopRight() const
{
    return Vector2(pos.x + diagonal.x, pos.y);
}

void Rect::setTopRight(const Vector2 &value)
{
    const Vector2 currentTopRight = getTopRight();
    const Vector2 direction = value - currentTopRight;
    move(direction);
}

const Vector2 Rect::getMidTop() const
{
    return Vector2(pos.x + diagonal.x / 2, pos.y);
}

void Rect::setMidTop(const Vector2 &value)
{
    const Vector2 currentMidTop = getMidTop();
    const Vector2 direction = value - currentMidTop;
    move(direction);
}

const Vector2 Rect::getMidLeft() const
{
    return Vector2(pos.x, pos.y + diagonal.y / 2);
}

void Rect::setMidLeft(const Vector2 &value)
{
    const Vector2 currentMidLeft = getMidLeft();
    const Vector2 direction = value - currentMidLeft;
    move(direction);    
}

const Vector2 Rect::getMidBottom() const
{
    return Vector2(pos.x + diagonal.x / 2, pos.y + diagonal.y);
}

void Rect::setMidBottom(const Vector2 &value)
{
    const Vector2 currentMidBottom = getMidBottom();
    const Vector2 direction = value - currentMidBottom;
    move(direction);
}

const Vector2 Rect::getMidRight() const
{
    return Vector2(pos.x + diagonal.x, pos.y + diagonal.y / 2);
}

void Rect::setMidRight(const Vector2 &value)
{
    const Vector2 currentMidRight = getMidRight();
    const Vector2 direction = value - currentMidRight;
    move(direction);
}

const Vector2 Rect::getCenter() const
{
    return Vector2(pos.x + diagonal.x / 2, pos.y + diagonal.y / 2);
}

void Rect::setCenter(const Vector2 &value)
{
    const Vector2 currentCenter = getCenter();
    const Vector2 direction = value - currentCenter;
    move(direction);
}

void Rect::move(const Vector2 &direction)
{
    pos += direction;
}

#endif
