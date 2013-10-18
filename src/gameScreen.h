#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_

#include "application.h"
#include "screen.h"
#include "game.h"
#include "hud.h"

/**
 * Implements a Screen managing the game.
 */
class GameScreen : public Screen {
  public:
    /**
     * Constructor.
     *
     * @param app    a pointer to the parent Application
     */
    GameScreen(Application *app);

    ScreenID run();

  private:
    bool focus;
    Game *game;
    Hud hud;
    ScreenID nextScreen;

    void onEvent(sf::Event &evt);
    void exit();
    void tick(sf::RenderTarget *target);
    void scroll();
    void update();
    void paintDebug(sf::RenderTarget *target);
    void paint(sf::RenderTarget *target);
    void onResized(sf::Event &evt);
    void onKeyReleased(sf::Event &evt);
    void onMouseWheelMoved(sf::Event &evt);
    void onMouseButtonPressed(sf::Event &evt);
    void onMouseButtonReleased(sf::Event &evt);
    void onMouseMoved(sf::Event &evt);
};

#endif /* _GAMESCREEN_H_ */
