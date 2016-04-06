#include "cocos2d.h"
#include "customSprite.h"

CustomSprite::CustomSprite(const std::string& spriteName) : 
  sprite( cocos2d::Sprite::createWithSpriteFrameName(spriteName) ),
  viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
  velocity( 0, 0 )
{
  sprite->setPosition(cocos2d::Vec2(viewSize.width/2, viewSize.height/2));
}
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
}
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
  cocos2d::Vec2 position = sprite->getPosition();
  cocos2d::Vec2 incr = velocity * dt;
  sprite->setPosition(position.x + incr.x, position.y + incr.y );

  cocos2d::Point location = sprite->getPosition();
  int width = sprite->getContentSize().width;
  int height = sprite->getContentSize().height;
  
  if ( location.x > viewSize.width - width/2 ) {
    velocity.x = -abs(velocity.x);
  }
  else if ( location.x < width/2 ) {
    velocity.x = abs(velocity.x);
  }
  else if ( location.y > viewSize.height - height/2 ) {
    velocity.y = -abs(velocity.y);
  }
  else if ( location.y < height/2 ) {
    velocity.y = abs(velocity.y);
  }
}

