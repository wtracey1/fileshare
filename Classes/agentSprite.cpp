#include "flockingSprite.h"
#include "agentSprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "vector2f.h"
#include <iostream>
#include <cmath>

AgentSprite::~AgentSprite(){
  delete baseSprite;
}

AgentSprite::AgentSprite(const Sprite& s, const Vector2f initPosition) : 
  Drawable(s),
  baseSprite(s.clone()),
  maxSpeed(Gamedata::getInstance().getXmlInt(s.getName()+"/maxSpeedX"), 
              Gamedata::getInstance().getXmlInt(s.getName()+"/maxSpeedY")),
  los(Gamedata::getInstance().getXmlInt(s.getName()+"/LoS"))
{ 
  baseSprite->setPosition(initPosition);
}
AgentSprite::AgentSprite(const AgentSprite& s) : 
  Drawable(s),
  baseSprite(s.baseSprite->clone()),
  maxSpeed(Gamedata::getInstance().getXmlInt(s.getName()+"/maxSpeedX"), 
            Gamedata::getInstance().getXmlInt(s.getName()+"/maxSpeedY")),
  los(Gamedata::getInstance().getXmlInt(s.getName()+"/LoS"))
{ }

void AgentSprite::draw() const {
  baseSprite->draw();
}

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
void AgentSprite::update( const std::list<AgentSprite*>& flock, float alignmentFactor, float cohesionFactor, float seperationFactor, Uint32 ticks){
  syncFromBase();

  //Could optimize and compute all in one loop through the flock rather than loops for each of alignment, cohesion, and seperation..
  Vector2f alignment = computeAlignment(flock);
  Vector2f cohesion = computeCohesion(flock);
  Vector2f seperation = computeSeperation(flock);

  setVelocity(getVelocity() + (alignmentFactor*alignment + cohesionFactor*cohesion + seperationFactor*seperation).cross(maxSpeed));
  setVelocity(getVelocity().normalize().cross(maxSpeed));

  syncToBase();
  update(ticks);
}
/*
  Compute alignment aspect of velocity, returns a normalized vector that includes the velocity of all neighboring agents
*/
Vector2f AgentSprite::computeAlignment(const std::list<AgentSprite*>& flock){
  Vector2f target;
  int neighbors = 0;
  std::list<AgentSprite*>::const_iterator ptr = flock.begin();
  while (ptr != flock.end()){
    if((*ptr) != this && this->getDistance(*ptr) < los){//arbitrary atm
      neighbors++;
      target += ((*ptr)->getVelocity());
    }
    ++ptr;
  }
  if(neighbors == 0) return target;
  
  target /= (neighbors);
  return target.normalize();
}
/*
  Compute cohesion aspect of velocity, returns a normalized vector that includes the vectors in the direction of all neighboring agents
*/
Vector2f AgentSprite::computeCohesion(const std::list<AgentSprite*>& flock){
  Vector2f target;
  int neighbors = 0;
  std::list<AgentSprite*>::const_iterator ptr = flock.begin();
  while (ptr != flock.end()){
    if((*ptr) != this && this->getDistance(*ptr) < los){//arbitrary atm
      neighbors++;
      target += (*ptr)->getPosition();
    }
    ++ptr;
  }
  
  if(neighbors == 0) return target;
  
  target /= neighbors;
  target = target - getPosition();
  
  return target.normalize();
}
/*
  Compute seperation aspect of velocity, returns a normalized vector that includes the vectors in the opposite direction of all neighboring agents, weighted by closeness to the agent
*/
Vector2f AgentSprite::computeSeperation(const std::list<AgentSprite*>& flock){
  Vector2f target;
  int neighbors = 0;
  std::list<AgentSprite*>::const_iterator ptr = flock.begin();
  while (ptr != flock.end()){
    if((*ptr) != this && this->getDistance(*ptr) < los){//arbitrary atm
      neighbors++;
      target += (*ptr)->getPosition() - getPosition();
    }
    ++ptr;
  }
  
  if(neighbors == 0) return target;
  
  target /= neighbors;
  target *= -1;
  
  return target.normalize();
}
/*
  Update the base sprite (allows for use with any class is Sprite inheritance tree
*/
void AgentSprite::update(Uint32 ticks) {
  baseSprite->update(ticks);
}