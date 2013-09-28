#include "building.h"

Building::Building(const std::string &className,
    JSONObject properties) :
  Entity(className, properties)
{
}

void Building::defaultAction(const sf::Vector2i &coords) {
}
