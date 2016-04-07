#include "cocos2d.h"
#include "multiSprite.h"
#include "sstream"
#include <random>
MultiSprite::MultiSprite(const std::string& name) :
    CustomSprite(name)
{
  int frameCount = Gamedata::getInstance().getXmlInt(name+"/frameCount");
  float frameSpeed = Gamedata::getInstance().getXmlFloat(name+"/frameInterval");
  cocos2d::Vector<cocos2d::SpriteFrame*> frames;
  frames.reserve(frameCount);
  std::stringstream strm;
  int frameOffset = Gamedata::getInstance().getRandInRange(0,frameCount); //start at random frame in set
  
  for(int i = 0; i < frameCount; ++i){
    strm.str("");
    strm << "frame" << ((i+frameOffset) % frameCount); //gets frame0...frameCount-1 in a "circular sequence"
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(
                                    Gamedata::getInstance().getXmlStr(name+"/"+strm.str())));
  }

  cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(frames, frameSpeed);
  cocos2d::Animate* animate = cocos2d::Animate::create(animation);
  sprite->runAction(cocos2d::RepeatForever::create(animate));
}

void MultiSprite::update(float dt){
  CustomSprite::update(dt);
}
//virtual MultiSprite::~MultiSprite(){};

