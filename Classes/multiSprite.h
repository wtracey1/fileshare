#ifndef __MULTISPRITE__
#define __MULTISPRITE__

#include "cocos2d.h"
#include "vector"
#include "customSprite.h"

class MultiSprite : public CustomSprite{
public:
  MultiSprite(std::vector<std::string>, float, cocos2d::Vec2, cocos2d::Vec2);
  virtual void update(float);
  virtual ~MultiSprite(){}//EDIT
private:

};
#endif
