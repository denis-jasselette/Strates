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
      S,
      E,
      N,
      W,
      SW,
      SE,
      NE,
      NW,
      SSE,
      NNE,
      NNW,
      SSW,
      ALL,
      NONE
    };

    FoW(Map *map, ImageManager *imgMgr);
    ~FoW();

    void set(int x, int y, FogStatus value);
    void set(const sf::Vector2i &coords, FogStatus value);
  private:
    Map *map;
    FogStatus **status;

    void updateNeighbours(int x, int y);
};

#endif /* _FOW_H_ */
