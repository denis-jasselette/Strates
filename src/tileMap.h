#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "config.h"
#include "imageManager.h"

/**
 * Provides an easy way to access tiles from an organized image file.
 *
 * The source image file should be composed of 32x32 (px) tiles separated by
 * 1 px vertically and horizontally.
 */
class TileMap {
  public:
    /**
     * Constructor.
     *
     * @param name      the name of the Texture
     * @param imgMgr    the ImageManager from which the Texture is retrieved
     */
    TileMap(std::string name, ImageManager *imgMgr);

    /**
     * Destructor.
     */
    ~TileMap();

    /**
     * Returns a pointer to a Sprite of the tile corresponding to an index.
     *
     * Tiles are indexed from 0 going from the top-left corner to the
     * bottom-right row by row.
     *
     * The returned Sprite *must not* be destructed and will only be usable until
     * the next call.
     *
     * @param type    the index of the tile
     *
     * @return        a pointer to a Sprite of the tile
     */
    sf::Sprite *get(unsigned int type);

    /**
     * Returns the width in pixel of a single tile.
     *
     * @return    the width of a tile
     */
    int getTileWidth();

    /**
     * Returns the height in pixel of a single tile.
     *
     * @return    the height of a tile
     */
    int getTileHeight();

  private:
    std::string name;
    const sf::Texture *src;
    sf::Sprite *sprite;
    int tileWidth, tileHeight;
    int rows, cols;
};

#endif /* _TILEMAP_H_ */
