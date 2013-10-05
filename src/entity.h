#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "JSON/JSON.h"
#include "config.h"
#include "imageManager.h"
#include "map.h"
#include "clonable.h"

/**
 * This class is a base for any element buildable by a Player.
 */
class Entity : public Clonable {
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
    Entity(const std::string &className, JSONObject properties);

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

    virtual Entity *clone() const = 0;

    /**
     * Returns the position of this Entity on the Map.
     *
     * @return    the position
     */
    sf::Vector2f getPosition() const;

    sf::Vector2i getTilePosition() const;

    /**
     * Sets the position of this Entity on the Map.
     *
     * @param position    the position
     */
    void setPosition(const sf::Vector2f &position);

    /**
     * Sets the Map this Entity sits on.
     *
     * @param map    the Map
     */
    void setMap(Map *map);

    void setTexture(const sf::Texture *texture);

    const JSONValue *getProperty(const std::wstring &name);

    /**
     * Paints this Entity on a RenderTarget
     *
     * @param target    the destination RenderTarget
     */
    void paint(sf::RenderTarget *target, sf::Color color);

    virtual void update(sf::Time frametime);

    virtual void defaultAction(const Entity *target) { }// TODO: = 0;
    virtual void defaultAction(const sf::Vector2i &coords) = 0;

  protected:
    Map *map;
    std::string className;
    //TODO: reference the owner player
    JSONObject properties;
    sf::Vector2f position;
    const sf::Texture *texture;
};

#endif /* _ENTITY_H_ */
