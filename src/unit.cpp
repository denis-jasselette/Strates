#include "unit.h"

Unit::Unit(const std::string &className,
    const std::string &displayName,
    const sf::IntRect &spriteRect,
    int size,
    ImageManager *imgMgr) :
  Entity(className, displayName, spriteRect, size)
{
  loadSprite(imgMgr, "units");
}
