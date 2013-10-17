#include <functional>
#include <SFML/Window/Keyboard.hpp>
#include <typeinfo>
#include <exception>
#include "config.h"
#include "game.h"
#include "utils.h"
#include "mouseEvent.h"
#include "ai.h"
#include "actionMove.h"

Game::Game(Application *app, Widget *parent) : Widget(parent) {
  this->app = app;

  radius = 3;
  techTree = TechTree::fromFile(res_path("techtree.json"));
  map = Map::fromFile(res_path("map"), app->getImgMgr());
  fogTileMap = new TileMap("fow", app->getImgMgr());
  selectionEnabled = false;

  players.push_back(new Player("Raymond", techTree, map, fogTileMap, sf::Color::Red, app->getImgMgr()));
  players.push_back(new Player("Jean-Pierre", techTree, map, fogTileMap, sf::Color::Blue, app->getImgMgr()));

  focusedPlayer = players[0];

  EventCallback *func;
  func = new EventMethodCallback<Game>(this, &Game::onMousePressed);
  addEventCallback("MousePressed", func);
  func = new EventMethodCallback<Game>(this, &Game::onMouseReleased);
  addEventCallback("MouseReleased", func);
  func = new EventMethodCallback<Game>(this, &Game::onMouseMoved);
  addEventCallback("MouseMoved", func);
}

bool Game::onMousePressed(const Event &evt) {
  log("Click!");

  const MouseEvent &e = (const MouseEvent&) evt;
  const sf::Vector2i &pos = e.getPosition();
  sf::Vector2i coords = app->mapPixelToCoords(pos);
  
  if(e.getButton() == MouseEvent::BUTTON3) {
    focusedPlayer->addEntity("worker", map->viewToMapCoords(coords));
  }
  
  selectionAction(evt);
  if( e.getButton() == MouseEvent::BUTTON1) {
    selectionEnabled = true;
    selectionStart = coords;
  }
  return true;
}

void Game::selectionAction(const Event &evt) {
  const MouseEvent &e = (const MouseEvent&) evt;
  const sf::Vector2i &pos = e.getPosition();
  sf::Vector2i coords = app->mapPixelToCoords(pos);
  sf::Vector2i map_coords = map->viewToMapCoords(coords);
  Entity *entity = findEntityAt(coords);
  if (e.getButton() == MouseEvent::BUTTON1) {
    selection.clear();
    setSelection(entity);
  } else if (e.getButton() == MouseEvent::BUTTON2) {
    int size = sqrt(selection.size());
    int i = 0;
    std::vector<Entity*>::iterator it;    
    //Prepare pathfinding
    //Todo find a better place
    AI::getInstance().prepareAccMap(selection);
    for(it = selection.begin(); it != selection.end(); it++) {
      int ent_size = (*it)->getProperty(L"size")->AsNumber(); 
      int x = map_coords.x + (i % size);
      int y = map_coords.y + (i / size);
      if (entity)
        (*it)->defaultAction(entity);
      else
        (*it)->defaultAction(sf::Vector2i(x, y));
      i++;
    }
  }
}

bool Game::onMouseMoved(const Event &evt) {
  const MouseEvent &e = (const MouseEvent&) evt;
  const sf::Vector2i &pos = e.getPosition();
  sf::Vector2i coords = app->mapPixelToCoords(pos);
  selectionEnd = coords;
  return true;
}

bool Game::onMouseReleased(const Event &evt) {
  log("Unclick!");

  if(selectionEnabled) {
    std::vector<Entity*>::const_iterator it;
    std::vector<Entity*> candidates = findEntityIn(getSelectionRect(), focusedPlayer);
    for (it = candidates.begin(); it != candidates.end(); it++) {
      selection.push_back(*it);
    }
    selectionEnabled = false;
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

std::vector<Entity*> Game::findEntityIn(sf::IntRect rect, Player* player=NULL) const {
  std::vector<Entity*> rtn;
  std::vector<Player*>::const_iterator it;
  for (it = players.begin(); it != players.end(); it++) {
    
    if (player != NULL && player != (*it))
      continue;
    
    std::vector<Entity*> entities = (*it)->getEntities();
    std::vector<Entity*>::const_iterator ent;
    for (ent = entities.begin(); ent != entities.end(); ent++) {
      sf::Vector2f pos = (*ent)->getPosition();
      int size = (*ent)->getProperty(L"size")->AsNumber();
      sf::FloatRect ent_rect(pos.x, pos.y, size, size);
 
      sf::FloatRect map_rect = map->viewToMapFloatRect(rect);
      if (ent_rect.intersects(map_rect)) {
	rtn.push_back(*ent);
      }
    }
  }  
  return rtn;
}

void Game::setSelection(Entity *entity) {
  selection.clear();
  if (entity)
    selection.push_back(entity);
}

sf::IntRect Game::getSelectionRect() const {
  sf::Vector2i rect_size;
  rect_size.x = std::abs(selectionStart.x - selectionEnd.x);
  rect_size.y = std::abs(selectionStart.y - selectionEnd.y);
  sf::Vector2i rect_pos;
  
  rect_pos.x = (selectionStart.x < selectionEnd.x) ? selectionStart.x : selectionEnd.x;
  rect_pos.y = (selectionStart.y < selectionEnd.y) ? selectionStart.y : selectionEnd.y;
  return sf::IntRect(rect_pos, rect_size);
}

void Game::paintSelection(sf::RenderTarget *target) const {
  std::vector<Entity*>::const_iterator it;
  if(selectionEnabled) {
    sf::IntRect sel_rect = getSelectionRect();
    sf::Vector2f rect_size(sel_rect.width, sel_rect.height);
    sf::Vector2f rect_pos(sel_rect.left, sel_rect.top);
	
    sf::RectangleShape shape(rect_size);
    shape.setPosition(rect_pos.x, rect_pos.y);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(1);
    target->draw(shape);
   
    std::vector<Entity*> candidates = findEntityIn(getSelectionRect(), focusedPlayer);
    for (it = candidates.begin(); it != candidates.end(); it++) {
      sf::IntRect rect = (*it)->getSelectionRect();
      sf::Vector2f rect_size(rect.width - 2, rect.height - 2);
      sf::RectangleShape shape(rect_size);
      shape.setPosition(rect.left + 1, rect.top + 1);
      shape.setFillColor(sf::Color::Transparent);
      shape.setOutlineColor(sf::Color::Green);
      shape.setOutlineThickness(1);
      target->draw(shape);
    }
  }

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

    Unit *u = dynamic_cast<Unit*>((*it));
    sf::Vector2i lastPos = map->mapToViewCoords(mapPos + float(size) * sf::Vector2f(0.5, 0.5));
    if (u == NULL)
      continue;

    const ActionMove *move = dynamic_cast<const ActionMove*>(&(u->getAction()));
    if (move == NULL)
      continue;

    std::list<sf::Vector2i> waypoints = move->getWaypoints();
    std::list<sf::Vector2i>::iterator wit;
    for(wit = waypoints.begin(); wit != waypoints.end(); wit++) {
        sf::Vector2f tmpPos(wit->x, wit->y);
        sf::Vector2i pos = map->mapToViewCoords(tmpPos);
        sf::CircleShape circle((rect.width - 2)/2);
        circle.setPosition(pos.x, pos.y);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(sf::Color::Green);
        circle.setOutlineThickness(1);
        target->draw(circle);
        sf::Vector2i newPos = map->mapToViewCoords(tmpPos + float(size) * sf::Vector2f(0.5, 0.5));
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(lastPos.x, lastPos.y)),
            sf::Vertex(sf::Vector2f(newPos.x, newPos.y))
        };
        line[0].color = sf::Color::Green;
        line[1].color = sf::Color::Green;
        target->draw(line, 2, sf::Lines);
        lastPos = newPos;            
    }
  }
}

void Game::paint(sf::RenderTarget *target) {
  map->paint(target);

  paintSelection(target);
  std::vector<Player*>::iterator it;
  for (it = players.begin(); it != players.end(); it++)
    (*it)->paint(target);

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

std::vector<Entity*> Game::getEntities() {
  std::vector<Entity*> rtn;

  std::vector<Player*>::iterator it;
  for (it = players.begin(); it != players.end(); it++) {
    std::vector<Entity*> pEnts = (*it)->getEntities();
    rtn.insert(rtn.end(), pEnts.begin(), pEnts.end()); 
  }

  return rtn;
}
