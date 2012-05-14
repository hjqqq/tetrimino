#ifndef _TOGGLELABEL_H_
#define _TOGGLELABEL_H_

#include <string>
#include "simplelabel.h"

class ToggleLabel : public Label {
 public:
  ToggleLabel(const Rect<int> &_rect,
	      const std::string &_text,
	      const bool &_toogle = true,
	      const SDL_Color &_color = black );
  virtual ~ToggleLabel();

  virtual void handleEvent(const SDL_Event &event);
  virtual void update();

 protected:
  bool toggle;
  std::string toggle_text;

  void letsToggle();
  void freshToggleText();
  virtual void constructLabelSurface();
  virtual void destroyLabelSurface();
  void act();
};

#endif /* _TOGGLELABEL_H_ */
