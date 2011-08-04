#ifndef _GAME_H_
#define	_GAME_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "cursor.h"
#include "map.h"
#include "tileMap.h"
#include "fow.h"

class Game {
  public:
    Game();
    ~Game();
    void run();
    void exit();

  private:
    void toggleFullscreen();

    void select();

    void paintDebug();
    void paint();

    void update();

    void onEvent(sf::Event&);
    void onKeyReleased(sf::Event&);
    void onMouseWheelMoved(sf::Event&);
    void onMouseButtonPressed(sf::Event&);

    bool running, isFullscreen;
    sf::RenderWindow *window;
    Cursor *cursor;
    int radius;
    ImageManager *imageMgr;
    Map *map;
    TileMap *fogTileMap;
    FoW *fog, *foglight;
};

#endif	/* _GAME_H_ */
