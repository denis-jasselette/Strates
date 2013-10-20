#ifndef _UNIT_H_
#define _UNIT_H_

#include "entity.h"

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

    virtual void defaultAction(const sf::Vector2i &coords);

  private:
    virtual std::string getTexturePath() const {
      return "units/" + className;
    }
};

#endif /* _UNIT_H_ */
