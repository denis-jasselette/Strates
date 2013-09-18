#include "building.h"

Building::Building(const std::string &className,
    JSONObject properties,
    ImageManager *imgMgr) :
  Entity(className, properties)
{
  loadSprite(imgMgr, "buildings");
}
