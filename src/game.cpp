#include <SFML/Window/Keyboard.hpp>
#include "config.h"
#include "game.h"

Game::Game() {
  window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Tiled Map");
  window->SetPosition(0, 0);

  imageMgr = new ImageManager();
  cursor = new Cursor(window, imageMgr);
  map = Map::fromFile(res_path("map"), imageMgr);
}

Game::~Game() {
  delete cursor;
  delete imageMgr;
}

void Game::onEvent(sf::Event &evt) {
  switch (evt.Type) {
    case sf::Event::Closed:
      log("Closed");
      exit();
      break;
    case sf::Event::KeyReleased:
      log("KeyReleased");
      onKeyReleased(evt);
      break;
    default:
      break;
  }
}

void Game::run() {
  window->EnableVerticalSync(true);
  window->SetFramerateLimit(FRAMERATE_LIMIT);
  window->EnableKeyRepeat(false);
  running = true;
  while (running) {
    sf::Event evt;
    while (window->PollEvent(evt)) {
      onEvent(evt);
    }

    if (!running)
      break;

    paint();
    window->Display();
  }
}

void Game::exit() {
  running = false;
  window->Close();
}

void Game::paintDebug() {
  sf::Text out = sf::Text();
  out.SetCharacterSize(12);
  out.SetColor(sf::Color::White);

  std::ostringstream s;
  sf::Vector2i cur = cursor->getPosition();
  s << "FPS: " << 1000. / window->GetFrameTime() << std::endl
    << "Cursor: " << cur.x << ", " << cur.y;
  out.SetString(s.str());

  out.SetPosition(window->ConvertCoords(0, 0));
  window->Draw(out);
}

void Game::select() {
  sf::Vector2i curPos = (sf::Vector2i) cursor->getViewPosition();
  sf::Vector2i mapPos = map->viewToMapCoords(curPos);
  sf::IntRect rect = map->mapToViewRect(mapPos);
  sf::Shape selection = sf::Shape::Rectangle(rect.Left + 1, rect.Top + 1, rect.Width - 2, rect.Height - 2, sf::Color::White, 1, sf::Color::Green);
  selection.EnableFill(false);
  window->Draw(selection);
}

void Game::paint() {
  window->Clear(sf::Color::Black);
  map->paint(window);
  select();
#if DEBUG
  paintDebug();
#endif
  cursor->paint();
}

void Game::onKeyReleased(sf::Event &evt) {
  switch (evt.Key.Code) {
    case sf::Keyboard::Escape:
    case sf::Keyboard::Q:
      exit();
      break;
    default:
      break;
  }
}
