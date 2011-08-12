#ifndef _MAP_H_
#define _MAP_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "config.h"
#include "tileMap.h"

class Map {
  public:
    static Map *fromFile(std::string filename, ImageManager *imgMgr);
    ~Map();

    void paint(sf::RenderTarget *target);
    sf::IntRect clampViewRect(const sf::IntRect &rect);
    sf::Vector2i viewToMapCoords(sf::Vector2i &coords);
    sf::IntRect viewToMapRect(sf::IntRect &viewRect);
    sf::Vector2i mapToViewCoords(sf::Vector2i &coords);
    sf::IntRect mapToViewRect(sf::Vector2i &coords);
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
