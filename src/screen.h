#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <SFML/Graphics.hpp>

class Application;
#include "application.h"

class Screen {
  public:
    Screen(Application *app);
    virtual ~Screen();

    virtual int run(sf::RenderWindow &window) = 0;
  protected:
    Application *app;
};

#endif /* _SCREEN_H_ */
