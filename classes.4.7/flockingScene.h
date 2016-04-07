#ifndef __FLOCKING_SCENE__
#define __FLOCKING_SCENE__

#include "cocos2d.h"
#include "drawable.h"
#include <list>
//#include "star.h"

class FlockingScene : public cocos2d::Layer
{
public:
  FlockingScene();
  ~FlockingScene();
  static cocos2d::Scene* createScene();
  virtual bool init();
  void update(float);
    
  // a selector callback
  void menuCloseCallback(cocos2d::Ref* pSender);
    
  // implement the "static create()" method manually
  CREATE_FUNC(FlockingScene);

private:

  cocos2d::Size visibleSize;
  cocos2d::Point origin;
  std::list<Drawable*> drawables;
};

#endif