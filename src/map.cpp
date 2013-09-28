#include <fstream>
#include "map.h"
#include "utils.h"

Map::Map(const Map &map, TileMap *tileMap) {
  init(map.width, map.height, tileMap);
}

Map::Map(int width, int height, TileMap *tileMap) {
  init(width, height, tileMap);
}

void Map::init(int width, int height, TileMap *tileMap) {
  this->width = width;
  this->height = height;
  this->tileMap = tileMap;
  deleteTileMap = false;
  viewSize = sf::Vector2i(
      width * tileMap->getTileWidth(),
      height * tileMap->getTileHeight());
  viewRect = sf::IntRect(sf::Vector2i(0, 0), viewSize);

  tiles = new int*[height];
  for (int i = 0; i < height; i++)
    tiles[i] = new int[width];

#if CACHE_RENDER
  renderedRect = sf::IntRect(0, 0, 0, 0);
  render = new sf::RenderTexture();
  refresh();
#else
  render = NULL;
#endif
}

Map::~Map() {
#if CACHE_RENDER
  delete render;
#endif
  if (deleteTileMap)
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

  res->deleteTileMap = true;

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

bool Map::rectEqual(sf::IntRect &a, sf::IntRect &b) {
  return a.left == b.left
    && a.top == b.top
    && a.width == b.width
    && a.height == b.height;
}

void Map::refresh() {
  forceRefresh = true;
}

bool Map::needsCacheRefresh(sf::IntRect &paintRect) {
  return forceRefresh
    || renderedRect.left > paintRect.left
    || renderedRect.top > paintRect.top
    || renderedRect.left + renderedRect.width < paintRect.left + paintRect.width
    || renderedRect.top + renderedRect.height < paintRect.top + paintRect.height;
}

void Map::checkCacheSize(sf::IntRect &paintRect) {
  if (renderedRect.width < paintRect.width + 1
      || renderedRect.height < paintRect.height + 1)
  {
    renderedRect.width = paintRect.width + 2;
    renderedRect.height = paintRect.height + 2;
    render->create(renderedRect.width * tileMap->getTileWidth(),
        renderedRect.height * tileMap->getTileHeight());
  }
}

void Map::refreshCache(sf::IntRect &paintRect) {
  if (!needsCacheRefresh(paintRect))
    return;

  forceRefresh = false;
  checkCacheSize(paintRect);

  render->clear(sf::Color(0, 0, 0, 0));
  sf::Vector2i orig(paintRect.left, paintRect.top);
  renderedRect.left = paintRect.left;
  renderedRect.top = paintRect.top;
  paint(render, renderedRect, orig);
  render->display();
}

void Map::paint(sf::RenderTarget *target) {
  sf::View targetView = target->getView();
  sf::IntRect targetRect = viewGetRect(targetView);
  sf::IntRect paintRect = viewToMapRect(targetRect);

#if CACHE_RENDER
  refreshCache(paintRect);

  sf::Sprite sprite(render->getTexture());
  sf::Vector2i mapCoords(renderedRect.left, renderedRect.top);
  sprite.setPosition((sf::Vector2f) mapToViewCoords(mapCoords));
  target->draw(sprite);
#else
  paint(target, paintRect);
#endif
}

void Map::paint(sf::RenderTarget *target,
    const sf::IntRect &paintRect,
    const sf::Vector2i &targetOrig)
{
  for (int i = 0; i < paintRect.height; i++) {
    for (int j = 0; j < paintRect.width; j++) {
      sf::Vector2i mapCoords(j + paintRect.left, i + paintRect.top);
      if (!contains(mapCoords.x, mapCoords.y))
        continue;

      sf::Sprite *sprite = tileMap->get(tiles[mapCoords.y][mapCoords.x]);
      sf::Vector2f pos(mapCoords - targetOrig);
      sprite->setPosition(sf::Vector2f(mapToViewCoords(pos)));
      target->draw(*sprite);
    }
  }
}

sf::IntRect Map::clampViewRect(const sf::IntRect &rect) {
  sf::IntRect clamped = rect;
  clamped.width = std::min(rect.width, viewRect.width);
  clamped.height = std::min(rect.height, viewRect.height);
  clamped.left = clamp(rect.left, viewRect.left, viewRect.left + viewRect.width - rect.width);
  clamped.top = clamp(rect.top, viewRect.top, viewRect.top + viewRect.height - rect.height);
  return clamped;
}

sf::Vector2f Map::viewToMapFloatCoords(const sf::Vector2i &coords) {
  float w = tileMap->getTileWidth();
  float h = tileMap->getTileHeight();
  return sf::Vector2f(coords.x / w, coords.y / h);
}

sf::Vector2i Map::viewToMapCoords(const sf::Vector2i &coords) {
  int w = tileMap->getTileWidth();
  int h = tileMap->getTileHeight();
  return sf::Vector2i(coords.x / w, coords.y / h);
}

sf::IntRect Map::viewToMapRect(const sf::IntRect &view) {
  int w = tileMap->getTileWidth();
  int h = tileMap->getTileHeight();
  int left = view.left / w;
  int top = view.top / h;
  int right = (view.left + view.width - 1) / w;
  int bottom = (view.top + view.height - 1) / h;
  int width = right - left + 1;
  int height = bottom - top + 1;
  return sf::IntRect(left, top, width, height);
}

sf::Vector2i Map::mapToViewCoords(const sf::Vector2f &coords) {
  int w = tileMap->getTileWidth();
  int h = tileMap->getTileHeight();
  return sf::Vector2i(coords.x * w, coords.y * h);
}

sf::IntRect Map::mapToViewRect(const sf::Vector2f &coords) {
  int w = tileMap->getTileWidth();
  int h = tileMap->getTileHeight();
  return sf::IntRect(coords.x * w, coords.y * h, w, h);
}

bool Map::contains(int x, int y) {
  return x >= 0 && x < width && y >= 0 && y < height;
}
