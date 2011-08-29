#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <vector>

#include "event.h"
#include "eventCallback.h"

/**
 * This class provides the base for any displayable object.
 *
 * It primarily allows the handling of events in a more object-oriented way.
 */
class Widget {
  private:
    typedef std::vector< EventCallback<Widget> > EventListener;

  public:
    /**
     * Constructor.
     */
    Widget(Widget *parent = NULL);

    /**
     * Destructor.
     */
    ~Widget();

    /**
     * Adds a Widget as a child.
     *
     * @param child    a pointer to the Widget to add
     */
    void add(Widget *child);

    /**
     * Changes the parent element.
     *
     * @param parent    a pointer to the new parent
     */
    void setParent(Widget *parent);

    /**
     * Returns whether the Widget is at the top level.
     *
     * @return    true if it is top level, false otherwise
     */
    bool isTopLevel();

    /**
     * Sets the top-left corner.
     *
     * @param pos    the new position of the top-left corner
     */
    void setPosition(const sf::Vector2i &pos);

    /**
     * Sets the width.
     *
     * @param width    the new width
     */
    void setWidth(int width);

    /**
     * Sets the height.
     *
     * @param height    the new height
     */
    void setHeight(int height);

    /**
     * Returns whether a point is located inside the Widget.
     *
     * @param point    the point
     * @return         true if the point is inside the Widget, false otherwise
     */
    bool contains(const sf::Vector2i &point);

    /**
     * Convenience function that updates the Widget then paints it if needed.
     *
     * @param target    a pointer to the RenderTarget on which to paint
     */
    virtual void tick(sf::RenderTarget *target);

    /**
     * Forces to paint the whole Widget on next tick.
     */
    void repaint();

    void setSensitive(bool sensitive = true, bool recursive = true);
    bool isSensitive();
    const EventListener &getListener(Event::Type type);
    void addEventCallback(Event::Type type,
        const EventCallback<Widget> &func);

  protected:
    Widget *parent;
    std::vector<Widget*> children;
    bool needsRepaint;
    sf::IntRect hitBox;
    bool sensitive;

    virtual void update() = 0;
    virtual void paint(sf::RenderTarget *target) = 0;

  private:
    std::map<Event::Type, int> eventTypesTracked;
    std::map<Event::Type, EventListener*> eventListeners;

    void trackEventType(Event::Type type);
    void untrackEventType(Event::Type type);
    bool isEventTypeTracked(Event::Type type);
    bool shouldPropagate(Widget *child, const Event &evt);
    void propagateEvent(Event &evt);
    void dispatchEvent(Event &evt);
};

#endif /* _WIDGET_H_ */
