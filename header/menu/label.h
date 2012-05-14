#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "rect.h"
#include "widget.h"
#include "action.h"
#include "color.h"

class Label : public Widget{
public:
    Label(const Rect<int> &_rect,
	  const std::string &_text,
	  const SDL_Color &_color = black);
    virtual ~Label();

    virtual void handleEvent(const SDL_Event &event) = 0;
    virtual void update() = 0;
    
    void setColor(const SDL_Color &newColor);
    void setText(const std::string &newText);

    virtual void setRect(const Rect<int> &newRect);
    
 protected:
    std::string text;
    SDL_Color color;
    SDL_Rect srcrect, dstrect;
    SDL_Surface *labelSurface;
    
    virtual void constructLabelSurface() = 0;
    virtual void destroyLabelSurface() = 0;
};

#endif
