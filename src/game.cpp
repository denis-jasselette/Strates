#include <SFML/Window/Keyboard.hpp>
#include "config.h"
#include "game.h"
#include "utils.h"

Game::Game(Application *app) {
  this->app = app;

  radius = 3;
  techTree = TechTree::fromFile(res_path("techtree.json"), app->getImgMgr());
  map = Map::fromFile(res_path("map"), app->getImgMgr());

  players.push_back(new Player("Raymond", techTree, map));
  players.push_back(new Player("Jean-Pierre", techTree, map));

  fogTileMap = new TileMap("fow", app->getImgMgr());
  fog = new FoW(map, fogTileMap);
  foglight = new FoW(map, fogTileMap, FoW::LIGHT);
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
  sf::View view = window.GetView();
  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
    view.Move(-scrollSpeed, 0);
  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
    view.Move(scrollSpeed, 0);
  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))
    view.Move(0, -scrollSpeed);
  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))
    view.Move(0, scrollSpeed);

  sf::IntRect rect = viewGetRect(view);
  rect = map->clampViewRect(rect);
  viewSetRect(view, rect);
  window.SetView(view);

  foglight->reset();
  sf::Vector2i coords = app->getCursorPosition();
  fog->set(map->viewToMapCoords(coords), radius, FoW::REVEALED);
  foglight->set(map->viewToMapCoords(coords), radius, FoW::REVEALED);

  std::vector<Player*>::iterator it;
  for (it = players.begin(); it != players.end(); it++)
    (*it)->update();
}

void Game::select() {
  sf::Vector2i curPos = app->getCursorPosition();
  sf::Vector2i mapPos = map->viewToMapCoords(curPos);
  sf::IntRect rect = map->mapToViewRect(mapPos);
  sf::Shape selection = sf::Shape::Rectangle(rect.Left + 1, rect.Top + 1, rect.Width - 2, rect.Height - 2, sf::Color::White, 1, sf::Color::Green);
  selection.EnableFill(false);
  app->getWindow()->Draw(selection);
}

void Game::paint() {
  map->paint(app->getWindow());

  std::vector<Player*>::iterator it;
  for (it = players.begin(); it != players.end(); it++)
    (*it)->paint(app->getWindow());

  foglight->paint(app->getWindow());
  fog->paint(app->getWindow());
  select();
}

int Game::getRadius() {
  return radius;
}

void Game::setRadius(int radius) {
  this->radius = radius;
}
