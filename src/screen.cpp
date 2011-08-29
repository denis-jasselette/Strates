#include "config.h"
#include "screen.h"

Screen::Screen(Application *app) : Widget() {
  this->app = app;
}

Screen::~Screen() {
}
