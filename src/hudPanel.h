#ifndef _HUDPANEL_H_
#define _HUDPANEL_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"

class HudPanel {
  public:
    HudPanel(ImageManager *imgMgr);
    ~HudPanel();

    void setPosition(int left, int top, int width);
    void paint(sf::RenderTarget *target);
  private:
    int left, top, width;
    sf::Sprite *sprite;
    sf::IntRect leftBorderRect, backgroundRect, spacerRect, rightBorderRect;

    int paintRect(sf::RenderTarget *target, int x, sf::IntRect &rect, int limitX);
};

#endif /* _HUDPANEL_H_ */
