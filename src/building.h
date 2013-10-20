#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "entity.h"

/**
 * Implements Entity specializing it for immobile units, i.e., buildings.
 */
class Building : public Entity {
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
    Building(const std::string &className,
        JSONObject properties);

    virtual Building *clone() const {
      return new Building(*this);
    }

    virtual void defaultAction(const sf::Vector2i &coords);

  private:
    virtual std::string getTexturePath() const {
      return "buildings/" + className;
    }
};

#endif /* _BUILDING_H_ */
