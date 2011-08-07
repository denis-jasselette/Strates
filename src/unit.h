#ifndef _UNIT_H_
#define _UNIT_H_

#include "entity.h"

class Unit : public Entity {
  public:
    Unit(const std::string &className,
        const std::string &displayName,
        const sf::IntRect &spriteRect,
        int size,
        ImageManager *imgMgr);
};

#endif /* _UNIT_H_ */
