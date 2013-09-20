#ifndef _GAME_H_
#define	_GAME_H_

#include <SFML/Graphics.hpp>
#include "application.h"
#include "widget.h"
#include "techTree.h"
#include "map.h"
#include "player.h"
#include "tileMap.h"

/**
 * Handles the Player's and Map of a game.
 */
class Game : public Widget {
  public:
    /**
     * Constructor.
     *
     * @param app    a pointer to the parent Application
     */
    Game(Application *app, Widget *parent);

    /**
     * Destructor.
     */
    ~Game();

    /**
     * Paints the Map and the Player's.
     * FIXME
     */
    void paint(sf::RenderTarget *target);

    /**
     * Updates the status of the Game.
     *
     * This should be called at each frame.
     */
    void update();

    /**
     * Returns the visibility radius of the Cursor.
     *
     * @return the radius
     */
    int getRadius();

    /**
     * Sets the visibility radius of the Cursor.
     *
     * @param radius    the visibility radius
     */
    void setRadius(int radius);

    Map *getMap();

    Entity *findEntityAt(sf::Vector2i coords) const;

    void setSelection(Entity *entity);

    bool onMousePressed(const Event &evt);

  private:
    void paintSelection(sf::RenderTarget *target) const;

    Application *app;
    int radius;
    TechTree *techTree;
    Map *map;
    std::vector<Player*> players;
    Player *focusedPlayer;
    std::vector<Entity*> selection;
    TileMap *fogTileMap;
};

#endif	/* _GAME_H_ */
