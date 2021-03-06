#ifndef __FLOCKING_SCENE__
#define __FLOCKING_SCENE__

#include "cocos2d.h"
#include "drawable.h"
#include "gamedata.h"
#include "player.h"
#include <list>
//#include "star.h"

class FlockingScene : public cocos2d::Layer
{
public:
  FlockingScene();
  ~FlockingScene();
  static cocos2d::Layer* createLayer();
  virtual bool init();
  void update(float);
    
  // a selector callback
  void menuCloseCallback(cocos2d::Ref* pSender);
    
  // implement the "static create()" method manually
  void onMouseDown(cocos2d::Event* event);
  void onMouseUp(cocos2d::Event* event);
  void onMouseMove(cocos2d::Event* event);
  void onMouseScroll(cocos2d::Event* event);
  CREATE_FUNC(FlockingScene);

private:
  Gamedata& gd;
  cocos2d::Size visibleSize;
  cocos2d::Point origin;
  std::list<Drawable*> drawables;
  Player* player;
};

#endif
