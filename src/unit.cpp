#include <cmath>
#include "unit.h"
#include "utils.h"

Unit::Unit(const std::string &className,
    JSONObject properties) :
  Entity(className, properties)
{
  isMoving = false;
}

void Unit::update(sf::Time frametime) {
  // FIXME: we assume that the time between each update is 1 / 60 (60 Hz), this
  // should be changed to use real time elapsed.
  float delta = frametime.asSeconds();

  if (isMoving) {
    float speed = getProperty(L"speed")->AsNumber();
    sf::Vector2f dir(sf::Vector2f(destination) - position);
    sf::Vector2f normalized_dir = dir / norm(dir);
    position += (speed * delta) * normalized_dir;
    if (approx(position, sf::Vector2f(destination))) {
      position = sf::Vector2f(destination);
      isMoving = false;
    }
  }
}

void Unit::defaultAction(const sf::Vector2i &coords) {
  isMoving = true;
  destination = map->viewToMapCoords(coords);
}
