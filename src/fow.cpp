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
      tiles[i][j] = ALL;
    }
  }
}

FoW::~FoW() {
  for (int i = 0; i < height; i++)
    delete[] status[i];
  delete[] status;
}

FoW::TileIndex FoW::getOpposite(TileIndex index) {
  if (index < NORTH)
    return (FoW::TileIndex) (index << 4);
  return (FoW::TileIndex) (index >> 4);
}

void FoW::set(int x, int y, FogStatus value) {
  struct neighbour_t {
    int i, j;
    TileIndex rmIndex;
  };

  static const neighbour_t neighbours[] = {
    { -1,  0, SOUTH },
    { -1, -1, SE },
    {  0, -1, EAST },
    {  1, -1, NE },
    {  1,  0, NORTH },
    {  1,  1, NW },
    {  0,  1, WEST },
    { -1,  1, SW },
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
      tiles[y][x] |= getOpposite(n.rmIndex);
    }
  }
}

void FoW::set(const sf::Vector2i &coords, FogStatus value) {
  set(coords.x, coords.y, value);
}
