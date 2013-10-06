#include <cmath>
#include "unit.h"
#include "utils.h"
#include "ai.h"

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
  
  if (isMoving && !waypoints.empty()) {
      destination = waypoints.front();
      if (approx(position, sf::Vector2f(destination))) {
	position = sf::Vector2f(destination);
	if (!waypoints.empty()) {
	  waypoints.pop_front();
	} else {
	  isMoving = false;
	}
      } else {
	float speed = getProperty(L"speed")->AsNumber();
	sf::Vector2f dir(sf::Vector2f(destination) - position);
	sf::Vector2f normalized_dir = dir / norm(dir);
	position += (speed * delta) * normalized_dir;
      }
  }
}

void Unit::defaultAction(const sf::Vector2i &coords) {
  AI::getInstance().computePath(this, coords);
}

void Unit::addWaypoint(const sf::Vector2i &tileCoords) {
  isMoving = true;
  waypoints.push_back(tileCoords);
}

void Unit::clearWaypoints() {
  waypoints.clear();
}

std::list<sf::Vector2i> Unit::getWaypoints() {
  return waypoints;
}
