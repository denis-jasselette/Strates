#include "config.h"
#include "imageManager.h"

ImageManager::~ImageManager() {
  std::map<std::string, sf::Texture*>::iterator i;
  for (i = pool.begin(); i != pool.end(); i++)
    delete i->second;
}

const sf::Texture *ImageManager::get(std::string name) {
  sf::Texture *value = pool[name];
  if (value != NULL)
    return value;

  sf::Texture *image = new sf::Texture();
  if (!image->LoadFromFile(nameToFile(name))) {
    log("Error: Loading of `" + name + "' failed");
    return NULL;
  }

  image->SetSmooth(false);
  pool[name] = image;
  return image;
}

std::string ImageManager::nameToFile(std::string name) {
  return res_path(name + ".png");
}
