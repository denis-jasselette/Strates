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

/* FIXME */
static bool rectEqual(sf::IntRect &a, sf::IntRect &b) {
  return a.Left == b.Left
    && a.Top == b.Top
    && a.Width == b.Width
    && a.Height == b.Height;
}

void Map::paint(sf::RenderTarget *target) {
  sf::View targetView = target->GetView();
  sf::IntRect targetRect = viewGetRect(targetView);
  sf::IntRect paintRect = viewToMapRect(targetRect);

#if CACHE_RENDER
  if (!rectEqual(renderedRect, paintRect)) {
    if (renderedRect.Width != paintRect.Width
        || renderedRect.Height != paintRect.Height)
    {
      render->Create(paintRect.Width * tileMap->getTileWidth(),
          paintRect.Height * tileMap->getTileHeight());
    }
    paint(render, paintRect);
    renderedRect = paintRect;
    render->Display();
  }

  sf::Sprite sprite(render->GetTexture());
  sf::Vector2i mapCoords(paintRect.Left, paintRect.Top);
  sprite.SetPosition((sf::Vector2f) mapToViewCoords(mapCoords));
  target->Draw(sprite);
#else
  paint(target, paintRect);
#endif
}

void Map::paint(sf::RenderTarget *target, sf::IntRect &paintRect) {
  for (int i = 0; i < paintRect.Height; i++) {
    for (int j = 0; j < paintRect.Width; j++) {
      sf::Vector2i mapCoords(j + paintRect.Left, i + paintRect.Top);
      if (!contains(mapCoords.x, mapCoords.y))
        continue;

      sf::Sprite *sprite = tileMap->get(tiles[mapCoords.y][mapCoords.x]);
      sprite->SetPosition((sf::Vector2f) mapToViewCoords(mapCoords));
      target->Draw(*sprite);
    }
  }
}

sf::IntRect Map::clampViewRect(const sf::IntRect &rect) {
  sf::IntRect clamped = rect;
  clamped.Width = std::min(rect.Width, viewRect.Width);
  clamped.Height = std::min(rect.Height, viewRect.Height);
  clamped.Left = clamp(rect.Left, viewRect.Left, viewRect.Left + viewRect.Width - rect.Width);
  clamped.Top = clamp(rect.Top, viewRect.Top, viewRect.Top + viewRect.Height - rect.Height);
  return clamped;
}

sf::Vector2i Map::viewToMapCoords(sf::Vector2i &coords) {
  int w = tileMap->getTileWidth();
  int h = tileMap->getTileHeight();
  return sf::Vector2i(coords.x / w, coords.y / h);
}

sf::IntRect Map::viewToMapRect(sf::IntRect &view) {
  int w = tileMap->getTileWidth();
  int h = tileMap->getTileHeight();
  int left = view.Left / w;
  int top = view.Top / h;
  int right = (view.Left + view.Width - 1) / w;
  int bottom = (view.Top + view.Height - 1) / h;
  int width = right - left + 1;
  int height = bottom - top + 1;
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

bool Map::contains(int x, int y) {
  return x >= 0 && x < width && y >= 0 && y < height;
}
