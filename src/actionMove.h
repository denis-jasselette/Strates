#ifndef _ACTION_MOVE_H_
#define _ACTION_MOVE_H_

#include <list>
#include "action.h"

class Unit;

class ActionMove : public Action {
public:
  ActionMove(Entity *owner, const sf::Vector2i &coords);

  virtual ActionMove *clone() const {
    return new ActionMove(*this);
  }

  virtual void update(sf::Time frametime);
  virtual bool isFinished() const;

  void addWaypoint(const sf::Vector2i &coords);
  void clearWaypoints();
  std::list<sf::Vector2i> getWaypoints() const;

protected:
  sf::Vector2i destination;
  std::list<sf::Vector2i> waypoints;

  float anim_next_state_wait;
  int anim_state;
  int anim_seq_len;
  int orientation;

  void updateOrientation(const sf::Vector2f dir);

private:
  virtual std::wstring getSpriteRectPropName() const;
  virtual sf::IntRect getAnimSpriteRect() const;
};

#endif /* _ACTION_MOVE_H_ */
