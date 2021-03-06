#ifndef __PROJECTILE__
#define __PROJECTILE__

#include "cocos2d.h"
#include "bidirectionalMultiSprite.h"
#include "gamedata.h"
#include "string"

class Projectile : public BidirectionalMultiSprite
{
public:
  Projectile(const string& name) :
    BidirectionalMultiSprite(name),
    speed(Gamedata::getInstance().getXmlInt(getName() + "/maxSpeed"))
    {
      sprite->retain();
    };
  ~Projectile(){sprite->release();};
  
  void update(float);
  void removeFromParent(){ sprite->removeFromParent(); }
  int getSpeed(){ return speed; }
private:
  int speed;
};

#endif
