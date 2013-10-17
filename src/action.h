#ifndef _ACTION_H_
#define _ACTION_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "JSON/JSON.h"
#include "clonable.h"

class Entity;

class Action : public Clonable {
public:
  Action(Entity *owner=NULL);
  virtual Action *clone() const = 0;
  void setOwner(Entity *owner);
  Entity *getOwner() const;
  virtual void update(sf::Time frametime) = 0;
  virtual bool isFinished() const = 0;
  sf::IntRect getSpriteRect(const JSONObject &properties) const;
  virtual std::wstring getSpriteRectPropName() const = 0;

protected:
  Entity *owner;

private:
  virtual sf::IntRect getAnimSpriteRect() const = 0;
};

#endif /* _ACTION_H_ */
