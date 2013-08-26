#include "utils.h"

sf::IntRect viewGetRect(sf::View &view) {
  sf::Vector2i center = (sf::Vector2i) view.getCenter();
  sf::Vector2i size = (sf::Vector2i) view.getSize();
  return sf::IntRect(center - size / 2, size);
}

void viewSetRect(sf::View &view, sf::IntRect &rect) {
  sf::Vector2i size (rect.width, rect.height);
  sf::Vector2i center (rect.left + rect.width / 2, rect.top + rect.height / 2);
  view.setCenter((sf::Vector2f) center);
  view.setSize((sf::Vector2f) size);
}
