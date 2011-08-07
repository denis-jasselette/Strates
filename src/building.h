#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "entity.h"

class Building : public Entity {
  public:
    Building(const std::string &className,
        const std::string &displayName,
        const sf::IntRect &spriteRect,
        int size,
        ImageManager *imgMgr);
};

#endif /* _BUILDING_H_ */
