#ifndef _HUD_H_
#define _HUD_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "hudPanel.h"

/**
 * Set of HudPanel's displaying status information and providing basic
 * controls.
 */
class Hud {
  public:
    /**
     * Constructor.
     *
     * @param imgMgr    a pointer to the ImageManager from which buttons' icons
     *                  are retrieved
     */
    Hud(ImageManager *imgMgr);

    /**
     * Destructor.
     */
    ~Hud();

    /**
     * Paints the HudPanel's on a RenderTarget.
     *
     * @param target    a pointer to the destination RenderTarget
     */
    void paint(sf::RenderTarget *target);

  private:
    HudPanel *statusPanel, *actionPanel, *miniMapPanel;
    int margin, actionWidth, miniMapWidth;
};

#endif /* _HUD_H_ */
