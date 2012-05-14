#ifndef _NUMBERLABEL_H_
#define _NUMBERLABEL_H_

#include <string>
#include <cstdlib>
#include "label.h"
#include "utility.h"

class NumberLabel : public Label{
 public:
  NumberLabel(const Rect<int> &_rect,
	      const std::string &_text,
	      const std::string &_unit,
	      const double &_number,
	      const double &_min_number,
	      const double &_max_number,
	      const double &_plus_factor,
	      const SDL_Color &_color = black);
  
  virtual ~NumberLabel();
  
  virtual void handleEvent( const SDL_Event &event);
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
