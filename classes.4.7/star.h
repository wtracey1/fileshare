#include "cocos2d.h"

class Star {
public:
  Star();
  void update(float);
  cocos2d::Sprite* getSprite() const { return sprite; }
    
private:
  cocos2d::Vec2 velocity;
  bool playSound;

  cocos2d::Size viewSize;
  cocos2d::Point origin;
  cocos2d::Sprite* sprite;
  int starWidth;
};
