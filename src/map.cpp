#include <fstream>
#include "map.h"

Map::Map(int width, int height, TileMap *tileMap) {
  this->width = width;
  this->height = height;
  this->tileMap = tileMap;

  tiles = new int*[height];
  for (int i = 0; i < height; i++)
    tiles[i] = new int[width];

#if CACHE_RENDER
  renderedRect = sf::IntRect(0, 0, 0, 0);
  render = new sf::RenderImage();
#else
  render = NULL;
#endif
}

Map::~Map() {
  delete render;
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

/* FIXME */
static bool rectEqual(sf::IntRect &a, sf::IntRect &b) {
  return a.Left == b.Left
    && a.Top == b.Top
    && a.Width == b.Width
    && a.Height == b.Height;
}

void Map::paint(sf::RenderTarget *target) {
  sf::IntRect targetRect = target->GetViewport(target->GetView());
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

  sf::Sprite sprite(render->GetImage());
  sf::Vector2i mapCoords(paintRect.Left, paintRect.Top);
  sprite.SetPosition((sf::Vector2f) mapToViewCoords(mapCoords));
  target->Draw(sprite);
#else
  paint(target, paintRect);
#endif
}

void Map::paint(sf::RenderTarget *target, sf::IntRect &paintRect) {
  for (int i = 0; i < paintRect.Height && i < height; i++) {
    for (int j = 0; j < paintRect.Width && j < width; j++) {
      sf::Vector2i mapCoords(j, i);
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
