#include "config.h"
#include "imageManager.h"

ImageManager::~ImageManager() {
  std::map<std::string, sf::Image*>::iterator i;
  for (i = pool.begin(); i != pool.end(); i++)
    delete i->second;
}

const sf::Image *ImageManager::get(std::string name) {
  sf::Image *value = pool[name];
  if (value != NULL)
    return value;

  sf::Image *image = new sf::Image();
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
