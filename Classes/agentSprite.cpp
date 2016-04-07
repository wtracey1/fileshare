#include "flock.h"
#include "agentSprite.h"
#include "gamedata.h"
#include <iostream>
#include <cmath>

AgentSprite::~AgentSprite(){
  delete baseSprite;
}

AgentSprite::AgentSprite(const CustomSprite& s) :
  Drawable("flocking " + s.getName()),
  baseSprite(s.clone()),
  speed(Gamedata::getInstance().getXmlInt(s.getName()+"/speed/x"), 
              Gamedata::getInstance().getXmlInt(s.getName()+"/speed/y")),
  los(Gamedata::getInstance().getXmlInt(s.getName()+"/LoS"))
{ 
}
AgentSprite::AgentSprite(const AgentSprite& s) :
  Drawable(s),
  baseSprite(s.baseSprite->clone()),
  speed(Gamedata::getInstance().getXmlInt(s.getName()+"/speed"), 
            Gamedata::getInstance().getXmlInt(s.getName()+"/speed")),
  los(Gamedata::getInstance().getXmlInt(s.getName()+"/LoS"))
{ }
//Utility functions to syncronize the position and velocity updating that occurs in the baseSprite and in the agentSprite wrapping it

void AgentSprite::syncToBase(){
  baseSprite->setVelocity(getVelocity());
  baseSprite->setPosition(getPosition());
}
void AgentSprite::syncFromBase(){
  setVelocity(baseSprite->getVelocity());
  setPosition(baseSprite->getPosition());
}

/*
  Cycle through flock computing cohesion, alignment, seperation and updating
*/
void AgentSprite::update( const std::list<AgentSprite*>& flock, float alignmentFactor, float cohesionFactor, float seperationFactor, float ticks){
  //syncFromBase();
  
  //Could optimize and compute all in one loop through the flock rather than loops for each of alignment, cohesion, and seperation..
  cocos2d::Vec2 alignment = computeAlignment(flock);
  cocos2d::Vec2 cohesion = computeCohesion(flock);
  cocos2d::Vec2 seperation = computeSeperation(flock);
  /*std::cout << "Alignment:" << "(" << alignment.x << ", " << alignment.y << ")" << std::endl;
  std::cout << "Cohesion:" << "(" << cohesion.x << ", " << cohesion.y << ")" << std::endl;
  std::cout << "Seperation:" << "(" << seperation.x << ", " << seperation.y << ")" << std::endl;
  std::cout << "CurrentVelocity:" << "(" << getVelocity().x << ", " << getVelocity().y << ")" << std::endl;*/
  cocos2d::Vec2 newVelocity = (alignmentFactor*alignment + cohesionFactor*cohesion + seperationFactor*seperation);
  newVelocity.scale(speed);
  newVelocity = newVelocity + getVelocity();
  //std::cout << "NewVelocity:" << "(" << newVelocity.x << ", " << newVelocity.y << ")" << std::endl;
  //newVelocity.scale(speed);
  
  //setVelocity(getVelocity() + (alignmentFactor*alignment + cohesionFactor*cohesion + seperationFactor*seperation).scale(speed));
  newVelocity.normalize();
  newVelocity.scale(speed);
  setVelocity(newVelocity);
  //setVelocity(getVelocity().normalize().scale(speed));
  
  //syncToBase();
  update(ticks);
}
/*
  Compute alignment aspect of velocity, returns a normalized vector that includes the velocity of all neighboring agents
*/
cocos2d::Vec2 AgentSprite::computeAlignment(const std::list<AgentSprite*>& flock){
  cocos2d::Vec2 target;
  int neighbors = 0;
  std::list<AgentSprite*>::const_iterator ptr = flock.begin();
  while (ptr != flock.end()){
    if((*ptr) != this && this->getDistance((*ptr)->getPosition()) < los){//agent is not this agent and is in the line of sight
      neighbors++;
      target += ((*ptr)->getVelocity());
    }
    ++ptr;
  }
  if(neighbors == 0) return target;
  
  target = target / (neighbors);
  target.normalize();
  return target;
}
/*
  Compute cohesion aspect of velocity, returns a normalized vector that includes the vectors in the direction of all neighboring agents
*/
cocos2d::Vec2 AgentSprite::computeCohesion(const std::list<AgentSprite*>& flock){
  cocos2d::Vec2 target;
  int neighbors = 0;
  std::list<AgentSprite*>::const_iterator ptr = flock.begin();
  while (ptr != flock.end()){
    if((*ptr) != this && this->getDistance((*ptr)->getPosition()) < los){
      neighbors++;
      target += (*ptr)->getPosition();
    }
    ++ptr;
  }
  
  if(neighbors == 0) return target;
  
  target = target / neighbors;
  target = target - getPosition();
  target.normalize();
  return target;
}
/*
  Compute seperation aspect of velocity, returns a normalized vector that includes the vectors in the opposite direction of all neighboring agents, weighted by closeness to the agent
*/
cocos2d::Vec2 AgentSprite::computeSeperation(const std::list<AgentSprite*>& flock){
  cocos2d::Vec2 target;
  int neighbors = 0;
  std::list<AgentSprite*>::const_iterator ptr = flock.begin();
  while (ptr != flock.end()){
    if((*ptr) != this && this->getDistance((*ptr)->getPosition()) < los){
      neighbors++;
      target += (*ptr)->getPosition() - getPosition();
    }
    ++ptr;
  }
  
  if(neighbors == 0) return target;
  
  target = target / neighbors;
  target *= -1;
  target.normalize();
  return target;
}
/*
  Update the base sprite (allows for use with any class is Sprite inheritance tree
*/
void AgentSprite::update(float dt) {
  baseSprite->update(dt);
}
