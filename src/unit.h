#ifndef _UNIT_H_
#define _UNIT_H_

#include "entity.h"
#include <list>

/**
 * Implements Entity specializing it for mobile units.
 */
class Unit : public Entity {
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
    Unit(const std::string &className,
        JSONObject properties);

    virtual Unit *clone() const {
      return new Unit(*this);
    }

    virtual void update(sf::Time frametime);

    virtual void defaultAction(const sf::Vector2i &coords);
    void addWaypoint(const sf::Vector2i &coords);
    void clearWaypoints();
    std::list<sf::Vector2i> getWaypoints();

  protected:
    bool isMoving;
    sf::Vector2i destination;
    std::list<sf::Vector2i> waypoints;
};

#endif /* _UNIT_H_ */
