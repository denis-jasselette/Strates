#ifndef _EVENTCALLBACK_H_
#define _EVENTCALLBACK_H_

#include "event.h"

template <class T>
class EventCallback {
  public:
    typedef bool (T::*Method)(const Event&);

    EventCallback(T *obj, Method method) {
      this->obj = obj;
      this->method = method;
    };

    bool operator()(const Event &evt) const {
      return (obj->*method)(evt);
    };

  private:
    T *obj;
    Method method;
};

#endif /* _EVENTCALLBACK_H_ */
