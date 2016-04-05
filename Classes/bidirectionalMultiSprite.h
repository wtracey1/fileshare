#ifndef __BIDIRECTIONAL__
#define __BIDIRECTIONAL__

#include "cocos2d.h"
#include "vector"
#include "multiSprite.h"

class BidirectionalMultiSprite : public MultiSprite{
public:
  BidirectionalMultiSprite(std::vector<std::string> frameNames, float speed, cocos2d::Vec2 pos, cocos2d::Vec2 vel) : 
    MultiSprite(frameNames, speed, pos, vel)
  {}
  virtual void update(float);
  //virtual ~BidirectionalMultiSprite(){}//EDIT
};
#endif
