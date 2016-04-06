#ifndef __MULTISPRITE__
#define __MULTISPRITE__

#include "cocos2d.h"
#include "vector"
#include "customSprite.h"

class MultiSprite : public CustomSprite{
public:
  MultiSprite(const std::vector<std::string>&, float, const cocos2d::Vec2&, const cocos2d::Vec2&);
  virtual void update(float);
  virtual ~MultiSprite(){}//EDIT
};
#endif
