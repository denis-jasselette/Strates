#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "config.h"
#include "imageManager.h"
#include "map.h"

/**
 * This class is a base for any element buildable by a Player.
 */
class Entity {
  public:
    /**
     * Constructor.
     *
     * @param className      the name identifying this Entity
     * @param displayName    the name that should be displayed in the ui
     * @param spriteRect     the IntRect locating the Sprite associated to this
     *                       Entity in a Texture
     * @param size           the number of cells this Entity occupies
     *                       vertically and horizontally
     */
    Entity(const std::string &className,
        const std::string &displayName,
        const sf::IntRect &spriteRect,
        int size);

    /**
     * Copy constructor.
     *
     * @param that    the Entity to copy
     */
    Entity(const Entity &that);

    /**
     * Virtual destructor.
     */
    virtual ~Entity();

    /**
     * Returns the position of this Entity on the Map.
     *
     * @return    the position
     */
    sf::Vector2i getPosition();

    /**
     * Sets the position of this Entity on the Map.
     *
     * @param position    the position
     */
    void setPosition(const sf::Vector2i &position);

    /**
     * Sets the Map this Entity sits on.
     *
     * @param map    the Map
     */
    void setMap(Map *map);

    /**
     * Paints this Entity on a RenderTarget
     *
     * @param target    the destination RenderTarget
     */
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
