#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "config.h"
#include "imageManager.h"
#include "map.h"

class Entity {
  public:
    Entity(const std::string &className,
        const std::string &displayName,
        const sf::IntRect &spriteRect,
        int size);
    virtual ~Entity();

    sf::Vector2i getPosition();
    void setPosition(const sf::Vector2i &position);
    void setMap(Map *map);
    void paint(sf::RenderTarget *target);
  protected:
    Map *map;
    std::string className;
    //TODO: reference the owner player
    std::string displayName;
    sf::IntRect spriteRect;
    int size;
    sf::Vector2i position;
    sf::Sprite *sprite;

    void loadSprite(ImageManager *imgMgr, const std::string &name);
};

#endif /* _ENTITY_H_ */
