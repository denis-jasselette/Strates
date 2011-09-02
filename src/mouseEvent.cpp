#include "mouseEvent.h"
#include "config.h"

Event::Type MouseEvent::typeNames[] = {
  "MouseClicked",
  "MouseEntered",
  "MouseExited",
  "MouseMoved",
  "MousePressed",
  "MouseReleased",
};

MouseEvent::MouseEvent(MouseType type,
    int button,
    const sf::Vector2i &position)
{
  this->type = type;
  this->button = button;
  this->position = position;
}

Event::Type MouseEvent::getType() const {
  return typeNames[type]; 
}

bool MouseEvent::shouldPropagate(Widget *widget) const {
  return widget->contains(position);
}

int MouseEvent::getButton() {
  return button;
}

const sf::Vector2i &MouseEvent::getPosition() {
  return position;
}
