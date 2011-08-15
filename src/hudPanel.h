#ifndef _HUDPANEL_H_
#define _HUDPANEL_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"

/**
 * Displays status information and basic controls.
 */
class HudPanel {
  public:
    /**
     * Constructor.
     *
     * @param imgMgr    a pointer to the ImageManager from which buttons' icons
     *                  are retrieved
     */
    HudPanel(ImageManager *imgMgr);

    /**
     * Destructor.
     */
    ~HudPanel();

    /**
     * Sets the position and width of the HudPanel.
     *
     * @param left     the left margin in pixels
     * @param top      the top margin in pixels
     * @param width    the width in pixels
     */
    void setPosition(int left, int top, int width);

    /**
     * Paints the HudPanel on a RenderTarget.
     *
     * @param target    a pointer to the destination RenderTarget
     */
    void paint(sf::RenderTarget *target);

  private:
    int left, top, width;
    sf::Sprite *sprite;
    sf::IntRect leftBorderRect, backgroundRect, spacerRect, rightBorderRect;

    int paintRect(sf::RenderTarget *target, int x, sf::IntRect &rect, int limitX);
};

#endif /* _HUDPANEL_H_ */
