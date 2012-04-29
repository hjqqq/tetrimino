#include <algorithm>
#include "rect.h"

Rect::Rect(double posX, double posY, double width, double height):
    pos(Vector2(posX, posY)), diagonal(Vector2(width, height))
{
    if (!this->isNormal())
	pos = diagonal = Vector2();
}

Rect::Rect(const Vector2 &_pos, const Vector2 &_diagonal):
    pos(_pos), diagonal(_diagonal)
{
    if (!this->isNormal())
	pos = diagonal = Vector2();
}

Rect::Rect(const SDL_Rect &rect):
    pos(rect.x, rect.y), diagonal(rect.w, rect.h)
{
    if (!this->isNormal())
	pos = diagonal = Vector2();
}

void Rect::clipRect(const Rect &rect)
{
    const Vector2 topLeft = getTopLeft(),
	          bottomRight = getBottomRight(),
	          clipTopLeft = rect.getTopLeft(),
	          clipBottomRight = rect.getBottomRight();
	
    const Vector2 newTopLeft = Vector2(
	std::max(topLeft.x, clipTopLeft.x),
	std::max(topLeft.y, clipTopLeft.y));
    const Vector2 newBottomRight = Vector2(
	std::min(bottomRight.x, clipBottomRight.x),
	std::min(bottomRight.y, clipBottomRight.y));

    pos = newTopLeft;
    diagonal = newBottomRight - newTopLeft;
    if (!isNormal())
	pos = diagonal = Vector2();
}

void Rect::unionRect(const Rect &rect)
{
    const Vector2 topLeft = getTopLeft(),
	          bottomRight = getBottomRight(),
	          unionTopLeft = rect.getTopLeft(),
	          unionBottomRight = rect.getBottomRight();
	
    const Vector2 newTopLeft = Vector2(
	std::min(topLeft.x, unionTopLeft.x),
	std::min(topLeft.y, unionTopLeft.y));
    const Vector2 newBottomRight = Vector2(
	std::max(bottomRight.x, unionBottomRight.x),
	std::max(bottomRight.y, unionBottomRight.y));

    pos = newTopLeft;
    diagonal = newBottomRight - newTopLeft;
}

std::ostream& operator<<(std::ostream &stream, const Rect &rect)
{
    return stream << "[" << rect.pos << ", " << rect.diagonal << "]";
}
