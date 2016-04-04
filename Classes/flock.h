#ifndef FLOCKINGSPRITE__H
#define FLOCKINGSPRITE__H
#include <string>
#include <list>
#include "sprite.h"
#include "multisprite.h"
#include "agentSprite.h"

class Flock : public Drawable {
public:
  Flock( const std::string& name, const Sprite& agentTemplate);
  
  virtual ~Flock();

  void draw() const;
  void update(Uint32 ticks);
  virtual const Frame* getFrame() const {
    if(flock.empty()) throw std::string("The flock is empty!!");
    return flock.front()->getFrame();
  }
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
