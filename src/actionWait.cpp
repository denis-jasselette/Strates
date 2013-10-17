#include "actionWait.h"

ActionWait::ActionWait(Entity *owner) : Action(owner) {
}

void ActionWait::update(sf::Time frametime) {
}

bool ActionWait::isFinished() const {
  return false;
}

std::wstring ActionWait::getSpriteRectPropName() const {
  return L"spriteRect";
}

sf::IntRect ActionWait::getAnimSpriteRect() const {
  return sf::IntRect(0, 0, 32, 35);
}
