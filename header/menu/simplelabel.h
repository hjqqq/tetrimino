#ifndef SIMPLELABEL_H
#define SIMPLELABEL_H

#include <string>
#include "rect.h"
#include "label.h"
#include "action.h"
#include "color.h"

class SimpleLabel : public Label{
 public:
  SimpleLabel(const Rect<int> &_rect,
	      const std::string &_text,
	      const SDL_Color &_color = black);
  virtual ~SimpleLabel();
  
  virtual void handleEvent(const SDL_Event &event);
  virtual void update();
    
 protected:
  virtual void constructLabelSurface();
  void destroyLabelSurface();
 
};

#endif
