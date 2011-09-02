#ifndef _EVENTCALLBACK_H_
#define _EVENTCALLBACK_H_

#include "event.h"

class EventCallback {
  public:
    virtual ~EventCallback() {}
    virtual bool operator() (const Event &evt) = 0;
};

template <typename T>
class EventMethodCallback : public EventCallback {
  public:
    EventMethodCallback(T *obj, bool (T::*method)(const Event&)) {
      this->obj = obj;
      this->method = method;
    }
    virtual bool operator() (const Event &evt) {
      return (obj->*method)(evt);
    }
  private:
    T *obj;
    bool (T::*method)(const Event&);
};

/*template <class T>
EventCallback EventCallbackFromMethod(T *obj,
    bool (T::*method)(const Event&))
{
  return EventMethodCallback<T>(obj, method);
}*/

#endif /* _EVENTCALLBACK_H_ */
