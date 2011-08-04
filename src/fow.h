#ifndef _FOW_H_
#define _FOW_H_

#include <SFML/Graphics.hpp>
#include "map.h"
#include "imageManager.h"

class FoW : public Map {
  public:
    enum FogType {
      DARK = 0,
      LIGHT = 16
    };

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

    FoW(Map *map, TileMap *tileMap, FogType type = DARK);
    ~FoW();

    void set(int x, int y, FogStatus value);
    void set(const sf::Vector2i &coords, FogStatus value);
  private:
    Map *map;
    FogStatus **status;
    int origin;

    void updateNeighbours(int x, int y);
    void updateTile(int x, int y);
};

#endif /* _FOW_H_ */
