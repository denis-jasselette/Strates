#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "config.h"
#include "imageManager.h"

class TileMap {
  public:
    TileMap(std::string, ImageManager*);

  private:
    std::string name;
    sf::Image *src;
};

#endif /* _TILEMAP_H_ */
