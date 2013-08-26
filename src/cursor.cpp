#include "cursor.h"
#include "utils.h"

Cursor::Cursor(sf::RenderWindow *window, ImageManager *imageMgr) {
  this->window = window;
  this->imageMgr = imageMgr;

  const sf::Texture *image = imageMgr->get("cursor");
  sprite = new sf::Sprite(*image);

  refreshPosition();
}

Cursor::~Cursor() {
  delete sprite;
}

void Cursor::refreshPosition() {
  int w = window->getSize().x;
  int h = window->getSize().y;

  position = sf::Mouse::getPosition(*window);
  position.x = clamp(position.x, 0, w - 1);
  position.y = clamp(position.y, 0, h - 1);
}

sf::Vector2i Cursor::getPosition() {
  return position;
}

sf::Vector2f Cursor::getViewPosition() {
  return window->mapPixelToCoords(position);
}

void Cursor::paint() {
  refreshPosition();
  sf::Vector2f viewPos = getViewPosition();
  sprite->setPosition(viewPos.x, viewPos.y);
  window->draw(*sprite);
}
