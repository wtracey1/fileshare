#include "weapon.h"

void Weapon::aim(cocos2d::Vec2 aim){
  
  int angle = static_cast<int>(CC_RADIANS_TO_DEGREES(aim.getAngle()));
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
  if(sprite->isFlippedX()){
    setAnchorPoint(cocos2d::Vec2(.75, .5));
  }else{
    setAnchorPoint(cocos2d::Vec2(.25, .5));
  }
}
