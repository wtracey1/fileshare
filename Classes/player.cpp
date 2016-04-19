#include "player.h"


Player::Player(const std::string& name) :
  BidirectionalMultiSprite(name),
  weapon("bow")
{
  sprite->addChild(weapon.getSprite(), 1);
  weapon.setAnchorPoint(cocos2d::Vec2(.25, .5));
  weapon.setPosition(cocos2d::Vec2(getSpriteSize().width/2,getSpriteSize().height/2));
}

void Player::update(float dt){
    BidirectionalMultiSprite::update(dt);
    weapon.update(dt);
}
void Player::aim(const cocos2d::Vec2& mousePos){
  //std::cout << "mouse: " << mousePos.x << ", " << mousePos.y << std::endl;
  //cocos2d::Vec2 wepPos = sprite->convertToWorldSpace(weapon.getPosition());
  //std::cout << "sprite: " << wepPos.x << ", " << wepPos.y << std::endl;
  cocos2d::Vec2 
  aim(
  sprite->convertToWorldSpace(weapon.getPosition()), 
  mousePos + cocos2d::Vec2(0,Gamedata::getInstance().getXmlInt("view/height"))
  );
  //std::cout << "aim: " << aim.x << ", " << aim.y << std::endl;
  
  weapon.aim(aim);
}
Projectile* Player::fire(const cocos2d::Vec2& mousePos){
  cocos2d::Vec2 bowPosition = sprite->convertToWorldSpace(weapon.getPosition());
  cocos2d::Vec2 
  aim(
  bowPosition, 
  mousePos + cocos2d::Vec2(0,Gamedata::getInstance().getXmlInt("view/height"))
  );

  return weapon.fire(aim, bowPosition);
}
