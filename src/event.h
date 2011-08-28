#ifndef _EVENT_H_
#define _EVENT_H_

#include <string>

class Widget;

class Event {
  public:
    typedef std::string Type;

    virtual Type getType() const = 0;
    virtual bool shouldPropagate(Widget *widget) const;
    bool isConsumed() const;
    void consume();

  private:
    bool consumed;
};

#endif /* _EVENT_H_ */
