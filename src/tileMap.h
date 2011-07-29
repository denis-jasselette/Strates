#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "config.h"
#include "imageManager.h"

class TileMap {
  public:
    TileMap(std::string, ImageManager*);
    ~TileMap();

    sf::Sprite *get(int);
    sf::Vector2i convertCoords(int, int);

  private:
    std::string name;
    sf::Image *src;
    sf::Sprite *sprite;
    int tileWidth, tileHeight, origin;
    int rows, cols;
};

#endif /* _TILEMAP_H_ */
