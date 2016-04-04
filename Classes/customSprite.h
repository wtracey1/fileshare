#ifndef __CUSTOMSPRITE__
#define __CUSTOMSPRITE__

#include <string>
#include "cocos2d.h"

class CustomSprite {
public:
  CustomSprite(const std::string&);
  CustomSprite(const std::string&, cocos2d::Vec2);
  CustomSprite(const std::string&, cocos2d::Vec2, cocos2d::Vec2);
  CustomSprite(const CustomSprite& s);
  void update(float);
  virtual ~CustomSprite();
private:
  cocos2d::Sprite* sprite;
  cocos2d::Size viewSize;
  cocos2d::Vec2 velocity;
};
#endif
