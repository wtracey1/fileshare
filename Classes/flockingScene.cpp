#include "flockingScene.h"
#include "SimpleAudioEngine.h"
#include "customSprite.h"
#include "multiSprite.h"
#include "bidirectionalMultiSprite.h"
#include "flock.h"
#include "player.h"
#include <vector>

FlockingScene::FlockingScene() :
  gd(Gamedata::getInstance()),
  visibleSize(),
  origin(),
  drawables(),
  player(NULL)
{ }
FlockingScene::~FlockingScene() { 
  std::list<Drawable*>::iterator ptr = drawables.begin();
  while(ptr != drawables.end()){
    delete *ptr;//really no need to erase from the list, its about to get destroyed
    ++ptr;
  }
  cocos2d::SpriteFrameCache::getInstance()->removeSpriteFrames();
}

void FlockingScene::update(float dt) {
  std::list<Projectile*>& arrows = player->getProjectileList();
  std::list<Projectile*>::iterator pptr = arrows.begin();
  while(pptr != arrows.end()){
    (*pptr)->update(dt);
    ++pptr;
  }
  
  std::list<Drawable*>::iterator ptr = drawables.begin();
  while(ptr != drawables.end()){
    //Occasionally remove stars, as per the project 4 specification
    string drawableName = (*ptr)->getName();
    if(drawableName == "grayBirds" || drawableName == "grayBirds" || drawableName == "grayBirds"){
      pptr = arrows.begin();
      while(pptr != arrows.end()){
        (*ptr)->handleCollisonWith(*pptr);
        ++pptr;
      }
      (*ptr)->update(dt);
      ++ptr;
    }else{
      (*ptr)->update(dt);
      ++ptr;
    }
  }
  
  
  
  /*
  std::list<Projectile*>& arrows = player->getProjectileList();
  std::list<Projectile*>::iterator pptr = arrows.begin();
  
  while(pptr != arrows.end()){
    (*pptr)->update(dt);
    
    ++pptr;
  }
  *//////////
}


cocos2d::Layer* FlockingScene::createLayer() {
  // 'scene' is an autorelease object
  //cocos2d::Scene* scene = cocos2d::Scene::create();
    
  // 'layer' is an autorelease object
  cocos2d::Layer* layer = FlockingScene::create();

  //Add the HUD layer around here?!?

  // add layer as a child to scene
  //scene->addChild(layer);

  // return the scene
  return layer;
}

// on "init" you need to initialize your instance
bool FlockingScene::init() {
  //////////////////////////////
  // 1. super init first
  if ( !Layer::init() ) {
    return false;
  }
  cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                  Gamedata::getInstance().getXmlStr("plistName"));
  //cocos2d::Size 
  //visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 
  origin = cocos2d::Director::getInstance()->getVisibleOrigin();


  player = new Player("player");
  player->addToNode(this,1);
  drawables.push_back(player);
  player->attachCamera(this);


  cocos2d::EventListenerMouse* listener = cocos2d::EventListenerMouse::create();

  listener->onMouseMove = CC_CALLBACK_1(FlockingScene::onMouseMove, this);
  listener->onMouseUp = CC_CALLBACK_1(FlockingScene::onMouseUp, this);
  listener->onMouseDown = CC_CALLBACK_1(FlockingScene::onMouseDown, this);
  listener->onMouseScroll = CC_CALLBACK_1(FlockingScene::onMouseScroll, this);
  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(listener, this);


  CustomSprite* sky = new CustomSprite("sky");
  sky->setScale(2);
  sky->addToNode(this, 0);
  sky->setAnchorPoint(cocos2d::Vec2(0,0));
  drawables.push_back(sky);
  CustomSprite* city = new CustomSprite("skyline");
  city->setScale(2);
  city->setAnchorPoint(cocos2d::Vec2(0,0));
  city->addToNode(this, 0);
  drawables.push_back(city);
  
  
  MultiSprite* star;
  for(int i = 0; i < 20; ++i){
    star = new MultiSprite("star");
    star->x(gd.getRandInRange(0,gd.getXmlInt("world/width")));
    star->y(gd.getRandInRange(.3*gd.getXmlInt("world/height"),gd.getXmlInt("world/height")));
    star->addToNode(this, 0);
    drawables.push_back(star);
  }
  
 
  CustomSprite* moon = new CustomSprite("moon");
  moon->x(gd.getRandInRange(0,Gamedata::getInstance().getXmlInt("world/width")));
  moon->addToNode(this, 1);
  drawables.push_back(moon);
  
  
  Flock* grayflock = new Flock("grayBirds", BidirectionalMultiSprite("grayBird"));
  grayflock->addToNode(this, 1);
  drawables.push_back(grayflock);
  
  Flock* redflock = new Flock("redBirds", BidirectionalMultiSprite("redBird"));
  redflock->addToNode(this, 1);
  drawables.push_back(redflock);
  
  Flock* blueflock = new Flock("blueBirds", BidirectionalMultiSprite("blueBird"));
  blueflock->addToNode(this, 1);
  drawables.push_back(blueflock);


  schedule( schedule_selector(FlockingScene::update));
  //CocosDenshion::SimpleAudioEngine::
  //    getInstance()->preloadEffect("audio/thud.mp3");
    
  return true;
}
void FlockingScene::onMouseDown(cocos2d::Event* event){
  cocos2d::EventMouse* e = static_cast<cocos2d::EventMouse*>(event);
  Projectile* newProjectile = player->fire(cocos2d::Vec2(e->getCursorX(),e->getCursorY()));
  if(newProjectile){
    addChild(newProjectile->getSprite(), 1);
  }
}
void FlockingScene::onMouseUp(cocos2d::Event* event){}
void FlockingScene::onMouseMove(cocos2d::Event* event){
  cocos2d::EventMouse* e = static_cast<cocos2d::EventMouse*>(event);
  player->aim(cocos2d::Vec2(e->getCursorX(),e->getCursorY()));
}
void FlockingScene::onMouseScroll(cocos2d::Event* event){}


void FlockingScene::menuCloseCallback(Ref* pSender) {
  cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}
