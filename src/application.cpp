#include "config.h"
#include "application.h"
#include "screens.h"

Application::Application() {
  setFullscreen(false);
  window.EnableVerticalSync(true);
  window.SetFramerateLimit(FRAMERATE_LIMIT);
  window.EnableKeyRepeat(false);

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
  sf::Thread screensThread(&Application::runScreens, this);

  screensThread.launch();
  screensThread.wait();

  return 0;
}

void Application::runScreens() {
  while (current >= 0)
    current = screens[current]->run();
}

void Application::setFullscreen(bool value) {
  std::string title = "Strates";
  if (value) {
    sf::VideoMode mode = sf::VideoMode::GetFullscreenModes()[0];
    window.Create(mode, title, sf::Style::Fullscreen);
  }
  else {
    sf::VideoMode mode = sf::VideoMode::GetDesktopMode();
    window.Create(sf::VideoMode(800, 600, mode.BitsPerPixel), title);
  }
  window.ShowMouseCursor(false);
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
