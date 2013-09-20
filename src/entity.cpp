#include "entity.h"

Entity::Entity(const std::string &className,
    JSONObject properties)
{
  this->className = className;
  this->properties = properties;
  position = sf::Vector2i(0, 0);
}

Entity::Entity(const Entity &that) {
  map = that.map;
  className = that.className;
  properties = that.properties;
  texture = that.texture;
  position = sf::Vector2i(0, 0);
}

Entity::~Entity() {
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

void Entity::paint(sf::RenderTarget *target, sf::Color color) {
  const JSONArray &rectVect = properties.find(L"spriteRect")->second->AsArray();
  sf::IntRect spriteRect(rectVect[0]->AsNumber(), rectVect[1]->AsNumber(),
            rectVect[2]->AsNumber(), rectVect[3]->AsNumber());
  sf::Sprite sprite(*texture, spriteRect);

  sprite.setPosition((sf::Vector2f) map->mapToViewCoords(position));
  target->draw(sprite);
}
