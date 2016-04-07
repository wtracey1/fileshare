#include "cocos2d.h"
#include "customSprite.h"
  //alignmentFactor(Gamedata::getInstance().getXmlInt(name+"/alignment")),
CustomSprite::CustomSprite(const std::string& name) :
  Drawable(name), 
  sprite( cocos2d::Sprite::createWithSpriteFrameName(Gamedata::getInstance().getXmlStr(name+"/frame0")) ),
  viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
  velocity( Gamedata::getInstance().getXmlInt(name+"/speed/x"),
            Gamedata::getInstance().getXmlInt(name+"/speed/y") )
{
  sprite->setPosition(cocos2d::Vec2(Gamedata::getInstance().getXmlInt(name+"/position/x"),
                                    Gamedata::getInstance().getXmlInt(name+"/position/y")));
}/*
CustomSprite::CustomSprite(const std::string& spriteName, cocos2d::Vec2 pos) : 
  sprite( cocos2d::Sprite::createWithSpriteFrameName(spriteName) ),
  viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
  velocity( 0, 0)
{
  sprite->setPosition(pos);
}
CustomSprite::CustomSprite(const std::string& spriteName, cocos2d::Vec2 pos, cocos2d::Vec2 vel) : 
  sprite( cocos2d::Sprite::createWithSpriteFrameName(spriteName) ),
  viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
  velocity(vel)
{
  sprite->setPosition(pos);
}*/
/*CustomSprite::CustomSprite(const CustomSprite& s){
  viewSize = s.viewSize;
  
}*/

CustomSprite::~CustomSprite(){}


void CustomSprite::addToNode(cocos2d::Node* node, int z){
  node->addChild(sprite, z);
}
void CustomSprite::removeFromNode(cocos2d::Node* node){
  node->removeChild(sprite);
}
void CustomSprite::update(float dt){
  cocos2d::Vec2 newPosition = sprite->getPosition();
  cocos2d::Vec2 incr = velocity * dt;
  newPosition.add(incr);

  int width = sprite->getContentSize().width;
  int height = sprite->getContentSize().height;
  
  if ( newPosition.x > viewSize.width - width/2 ) {
    velocity.x = -abs(velocity.x);
  }
  else if ( newPosition.x < width/2 ) {
    velocity.x = abs(velocity.x);
  }
  else if ( newPosition.y > viewSize.height - height/2 ) {
    velocity.y = -abs(velocity.y);
  }
  else if ( newPosition.y < height/2 ) {
    velocity.y = abs(velocity.y);
  }
  newPosition = sprite->getPosition(); //recalculate new position with updated velocity
  incr = velocity * dt;
  newPosition.add(incr);
  sprite->setPosition(newPosition);
}

