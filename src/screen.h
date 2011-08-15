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

/**
 * This class is a basis to implement screens run by an Application.
 */
class Screen {
  public:
    /**
     * Constructor.
     *
     * @param app    a pointer to the parent Application
     */
    Screen(Application *app);

    /**
     * Virtual destructor.
     */
    virtual ~Screen();

    /**
     * Method that is called by Application.
     *
     * When called, the Screen takes control of the event loop and the window
     * in general.
     *
     * @return    the ScreenID of the next Screen the Application should run
     */
    virtual ScreenID run() = 0;

  protected:
    /**
     * Pointer to the parent Application.
     */
    Application *app;
};

#endif /* _SCREEN_H_ */
