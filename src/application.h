#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "cursor.h"

class Screen;
#include "screen.h"

class Application {
  public:
    Application();
    ~Application();

    int run();
    void setFullscreen(bool value);
    void toggleFullscreen();
    sf::RenderWindow *getWindow();
    ImageManager *getImgMgr();
    Cursor *getCursor();
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
