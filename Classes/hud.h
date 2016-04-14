#ifndef __HUD__
#define __HUD__

#include "cocos2d.h"
#include "drawable.h"
#include "gamedata.h"

class HUD : public cocos2d::Layer
{
public:
  HUD();
  ~HUD();
  static cocos2d::Layer* createLayer();
  virtual bool init();
  void update(float);
    
  // a selector callback
  void menuCloseCallback(cocos2d::Ref* pSender);
    
  // implement the "static create()" method manually
  CREATE_FUNC(HUD);

private:
  Gamedata& gd;
  cocos2d::Size visibleSize;
  cocos2d::Point origin;
  std::list<Drawable*> drawables;
};

#endif
