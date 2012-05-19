#ifndef _TOGGLELABEL_H_
#define _TOGGLELABEL_H_

#include <string>
#include "simplelabel.h"

/**
   @file togglelabel.h
 */

/**
   @brief 该label保存两种状态，true&false
 */
class ToggleLabel : public Label {
 public:
    /**
       @param _rect 初始化blit的位置
       @param _text 初始化label的内容
       @param _toggle 初始化状态
       @param _color 初始化blit改内容字体的颜色
     */
  ToggleLabel(const Rect<int> &_rect,
	      const std::string &_text,
	      const bool &_toogle = true,
	      const SDL_Color &_color = black );
  virtual ~ToggleLabel();

    /**
       @param event 根据传入的状态更改状态
     */
  virtual void handleEvent(const SDL_Event &event);

    /**
       blit 该label的内容和状态到屏幕上
     */
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
