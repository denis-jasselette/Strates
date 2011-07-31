#include "utils.h"

sf::IntRect viewGetRect(sf::View &view) {
  sf::Vector2i center = (sf::Vector2i) view.GetCenter();
  sf::Vector2i size = (sf::Vector2i) view.GetSize();
  return sf::IntRect(center - size / 2, size);
}

void viewSetRect(sf::View &view, sf::IntRect &rect) {
  sf::Vector2i size (rect.Width, rect.Height);
  sf::Vector2i center (rect.Left + rect.Width / 2, rect.Top + rect.Height / 2);
  view.SetCenter((sf::Vector2f) center);
  view.SetSize((sf::Vector2f) size);
}
