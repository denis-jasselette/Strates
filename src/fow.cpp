#include "fow.h"

FoW::FoW(Map *map, ImageManager *imgMgr) :
  Map(*map, new TileMap("fow", imgMgr))
{
  this->map = map;

  status = new FogStatus*[height];
  for (int i = 0; i < height; i++) {
    status[i] = new FogStatus[width];
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      status[i][j] = HIDDEN;
      tiles[i][j] = SOUTH | EAST | NORTH | WEST;
    }
  }
}

FoW::~FoW() {
  for (int i = 0; i < height; i++)
    delete[] status[i];
  delete[] status;
}

void FoW::set(int x, int y, FogStatus value) {
  struct neighbour_t {
    int i, j;
    TileIndex rmIndex, addIndex;
  };

  static const neighbour_t neighbours[] = {
    { -1, 0, SOUTH, NORTH },
    { 0, -1, EAST, WEST },
    { 1, 0, NORTH, SOUTH },
    { 0, 1, WEST, EAST }
  };

  if (status[y][x] == value)
    return;

  status[y][x] = value;

  if (value == REVEALED)
    tiles[y][x] = NONE;
  else
    tiles[y][x] = 0;

  for (size_t i = 0; i < sizeof(neighbours); i++) {
    neighbour_t n = neighbours[i];
    if (y + n.i < 0 || y + n.i >= height
        || x + n.j < 0 || x + n.j >= width)
      continue;

    if (value == REVEALED)
      tiles[y + n.i][x + n.j] &= ~n.rmIndex;
    else if (status[y + n.i][x + n.j] == HIDDEN) {
      tiles[y + n.i][x + n.j] |= n.rmIndex;
      tiles[y][x] |= n.addIndex;
    }
  }
}

void FoW::set(const sf::Vector2i &coords, FogStatus value) {
  set(coords.x, coords.y, value);
}
