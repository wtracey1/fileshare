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
  
  ~Flock();
  void update(float);
  virtual void addToNode(cocos2d::Node* node, int z = 0){
    std::list<AgentSprite*>::iterator i = flock.begin();
    while(i != flock.end()){
      (*i)->addToNode(node, z);
      ++i;
    }
  }
  virtual void removeFromNode(cocos2d::Node* node){
    std::list<AgentSprite*>::iterator i = flock.begin();
    while(i != flock.end()){
      (*i)->removeFromNode(node);
      ++i;
    }
  }
  virtual void x(float x){}
  virtual void y(float y){}
  virtual float x() const {return flock.front()->x();}
  virtual float y() const {return flock.front()->y();}
  virtual void dx(float dx){}
  virtual void dy(float dy){}
  virtual float dx() const {return flock.front()->dx();}
  virtual float dy() const {return flock.front()->dy();}
  virtual void setPosition(cocos2d::Vec2 pos){}
  virtual void setVelocity(cocos2d::Vec2 vel){}
  virtual cocos2d::Vec2 getPosition() const {return flock.front()->getPosition();}
  virtual cocos2d::Vec2 getVelocity() const {return flock.front()->getVelocity();}
  
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
