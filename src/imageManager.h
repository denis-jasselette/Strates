#ifndef _IMAGEMANAGER_H_
#define _IMAGEMANAGER_H_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ImageManager {
  public:
    ~ImageManager();
    const sf::Texture *get(std::string);

  private:
    std::string nameToFile(std::string);

    std::map<std::string, sf::Texture*> pool;
};

#endif /* _IMAGEMANAGER_H_ */
