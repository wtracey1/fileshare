#ifndef __CUSTOMSPRITE__
#define __CUSTOMSPRITE__

#include <string>
#include "cocos2d.h"
#include "gamedata.h"
#include "drawable.h"

class CustomSprite : public Drawable{
public:
  CustomSprite(const std::string&);
  CustomSprite(const CustomSprite& s);
  virtual void update(float);
  virtual CustomSprite* clone() const {
    CustomSprite* copy = new CustomSprite(getName());
    copy->setPosition(getPosition());
    return copy;
  }
 
  virtual ~CustomSprite();
  virtual void addToNode(cocos2d::Node*, int z = 0);
  virtual void removeFromNode(cocos2d::Node*);  
  virtual void x(float x){sprite->setPositionX(x);}
  virtual void y(float y){sprite->setPositionY(y);}
  virtual float x() const {return sprite->getPositionX();}
  virtual float y() const {return sprite->getPositionY();}
  virtual void dx(float dx){velocity.x = dx;}
  virtual void dy(float dy){velocity.y = dy;}
  virtual float dx() const {return velocity.x;}
  virtual float dy() const {return velocity.y;}
  virtual void setPosition(cocos2d::Vec2 pos){sprite->setPosition(pos);}
  virtual void setVelocity(cocos2d::Vec2 vel){velocity = vel;}
  virtual cocos2d::Vec2 getPosition() const {return sprite->getPosition();}
  virtual cocos2d::Vec2 getVelocity() const {return velocity;}
  virtual cocos2d::Size getSpriteSize() const {return sprite->getContentSize();}
  virtual cocos2d::Sprite* getSprite(){ return sprite; }
  void setAnchorPoint(cocos2d::Vec2 v) { sprite->setAnchorPoint(v);}
  void setScale(float s){sprite->setScale(s);}
  void runAction(cocos2d::Action* a) {sprite->runAction(a);}
  void removeFromParent(){sprite->removeFromParent();}
  void attachCamera(cocos2d::Node*);
protected:
  cocos2d::Sprite* sprite;
private:
  cocos2d::Size worldSize;
  cocos2d::Vec2 velocity;
};
#endif
