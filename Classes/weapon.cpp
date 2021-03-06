#include "weapon.h"

Weapon::Weapon(const string& name) :
  BidirectionalMultiSprite(name),
  ammo(Gamedata::getInstance().getXmlStr(getName()+"/ammo")),
  ammoCap(Gamedata::getInstance().getXmlInt(getName()+"/ammoCap")),
  inactiveAmmo(),
  activeAmmo()
{
  setVelocity(cocos2d::Vec2(0,0));
  Projectile* p;
  for(int i = 0; i < ammoCap; ++i){
    p = new Projectile(ammo);
    inactiveAmmo.push_back(p);
  }
}

Weapon::~Weapon(){
  std::vector<Projectile*>::iterator ptr = inactiveAmmo.begin();
  while(ptr != inactiveAmmo.end()){
    delete *ptr;//really no need to erase from the list, its about to get destroyed
    ++ptr;
  }
  std::list<Projectile*>::iterator itr = activeAmmo.begin();
  itr = activeAmmo.begin();
  while(itr != activeAmmo.end()){
    delete *itr;//really no need to erase from the list, its about to get destroyed
    ++itr;
  }
}
void Weapon::update(float dt){
  //Reclaim projectiles that have left the world bounds
  std::list<Projectile*>::iterator itr = activeAmmo.begin();
  itr = activeAmmo.begin();
  Projectile* p;
  int worldWidth = Gamedata::getInstance().getXmlInt("world/width");
  int worldHeight = Gamedata::getInstance().getXmlInt("world/width");
  while(itr != activeAmmo.end()){
    p = *itr;
    if(p->x() < 0 || p->x() > worldWidth || p->y() < 0 || p->y() > worldHeight){
      itr = activeAmmo.erase(itr);
      p->removeFromParent();
      inactiveAmmo.push_back(p);
    }else{
      ++itr;
    }
  }
}
void Weapon::aim(const cocos2d::Vec2& direction){
  
  int angle = static_cast<int>(CC_RADIANS_TO_DEGREES(direction.getAngle()));
  if(angle == 90 || angle == -90){ //moving vertical
  
  }else if(angle > 0 && angle < 90){ //moving up and right
    sprite->setFlippedX(invert);
    sprite->setRotation(-angle);
  }else if(angle > 90 && angle < 180){ //moving up and left
    sprite->setFlippedX(!invert);
    sprite->setRotation(180-angle);
  }else if(angle < 0 && angle > -90){ //moving down and right
    sprite->setFlippedX(invert);
    sprite->setRotation(-angle);
  }else if(angle < -90 && angle > -180){  //moving down and left
    sprite->setFlippedX(!invert);
    sprite->setRotation(-(180+angle));
  }else if(angle == -180 || angle == 180){
    sprite->setFlippedX(!invert);
    sprite->setRotation(0);
  }else if(angle == 0){
    sprite->setFlippedX(invert);
    sprite->setRotation(0);
  }
  
  if(!useRotate){
    sprite->setRotation(0);
  }
  if(sprite->isFlippedX()){
    setAnchorPoint(cocos2d::Vec2(.75, .5));
  }else{
    setAnchorPoint(cocos2d::Vec2(.25, .5));
  }
}

Projectile* Weapon::fire(const cocos2d::Vec2& direction, const cocos2d::Vec2& bowPosition){
  if(inactiveAmmo.empty()){
    return NULL;
  }
  aim(direction);
  runFireAnimation();
  
  Projectile*  p = inactiveAmmo.back();
  inactiveAmmo.pop_back();
  
  p->setPosition(bowPosition);
  cocos2d::Vec2 speed = direction;
  speed.normalize();
  speed.scale(p->getSpeed());
  
  p->dx(speed.x);
  p->dy(speed.y);
  
  activeAmmo.push_back(p);
  return p;
}
void Weapon::runFireAnimation(){
  int frameCount = Gamedata::getInstance().getXmlInt(getName()+"/animFrameCount");
  float frameSpeed = Gamedata::getInstance().getXmlFloat(getName()+"/frameInterval");
  cocos2d::Vector<cocos2d::SpriteFrame*> frames;
  frames.reserve(frameCount);
  std::stringstream strm;

  for(int i = 0; i < frameCount; ++i){
    strm.str("");
    strm << "frame" << i; //gets frame0...frameCount-1 in a "circular sequence"
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(
                                    Gamedata::getInstance().getXmlStr(getName()+"/"+strm.str())));
  }

  cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(frames, frameSpeed);
  sprite->runAction(cocos2d::Animate::create(animation));
}
