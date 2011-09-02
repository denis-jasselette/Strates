#include "event.h"

Event::Event() {
  consumed = false;
}

bool Event::shouldPropagate(Widget *widget) const {
  return true;
}

bool Event::isConsumed() const {
  return consumed;
}

void Event::consume() {
  consumed = true;
}
