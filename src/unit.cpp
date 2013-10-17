#include "unit.h"
#include "actionMove.h"

Unit::Unit(const std::string &className,
    JSONObject properties) :
  Entity(className, properties)
{
}

void Unit::defaultAction(const sf::Vector2i &coords) {
  ActionMove a(this, coords);
  setAction(a);
}
