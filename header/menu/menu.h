#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

#include "SDL.h"
#include "label.h"
/**
   @file menu.h
*/

/**
   @brief 保存多个Label，blit一页菜单
 */
class Menu : public Widget{
public:
    /**
       初始化菜单的内容
       @param _rect 保存blit菜单的位置
     */
    Menu(const Rect<int> &_rect);
    ~Menu();

    /**
       @param label 添加一个菜单项，传入Label子类对象的指针
     */
    void addLabel(Label *label);

    /**
       对保存的label按照竖直方向blit
     */
    void verticalLayout();

    /**
       @param event 对传入的event分发给label处理
     */
    virtual void handleEvent(const SDL_Event &event);

    /**
       blit一页菜单
     */
    virtual void update();

    /**
       @param newRect 设置菜单blit的位置和范围
     */
    virtual void setRect(const Rect<int> &newRect);

    /**
       激活前一个label
     */
    void selectPrevious();

    /**
       激活下一个label
     */
    void selectNext();

    /**
       @return int 返回选择的label标号，从0开始自上而下
     */
    int getSelect() const;

    /**
       @param index 激活给定标号的label
     */
    void setSelect(int index);

    /**
       激活标号为0的label
     */
    inline void resetSelect();
    
private:
    /**
       @param sym 处理传入的按键
     */
    void handleKey(const SDLKey &sym);

    /**
       根据选中label位置blit菜单的选中效果
     */
    void updateSelect();

    /**
       菜单的选中背景效果
     */
    SDL_Surface *menufg;

    /**
       选中背景效果图片的文件名
     */
    std::string image_file;

    /**
       保存添加的label
     */
    std::vector<Label*> labelVector;

    /**
       当前菜单选中的label的标号
     */
    int select;
};

void Menu::resetSelect()
{
  select = 0;
}
#endif
