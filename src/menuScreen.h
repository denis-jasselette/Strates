#ifndef _MENUSCREEN_H_
#define _MENUSCREEN_H_

#include <SFML/Graphics.hpp>
#include "application.h"
#include "screens.h"

/**
 * Implements a Screen managing the main menu.
 */
class MenuScreen : public Screen {
  public:
    /**
     * Constructor.
     *
     * @param app    a pointer to the parent Application
     */
    MenuScreen(Application *app);

    ScreenID run();

  private:
    void update();
    void paint(sf::RenderTarget *target);
};

#endif /* _MENUSCREEN_H_ */
