#include "cocos2d.h"
#include "bidirectionalMultiSprite.h"
#include "vector"

void BidirectionalMultiSprite::update(float dt){
  MultiSprite::update(dt);
  if(dx() < 0){
    sprite->setFlippedX(false);
  }else{
    sprite->setFlippedX(true);
  }
  //dot product of x and y / (magnitude(x)*magnitude(y)) gives degrees for rotation
}
