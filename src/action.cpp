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
  const JSONObject &sprite_prop = properties.find(L"sprite")->second->AsObject();
  const JSONArray &rect_prop = sprite_prop.find(propName)->second->AsArray();
  sf::IntRect sheet(rect_prop[0]->AsNumber(), rect_prop[1]->AsNumber(),
            rect_prop[2]->AsNumber(), rect_prop[3]->AsNumber());
  const JSONArray &size_prop = sprite_prop.find(L"size")->second->AsArray();
  sf::Vector2i size(size_prop[0]->AsNumber(), size_prop[1]->AsNumber());
  sf::IntRect anim = getAnimSpriteRect();
  anim.left += sheet.left;
  anim.top += sheet.top;
  anim.width = size.x;
  anim.height = size.y;
  return anim;
}
