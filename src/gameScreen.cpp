#include "config.h"
#include "gameScreen.h"
#include "utils.h"

GameScreen::GameScreen(Application *app) :
  Screen(app),
  game(app),
  hud(app->getImgMgr())
{
}

void GameScreen::onEvent(sf::Event &evt) {
  switch (evt.Type) {
    case sf::Event::Closed:
      log("Closed");
      exit();
      break;
    case sf::Event::Resized:
      log("Resized");
      onResized(evt);
      break;
    case sf::Event::KeyReleased:
      log("KeyReleased");
      onKeyReleased(evt);
      break;
    case sf::Event::MouseWheelMoved:
      log("MouseWheelMoved");
      onMouseWheelMoved(evt);
      break;
    case sf::Event::MouseButtonPressed:
      log("MouseButtonPressed");
      onMouseButtonPressed(evt);
      break;
    default:
      break;
  }
}

ScreenID GameScreen::run() {
  log("GAME");

  sf::RenderWindow &window = *app->getWindow();

  nextScreen = SCREEN_THIS;
  while (nextScreen == SCREEN_THIS) {
    sf::Event evt;
    while (window.PollEvent(evt))
      onEvent(evt);

    if (nextScreen != SCREEN_THIS)
      break;

    update();
    paint();
    window.Display();
  }

  if (nextScreen != SCREEN_THIS)
    return nextScreen;

  return SCREEN_EXIT;
}

void GameScreen::exit() {
  nextScreen = SCREEN_EXIT;
}

void GameScreen::update() {
  game.update();
}

void GameScreen::paintDebug() {
  sf::Text out = sf::Text();
  out.SetCharacterSize(12);
  out.SetColor(sf::Color::White);

  std::ostringstream s;
  sf::RenderWindow &window = *app->getWindow();
  sf::Vector2i cur = app->getCursorPosition();
  s << "FPS: " << 1000. / window.GetFrameTime() << std::endl
    << "Cursor: " << cur.x << ", " << cur.y << std::endl
    << "Radius: " << game.getRadius();
  out.SetString(s.str());

  out.SetPosition(window.ConvertCoords(0, 0));
  window.Draw(out);
}

void GameScreen::paint() {
  sf::RenderWindow &window = *app->getWindow();
  window.Clear(sf::Color::Black);
  game.paint();
#if DEBUG
  paintDebug();
#endif
  //TODO: unleash the hud *only* when decent graphics for it are added
  //hud.paint(window);
  app->getCursor()->paint();
}

void GameScreen::onResized(sf::Event &evt) {
  sf::RenderWindow &window = *app->getWindow();
  sf::View view = window.GetView();
  view.SetSize(evt.Size.Width, evt.Size.Height);
  window.SetView(view);
}

void GameScreen::onKeyReleased(sf::Event &evt) {
  switch (evt.Key.Code) {
    case sf::Keyboard::Escape:
    case sf::Keyboard::Q:
      exit();
      break;
    case sf::Keyboard::F11:
      nextScreen = SCREEN_MENU;
      break;
    case sf::Keyboard::F10:
      app->toggleFullscreen();
      break;
    default:
      break;
  }
}

void GameScreen::onMouseWheelMoved(sf::Event &evt) {
  int radius = game.getRadius() + evt.MouseWheel.Delta;
  radius = clamp(radius, 0, 10);
  game.setRadius(radius);
}

void GameScreen::onMouseButtonPressed(sf::Event &evt) {
  sf::Vector2i coords = app->getCursorPosition();
  switch (evt.MouseButton.Button) {
    case sf::Mouse::Left:
      break;
    case sf::Mouse::Right:
      break;
    default:
      break;
  }
}