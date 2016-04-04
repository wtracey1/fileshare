#ifndef AGENTSPRITE__H
#define AGENTSPRITE__H
#include <string>
#include <vector>
#include "sprite.h"
#include "multisprite.h"
#include <list>

class AgentSprite : public Drawable {
public:
  AgentSprite(const AgentSprite&);
  AgentSprite(const Sprite&, const Vector2f);
  virtual ~AgentSprite();
  virtual AgentSprite* clone() const { return new AgentSprite(*this);}
  virtual const Frame* getFrame() const { return baseSprite->getFrame(); }
  void draw() const;
  void update( const std::list<AgentSprite*>& flock, float, float, float, Uint32 ticks);
  void update(Uint32 ticks);
  
private:
  Sprite* baseSprite;
  const Vector2f maxSpeed;
  int los;
  AgentSprite& operator=(const AgentSprite&);
  Vector2f computeAlignment(const std::list<AgentSprite*>& flock);
  Vector2f computeCohesion(const std::list<AgentSprite*>& flock);
  Vector2f computeSeperation(const std::list<AgentSprite*>& flock);
  void syncToBase();
  void syncFromBase();
};
#endif
