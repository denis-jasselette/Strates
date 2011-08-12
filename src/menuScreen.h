#ifndef _MENUSCREEN_H_
#define _MENUSCREEN_H_

#include "application.h"
#include "screens.h"

class MenuScreen : public Screen {
  public:
    MenuScreen(Application *app);

    int run(sf::RenderWindow &window);
  private:
    Application *app;
};

#endif /* _MENUSCREEN_H_ */
