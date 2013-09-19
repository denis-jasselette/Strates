#include <iostream>
#include "player.h"

Player::Player(std::string name, TechTree *techTree, Map *map, sf::Color color, ImageManager *imgMgr) {
  this->name = name;
  this->techTree = techTree;
  this->map = map;
  this->color = color;
  loadSpriteSheet(imgMgr);

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
}

void Player::loadSpriteSheet(ImageManager *imgMgr) {
  sprite_sheet = new sf::Texture(*imgMgr->get("entities"));

  /* Apply the player color to the generic sprite sheet */
  sf::Image img = sprite_sheet->copyToImage();

  sf::Color MASK_COLOR(0xff, 0, 0xff);
  for (int i = 0; i < img.getSize().y; i++) {
    for (int j = 0; j < img.getSize().x; j++) {
      if (img.getPixel(j, i) == MASK_COLOR)
        img.setPixel(j, i, color);
    }
  }

  sprite_sheet->update(img);
}

void Player::addEntity(std::string className, sf::Vector2i pos) {
  addEntity(techTree->createEntity(className), pos);
}

void Player::addEntity(Entity *ent, sf::Vector2i pos) {
  ent->setMap(map);
  ent->setPosition(pos);
  ent->setTexture(sprite_sheet);
  entities.push_back(ent);
}

std::vector<Entity*> Player::getEntities() {
  return entities;
}

void Player::update() {
}

void Player::paint(sf::RenderTarget *target) {
  std::vector<Entity*>::iterator it;
  for (it = entities.begin(); it != entities.end(); it++)
    (*it)->paint(target, color);
}
