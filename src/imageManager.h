#ifndef _IMAGEMANAGER_H_
#define _IMAGEMANAGER_H_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

/**
 * Handles the loading of Textures in a centralized manner.
 */
class ImageManager {
  public:
    /**
     * Destructor.
     *
     * Every Texture is destructed here.
     */
    ~ImageManager();

    /**
     * Returns the file `NAME.png' in the resource directory as a Texture.
     *
     * @param name    the filename without the `.png' extension
     *
     * @return        the corresponding Texture
     */
    const sf::Texture *get(std::string name);

  private:
    std::string nameToFile(std::string);

    std::map<std::string, sf::Texture*> pool;
};

#endif /* _IMAGEMANAGER_H_ */
