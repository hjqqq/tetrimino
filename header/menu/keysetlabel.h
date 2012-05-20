#ifndef _KEYSETLABEL_H_
#define _KEYSETLABEL_H_

#include <string>
#include "label.h"
#include "rect.h"
#include "action.h"
#include "color.h"

/**
   @file keysetlabel.h
 */

/**
   @brief 获取按键并blit显示出来
 */
class KeySetLabel : public Label{
 public:
    /**
       @param _rect 初始化blit的位置
       @param _text 初始化label的文本内容
       @param _key 初始化保存的按键
       @param _help 初始化label的帮助信息
       @param _color 初始化blit到菜单的内容的颜色
     */
  KeySetLabel( const Rect<int> &_rect,
	       const std::string &_text,
	       const SDLKey &_key,
	       const std::string &_help = "this is a keysetlabel",
	       const SDL_Color &_color = black );

  virtual ~KeySetLabel();

    /**
       @param event 根据传入的事件获取按键
     */
  virtual void handleEvent(const SDL_Event &event);

    /**
       blit该label的内容和按键到屏幕上
     */
  virtual void update();

 private:
  std::string show_text;
  std::string key_text;
  SDLKey key;
  const SDLKey default_key;
  
  void constructLabelSurface();
  void destroyLabelSurface();
  void act();
    
    /**
       获取按键
     */
  void getUserInput();
  inline void freshShowText();
};

void KeySetLabel::freshShowText()
{
  key_text = SDL_GetKeyName(key);
  show_text = text + " : " + key_text;
}

#endif /* _KEYSETLABEL_H_ */
