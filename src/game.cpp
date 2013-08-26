#include <functional>
#include <SFML/Window/Keyboard.hpp>
#include "config.h"
#include "game.h"
#include "utils.h"

Game::Game(Application *app, Widget *parent) : Widget(parent) {
  this->app = app;

  radius = 3;
  techTree = TechTree::fromFile(res_path("techtree.json"), app->getImgMgr());
  map = Map::fromFile(res_path("map"), app->getImgMgr());

  players.push_back(new Player("Raymond", techTree, map));
  players.push_back(new Player("Jean-Pierre", techTree, map));

  fogTileMap = new TileMap("fow", app->getImgMgr());
  fog = new FoW(map, fogTileMap);
  foglight = new FoW(map, fogTileMap, FoW::LIGHT);

  EventCallback *func;
  func = new EventMethodCallback<Game>(this, &Game::onMousePressed);
  addEventCallback("MousePressed", func);
}

bool Game::onMousePressed(const Event &evt) {
  log("received event");
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

void Game::select() {
  sf::Vector2i curPos = app->getCursorPosition();
  sf::Vector2i mapPos = map->viewToMapCoords(curPos);
  sf::IntRect rect = map->mapToViewRect(mapPos);
  sf::Vector2f size(rect.width - 2, rect.height - 2);
  sf::RectangleShape selection(size);
  selection.setPosition(rect.left + 1, rect.top + 1);
  selection.setFillColor(sf::Color::Transparent);
  selection.setOutlineColor(sf::Color::Green);
  selection.setOutlineThickness(1);
  app->getWindow()->draw(selection);
}

void Game::paint(sf::RenderTarget *target) {
  map->paint(target);

  std::vector<Player*>::iterator it;
  for (it = players.begin(); it != players.end(); it++)
    (*it)->paint(target);

  foglight->paint(target);
  fog->paint(target);
  select();
}

int Game::getRadius() {
  return radius;
}

void Game::setRadius(int radius) {
  this->radius = radius;
}
