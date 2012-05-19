/*#ifndef _MENUBG_H_
#define _MENUBG_H_

#include <string>
#include "SDL.h"
#include "rect.h"

class MenuBG {
 public:
  MenuBG( const int &, const SDL_Rect &outside, const SDL_Rect &inside);
  virtual ~MenuBG();

  SDL_Rect  getPos();

 private:
  Rect<int>
  const int count;
  
  void freshPos();
};

#endif /* _MENUBG_H_ */
*/
