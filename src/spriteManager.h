#ifndef _SPRITEMANAGER_H_
#define _SPRITEMANAGER_H_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "imageManager.h"
#include "playerColor.h"

class SpriteManager {
  public:
    SpriteManager(ImageManager *imgMgr, const PlayerColor &color);
    ~SpriteManager();

    const sf::Texture *get(std::string name);

  private:
    ImageManager *imgMgr;
    const PlayerColor &color;
    std::map<std::string, sf::Texture*> pool;
};

#endif /* _SPRITEMANAGER_H_ */
