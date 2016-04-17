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
    BidirectionalMultiSprite(name)
    {
      sprite->retain();
    };
  ~Projectile(){sprite->release();};
  
private:
  
};

#endif
