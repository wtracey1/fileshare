#ifndef AGENTSPRITE__H
#define AGENTSPRITE__H
#include <string>
#include <vector>
#include "cocos2d.h"
#include "sprite.h"
#include <list>

class AgentSprite : public Drawable {
public:
  AgentSprite(const AgentSprite&);
  AgentSprite(const CustomSprite&, const cocos2d::Vec2);
  virtual ~AgentSprite();
  virtual AgentSprite* clone() const { return new AgentSprite(*this);}
  void update( const std::list<AgentSprite*>&, float, float, float, float);
  void update(float);
  
private:
  CustomSprite* baseSprite;
  const int speed;
  int los;
  AgentSprite& operator=(const AgentSprite&);
  cocos2d::Vec2 computeAlignment(const std::list<AgentSprite*>& flock);
  cocos2d::Vec2 computeCohesion(const std::list<AgentSprite*>& flock);
  cocos2d::Vec2 computeSeperation(const std::list<AgentSprite*>& flock);
  void syncToBase();
  void syncFromBase();
};
#endif
