#include <iostream>
#include "player.h"

Player::Player(std::string name, TechTree *techTree, Map *map) {
  this->name = name;
  this->techTree = techTree;
  this->map = map;

  static int move = 0;
  addEntity("worker", sf::Vector2i(3 + move, 5 + move));
  addEntity("forum", sf::Vector2i(5 + move, 4 + move));
  move += 10;
}

Player::~Player() {
  std::vector<Entity*>::iterator it;
  for (it = entities.begin(); it != entities.end(); it++)
    delete *it;
}

void Player::addEntity(std::string className, sf::Vector2i pos) {
  addEntity(techTree->createEntity(className), pos);
}

void Player::addEntity(Entity *ent, sf::Vector2i pos) {
  ent->setMap(map);
  ent->setPosition(pos);
  entities.push_back(ent);
}

void Player::update() {
}

void Player::paint(sf::RenderTarget *target) {
  std::vector<Entity*>::iterator it;
  for (it = entities.begin(); it != entities.end(); it++)
    (*it)->paint(target);
}
