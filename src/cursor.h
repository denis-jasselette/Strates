#ifndef _CURSOR_H_
#define _CURSOR_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"

/**
 * Displays a cursor and stores its position.
 */
class Cursor {
  public:
    /**
     * Constructor.
     *
     * @param window      a pointer to the RenderWindow this Cursor is
     *                    displayed on
     * @param imageMgr    a pointer to the ImageManager from which the
     *                    Texture of the cursor is retrieved
     */
    Cursor(sf::RenderWindow *window, ImageManager *imageMgr);

    /**
     * Destructor.
     */
    ~Cursor();

    /**
     * Returns the coordinates of the cursor relatively to the RenderWindow.
     *
     * @return    the position
     */
    sf::Vector2i getPosition();

    /**
     * Returns the coordinates of the cursor relatively to the RenderWindow's
     * View.
     *
     * @return    the position
     */
    sf::Vector2f getViewPosition();

    /**
     * Paints the cursor on the RenderWindow.
     */
    void paint();

  private:
    void refreshPosition();
    void centerCursor();

    sf::RenderWindow *window;
    ImageManager *imageMgr;
    sf::Vector2i position;
    sf::Sprite *sprite;
};

#endif /* _CURSOR_H_ */
