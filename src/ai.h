#ifndef _AI_H_
#define _AI_H_

#include "game.h"
#include "unit.h"

class AI {
 public:
  static AI& getInstance()
  {
    static AI singleton;
    return singleton;
  }

  void init(Game *game);
  void computePath(Unit *e, const sf::Vector2i &coords);
  void prepareAccMap(std::vector<Entity*> &exclude);
 private:
  AI();
 
  Game *game;
  std::vector<bool> accMap;
};


#endif /* _AI_H_ */
