#include "tileMap.h"

TileMap::TileMap(std::string name, ImageManager *imgMgr) {
  this->name = name;
  src = imgMgr->get(name + "tiles");
  sprite = new sf::Sprite(*src);
  tileWidth = 32;
  tileHeight = 32;
  rows = src->getSize().y / tileHeight;
  cols = src->getSize().x / tileWidth;
}

TileMap::~TileMap() {
  delete sprite;
}

sf::Sprite *TileMap::get(unsigned int type) {
  int x = type % cols;
  int y = type / cols;
  sf::IntRect rect(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
  sprite->setTextureRect(rect);
  return sprite;
}

int TileMap::getTileWidth() { return tileWidth; }
int TileMap::getTileHeight() { return tileHeight; }
