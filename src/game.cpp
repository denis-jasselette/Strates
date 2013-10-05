#include <functional>
#include <SFML/Window/Keyboard.hpp>
#include "config.h"
#include "game.h"
#include "utils.h"
#include "mouseEvent.h"

Game::Game(Application *app, Widget *parent) : Widget(parent) {
  this->app = app;

  radius = 3;
  techTree = TechTree::fromFile(res_path("techtree.json"));
  map = Map::fromFile(res_path("map"), app->getImgMgr());
  fogTileMap = new TileMap("fow", app->getImgMgr());

  players.push_back(new Player("Raymond", techTree, map, fogTileMap, sf::Color::Red, app->getImgMgr()));
  players.push_back(new Player("Jean-Pierre", techTree, map, fogTileMap, sf::Color::Blue, app->getImgMgr()));

  focusedPlayer = players[0];

  EventCallback *func;
  func = new EventMethodCallback<Game>(this, &Game::onMousePressed);
  addEventCallback("MousePressed", func);
}

bool Game::onMousePressed(const Event &evt) {
  log("Click!");

  const MouseEvent &e = (const MouseEvent&) evt;
  const sf::Vector2i &pos = e.getPosition();
  sf::Vector2i coords = app->mapPixelToCoords(pos);

  Entity *entity = findEntityAt(coords);
  if (e.getButton() == MouseEvent::BUTTON1) {
    setSelection(entity);
  } else if (e.getButton() == MouseEvent::BUTTON2) {
    if (selection.size() > 0) {
      if (entity)
        selection.back()->defaultAction(entity);
      else
        selection.back()->defaultAction(coords);
    }
  }

  return true;
}

Game::~Game() {
  std::vector<Player*>::iterator it;
  for (it = players.begin(); it != players.end(); it++)
    delete *it;

  delete techTree;
  delete map;
  delete fogTileMap;
}

void Game::update() {

  sf::Time frametime = clock.restart();
  std::vector<Player*>::iterator it;
  for (it = players.begin(); it != players.end(); it++)
    (*it)->update(frametime);

  repaint();
}

Entity *Game::findEntityAt(sf::Vector2i coords) const {
  std::vector<Player*>::const_iterator it;
  for (it = players.begin(); it != players.end(); it++) {
    std::vector<Entity*> entities = (*it)->getEntities();
    std::vector<Entity*>::const_iterator ent;
    for (ent = entities.begin(); ent != entities.end(); ent++) {
      sf::Vector2f pos = (*ent)->getPosition();
      sf::Vector2f map_coords = map->viewToMapFloatCoords(coords);
      int size = (*ent)->getProperty(L"size")->AsNumber();
      if (pos.x <= map_coords.x && map_coords.x < pos.x + size &&
          pos.y <= map_coords.y && map_coords.y < pos.y + size)
      {
        return *ent;
      }
    }
  }

  return NULL;
}

void Game::setSelection(Entity *entity) {
  selection.clear();
  if (entity)
    selection.push_back(entity);
}

void Game::paintSelection(sf::RenderTarget *target) const {
  std::vector<Entity*>::const_iterator it;
  for (it = selection.begin(); it != selection.end(); it++) {
    int size = (*it)->getProperty(L"size")->AsNumber();
    sf::Vector2f mapPos = (*it)->getPosition();
    sf::IntRect rect = map->mapToViewRect(mapPos);
    rect.width *= size;
    rect.height *= size;
    sf::Vector2f rect_size(rect.width - 2, rect.height - 2);
    sf::RectangleShape shape(rect_size);
    shape.setPosition(rect.left + 1, rect.top + 1);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(1);
    target->draw(shape);
  }
}

void Game::paint(sf::RenderTarget *target) {
  map->paint(target);

  std::vector<Player*>::iterator it;
  for (it = players.begin(); it != players.end(); it++)
    (*it)->paint(target);

  paintSelection(target);
  focusedPlayer->paintFoW(target);
}

int Game::getRadius() {
  return radius;
}

void Game::setRadius(int radius) {
  this->radius = radius;
}

Map *Game::getMap() {
  return map;
}
