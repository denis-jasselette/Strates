#ifndef _GAME_H_
#define	_GAME_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "cursor.h"
#include "map.h"

class Game {
  public:
    Game();
    ~Game();
    void run();
    void exit();

  private:
    void paintDebug();
    void paint();

    void onEvent(sf::Event&);
    void onKeyReleased(sf::Event&);

    bool running;
    sf::RenderWindow *window;
    Cursor *cursor;
    ImageManager *imageMgr;
    Map *map;
};

#endif	/* _GAME_H_ */
