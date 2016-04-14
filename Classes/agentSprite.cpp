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
  speed(cocos2d::Vec2(Gamedata::getInstance().getXmlInt(s.getName()+"/speed/x"), 
                      Gamedata::getInstance().getXmlInt(s.getName()+"/speed/y")).getLength()),
  los(Gamedata::getInstance().getXmlInt(s.getName()+"/LoS"))
{
}
AgentSprite::AgentSprite(const AgentSprite& s) :
  Drawable(s),
  baseSprite(s.baseSprite->clone()),
  speed(cocos2d::Vec2(Gamedata::getInstance().getXmlInt(s.getName()+"/speed/x"), 
                      Gamedata::getInstance().getXmlInt(s.getName()+"/speed/y")).getLength()),
  los(Gamedata::getInstance().getXmlInt(s.getName()+"/LoS"))
{ }

/*
  Cycle through flock computing cohesion, alignment, seperation and updating
*/
void AgentSprite::update( const std::list<AgentSprite*>& flock, float alignmentFactor, float cohesionFactor, float seperationFactor, float ticks){

  
  //Could optimize and compute all in one loop through the flock rather than loops for each of alignment, cohesion, and seperation..
  cocos2d::Vec2 alignment = computeAlignment(flock);
  cocos2d::Vec2 cohesion = computeCohesion(flock);
  cocos2d::Vec2 seperation = computeSeperation(flock);
/*
  cocos2d::Vec2 newVelocity = (alignmentFactor*alignment + cohesionFactor*cohesion + seperationFactor*seperation);
  newVelocity.scale(speed);
  newVelocity = newVelocity + getVelocity();

  newVelocity.normalize();
  newVelocity.scale(speed);
  */
  //////
  cocos2d::Vec2 wallAvoidance = computeWallAvoidance();
  
  cocos2d::Vec2 newVelocity = (alignmentFactor*alignment + cohesionFactor*cohesion + seperationFactor*seperation);
  newVelocity.scale(speed);
  newVelocity = newVelocity + getVelocity();
  newVelocity.normalize();
  //newVelocity.scale(speed);
  
  setVelocity(newVelocity);
  
  newVelocity.add(wallAvoidance);
  newVelocity.normalize();
  newVelocity.scale(speed);
  
  //////
  
  
  setVelocity(newVelocity);
  
  
  
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
  Compute seperation aspect of velocity, returns a normalized vector that includes the vectors in the opposite direction of all neighboring agents, weighted by closeness to the agent
*/
cocos2d::Vec2 AgentSprite::computeWallAvoidance(){
  //cocos2d::Size worldSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Size worldSize = cocos2d::Size( Gamedata::getInstance().getXmlInt("world/width"), 
                                          Gamedata::getInstance().getXmlInt("world/height"));
  cocos2d::Vec2 force(0,0);
  cocos2d::Vec2 position = baseSprite->getPosition();
  int width = baseSprite->getSpriteSize().width;
  int height = baseSprite->getSpriteSize().height;
  int distanceToWall;
  float forceStrength;
  
  int wallSight = los*Gamedata::getInstance().getXmlInt("wallScaryness");
  
  if ( position.x > worldSize.width - width/2 - wallSight ) { //within sight of right wall
    distanceToWall = worldSize.width - width/2 - position.x;
    forceStrength = 2.0/(distanceToWall+.1);
    force.x = force.x - forceStrength;
    if(force.y > 0){
      force.y = force.y + forceStrength;
    }else{
      force.y = force.y - forceStrength;
    }
  }
  if ( position.x < width/2 + wallSight) { //within sight of left wall
    distanceToWall = position.x - width/2;
    forceStrength = 2.0/(distanceToWall+.1);
    force.x = force.x + forceStrength;
    if(force.y > 0){
      force.y = force.y + forceStrength;
    }else{
      force.y = force.y - forceStrength;
    }
  }
  if ( position.y > worldSize.height - height/2 - wallSight ) {  //within sight of top wall
    distanceToWall = worldSize.height - position.y - height/2;
    forceStrength = 2.0/(distanceToWall+.1);
    force.y = force.y - forceStrength;
    if(force.x > 0){
      force.x = force.x + forceStrength;
    }else{
      force.x = force.x - forceStrength;
    }
  }
  if ( position.y < height/2 + wallSight) {  //within sight of bottom wall
    distanceToWall = position.y - height/2;
    forceStrength = 2.0/(distanceToWall+.1);
    force.y = force.y + forceStrength;
    if(force.x > 0){
      force.x = force.x + forceStrength;
    }else{
      force.x = force.x - forceStrength;
    }
  }
  return force;
}
/*
  Update the base sprite (allows for use with any class is Sprite inheritance tree
*/
void AgentSprite::update(float dt) {
  baseSprite->update(dt);
}
