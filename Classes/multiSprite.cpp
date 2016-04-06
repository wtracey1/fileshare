#include "cocos2d.h"
#include "multiSprite.h"
#include "vector"

MultiSprite::MultiSprite(const std::vector<std::string>& frameNames, float speed, const cocos2d::Vec2& pos, const cocos2d::Vec2& vel) :
    CustomSprite(frameNames[0], pos, vel)
{
  cocos2d::Vector<cocos2d::SpriteFrame*> frames;
  frames.reserve(frameNames.size());
  
  std::vector<std::string>::const_iterator ptr = frameNames.begin();
  while(ptr != frameNames.end()){
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(*ptr));
    ++ptr;
  }
  
  cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(frames, speed);
  cocos2d::Animate* animate = cocos2d::Animate::create(animation);
  sprite->runAction(cocos2d::RepeatForever::create(animate));
}

void MultiSprite::update(float dt){
  CustomSprite::update(dt);
}
//virtual MultiSprite::~MultiSprite(){};

