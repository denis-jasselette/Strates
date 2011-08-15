#ifndef _MENUSCREEN_H_
#define _MENUSCREEN_H_

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
};

#endif /* _MENUSCREEN_H_ */
