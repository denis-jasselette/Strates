#include "action.h"

Action::Action(Entity *owner) : owner(owner)
{
}

void Action::setOwner(Entity *owner) {
  this->owner = owner;
}

Entity *Action::getOwner() const {
  return owner;
}

sf::IntRect Action::getSpriteRect(const JSONObject &properties) const {
  std::wstring propName = getSpriteRectPropName();
  const JSONArray &rectVect = properties.find(propName)->second->AsArray();
  sf::IntRect sheet(rectVect[0]->AsNumber(), rectVect[1]->AsNumber(),
            rectVect[2]->AsNumber(), rectVect[3]->AsNumber());
  sf::IntRect anim = getAnimSpriteRect();
  sheet.left += anim.left;
  sheet.top += anim.top;
  return sheet;
}
