#include "config.h"
#include "gameScreen.h"
#include "utils.h"
#include "mouseEvent.h"

GameScreen::GameScreen(Application *app) :
  Screen(app),
  hud(app->getImgMgr())
{
  game = new Game(app, this);
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

    tick(&window);
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
  game->update();
  repaint();
}

void GameScreen::paintDebug(sf::RenderTarget *target) {
  sf::Text out = sf::Text();
  out.SetCharacterSize(12);
  out.SetColor(sf::Color::White);

  std::ostringstream s;
  sf::Vector2i cur = app->getCursorPosition();
  s << "FPS: " << 1000. / app->getWindow()->GetFrameTime() << std::endl
    << "Cursor: " << cur.x << ", " << cur.y << std::endl
    << "Radius: " << game->getRadius();
  out.SetString(s.str());

  out.SetPosition(target->ConvertCoords(0, 0));
  target->Draw(out);
}

void GameScreen::paint(sf::RenderTarget *target) {
  target->Clear(sf::Color::Black);
}

void GameScreen::tick(sf::RenderTarget *target) {
  Screen::tick(target);

#if DEBUG
  paintDebug(target);
#endif
  //TODO: unleash the hud *only* when decent graphics for it are added
  //hud.paint(target);
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
  int radius = game->getRadius() + evt.MouseWheel.Delta;
  radius = clamp(radius, 0, 10);
  game->setRadius(radius);
}

void GameScreen::onMouseButtonPressed(sf::Event &evt) {
  int button;
  sf::Vector2i coords = app->getCursorPosition();

  switch (evt.MouseButton.Button) {
    case sf::Mouse::Left:
      button = MouseEvent::BUTTON1;
      break;
    case sf::Mouse::Right:
      button = MouseEvent::BUTTON2;
      break;
    case sf::Mouse::Middle:
      button = MouseEvent::BUTTON3;
      break;
    default:
      button = MouseEvent::NOBUTTON;
      break;
  }

  if (button != MouseEvent::NOBUTTON) {
    MouseEvent e(MouseEvent::MOUSE_PRESSED, button, coords);
    dispatchEvent(e);
  }
}
