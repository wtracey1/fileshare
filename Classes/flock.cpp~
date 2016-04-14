#include "flock.h"
#include "gamedata.h"
#include <iostream>
#include <list>
#include <ctime>

Flock::~Flock()
{
  std::list<AgentSprite*>::const_iterator ptr = flock.begin();
  while (ptr != flock.end()){
    delete *ptr;
    ++ptr;
  }
}

Flock::Flock( const std::string& name, const CustomSprite& agentTemplate) :
  Drawable(name),
  flock(),
  alignmentFactor(Gamedata::getInstance().getXmlInt(name+"/alignment")),
  cohesionFactor(Gamedata::getInstance().getXmlInt(name+"/cohesion")),
  seperationFactor(Gamedata::getInstance().getXmlInt(name+"/seperation"))
{ 
  
  cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  int count = Gamedata::getInstance().getXmlInt(name+"/count");
  int width = visibleSize.width;
  int height = visibleSize.height;
  int x,y;
  //Randomly place agentSprites on map
  AgentSprite* newSprite = NULL;
  for(int i = 0; i < count; ++i){
    newSprite = new AgentSprite(agentTemplate);
    x = Gamedata::getInstance().getRandInRange(0,
                                  width - static_cast<int>(agentTemplate.getSpriteSize().width));
    y = Gamedata::getInstance().getRandInRange(0,
                                  height - static_cast<int>(agentTemplate.getSpriteSize().height));
    newSprite->setPosition(cocos2d::Vec2(x,y));
    flock.push_back(newSprite);
  }


}
Flock::Flock(const Flock& s) :
  Drawable(s),
  flock(s.flock),
  alignmentFactor(s.alignmentFactor),
  cohesionFactor(s.cohesionFactor),
  seperationFactor(s.seperationFactor)
{ }


void Flock::handleCollisonWith(const Drawable* other){
  std::list<AgentSprite*>::iterator ptr = flock.begin();
  while (ptr != flock.end()){
    if((*ptr)->collidedWith(other)){
      (*ptr)->removeFromParent();
      delete *ptr;
      ptr = flock.erase(ptr);
    }else{
      ++ptr;
    }
  }
}

void Flock::addToNode(cocos2d::Node* node, int z){
  std::list<AgentSprite*>::iterator i = flock.begin();
  while(i != flock.end()){
    (*i)->addToNode(node, z);
    ++i;
  }
}
void Flock::removeFromNode(cocos2d::Node* node){
  std::list<AgentSprite*>::iterator i = flock.begin();
  while(i != flock.end()){
    (*i)->removeFromNode(node);
    ++i;
  }
}
void Flock::attach(AgentSprite *a) { 
  flock.push_back(a);   
}
void Flock::detach(AgentSprite *a){
  std::list<AgentSprite*>::iterator ptr = flock.begin();
  while (ptr != flock.end()){
    if(*ptr == a){
      (*ptr)->removeFromParent();
      delete *ptr;
      ptr = flock.erase(ptr);
      return;
    }
    ++ptr;
  }
}

void Flock::update(float dt) {
  std::list<AgentSprite*>::iterator ptr = flock.begin();
  while (ptr != flock.end()){
    (*ptr)->update(flock, alignmentFactor/10, cohesionFactor/10, seperationFactor/10, dt);
    ++ptr;
  }
}
