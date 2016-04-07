#ifndef __DRAWABLE__
#define __DRAWABLE__

#include "cocos2d.h"
#include "string"

class Drawable {
public:
  Drawable(const std::string& n): name(n){}
  virtual Drawable* clone() const = 0;
  virtual void update(float) = 0;
  virtual void addToNode(cocos2d::Node*, int x) = 0;
  virtual void removeFromNode(cocos2d::Node*) = 0;
  virtual void x(float) = 0;
  virtual void y(float) = 0;
  virtual float x() const = 0;
  virtual float y() const = 0;
  virtual void dx(float) = 0;
  virtual void dy(float) = 0;
  virtual float dx() const = 0;
  virtual float dy() const = 0;
  virtual void setPosition(cocos2d::Vec2) = 0;
  virtual void setVelocity(cocos2d::Vec2) = 0;
  virtual cocos2d::Vec2 getPosition() const = 0;
  virtual cocos2d::Vec2 getVelocity() const = 0;
  virtual ~Drawable() { };
  std::string getName() const {return name;}
  float getDistance(cocos2d::Vec2 v) const { return getPosition().getDistance(v);}
private:
  std::string name;
};
#endif
