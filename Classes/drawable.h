#ifndef __DRAWABLE__
#define __DRAWABLE__

#include "cocos2d.h"

class Drawable {
public:
  //const cocos2d:Vec2 const pos(){
    //return position;
  //}
  const cocos2d:Vec2 const vel(){
    return velocity;
  }
  virtual void update(float) = 0;
  virtual ~Drawable() { };
private:
}
