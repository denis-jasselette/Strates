#include "tileMap.h"

TileMap::TileMap(std::string name, ImageManager *imgMgr) {
  this->name = name;
  src = imgMgr->get(name + "tiles");
}
