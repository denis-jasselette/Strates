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

 private:
  AI();
 
  Game *game;
};


#endif /* _AI_H_ */
