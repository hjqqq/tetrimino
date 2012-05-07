#ifndef _TOGGLELABEL_H_
#define _TOGGLELABEL_H_

#include <string>
#include "label.h"

class ToggleLabel : public Label {
 public:
  ToggleLabel(const Rect<int> &_rect,
	      const std::string &_text,
	      const SDL_Color &_color = black,
	      bool _toogle = true);
  virtual ~ToggleLabel();

  virtual void handleEvent(const SDL_Event &event);
  virtual void update();

 private:
  bool toggle;
  std::string toggle_text;

  void letsToggle();
  void freshToggleText();
  virtual void constructLabelSurface();
  void act();
};

#endif /* _TOGGLELABEL_H_ */
