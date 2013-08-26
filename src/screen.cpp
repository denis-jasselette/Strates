#include "config.h"
#include "screen.h"

Screen::Screen(Application *app) : Widget() {
  this->app = app;
  setWidth(app->getWindow()->getSize().x);
  setHeight(app->getWindow()->getSize().y);
}

Screen::~Screen() {
}
