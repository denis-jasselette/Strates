#include "cursor.h"

Cursor::Cursor(sf::RenderWindow *window, ImageManager *imageMgr) {
  this->window = window;
  this->imageMgr = imageMgr;

  sf::Image *image = imageMgr->get("cursor");
  sprite = new sf::Sprite(*image);

  position = sf::Vector2i(window->GetWidth() / 2, window->GetHeight() / 2);
  window->ShowMouseCursor(false);
  centerCursor();
}

Cursor::~Cursor() {
  delete sprite;
}

void Cursor::centerCursor() {
  sf::Vector2i center(window->GetWidth() / 2, window->GetHeight() / 2);
  if (center != sf::Mouse::GetPosition(*window))
    sf::Mouse::SetPosition(center, *window);
}

float clamp(float v, float min, float max) {
  if (v < min)
    return min;
  return (v > max)? max : v;
}

void Cursor::onMoved(const sf::Event::MouseMoveEvent &move) {
  sf::Vector2i mouse = sf::Vector2i(move.X, move.Y);
  int w = window->GetWidth();
  int h = window->GetHeight();

  position += mouse - sf::Vector2i(w / 2, h / 2);
  position.x = clamp(position.x, 0, w - 1);
  position.y = clamp(position.y, 0, h - 1);

  centerCursor();
}

sf::Vector2i Cursor::getPosition() {
  return position;
}

sf::Vector2f Cursor::getViewPosition() {
  return window->ConvertCoords(position.x, position.y);
}

void Cursor::paint() {
  sf::Vector2f viewPos = getViewPosition();
  sprite->SetPosition(viewPos.x, viewPos.y);
  window->Draw(*sprite);
}
