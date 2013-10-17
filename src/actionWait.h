#ifndef _ACTION_WAIT_H_
#define _ACTION_WAIT_H_

#include "action.h"

class ActionWait : public Action {
public:
  ActionWait(Entity *owner=NULL);

  virtual ActionWait *clone() const {
    return new ActionWait(*this);
  }

  virtual void update(sf::Time frametime);
  virtual bool isFinished() const;

private:
  virtual std::wstring getSpriteRectPropName() const;
  virtual sf::IntRect getAnimSpriteRect() const;
};

#endif /* _ACTION_WAIT_H_ */
