#ifndef _FOW_H_
#define _FOW_H_

#include <SFML/Graphics.hpp>
#include "map.h"
#include "imageManager.h"

/**
 * This class is a Map specialized to handle the "Fog of War".
 */
class FoW : public Map {
  public:
    enum FogType {
      /** Totally opaque */
      DARK = 0,
      /** Partially transparent */
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

    /**
     * Constructor.
     *
     * @param map        a pointer to the Map on which the fog is applied
     * @param tileMap    a pointer to the TileMap to use
     * @param type       the type of fog
     */
    FoW(Map *map, TileMap *tileMap, FogType type = DARK);

    /**
     * Destructor.
     */
    ~FoW();

    /**
     * Sets every cell to a FogStatus.
     *
     * @param value    the FogStatus to set
     */
    void reset(FogStatus value = HIDDEN);

    /**
     * Sets every cell within a given radius of a position to a FogStatus.
     *
     * @param x         the column of the center
     * @param y         the row of the center
     * @param radius    the radius
     * @param value     the FogStatus to set
     */
    void set(int x, int y, int radius, FogStatus value);

    /**
     * Sets every cell within a given radius of a position to a FogStatus.
     *
     * @param coords    the position of the center
     * @param radius    the radius
     * @param value     the FogStatus to set
     */
    void set(const sf::Vector2i &coords, int radius, FogStatus value);

  private:
    Map *map;
    FogStatus **status;
    int origin;

    void setRow(int x1, int x2, int y, FogStatus value);
    void setTile(int x, int y, int value);
    void updateNeighbours(int x, int y);
    void updateTile(int x, int y);
};

#endif /* _FOW_H_ */
