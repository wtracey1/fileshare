#include "flockingScene.h"
#include "SimpleAudioEngine.h"
#include "customSprite.h"
#include "multiSprite.h"
#include "bidirectionalMultiSprite.h"
#include "flock.h"
#include <vector>

FlockingScene::FlockingScene() :
  gd(Gamedata::getInstance()),
  visibleSize(),
  origin(),
  drawables()
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
  //setPositionX(getPositionX()+dt);
  std::list<Drawable*>::iterator ptr = drawables.begin();
  int starsToReplace = 0;
  Drawable* windmill = *ptr;
  
  while(ptr != drawables.end()){
    //Occasionally remove stars, as per the project 4 specification
    if((*ptr)->getName() == "star" && gd.getRandInRange(0,1000) < Gamedata::getInstance().getXmlInt("twinkleLevel")){
      ++starsToReplace;
      (*ptr)->removeFromNode(this);
      delete *ptr;
      ptr = drawables.erase(ptr);
      //Kill the gray birds!
    }else if((*ptr)->getName() == "grayBirds"){
      (*ptr)->update(dt);
      (*ptr)->handleCollisonWith(windmill);
      ++ptr;
    }else{
      (*ptr)->update(dt);
      ++ptr;
    }
  }
  
  MultiSprite* star;
  //Replace stars, to further compliance with the project 4 specification
  for(int i = 0; i < starsToReplace; ++i){
      star = new MultiSprite("star");
      star->x(gd.getRandInRange(0,Gamedata::getInstance().getXmlInt("view/width")));
      star->y(gd.getRandInRange(275,Gamedata::getInstance().getXmlInt("view/height")));
      star->addToNode(this, 0);
      drawables.push_back(star);
  }
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
  cocos2d::Size 
  visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 
  origin = cocos2d::Director::getInstance()->getVisibleOrigin();
/*
  /////////////////////////////
  // 2. add a menu item with "X" image, which is clicked to quit the program
  //    you may modify it.

  // add a "close" icon to exit the progress. it's an autorelease object
  cocos2d::MenuItemImage* closeItem = cocos2d::MenuItemImage::create(
                      "CloseNormal.png",
                      "CloseSelected.png",
                      CC_CALLBACK_1(FlockingScene::menuCloseCallback, this));
    
	closeItem->setPosition(
    cocos2d::Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
         origin.y + closeItem->getContentSize().height/2)
  );

  // create menu, it's an autorelease object
  cocos2d::Menu* menu = cocos2d::Menu::create(closeItem, NULL);
  menu->setPosition(cocos2d::Vec2::ZERO);
  this->addChild(menu, 1);

  /////////////////////////////
  // 3. add your codes below...

  cocos2d::Label* 
  label = 
    cocos2d::Label::createWithTTF(gd.getXmlStr("screenTitle"), "fonts/Marker Felt.ttf", 24);

  label->setPosition(
    cocos2d::Vec2(origin.x + visibleSize.width/2,
         origin.y + visibleSize.height - label->getContentSize().height)
  );
  addChild(label, 1);
*/
  //This one is our special one!!
  CustomSprite* windmill = new CustomSprite("windmill");
  windmill->addToNode(this,1);
  cocos2d::RepeatForever* rotateAction = 
    cocos2d::RepeatForever::create(cocos2d::RotateBy::create(1, 360));
  windmill->runAction(rotateAction);
  drawables.push_back(windmill);
  
  
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
    star->x(gd.getRandInRange(0,Gamedata::getInstance().getXmlInt("view/width")));
    star->y(gd.getRandInRange(275,Gamedata::getInstance().getXmlInt("view/height")));
    star->addToNode(this, 0);
    drawables.push_back(star);
  }
  
 
  CustomSprite* moon = new CustomSprite("moon");
  moon->x(gd.getRandInRange(0,gd.getRandInRange(0,Gamedata::getInstance().getXmlInt("view/width"))));
  moon->addToNode(this, 1);
  drawables.push_back(moon);
  
  CustomSprite* pole = new CustomSprite("pole");
  pole->addToNode(this,0);
  drawables.push_back(pole);
  
  BidirectionalMultiSprite* cameraGuy = new BidirectionalMultiSprite("grayBird");
  cameraGuy->addToNode(this,1);
  drawables.push_back(cameraGuy);
  cameraGuy->attachCamera(this);
  //this->runAction(Follow::create(testSprite, Rect( center.x - playfield_width/2, center.y - playfield_height/2 , playfield_width, playfield_height)));
 
 
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


void FlockingScene::menuCloseCallback(Ref* pSender) {
  cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}