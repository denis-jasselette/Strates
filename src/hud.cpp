#include "hud.h"

Hud::Hud(ImageManager *imgMgr) {
  statusPanel = new HudPanel(imgMgr);
  actionPanel = new HudPanel(imgMgr);
  miniMapPanel = new HudPanel(imgMgr);

  margin = 16;
  actionWidth = 256;
  miniMapWidth = 256;
  actionPanel->setPosition(margin, -margin, actionWidth);
  miniMapPanel->setPosition(-margin, -margin, miniMapWidth);
}

Hud::~Hud() {
  delete statusPanel;
  delete actionPanel;
  delete miniMapPanel;
}

void Hud::paint(sf::RenderTarget *target) {
  static int leftMargin = 2 * margin + actionWidth;
  static int rightMargin = 2 * margin + miniMapWidth;
  int width = target->getSize().x - leftMargin - rightMargin;
  statusPanel->setPosition(leftMargin, -margin, width);

  statusPanel->paint(target);
  actionPanel->paint(target);
  miniMapPanel->paint(target);
}
