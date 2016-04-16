#ifndef __WEAPON__
#define __WEAPON__

#include "cocos2d.h"
#include "bidirectionalMultiSprite.h"
#include "gamedata.h"
#include "string"

class Weapon : public BidirectionalMultiSprite
{
public:
  Weapon(const string& name) :
    BidirectionalMultiSprite(name)
    {setVelocity(cocos2d::Vec2(0,0));};
  ~Weapon(){};
  void aim(cocos2d::Vec2);
  
private:
  
};

#endif
