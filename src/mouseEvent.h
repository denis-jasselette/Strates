#ifndef _MOUSEEVENT_H_
#define _MOUSEEVENT_H_

#include <SFML/Graphics.hpp>
#include "event.h"
#include "widget.h"

class MouseEvent : public Event {
  public:
    enum Button {
      NOBUTTON, BUTTON1, BUTTON2, BUTTON3
    };

    enum MouseType {
      MOUSE_CLICKED, MOUSE_ENTERED, MOUSE_EXITED,
      MOUSE_MOVED, MOUSE_PRESSED, MOUSE_RELEASED
    };

    MouseEvent(MouseType type, int button, const sf::Vector2i &position);

    Event::Type getType() const;
    bool shouldPropagate(Widget *widget) const;
    int getButton();
    const sf::Vector2i &getPosition();

  protected:
    MouseType type;
    int button;
    sf::Vector2i position;

  private:
    static Event::Type typeNames[];
};

#endif /* _MOUSEEVENT_H_ */
