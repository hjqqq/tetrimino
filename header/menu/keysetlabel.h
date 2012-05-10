#ifndef _KEYSETLABEL_H_
#define _KEYSETLABEL_H_

#include <string>
#include "label.h"
#include "rect.h"
#include "action.h"
#include "color.h"

class KeySetLabel : public Label{
 public:
  KeySetLabel( const Rect<int> &_rect,
	       const std::string &_text,
	       const SDLKey &_key,
	       const SDL_Color &_color = black );

  virtual ~KeySetLabel();
  
  virtual void handleEvent(const SDL_Event &event);
  virtual void update();

 private:
  std::string show_text;
  std::string key_text;
  SDLKey key;
  const SDLKey default_key;
  
  void constructLabelSurface();
  void act();
  void getUserInput();
  inline void freshShowText();
};

void KeySetLabel::freshShowText()
{
  key_text = SDL_GetKeyName(key);
  show_text = text + " : " + key_text;
}

#endif /* _KEYSETLABEL_H_ */
