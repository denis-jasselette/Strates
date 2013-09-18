#include "unit.h"

Unit::Unit(const std::string &className,
    JSONObject properties,
    ImageManager *imgMgr) :
  Entity(className, properties)
{
  loadSprite(imgMgr, "units");
}
