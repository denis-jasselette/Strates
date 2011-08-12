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

Entity::Entity(const Entity &that) {
  map = that.map;
  className = that.className;
  displayName = that.displayName;
  spriteRect = that.spriteRect;
  size = that.size;
  position = sf::Vector2i(0, 0);

  sprite = NULL;
  if (sprite)
    sprite = new sf::Sprite(*that.sprite);
}

Entity::~Entity() {
  delete sprite;
}

void Entity::setMap(Map *map) {
  this->map = map;
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

  sprite->SetPosition((sf::Vector2f) map->mapToViewCoords(position));
  target->Draw(*sprite);
}

void Entity::loadSprite(ImageManager *imgMgr, const std::string &name) {
  const sf::Texture *src = imgMgr->get(name);
  sprite = new sf::Sprite(*src);
  sprite->SetSubRect(spriteRect);
}
