#include <cmath>
#include "entity.h"
#include "actionWait.h"
#include "actionQueue.h"

Entity::Entity(const std::string &className,
    JSONObject properties)
{
  this->className = className;
  this->properties = properties;
  position = sf::Vector2f(0, 0);
  action = new ActionWait(this);
}

Entity::Entity(const Entity &that) {
  map = that.map;
  className = that.className;
  properties = that.properties;
  texture = that.texture;
  position = sf::Vector2f(0, 0);
  action = new ActionWait(this);
}

Entity::~Entity() {
  delete action;
}

void Entity::setMap(Map *map) {
  this->map = map;
}

sf::Vector2f Entity::getPosition() const {
  return position;
}

sf::Vector2i Entity::getTilePosition() const {
  return sf::Vector2i(round(position.x), round(position.y));
}

void Entity::setPosition(const sf::Vector2f &position) {
  this->position = position;
}

void Entity::setTexture(const sf::Texture *texture) {
  this->texture = texture;
}

const JSONValue *Entity::getProperty(const std::wstring &name) {
  JSONObject::iterator it = properties.find(name);
  if (it == properties.end()) {
    std::stringstream ss;
    ss << "Property not found '" << std::string(name.begin(), name.end()) << "' for class '" << className << "'";
    log(ss);
  }

  return it->second;
}

bool Entity::occupyTile(const sf::Vector2i &coord) {
  int size = getProperty(L"size")->AsNumber();
  sf::Vector2f pos = getPosition();
  sf::FloatRect tileRect = sf::FloatRect(coord.x, coord.y, 1, 1);
  sf::FloatRect entityRect = sf::FloatRect(pos.x, pos.y, size, size);

  return tileRect.intersects(entityRect);  
}

void Entity::paint(sf::RenderTarget *target, sf::Color color) {
  sf::IntRect spriteRect = action->getSpriteRect(properties);
  sf::Sprite sprite(*texture, spriteRect);

  sprite.setPosition((sf::Vector2f) map->mapToViewCoords(position));
  target->draw(sprite);
}

void Entity::update(sf::Time frametime) {
  assert(action != NULL);
  action->update(frametime);
  if (action->isFinished()) {
    delete action;
    action = new ActionWait(this);
  }
}

const Action &Entity::getAction() const {
  return *action;
}

void Entity::setAction(const Action &a) {
  delete action;
  action = a.clone();
  action->setOwner(this);
}

void Entity::queueAction(const Action &a) {
  ActionQueue *queue = new ActionQueue(this);
  queue->append(action);
  Action *next_action = a.clone();
  next_action->setOwner(this);
  queue->append(next_action);
  action = queue;
}
