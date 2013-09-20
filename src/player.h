#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <SFML/Graphics.hpp>
#include "techTree.h"
#include "map.h"
#include "entity.h"
#include "fow.h"

/**
 * Handles the units and buildings of a player.
 */
class Player {
  public:
    /**
     * Constructor.
     *
     * @param name        the displayed name of the Player
     * @param techTree    a pointer to the TechTree
     * @param map         a pointer to the Map
     */
    Player(std::string name, TechTree *techTree, Map *map, TileMap *fogTileMap, sf::Color color, ImageManager *imgMgr);

    /**
     * Destructor.
     */
    ~Player();

    /**
     * Creates an Entity and places it at a position on the Map.
     *
     * @param className    the className identifying the Entity
     * @param pos          the position where the Entity should be placed
     */
    void addEntity(std::string className, sf::Vector2i pos);

    /**
     * Places an Entity at a position on the Map.
     *
     * @param ent    a pointer to the Entity
     * @param pos    the position where the Entity should be placed
     */
    void addEntity(Entity *ent, sf::Vector2i pos);

    std::vector<Entity*> getEntities();

    /**
     * Updates the status of the Player.
     *
     * This should be called at each frame.
     */
    void update();

    /**
     * Paints the Entity's on a RenderTarget.
     *
     * @param target    the RenderTarget on which to paint
     */
    void paint(sf::RenderTarget *target);

    void paintFoW(sf::RenderTarget *target);

  private:
    std::string name;
    TechTree *techTree;
    Map *map;
    FoW *fog, *foglight;
    sf::Color color;
    sf::Texture *sprite_sheet;
    std::vector<Entity*> entities;

    void loadSpriteSheet(ImageManager *imgMgr);
};

#endif /* _PLAYER_H_ */
