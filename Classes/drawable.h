#ifndef __DRAWABLE__
#define __DRAWABLE__

#include "cocos2d.h"

class Drawable {
public:
  //const cocos2d:Vec2 const pos(){
    //return position;
  //}
  virtual Drawable* clone() const = 0;
  virtual void update(float) = 0;
  virtual void addToNode(cocos2d::Node*, int x) = 0;
  virtual void removeFromNode(cocos2d::Node*) = 0;
  virtual void x(float) = 0;
  virtual void y(float) = 0;
  virtual float x() = 0;
  virtual float y() = 0;
  virtual void dx(float) = 0;
  virtual void dy(float) = 0;
  virtual float dx() = 0;
  virtual float dy() = 0;
  virtual void setPosition(cocos2d::Vec2) = 0;
  virtual void setVelocity(cocos2d::Vec2) = 0;
  virtual cocos2d::Vec2 getPosition() = 0;
  virtual cocos2d::Vec2 getVelocity() = 0;
  virtual ~Drawable() { };
private:
};
#endif
