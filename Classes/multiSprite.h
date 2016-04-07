#ifndef __MULTISPRITE__
#define __MULTISPRITE__

#include "cocos2d.h"
#include "vector"
#include "gamedata.h"
#include "customSprite.h"

class MultiSprite : public CustomSprite{
public:
  virtual MultiSprite* clone() const {
    MultiSprite* copy = new MultiSprite(getName());
    copy->setPosition(getPosition());
    return copy;
  }
  MultiSprite(const std::string&);
  virtual void update(float);
  virtual ~MultiSprite(){}//EDIT
};
#endif
