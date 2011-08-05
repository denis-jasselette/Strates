#ifndef _HUD_H_
#define _HUD_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "hudPanel.h"

class Hud {
  public:
    Hud(ImageManager *imgMgr);
    ~Hud();

    void paint(sf::RenderTarget *target);
  private:
    HudPanel *statusPanel, *actionPanel, *miniMapPanel;
    int margin, actionWidth, miniMapWidth;
};

#endif /* _HUD_H_ */
