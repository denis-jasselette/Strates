#include "fow.h"

FoW::FoW(Map *map, TileMap *tileMap, FogType type) :
  Map(*map, tileMap)
{
  this->map = map;
  origin = type;

  status = new FogStatus*[height];
  for (int i = 0; i < height; i++) {
    status[i] = new FogStatus[width];
  }

  reset();
}

FoW::~FoW() {
  for (int i = 0; i < height; i++)
    delete[] status[i];
  delete[] status;
}

void FoW::setTile(int x, int y, int value) {
  tiles[y][x] = origin + value;
  refresh();
}

void FoW::reset(FogStatus value) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      status[i][j] = value;
      setTile(j, i, (value == HIDDEN)? ALL : NONE);
    }
  }
}

void FoW::setRow(int x1, int x2, int y, FogStatus value) {
  if (y < 0 || y >= height)
    return;

  x1 = std::max(0, x1);
  x2 = std::min(x2, width - 1);
  for (int x = x1; x <= x2; x++)
    set(x, y, 0, value);
}

void FoW::set(int x0, int y0, int radius, FogStatus value) {
  /* FIXME: split this method into two and don't update the neighbours of
   * internal tiles */
  if (radius == 0) {
    int x = x0, y = y0;
    if (!contains(x, y) || status[y][x] == value)
      return;

    status[y][x] = value;

    if (value == REVEALED)
      setTile(x, y, NONE);
    else
      updateTile(x, y);

    updateNeighbours(x, y);
  }
  else {
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;

    set(x0, y0 - radius, 0, value);
    set(x0, y0 + radius, 0, value);
    setRow(x0 - radius, x0 + radius, y0, value);

    while (x < y) {
      // ddF_x == 2 * x + 1;
      // ddF_y == -2 * y;
      // f == x*x + y*y - radius*radius + 2*x - y + 1;
      if (f >= 0) {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;
      setRow(x0 - x, x0 + x, y0 + y, value);
      setRow(x0 - x, x0 + x, y0 - y, value);
      setRow(x0 - y, x0 + y, y0 + x, value);
      setRow(x0 - y, x0 + y, y0 - x, value);
    }
  }
}

void FoW::set(const sf::Vector2i &coords, int radius, FogStatus value) {
  set(coords.x, coords.y, radius, value);
}

struct neighbour_t {
  int i, j;
  FoW::TileIndex rmIndex;
};

static const size_t neighbours_len = 8;
static const neighbour_t neighbours[] = {
  {  1,  0, FoW::S },
  {  1,  1, FoW::SE },
  {  0,  1, FoW::E },
  { -1,  1, FoW::NE },
  { -1,  0, FoW::N },
  { -1, -1, FoW::NW },
  {  0, -1, FoW::W },
  {  1, -1, FoW::SW },
};

static const int test[256] = {
  12,  0,  5,  0,  1,  8,  1,  8,
   6,  8,  1,  8,  1,  8,  1,  8,
   2, 13,  9, 13,  9, 13,  9, 13,
   2, 13,  9, 13,  9, 13,  9, 13,
   7, 11, 15, 11,  9, 13,  9, 13,
   2, 13,  9, 13,  9, 13,  9, 13,
   2, 13,  9, 13,  9, 13,  9, 13,
   2, 13,  9, 13,  9, 13,  9, 13,
   3, 11, 11, 11, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
   3, 11, 11, 11, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,

   4,  0,  0,  0,  8,  8,  8,  8,
  14,  8,  8,  8,  8,  8,  8,  8,
  10, 13, 13, 13, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
   3, 11, 11, 11, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
   3, 11, 11, 11, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
   3, 11, 11, 11, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,
  10, 13, 13, 13, 13, 13, 13, 13,

};

void FoW::updateNeighbours(int x, int y) {
  for (size_t i = 0; i < neighbours_len; i++)
    updateTile(x + neighbours[i].j, y + neighbours[i].i);
}

void FoW::updateTile(int x, int y) {
  const neighbour_t *n = neighbours; // for shortness
  if (!contains(x, y) || status[y][x] == REVEALED)
    return;

  int index = 0;
  for (ssize_t i = neighbours_len - 1; i >= 0; i--) {
    int bit;
    if (contains(x + n[i].j, y + n[i].i))
      bit = (status[y + n[i].i][x + n[i].j] == REVEALED);
    else
      bit = 0;
    index = index * 2 + bit;
  }

  setTile(x, y, test[index]);
}
