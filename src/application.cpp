#include "config.h"
#include "application.h"
#include "screens.h"

Application::Application() {
  setFullscreen(false);
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(FRAMERATE_LIMIT);
  window.setKeyRepeatEnabled(false);

  DEFAULT_FONT.loadFromFile(res_path("arial.ttf"));

  imgMgr = new ImageManager();
  cursor = new Cursor(&window, imgMgr);

  GameScreen *game = new GameScreen(this);
  screens.push_back(game);
  MenuScreen *menu = new MenuScreen(this);
  screens.push_back(menu);

  current = SCREEN_GAME;
}

Application::~Application() {
  std::vector<Screen*>::iterator it;
  for (it = screens.begin(); it != screens.end(); it++)
    delete *it;

  delete cursor;
  delete imgMgr;
}

int Application::run() {
  window.setActive(false);
  sf::Thread screensThread(&Application::runScreens, this);

  screensThread.launch();
  screensThread.wait();

  return 0;
}

void Application::runScreens() {
  window.setActive(true);
  while (current >= 0)
    current = screens[current]->run();
}

void Application::setFullscreen(bool value) {
  std::string title = "Strates";
  if (value) {
    sf::VideoMode mode = sf::VideoMode::getFullscreenModes()[0];
    window.create(mode, title, sf::Style::Fullscreen);
  }
  else {
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode(800, 600, mode.bitsPerPixel), title);
  }
  window.setMouseCursorVisible(false);
  isFullscreen = value;
}

void Application::toggleFullscreen() {
  setFullscreen(!isFullscreen);
}

sf::RenderWindow *Application::getWindow() {
  return &window;
}

ImageManager *Application::getImgMgr() {
  return imgMgr;
}

Cursor *Application::getCursor() {
  return cursor;
}

sf::Vector2i Application::getCursorPosition() {
  return (sf::Vector2i) cursor->getViewPosition();
}

sf::Vector2i Application::mapPixelToCoords(const sf::Vector2i &pixel) {
  return (sf::Vector2i) window.mapPixelToCoords(pixel);
}
