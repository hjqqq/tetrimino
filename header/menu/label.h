#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "rect.h"
#include "widget.h"
#include "action.h"
#include "color.h"

/**
   @file label.h
 */

/**
   @brief blit一个菜单项。
 */
class Label : public Widget{
public:
    /**
       @param _rect 初始化blit到屏幕的位置
       @param _text 初始化label的文本内容
       @param _help 初始化label的帮助信息
       @param _color 初始化blit文本字体的颜色
     */
    Label(const Rect<int> &_rect,
	  const std::string &_text,
	  const std::string &_help = "this is a label",
	  const SDL_Color &_color = black);
    virtual ~Label();

    /**
       @param event 根据传入的event处理事件
     */
    virtual void handleEvent(const SDL_Event &event) = 0;

    /**
       blit该Label的surface到屏幕上，所有label的派生类必须实现
     */
    virtual void update() = 0;
    
    /*
      @param newColor 更改字体颜色值
     */
    void setColor(const SDL_Color &newColor);

    /*
      @param newText 用于更改label的内容
     */
    void setText(const std::string &newText);

    /*
      @param newHelp 用于更改label的帮助信息
     */
    void setHelp(const std::string &newHelp);

    /**
       @return string 用于获取label的帮助信息
     */
    std::string getHelp();

    /**
       @param Rect<int> 更改blit的位置
     */
    virtual void setRect(const Rect<int> &newRect);
    
 protected:
    /**
       保存label的文本内容
     */
    std::string text;
    
    /**
       保存label的相关帮助信息
     */
    std::string help;

    /**
       保存blit字体的颜色
     */
    SDL_Color color;

    SDL_Rect srcrect, dstrect;

    /**
       将要blit到屏幕上的Surface
     */
    SDL_Surface *labelSurface;

    /**
       创建labelSurface
     */
    virtual void constructLabelSurface() = 0;

    /**
       释放labelSurface
     */
    virtual void destroyLabelSurface() = 0;
};

#endif
