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

  players.push_back(new Player("Raymond", techTree, map, sf::Color::Red, app->getImgMgr()));
  players.push_back(new Player("Jean-Pierre", techTree, map, sf::Color::Blue, app->getImgMgr()));

  fogTileMap = new TileMap("fow", app->getImgMgr());
  fog = new FoW(map, fogTileMap);
  foglight = new FoW(map, fogTileMap, FoW::LIGHT);

  EventCallback *func;
  func = new EventMethodCallback<Game>(this, &Game::onMousePressed);
  addEventCallback("MousePressed", func);
}

bool Game::onMousePressed(const Event &evt) {
  log("Click!");

  const MouseEvent &e = (const MouseEvent&) evt;
  const sf::Vector2i &pos = e.getPosition();
  sf::Vector2i coords = app->mapPixelToCoords(pos);
  sf::Vector2i map_coords = map->viewToMapCoords(coords);

  if (e.getButton() == MouseEvent::BUTTON1) {
    Entity *entity = findEntityAt(map_coords);
    setSelection(entity);
  }

  return true;
}

Game::~Game() {
  std::vector<Player*>::iterator it;
  for (it = players.begin(); it != players.end(); it++)
    delete *it;

  delete techTree;
  delete map;
  delete fog;
  delete foglight;
  delete fogTileMap;
}

void Game::update() {
  int scrollSpeed = 6;
  sf::RenderWindow &window = *app->getWindow();
  sf::View view = window.getView();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    view.move(-scrollSpeed, 0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    view.move(scrollSpeed, 0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    view.move(0, -scrollSpeed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    view.move(0, scrollSpeed);

  sf::IntRect rect = viewGetRect(view);
  rect = map->clampViewRect(rect);
  viewSetRect(view, rect);
  window.setView(view);

  foglight->reset();
  sf::Vector2i coords = app->getCursorPosition();
  fog->set(map->viewToMapCoords(coords), radius, FoW::REVEALED);
  foglight->set(map->viewToMapCoords(coords), radius, FoW::REVEALED);

  std::vector<Player*>::iterator it;
  for (it = players.begin(); it != players.end(); it++)
    (*it)->update();

  repaint();
}

Entity *Game::findEntityAt(sf::Vector2i coords) const {
  std::vector<Player*>::const_iterator it;
  for (it = players.begin(); it != players.end(); it++) {
    std::vector<Entity*> entities = (*it)->getEntities();
    std::vector<Entity*>::const_iterator ent;
    for (ent = entities.begin(); ent != entities.end(); ent++) {
      sf::Vector2i pos = (*ent)->getPosition();
      int size = (*ent)->getProperty(L"size")->AsNumber();
      if (pos.x <= coords.x && coords.x < pos.x + size &&
          pos.y <= coords.y && coords.y < pos.y + size)
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
    sf::Vector2i mapPos = (*it)->getPosition();
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
  foglight->paint(target);
  fog->paint(target);
}

int Game::getRadius() {
  return radius;
}

void Game::setRadius(int radius) {
  this->radius = radius;
}
