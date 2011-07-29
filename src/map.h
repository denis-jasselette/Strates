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
  private:
    int width, height;
    int **tiles;
    TileMap *tileMap;

    Map(int width, int height, TileMap *tileMap);
};

#endif /* _MAP_H_ */
