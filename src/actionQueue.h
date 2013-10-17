#ifndef _ACTION_QUEUE_H_
#define _ACTION_QUEUE_H_

#include <queue>
#include "action.h"

class ActionQueue : public Action {
public:
  ActionQueue(Entity *owner=NULL);
  ~ActionQueue();

  virtual ActionQueue *clone() const {
    return new ActionQueue(*this);
  }

  virtual void update(sf::Time frametime);
  virtual bool isFinished() const;
  void append(Action *action);

protected:
  std::queue<Action*> queue;
  int anim;

private:
  virtual std::wstring getSpriteRectPropName() const;
  virtual sf::IntRect getAnimSpriteRect() const;
};

#endif /* _ACTION_QUEUE_H_ */
