#ifndef __CUSTOMSPRITE__
#define __CUSTOMSPRITE__

#include <string>
#include "cocos2d.h"
#include "drawable.h"

class CustomSprite : public Drawable{
public:
  CustomSprite(const std::string&);
  CustomSprite(const std::string&, cocos2d::Vec2);
  CustomSprite(const std::string&, cocos2d::Vec2, cocos2d::Vec2);
  CustomSprite(const CustomSprite& s);
  void update(float);
  virtual ~CustomSprite();
  virtual void addToNode(cocos2d::Node*, int z = 0);
  virtual void removeFromNode(cocos2d::Node*);  
  virtual void x(float x){sprite->setPositionX(x);}
  virtual void y(float y){sprite->setPositionY(y);}
  virtual float x(){return sprite->getPositionX();}
  virtual float y(){return sprite->getPositionY();}
  virtual void dx(float dx){velocity.x = dx;}
  virtual void dy(float dy){velocity.y = dy;}
  virtual float dx(){return velocity.x;}
  virtual float dy(){return velocity.y;}
  virtual void setPosition(cocos2d::Vec2 pos){sprite->setPosition(pos);}
  virtual void setVelocity(cocos2d::Vec2 vel){velocity = vel;}
  virtual cocos2d::Vec2 getPosition(){return sprite->getPosition();}
  virtual cocos2d::Vec2 getVelocity(){return velocity;}
protected:
  cocos2d::Sprite* sprite;
private:
  cocos2d::Size viewSize;
  cocos2d::Vec2 velocity;
};
#endif
