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
     * @param imgMgr         the ImageManager from which the Texture is
     *                       retrieved
     */
    Unit(const std::string &className,
        JSONObject properties,
        ImageManager *imgMgr);
};

#endif /* _UNIT_H_ */
