#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "cursor.h"

class Screen;
#include "screen.h"

/**
 * Handles the whole application and generates its own window.
 */
class Application {
  public:
    /**
     * Default constructor.
     *
     * Nothing is displayed until run() is called.
     */
    Application();

    /**
     * Destructor.
     */
    ~Application();

    /**
     * Displays the application and returns an exit code when it terminates.
     *
     * The exit code follows the same conventions as main(): 0 = no error, any
     * other integer = error.
     *
     * @return    exit code
     */
    int run();

    /**
     * Switches to windowed or fullscreen mode.
     *
     * @param value    go to fullscreen mode if true, windowed mode otherwise
     */
    void setFullscreen(bool value);

    /**
     * Switches between windowed and fullscreen modes.
     */
    void toggleFullscreen();

    /**
     * Returns the main RenderWindow in which the Application is displayed.
     *
     * @return    a pointer to the main RenderWindow
     */
    sf::RenderWindow *getWindow();

    /**
     * Returns the main ImageManager used by this Application.
     *
     * @return    a pointer to the main ImageManager
     */
    ImageManager *getImgMgr();

    /**
     * Returns the only Cursor displayed by this Application.
     *
     * @return    a pointer to the Cursor
     */
    Cursor *getCursor();

    /**
     * Returns the Cursor's position using View coordinates.
     *
     * @return    the Cursor's position
     */
    sf::Vector2i getCursorPosition();

  private:
    sf::RenderWindow window;
    std::vector<Screen*> screens;
    ScreenID current;
    bool isFullscreen;
    ImageManager *imgMgr;
    Cursor *cursor;
};

#endif /* _APPLICATION_H_ */
