#include "tileMap.h"

TileMap::TileMap(std::string name, ImageManager *imgMgr) {
  this->name = name;
  src = imgMgr->get(name + "tiles");
  sprite = new sf::Sprite(*src);
  tileWidth = 32;
  tileHeight = 32;
  origin = 16;
  rows = (src->GetHeight() + 1) / (tileHeight + 1);
  cols = (src->GetWidth() + 1) / (tileWidth + 1);
}

TileMap::~TileMap() {
  delete sprite;
}

sf::Sprite *TileMap::get(int type) {
  int x = (type + origin) % cols;
  int y = (type + origin) / cols;
  sf::IntRect rect(x * (tileWidth + 1), y * (tileHeight + 1), tileWidth, tileHeight);
  sprite->SetSubRect(rect);
  return sprite;
}

sf::Vector2i TileMap::convertCoords(int x, int y) {
  return sf::Vector2i(x * tileWidth, y * tileHeight);
}
