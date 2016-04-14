#ifndef __BIDIRECTIONAL__
#define __BIDIRECTIONAL__

#include "cocos2d.h"
#include "vector"
#include "gamedata.h"
#include "multiSprite.h"

class BidirectionalMultiSprite : public MultiSprite{
public:
  virtual BidirectionalMultiSprite* clone() const {
    BidirectionalMultiSprite* copy = new BidirectionalMultiSprite(getName());
    copy->setPosition(getPosition());
    return copy;
  }
  BidirectionalMultiSprite(const std::string& name) : MultiSprite(name){}
  BidirectionalMultiSprite(const BidirectionalMultiSprite& s) : MultiSprite(s){}
  virtual void update(float);
  virtual ~BidirectionalMultiSprite(){}//EDIT
};
#endif
