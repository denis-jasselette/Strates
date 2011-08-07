#include "entity.h"

Entity::Entity(const std::string &className,
    const std::string &displayName,
    const sf::IntRect &spriteRect,
    int size)
{
  this->className = className;
  this->displayName = displayName;
  this->spriteRect = spriteRect;
  this->size = size;
  position = sf::Vector2i(0, 0);
  sprite = NULL;
}

Entity::~Entity() {
  delete sprite;
}

sf::Vector2i Entity::getPosition() {
  return position;
}

void Entity::setPosition(const sf::Vector2i &position) {
  this->position = position;
}

void Entity::paint(sf::RenderTarget *target) {
  if (!sprite)
    return;

  sprite->SetPosition((sf::Vector2f) position);
  target->Draw(*sprite);
}

void Entity::loadSprite(ImageManager *imgMgr, const std::string &name) {
  sf::Image *src = imgMgr->get(name);
  sprite = new sf::Sprite(*src);
  sprite->SetSubRect(spriteRect);
}
