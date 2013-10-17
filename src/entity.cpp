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

const JSONValue *Entity::getProperty(const std::wstring &name) const {
  JSONObject::const_iterator it = properties.find(name);
  if (it == properties.end()) {
    std::stringstream ss;
    ss << "Property not found '" << std::string(name.begin(), name.end()) << "' for class '" << className << "'";
    log(ss);
  }

  return it->second;
}

sf::IntRect Entity::getSelectionRect() const {
  int size = getProperty(L"size")->AsNumber();
  sf::Vector2f mapPos = getPosition();
  sf::IntRect rect = map->mapToViewRect(mapPos);
  rect.width *= size;
  rect.height *= size;
  return rect;
}

bool Entity::occupyTile(const sf::Vector2i &coord) {
  int size = getProperty(L"size")->AsNumber();
  sf::Vector2f pos = getPosition();
  sf::FloatRect tileRect = sf::FloatRect(coord.x, coord.y, 1, 1);
  sf::FloatRect entityRect = sf::FloatRect(pos.x, pos.y, size, size);

  return tileRect.intersects(entityRect);  
}

sf::Vector2i Entity::centerSprite(sf::IntRect sprite, sf::IntRect selection) const {
  sf::Vector2i view_pos = map->mapToViewCoords(position);
  view_pos.x -= (sprite.width - selection.width) / 2;
  view_pos.y -= (sprite.height - selection.height) / 2;
  return view_pos;
}

void Entity::paint(sf::RenderTarget *target, sf::Color color) {
  sf::IntRect spriteRect = action->getSpriteRect(properties);
  sf::Sprite sprite(*texture, spriteRect);

  sf::Vector2i view_pos = centerSprite(spriteRect, getSelectionRect());
  sprite.setPosition((sf::Vector2f) view_pos);
  target->draw(sprite);
}

void Entity::update(sf::Time frametime) {
  assert(action != NULL);
  action->update(frametime);
  if (action->isFinished()) {
    /* Delete action last so that the object always has a valid action. */
    Action *old_action = action;
    action = new ActionWait(this);
    delete old_action;
  }
}

const Action &Entity::getAction() const {
  return *action;
}

void Entity::setAction(const Action &a) {
  /* Delete action last so that the object always has a valid action. */
  Action *new_action = a.clone();
  new_action->setOwner(this);
  Action *old_action = action;
  action = new_action;
  delete old_action;
}

void Entity::queueAction(const Action &a) {
  ActionQueue *queue = new ActionQueue(this);
  queue->append(action);
  Action *next_action = a.clone();
  next_action->setOwner(this);
  queue->append(next_action);
  action = queue;
}
