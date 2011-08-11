#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <SFML/Graphics.hpp>
#include "techTree.h"
#include "map.h"
#include "entity.h"

class Player {
  public:
    Player(std::string name, TechTree *techTree, Map *map);
    ~Player();

    void addEntity(std::string className, sf::Vector2i pos);
    void addEntity(Entity *ent, sf::Vector2i pos);
    void update();
    void paint(sf::RenderTarget *target);
  private:
    std::string name;
    TechTree *techTree;
    Map *map;
    std::vector<Entity*> entities;
};

#endif /* _PLAYER_H_ */
