#ifndef _GAME_H_
#define	_GAME_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "cursor.h"
#include "map.h"
#include "fow.h"

class Game {
  public:
    Game();
    ~Game();
    void run();
    void exit();

  private:
    void select();

    void paintDebug();
    void paint();

    void update();

    void onEvent(sf::Event&);
    void onKeyReleased(sf::Event&);
    void onMouseButtonPressed(sf::Event&);

    bool running;
    sf::RenderWindow *window;
    Cursor *cursor;
    ImageManager *imageMgr;
    Map *map;
    FoW *fog;
};

#endif	/* _GAME_H_ */
