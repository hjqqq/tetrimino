#ifndef _NUMBERLABEL_H_
#define _NUMBERLABEL_H_

#include <string>
#include <cstdlib>
#include "label.h"
#include "utility.h"
/**
   @file numberlabel.h
 */

/**
   @brief 获取一个double值并显示出来
 */
class NumberLabel : public Label{
 public:
    /**
       @param _rect 初始化blit的位置
       @param _text 初始化label的内容
       @param _unit 初始化该label保存数值单位
       @param _number 初始化保存的数值
       @param _min_number 初始化保存数值的下限
       @param _max_number 初始化保存数值的上限
       @param _plus_factor 初始化每次增减数值的大小
       @param _color 初始化blit该label内容字体的颜色
     */
  NumberLabel(const Rect<int> &_rect,
	      const std::string &_text,
	      const std::string &_unit,
	      const double &_number,
	      const double &_min_number,
	      const double &_max_number,
	      const double &_plus_factor,
	      const SDL_Color &_color = black);
  
  virtual ~NumberLabel();

    /**
       根据传入的时间更改或增减数值
     */
  virtual void handleEvent( const SDL_Event &event);

    /**
       blit 该label的内容和数值到屏幕上
     */
  virtual void update();
  
 private:
  double number;
  double default_number;
  const double PLUS_FACTOR;
  const double MIN_NUMBER;
  const double MAX_NUMBER;
  const std::string UNIT;
  std::string number_text;
  std::string show_text;
  bool input_state;

  void constructLabelSurface();
  void destroyLabelSurface();
  void getUserInput(const SDL_Event&);
  void toggleInputState();

  inline void freshShowText();
  inline void syncToNumber();
  inline void syncToNumberText();
  void reset();
  void act();
  
};

void NumberLabel::syncToNumber()
{
  number = atof(number_text.c_str());
}

void NumberLabel::syncToNumberText()
{
  doubleToString(number, number_text);
}

void NumberLabel::freshShowText()
{
  show_text = text + " : " + number_text + " " + UNIT;
}

#endif /* _NUMBERLABEL_H_ */
