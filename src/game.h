#ifndef _GAME_H_
#define	_GAME_H_

#include <SFML/Graphics.hpp>
#include "application.h"
#include "techTree.h"
#include "map.h"
#include "player.h"
#include "tileMap.h"
#include "fow.h"

class Game {
  public:
    Game(Application *app);
    ~Game();

    void paint();
    void update();
    int getRadius();
    void setRadius(int radius);
  private:
    void select();

    Application *app;
    int radius;
    TechTree *techTree;
    Map *map;
    std::vector<Player*> players;
    TileMap *fogTileMap;
    FoW *fog, *foglight;
};

#endif	/* _GAME_H_ */
