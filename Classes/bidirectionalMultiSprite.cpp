#include "cocos2d.h"
#include "bidirectionalMultiSprite.h"
#include "vector"
#include "iostream"

void BidirectionalMultiSprite::update(float dt){
  MultiSprite::update(dt);
  
  //dot product of x and y / (magnitude(x)*magnitude(y)) gives degrees for rotation
  int angle = static_cast<int>(CC_RADIANS_TO_DEGREES(getVelocity().getAngle()));
  //std::cout << angle <<std::endl;
  
  if(dx() < 0){
    sprite->setFlippedX(false);
  }else{
    sprite->setFlippedX(true);
    angle *= -1;
  }
  
  //if(angle > 0){
  sprite->setRotation(angle % 90);
  //}else{
  //  sprite->setRotation(0);
 // }
  
}
