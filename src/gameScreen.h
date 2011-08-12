#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_

#include "application.h"
#include "screen.h"
#include "game.h"
#include "hud.h"

class GameScreen : public Screen {
  public:
    GameScreen(Application *app);

    ScreenID run();
  private:
    Game game;
    Hud hud;
    ScreenID nextScreen;

    void onEvent(sf::Event &evt);
    void exit();
    void update();
    void paintDebug();
    void paint();
    void onResized(sf::Event &evt);
    void onKeyReleased(sf::Event &evt);
    void onMouseWheelMoved(sf::Event &evt);
    void onMouseButtonPressed(sf::Event &evt);
};

#endif /* _GAMESCREEN_H_ */