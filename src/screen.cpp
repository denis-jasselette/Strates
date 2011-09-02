#include "config.h"
#include "screen.h"

Screen::Screen(Application *app) : Widget() {
  this->app = app;
  setWidth(app->getWindow()->GetWidth());
  setHeight(app->getWindow()->GetHeight());
}

Screen::~Screen() {
}
