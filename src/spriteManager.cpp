#include "config.h"
#include "spriteManager.h"

SpriteManager::SpriteManager(ImageManager *imgMgr, const PlayerColor &color)
  :
    imgMgr(imgMgr), color(color)
{
}

SpriteManager::~SpriteManager() {
  std::map<std::string, sf::Texture*>::iterator i;
  for (i = pool.begin(); i != pool.end(); i++)
    delete i->second;
}

const sf::Texture *SpriteManager::get(std::string name) {
  sf::Texture *value = pool[name];
  if (value != NULL)
    return value;

  value = new sf::Texture(*imgMgr->get(name));
  color.apply(value);

  pool[name] = value;
  return value;
}
