#include "cocos2d.h"
#include "customSprite.h"

  CustomSprite::CustomSprite(const std::string& spriteName) : 
    sprite( cocos2d::Sprite::createWithSpriteFrameName(spriteName) ),
    viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
    velocity( 0, 0 )
  {}
  CustomSprite::CustomSprite(const std::string& spriteName, cocos2d::Vec2 vel) : 
    sprite( cocos2d::Sprite::createWithSpriteFrameName(spriteName) ),
    viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
    velocity(vel)
  {}
  CustomSprite::CustomSprite(const std::string& spriteName, cocos2d::Vec2 vel, cocos2d::Vec2 pos) : 
    sprite( cocos2d::Sprite::createWithSpriteFrameName(spriteName) ),
    viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
    velocity(vel)
  {
    sprite->setPosition(pos);
  }
  CustomSprite::CustomSprite(const CustomSprite& s){} //EDIT
  CustomSprite::~CustomSprite(){}
  void CustomSprite::update(float){
  
  }

