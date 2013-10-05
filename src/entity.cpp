#include "entity.h"
#include <cmath>

Entity::Entity(const std::string &className,
    JSONObject properties)
{
  this->className = className;
  this->properties = properties;
  position = sf::Vector2f(0, 0);
}

Entity::Entity(const Entity &that) {
  map = that.map;
  className = that.className;
  properties = that.properties;
  texture = that.texture;
  position = sf::Vector2f(0, 0);
}

Entity::~Entity() {
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
  const JSONArray &rectVect = properties.find(L"spriteRect")->second->AsArray();
  sf::IntRect spriteRect(rectVect[0]->AsNumber(), rectVect[1]->AsNumber(),
            rectVect[2]->AsNumber(), rectVect[3]->AsNumber());
  sf::Sprite sprite(*texture, spriteRect);

  sprite.setPosition((sf::Vector2f) map->mapToViewCoords(position));
  target->draw(sprite);
}

void Entity::update(sf::Time frametime) {
}
