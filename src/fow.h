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
      SE    = 1 << 1,
      EAST  = 1 << 2,
      NE    = 1 << 3,
      NORTH = 1 << 4,
      NW    = 1 << 5,
      WEST  = 1 << 6,
      SW    = 1 << 7,
      ALL   = (1 << 8) - 1,
      NONE  = 1 << 8
    };

    FoW(Map *map, ImageManager *imgMgr);
    ~FoW();

    TileIndex getOpposite(TileIndex);
    void set(int x, int y, FogStatus value);
    void set(const sf::Vector2i &coords, FogStatus value);
  private:
    Map *map;
    FogStatus **status;
};

#endif /* _FOW_H_ */
