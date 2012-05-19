#ifndef QUITLABEL_H
#define QUITLABEL_H

#include <string>

#include "label.h"
#include "color.h"

/**
   @file quitlabel.h
 */

/**
   @brief 用来显示游戏过程中按下 Esc 所出现的暂停中的文字。

   从 menu/togglelable.h 中来的，但是退化了，没有回调函数，仅是单纯的打印通过左
   右可以改变的 “Yes” “No”。
 */
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

#endif
