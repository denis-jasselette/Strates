#ifndef _MAP_H_
#define _MAP_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "config.h"
#include "tileMap.h"

/**
 * Handles a grid of tiles.
 */
class Map {
  public:
    /**
     * Constructs a Map from a file and returns a pointer to it.
     *
     * @param filename    the name of the file to read in the resource
     *                    directory
     * @param imgMgr      the ImageManager to use to load the TileMap
     *
     * @return            a pointer to the Map constructed
     */
    static Map *fromFile(std::string filename, ImageManager *imgMgr);

    /**
     * Destructor.
     */
    ~Map();

    /**
     * Paints the grid of tiles on a RenderTarget.
     *
     * @param target    a pointer to the RenderTarget on which to paint
     */
    void paint(sf::RenderTarget *target);

    /**
     * Returns a version of the IntRect totally contained in the Map in View
     * coordinates.
     *
     * @param rect    the IntRect
     *
     * @return        an IntRect totally contained in the Map and the most
     *                similar to rect as possible
     */
    sf::IntRect clampViewRect(const sf::IntRect &rect);

    sf::Vector2f viewToMapFloatCoords(const sf::Vector2i &coords);

    /**
     * Converts a position in View coordinates to a position in Map
     * coordinates.
     *
     * @param coords    the position in View coordinates
     *
     * @return          the position in Map coordinates
     */
    sf::Vector2i viewToMapCoords(const sf::Vector2i &coords);

    /**
     * Converts an IntRect in View coordinates to an IntRect in Map
     * coordinates.
     *
     * @param viewRect    the IntRect in View coordinates
     *
     * @return            the IntRect in Map coordinates
     */
    sf::IntRect viewToMapRect(const sf::IntRect &viewRect);

    /**
     * Converts a position in Map coordinates to a position in View
     * coordinates.
     *
     * @param coords    the position in Map coordinates
     *
     * @return          the position in View coordinates
     */
    sf::Vector2i mapToViewCoords(const sf::Vector2f &coords);

    /**
     * Converts an IntRect in Map coordinates to an IntRect in View
     * coordinates.
     *
     * @param viewRect    the IntRect in Map coordinates
     *
     * @return            the IntRect in View coordinates
     */
    sf::IntRect mapToViewRect(const sf::Vector2f &coords);

    /**
     * Returns whether a position in Map coordinates is contained in the Map.
     *
     * @param x    the column of the position
     * @param y    the row of the position
     *
     * @return     true if the position is in the Map, false otherwise
     */
    bool contains(int x, int y);

  protected:
    int width, height;
    int **tiles;
    bool deleteTileMap;
    TileMap *tileMap;
    sf::Vector2i viewSize;
    sf::IntRect viewRect;
    sf::IntRect renderedRect;
    sf::RenderTexture *render;
    bool forceRefresh;

    Map(const Map &map, TileMap *tileMap);
    Map(int width, int height, TileMap *tileMap);
    void init(int width, int height, TileMap *tileMap);

    bool rectEqual(sf::IntRect &a, sf::IntRect &b);
    void refresh();
    void checkCacheSize(sf::IntRect &paintRect);
    bool needsCacheRefresh(sf::IntRect &paintRect);
    void refreshCache(sf::IntRect &paintRect);
    void paint(sf::RenderTarget *target,
        const sf::IntRect &paintRect,
        const sf::Vector2i &targetOrig = sf::Vector2i(0, 0));
};

#endif /* _MAP_H_ */
