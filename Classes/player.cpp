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
}
void Player::aim(const cocos2d::Vec2& mousePos){
  std::cout << "mouse: " << mousePos.x << ", " << mousePos.y << std::endl;
  cocos2d::Vec2 wepPos = sprite->convertToWorldSpaceAR(weapon.getPosition());
  std::cout << "sprite: " << wepPos.x << ", " << wepPos.y << std::endl;
  cocos2d::Vec2 aim(sprite->convertToWorldSpaceAR(weapon.getPosition()), mousePos + cocos2d::Vec2(0, 1024));
  weapon.aim(aim);
}
