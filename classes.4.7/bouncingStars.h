#ifndef __BOUNCING_STARS__
#define __BOUNCING_STARS__

#include "cocos2d.h"
#include "star.h"

class BouncingStars : public cocos2d::Layer
{
public:
  BouncingStars();
  ~BouncingStars() { delete star; }
  static cocos2d::Scene* createScene();
  virtual bool init();
  void update(float);
    
  // a selector callback
  void menuCloseCallback(cocos2d::Ref* pSender);
    
  // implement the "static create()" method manually
  CREATE_FUNC(BouncingStars);

private:
  float moveTime;
  float dx, dy;

  Star* star;
  cocos2d::Size visibleSize;
  cocos2d::Point origin;
  int starWidth;
};

#endif // __HELLOWORLD_SCENE_H__
