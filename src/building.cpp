#include "building.h"

Building::Building(const std::string &className,
    const std::string &displayName,
    const sf::IntRect &spriteRect,
    int size,
    ImageManager *imgMgr) :
  Entity(className, displayName, spriteRect, size)
{
  loadSprite(imgMgr, "buildings");
}
