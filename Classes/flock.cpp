#include "flockingSprite.h"
#include "gamedata.h"
#include "frameFactory.h"
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
  flock(),
  alignmentFactor(Gamedata::getInstance().getXmlInt(name+"/alignment")),
  cohesionFactor(Gamedata::getInstance().getXmlInt(name+"/cohesion")),
  seperationFactor(Gamedata::getInstance().getXmlInt(name+"/seperation"))
{ 
  int count = Gamedata::getInstance().getXmlInt(name+"/count");
  int width = Gamedata::getInstance().getXmlInt("world/width");
  int height = Gamedata::getInstance().getXmlInt("world/height");
  int x,y;
  //Randomly place agentSprites on map
  for(int i = 0; i < count; ++i){
    x = rand() % (width - agentTemplate.getFrame()->getWidth());
    y = rand() % (height - agentTemplate.getFrame()->getHeight());
    flock.push_back(new AgentSprite(agentTemplate, cocos2d::Vec2(x,y)));
  }


}
FlockingSprite::FlockingSprite(const FlockingSprite& s) :
  flock(s.flock),
  alignmentFactor(s.alignmentFactor),
  cohesionFactor(s.cohesionFactor),
  seperationFactor(s.seperationFactor)
{ }

void FlockingSprite::detach(AgentSprite *a){
  std::list<AgentSprite*>::iterator ptr = flock.begin();
  while (ptr != flock.end()){
    if(*ptr == a){
      delete *ptr;
      ptr = flock.erase(ptr);
      return;
    }
    ++ptr;
  }
}

void FlockingSprite::update(float dt) {
  std::list<AgentSprite*>::iterator ptr = flock.begin();
  while (ptr != flock.end()){
    (*ptr)->update(flock, alignmentFactor/10, cohesionFactor/10, seperationFactor/10, dt);
    ++ptr;
  }
}
