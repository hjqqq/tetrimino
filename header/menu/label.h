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
	  Action *_action,
	  const std::string &_text,
	  const SDL_Color &_color = black);
    virtual ~Label();

    virtual void handleEvent(const SDL_Event &event);
    virtual void update();
    
    void setColor(const SDL_Color &newColor);
    void setText(const std::string &newText);

    virtual void setRect(const Rect<int> &newRect);
    
private:
    void constructLabelSurface();
    void destroyLabelSurface();
    
    std::string text;
    SDL_Color color;
    
    SDL_Rect srcrect, dstrect;
    SDL_Surface *labelSurface;
};

#endif
