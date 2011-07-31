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
  private:
    int width, height;
    int **tiles;
    TileMap *tileMap;
    sf::Vector2i viewSize;
    sf::IntRect viewRect;
    sf::IntRect renderedRect;
    sf::RenderImage *render;

    Map(int width, int height, TileMap *tileMap);
    void paint(sf::RenderTarget *target, sf::IntRect &paintRect);
};

#endif /* _MAP_H_ */
