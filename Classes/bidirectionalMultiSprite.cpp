#include "cocos2d.h"
#include "bidirectionalMultiSprite.h"
#include "iostream"
#include <cmath>

void BidirectionalMultiSprite::update(float dt){
  MultiSprite::update(dt);
  updateWithoutBaseCall(dt);
}
void BidirectionalMultiSprite::updateWithoutBaseCall(float dt){
  int angle = static_cast<int>(CC_RADIANS_TO_DEGREES(getVelocity().getAngle()));
 
  if(angle == 90 || angle == -90){ //moving vertical
  
  }else if(angle > 0 && angle < 90){ //moving up and right
    sprite->setFlippedX(invert);
    sprite->setRotation(-angle);
  }else if(angle > 90 && angle < 180){ //moving up and left
    sprite->setFlippedX(!invert);
    sprite->setRotation(180-angle);
  }else if(angle < 0 && angle > -90){ //moving down and right
    sprite->setFlippedX(invert);
    sprite->setRotation(-angle);
  }else if(angle < -90 && angle > -180){  //moving down and left
    sprite->setFlippedX(!invert);
    sprite->setRotation(-(180+angle));
  }else if(angle == -180 || angle == 180){
    sprite->setFlippedX(!invert);
    sprite->setRotation(0);
  }else if(angle == 0){
    sprite->setFlippedX(invert);
    sprite->setRotation(0);
  }
  
  if(!useRotate){
    sprite->setRotation(0);
  }
  
}
