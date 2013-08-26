#include "config.h"
#include "menuScreen.h"

MenuScreen::MenuScreen(Application *app) : Screen(app) {
  // TODO: construct things
}

ScreenID MenuScreen::run() {
  log("MENU");

  sf::RenderWindow &window = *app->getWindow();

  bool running = true;
  while (running) {
    sf::Event evt;
    while (window.pollEvent(evt)) {
      switch (evt.type) {
        case sf::Event::Closed:
          log("Closed");
          running = false;
          break;
        case sf::Event::KeyReleased:
          log("KeyReleased");
          switch (evt.key.code) {
            case sf::Keyboard::Escape:
            case sf::Keyboard::Q:
              running = false;
              break;
            case sf::Keyboard::F11:
              return SCREEN_GAME;
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
    }

    if (!running)
      break;

    tick(&window);
    window.display();
  }

  return SCREEN_EXIT;
}

void MenuScreen::update() {}

void MenuScreen::paint(sf::RenderTarget *target) {}
