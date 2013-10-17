#include "actionQueue.h"

ActionQueue::ActionQueue(Entity *owner) : Action(owner), anim(0) {
}

ActionQueue::~ActionQueue() {
  while (!queue.empty()) {
    delete queue.front();
    queue.pop();
  }
}

void ActionQueue::update(sf::Time frametime) {
  if (isFinished())
    return;

  queue.front()->update(frametime);
  if (queue.front()->isFinished()) {
    delete queue.front();
    queue.pop();
  }
}

bool ActionQueue::isFinished() const {
  return queue.empty();
}

void ActionQueue::append(Action *action) {
  queue.push(action);
}

std::wstring ActionQueue::getSpriteRectPropName() const {
  return queue.front()->getSpriteRectPropName();
}

sf::IntRect ActionQueue::getAnimSpriteRect() const {
  int size = 1;
  sf::IntRect(anim * size * 32, 0, size * 32, size * 32);
}
