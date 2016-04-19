#ifndef __MULTISPRITE__
#define __MULTISPRITE__

#include "cocos2d.h"
#include "vector"
#include "gamedata.h"
#include "customSprite.h"

class MultiSprite : public CustomSprite{
public:
  MultiSprite(const std::string&);
  MultiSprite( const MultiSprite& s);
  virtual MultiSprite* clone() const {
    MultiSprite* copy = new MultiSprite(getName());
    copy->setPosition(getPosition());
    return copy;
  }
  virtual void update(float);
  virtual ~MultiSprite();
private:
};
#endif
