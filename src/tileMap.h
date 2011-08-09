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
    int getTileWidth();
    int getTileHeight();

  private:
    std::string name;
    const sf::Texture *src;
    sf::Sprite *sprite;
    int tileWidth, tileHeight;
    int rows, cols;
};

#endif /* _TILEMAP_H_ */
