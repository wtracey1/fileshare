#ifndef FLOCKINGSPRITE__H
#define FLOCKINGSPRITE__H
#include <string>
#include <list>
#include "cocos2d.h"
#include "drawable.h"
#include "customSprite.h"
#include "agentSprite.h"

class Flock : public Drawable {
public:
  Flock( const std::string& name, const CustomSprite& agentTemplate);
  
  virtual ~Flock();
  void update(float);
  virtual ~CustomSprite();
  virtual void addToNode(cocos2d::Node*, int z = 0);
  virtual void removeFromNode(cocos2d::Node*);  
  virtual void x(float x){}
  virtual void y(float y){}
  virtual float x(){return flock[0]->x();}
  virtual float y(){return flock[0]->y();}
  virtual void dx(float dx){}
  virtual void dy(float dy){}
  virtual float dx(){return flock[0]->dx();}
  virtual float dy(){return flock[0]->dy();}
  virtual void setPosition(cocos2d::Vec2 pos){}
  virtual void setVelocity(cocos2d::Vec2 vel){}
  virtual cocos2d::Vec2 getPosition(){return flock[0]->getPosition();}
  virtual cocos2d::Vec2 getVelocity(){return flock[0]->getVelocity();}
  
  virtual Flock* clone() const {
    //return new FlockingSprite(*this);
    throw std::string("Don't try to clone a flock!");
  }
  
  void attach(AgentSprite *a) { 
    flock.push_back(a);   
  }
  void detach(AgentSprite *a);
private:
  Flock(const Flock&);
  std::list<AgentSprite*> flock;
  float alignmentFactor;
  float cohesionFactor;
  float seperationFactor;
};
#endif
