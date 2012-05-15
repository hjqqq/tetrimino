#ifndef _QUITLABEL_H_
#define _QUITLABEL_H_

#include <string>

#include "label.h"
#include "color.h"

class QuitLabel : public Label {
public:
    QuitLabel(const Rect<int> &_rect,
	      const std::string &_text,
	      const SDL_Color &_color = black,
      	      bool _toogle = false);
    virtual ~QuitLabel();

    virtual void handleEvent(const SDL_Event &event);
    virtual void update();
    
    bool getToggle();

protected:
    bool toggle;
    virtual void constructLabelSurface();
    virtual void destroyLabelSurface();
    void act();
};

#endif /* _TOGGLELABEL_H_ */
