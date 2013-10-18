#include <iostream>
#include "player.h"

Player::Player(std::string name, TechTree *techTree, Map *map, TileMap *fogTileMap, const PlayerColor &color, ImageManager *imgMgr)
  :
    color(color)
{
  this->name = name;
  this->techTree = techTree;
  this->map = map;
  loadSpriteSheet(imgMgr);

  fog = new FoW(map, fogTileMap);
  foglight = new FoW(map, fogTileMap, FoW::LIGHT);

  static int move = 0;
  addEntity("worker", sf::Vector2i(3 + move, 5 + move));
  addEntity("forum", sf::Vector2i(5 + move, 4 + move));
  move += 10;
}

Player::~Player() {
  std::vector<Entity*>::iterator it;
  for (it = entities.begin(); it != entities.end(); it++)
    delete *it;

  delete sprite_sheet;
  delete fog;
  delete foglight;
}

void Player::loadSpriteSheet(ImageManager *imgMgr) {
  sprite_sheet = new sf::Texture(*imgMgr->get("entities"));
  color.apply(sprite_sheet);
}

void Player::addEntity(std::string className, sf::Vector2i pos) {
  addEntity(techTree->createEntity(className), pos);
}

void Player::addEntity(Entity *ent, sf::Vector2i pos) {
  ent->setMap(map);
  ent->setPosition(sf::Vector2f(pos));
  ent->setTexture(sprite_sheet);
  entities.push_back(ent);
}

std::vector<Entity*> Player::getEntities() {
  return entities;
}

void Player::update(sf::Time frametime) {
  foglight->reset();
  std::vector<Entity*>::iterator it;
  for (it = entities.begin(); it != entities.end(); it++) {
    (*it)->update(frametime);

    int radius = (*it)->getProperty(L"visibility")->AsNumber();
    sf::Vector2i pos = (*it)->getTilePosition();
    int size = (*it)->getProperty(L"size")->AsNumber();
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        sf::Vector2i tile = pos + sf::Vector2i(i, j);
        fog->set(tile, radius, FoW::REVEALED);
        foglight->set(tile, radius, FoW::REVEALED);
      }
    }
  }
}

void Player::paint(sf::RenderTarget *target) {
  std::vector<Entity*>::iterator it;
  for (it = entities.begin(); it != entities.end(); it++)
    (*it)->paint(target);
}

void Player::paintFoW(sf::RenderTarget *target) {
  foglight->paint(target);
  fog->paint(target);
}
