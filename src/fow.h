#ifndef _FOW_H_
#define _FOW_H_

#include <SFML/Graphics.hpp>
#include "map.h"
#include "imageManager.h"

class FoW : public Map {
  public:
    enum FogStatus {
      HIDDEN, REVEALED
    };

    enum TileIndex {
      SOUTH = 1,
      EAST  = 1 << 1,
      NORTH = 1 << 2,
      WEST  = 1 << 3,
      NONE  = 1<< 4
    };

    FoW(Map *map, ImageManager *imgMgr);
    ~FoW();

    void set(int x, int y, FogStatus value);
    void set(const sf::Vector2i &coords, FogStatus value);
  private:
    Map *map;
    FogStatus **status;
};

#endif /* _FOW_H_ */
