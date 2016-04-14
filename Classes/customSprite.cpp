#include "cocos2d.h"
#include "customSprite.h"
  //alignmentFactor(Gamedata::getInstance().getXmlInt(name+"/alignment")),
CustomSprite::CustomSprite(const std::string& name) :
  Drawable(name), 
  sprite( cocos2d::Sprite::createWithSpriteFrameName(Gamedata::getInstance().getXmlStr(name+"/frame0")) ),
  //worldSize( cocos2d::Director::getInstance()->getVisibleSize() ),
  worldSize( Gamedata::getInstance().getXmlInt("world/width"), 
             Gamedata::getInstance().getXmlInt("world/height") ),
  velocity( Gamedata::getInstance().getXmlInt(name+"/speed/x"),
            Gamedata::getInstance().getXmlInt(name+"/speed/y") )
{
  sprite->setPosition(cocos2d::Vec2(Gamedata::getInstance().getXmlInt(name+"/position/x"),
                                    Gamedata::getInstance().getXmlInt(name+"/position/y")));
}

CustomSprite::CustomSprite(const CustomSprite& s) :
  Drawable(s), 
  sprite( cocos2d::Sprite::createWithSpriteFrameName(Gamedata::getInstance().getXmlStr(s.getName()+"/frame0")) ),
  worldSize( s.worldSize ),
  velocity( s.velocity )
{
  sprite->setPosition(s.getPosition());
}
CustomSprite::~CustomSprite(){}

void CustomSprite::addToNode(cocos2d::Node* node, int z){
  node->addChild(sprite, z);
}
void CustomSprite::removeFromNode(cocos2d::Node* node){
  node->removeChild(sprite);
}
void CustomSprite::attachCamera(cocos2d::Node* layer){
    layer->runAction(cocos2d::Follow::create(sprite, cocos2d::Rect( 0, 0 , worldSize.width, worldSize.height)));
  }

void CustomSprite::update(float dt){
  cocos2d::Vec2 newPosition = sprite->getPosition();
  cocos2d::Vec2 incr = velocity * dt;
  newPosition.add(incr);

  int width = sprite->getContentSize().width;
  int height = sprite->getContentSize().height;
  
  if ( newPosition.x > worldSize.width - width/2 ) {
    velocity.x = -abs(velocity.x);
  }
  else if ( newPosition.x < width/2 ) {
    velocity.x = abs(velocity.x);
  }
  else if ( newPosition.y > worldSize.height - height/2 ) {
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

