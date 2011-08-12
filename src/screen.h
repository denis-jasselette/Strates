#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <SFML/Graphics.hpp>

enum ScreenID {
  SCREEN_THIS = -2,
  SCREEN_EXIT = -1,
  SCREEN_GAME,
  SCREEN_MENU,
};

class Application;
#include "application.h"

class Screen {
  public:
    Screen(Application *app);
    virtual ~Screen();

    virtual ScreenID run() = 0;
  protected:
    Application *app;
};

#endif /* _SCREEN_H_ */
