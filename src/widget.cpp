#include "widget.h"

Widget::Widget(Widget *parent) : parent(parent) {
  setSensitive(true);
  repaint();
}

Widget::~Widget() {
  std::vector<Widget*>::iterator c_it;
  for (c_it = children.begin(); c_it != children.end(); c_it++)
    delete *c_it;

  std::map<Event::Type, EventListener*>::iterator l_it;
  for (l_it = eventListeners.begin(); l_it != eventListeners.end(); l_it++)
    delete l_it->second;
}

void Widget::add(Widget *child) {
  if (!child)
    return;

  child->setParent(this);
  children.push_back(child);
}

void Widget::setParent(Widget *parent) {
  this->parent = parent;
}

bool Widget::isTopLevel() {
  return parent == NULL;
}

void Widget::setPosition(const sf::Vector2i &pos) {
  hitBox.Left = pos.x;
  hitBox.Top = pos.y;
}

void Widget::setWidth(int width) {
  hitBox.Width = width;
}

void Widget::setHeight(int height) {
  hitBox.Height = height;
}

bool Widget::contains(const sf::Vector2i &point) {
  return hitBox.Contains(point);
}

void Widget::tick(sf::RenderTarget *target) {
  update();

  if (needsRepaint) {
    paint(target);
    needsRepaint = false;
  }

  std::vector<Widget*>::iterator it;
  for (it = children.begin(); it < children.end(); it++)
    (*it)->tick(target);
}

void Widget::repaint() {
  needsRepaint = true;

  std::vector<Widget*>::iterator it;
  for (it = children.begin(); it < children.end(); it++)
    (*it)->repaint();
}

void Widget::setSensitive(bool sensitive) {
  this->sensitive = sensitive;
}

bool Widget::isSensitive() {
  return sensitive;
}

void Widget::addEventCallback(Event::Type type,
    const EventCallback<Widget> &func)
{
  Widget::EventListener *&listener = eventListeners[type];

  if (listener == NULL) {
    if (!isTopLevel())
      parent->trackEventType(type);

    listener = new Widget::EventListener();
  }

  listener->push_back(func);
}

const Widget::EventListener &Widget::getListener(Event::Type type) {
  return *eventListeners.find(type)->second;
}

void Widget::trackEventType(Event::Type type) {
  eventTypesTracked[type]++;
}

void Widget::untrackEventType(Event::Type type) {
  eventTypesTracked[type]--;
}

bool Widget::isEventTypeTracked(Event::Type type) {
  return eventTypesTracked.find(type)->second > 0
    || !getListener(type).empty();
}

bool Widget::shouldPropagate(Widget *child, const Event &evt) {
  return child->isSensitive()
    && child->isEventTypeTracked(evt.getType())
    && evt.shouldPropagate(child);
}

void Widget::propagateEvent(Event &evt) {
  std::vector<Widget*>::iterator it;
  for (it = children.begin(); it != children.end(); it++) {
    if (shouldPropagate(*it, evt))
      (*it)->dispatchEvent(evt);
  }
}

void Widget::dispatchEvent(Event &evt) {
  if (!isEventTypeTracked(evt.getType()))
    return;

  propagateEvent(evt);

  if (evt.isConsumed())
    return;

  EventListener listener = getListener(evt.getType());
  EventListener::const_iterator it;
  for (it = listener.begin(); it != listener.end(); it++)
    (*it)(evt);
}
