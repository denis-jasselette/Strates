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

  //std::cout << position.x << " " << position.y << std::endl;

  if (isMoving) {
    float speed = getProperty(L"speed")->AsNumber();
    sf::Vector2f dir(sf::Vector2f(destination) - position);
    sf::Vector2f normalized_dir = dir / norm(dir);
    position += (speed * delta) * normalized_dir;
    if (approx(position, sf::Vector2f(destination))) {
      position = sf::Vector2f(destination);
      if (!waypoints.empty()) {
	destination = waypoints.front();
	waypoints.pop_front();
      } else {
      isMoving = false;
      }
    }
  }
}

void Unit::defaultAction(const sf::Vector2i &coords) {
  //isMoving = true;
  //destination = map->viewToMapCoords(coords);
  AI::getInstance().computePath(this, map->viewToMapCoords(coords));
}

void Unit::addWaypoint(const sf::Vector2i &tileCoords) {
  if(!isMoving) {
    destination = tileCoords;
    isMoving = true;
  } else {
    waypoints.push_back(tileCoords);
  }
}

void Unit::clearWaypoints() {
    waypoints.clear();
    isMoving = false;
}

std::list<sf::Vector2i> Unit::getWaypoints() {
    return waypoints;
}