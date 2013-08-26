#include "hudPanel.h"
#include "utils.h"

HudPanel::HudPanel(ImageManager *imgMgr) {
  const sf::Texture *src = imgMgr->get("hudpanel");
  sprite = new sf::Sprite(*src);
  leftBorderRect = sf::IntRect(0, 0, 16, src->getSize().y);
  backgroundRect = sf::IntRect(17, 0, 46, src->getSize().y);
  spacerRect = sf::IntRect(64, 0, 128, src->getSize().y);
  rightBorderRect = sf::IntRect(193, 0, 16, src->getSize().y);

  setPosition(0, 0, 0);
}

HudPanel::~HudPanel() {
  delete sprite;
}

void HudPanel::setPosition(int left, int top, int width) {
  this->left = left;
  this->top = top;
  this->width = width;
}

int HudPanel::paintRect(sf::RenderTarget *target, int x, sf::IntRect &rect, int limitX) {
  int y = top;
  if (top < 0)
    y = target->getSize().y + top - rect.height;

  int maxWidth = rect.width;
  if (limitX >= 0)
    maxWidth = clamp(rect.width, 0, limitX - x + 1);
  sf::IntRect r = rect;
  r.width = maxWidth;

  sprite->setTextureRect(r);
  sprite->setPosition(target->mapPixelToCoords(sf::Vector2i(x, y)));
  target->draw(*sprite);
  return maxWidth;
}

void HudPanel::paint(sf::RenderTarget *target) {
  int orig = left;
  if (left < 0)
    orig = target->getSize().x + left - width;

  int x = orig;
  int rightBorderX = orig + width - rightBorderRect.width;
  x += paintRect(target, x, leftBorderRect, rightBorderX);
  x += paintRect(target, x, backgroundRect, rightBorderX);

  while (x < rightBorderX)
    x += paintRect(target, x, spacerRect, rightBorderX);

  paintRect(target, rightBorderX, rightBorderRect, -1);
}
