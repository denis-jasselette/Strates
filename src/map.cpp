#include <fstream>
#include "map.h"

Map::Map(int width, int height, TileMap *tileMap) {
  this->width = width;
  this->height = height;
  this->tileMap = tileMap;

  tiles = new int*[height];
  for (int i = 0; i < height; i++)
    tiles[i] = new int[width];
}

Map::~Map() {
  delete tileMap;
  for (int i = 0; i < height; i++)
    delete[] tiles[i];
  delete[] tiles;
}

Map *Map::fromFile(std::string filename, ImageManager *imgMgr) {
  std::ifstream mapFile(filename.c_str());
  if (!mapFile.is_open()) {
    log("Error: could not open map file `" + filename + "'");
    return NULL;
  }

  Map *res = NULL;
  int width, height;
  std::string name;
  TileMap *tileMap;

  if (!mapFile.good()) {
    log("Error: incorrect map file format: missing header");
    goto fail;
  }

  if (!(mapFile >> width >> height >> name)) {
    log("Error: incorrect map file format: invalid header");
    goto fail;
  }

  tileMap = new TileMap(name, imgMgr);
  res = new Map(width, height, tileMap);
  if (res == NULL) {
    delete tileMap;
    goto fail;
  }

  /* fill res->tiles */
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (!(mapFile >> res->tiles[i][j])) {
        log("Error: incorrect map file format: too few tiles found");
        goto fail;
      }
    }
  }

  log("Map correctly loaded");

fail:
  mapFile.close();
  return res;
}

void Map::paint(sf::RenderTarget *target) {
  sf::IntRect targetRect = target->GetViewport(target->GetView());
  sf::IntRect paintRect = viewToMapRect(targetRect);
  paint(target, paintRect);
}

void Map::paint(sf::RenderTarget *target, sf::IntRect &paintRect) {
  for (int i = 0; i < paintRect.Height && i < height; i++) {
    for (int j = 0; j < paintRect.Width && j < width; j++) {
      sf::Vector2i mapCoords(j + paintRect.Left, i + paintRect.Top);
      sf::Sprite *sprite = tileMap->get(tiles[mapCoords.y][mapCoords.x]);
      sprite->SetPosition((sf::Vector2f) mapToViewCoords(mapCoords));
      target->Draw(*sprite);
    }
  }
}

sf::Vector2i Map::viewToMapCoords(sf::Vector2i &coords) {
  int w = tileMap->getTileWidth();
  int h = tileMap->getTileHeight();
  return sf::Vector2i(coords.x / w, coords.y / h);
}

sf::IntRect Map::viewToMapRect(sf::IntRect &viewRect) {
  int w = tileMap->getTileWidth();
  int h = tileMap->getTileHeight();
  int left = viewRect.Left / w;
  int top = viewRect.Top / h;
  int width = (viewRect.Width - 1) / w + 1;
  int height = (viewRect.Height - 1) / h + 1;
  return sf::IntRect(left, top, width, height);
}

sf::Vector2i Map::mapToViewCoords(sf::Vector2i &coords) {
  int w = tileMap->getTileWidth();
  int h = tileMap->getTileHeight();
  return sf::Vector2i(coords.x * w, coords.y * h);
}

sf::IntRect Map::mapToViewRect(sf::Vector2i &coords) {
  int w = tileMap->getTileWidth();
  int h = tileMap->getTileHeight();
  return sf::IntRect(coords.x * w, coords.y * h, w, h);
}
