#ifndef _CURSOR_H_
#define _CURSOR_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"

class Cursor {
  public:
    Cursor(sf::RenderWindow*, ImageManager*);
    ~Cursor();
    void onMoved(const sf::Event::MouseMoveEvent&);
    sf::Vector2i getPosition();
    sf::Vector2f getViewPosition();
    void paint();

  private:
    void centerCursor();

    sf::RenderWindow *window;
    ImageManager *imageMgr;
    sf::Vector2i position;
    sf::Sprite *sprite;
};

#endif /* _CURSOR_H_ */
