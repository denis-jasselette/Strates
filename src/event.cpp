#include "event.h"

bool Event::shouldPropagate(Widget *widget) const {
  return true;
}

bool Event::isConsumed() const {
  return consumed;
}

void Event::consume() {
  consumed = true;
}
