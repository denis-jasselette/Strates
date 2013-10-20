#include <cmath>
#include "actionMove.h"
#include "utils.h"
#include "ai.h"

ActionMove::ActionMove(Entity *owner, const sf::Vector2i &coords)
  :
    Action(owner)
{
  AI::getInstance().computePath(dynamic_cast<Unit*>(owner), coords, this);

  anim_next_state_wait = 0;
  anim_state = -1;
  anim_seq_len = 6;
}

void ActionMove::update(sf::Time frametime) {
  float delta = frametime.asSeconds();

  anim_next_state_wait -= delta;
  while (anim_next_state_wait < 0) {
    anim_next_state_wait += 0.1;
    anim_state = (anim_state + 1) % anim_seq_len;
  }
  
  if (!waypoints.empty()) {
      destination = waypoints.front();
      if (approx(owner->getPosition(), sf::Vector2f(destination))) {
	owner->setPosition(sf::Vector2f(destination));
	if (!waypoints.empty())
	  waypoints.pop_front();
      } else {
	float speed = owner->getProperty(L"speed")->AsNumber();
	sf::Vector2f dir(sf::Vector2f(destination) - owner->getPosition());
	sf::Vector2f normalized_dir = dir / norm(dir);
	owner->setPosition(owner->getPosition() + (speed * delta) * normalized_dir);
      }
  }
}

bool ActionMove::isFinished() const {
  return waypoints.empty();
}

void ActionMove::addWaypoint(const sf::Vector2i &tileCoords) {
  waypoints.push_back(tileCoords);
}

void ActionMove::clearWaypoints() {
  waypoints.clear();
}

std::list<sf::Vector2i> ActionMove::getWaypoints() const {
  return waypoints;
}

std::wstring ActionMove::getSpriteRectPropName() const {
  return L"movingRect";
}

sf::IntRect ActionMove::getAnimSpriteRect() const {
  /* TODO: These values should all come from the tech tree, as well.
   * The animation part should probably be split into a class of its own, with
   * several ways to increment the state (random anim, linear, with
   * pauses...). */
  int width = 72;
  int height = 72;
  int anim_seq[] = { 1, 0, 1, 3, 2, 3 };
  int sprite = anim_seq[anim_state];
  return sf::IntRect(0, sprite * height, width, height);
}
