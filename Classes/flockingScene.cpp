#include "flockingScene.h"
#include "SimpleAudioEngine.h"
#include "customSprite.h"
#include "multiSprite.h"
#include "bidirectionalMultiSprite.h"
#include <vector>

FlockingScene::FlockingScene() : 
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
}

void FlockingScene::update(float dt) {
  std::list<Drawable*>::iterator ptr = drawables.begin();
  while(ptr != drawables.end()){
    (*ptr)->update(dt);//really no need to erase from the list, its about to get destroyed
    ++ptr;
  }
}


cocos2d::Scene* FlockingScene::createScene() {
  // 'scene' is an autorelease object
  cocos2d::Scene* scene = cocos2d::Scene::create();
    
  // 'layer' is an autorelease object
  cocos2d::Layer* layer = FlockingScene::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

// on "init" you need to initialize your instance
bool FlockingScene::init() {
  //////////////////////////////
  // 1. super init first
  if ( !Layer::init() ) {
    return false;
  }
    
  cocos2d::Size 
  visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 
  origin = cocos2d::Director::getInstance()->getVisibleOrigin();

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
    cocos2d::Label::createWithTTF("Flocking Birds", "fonts/Marker Felt.ttf", 24);

  label->setPosition(
    cocos2d::Vec2(origin.x + visibleSize.width/2,
         origin.y + visibleSize.height - label->getContentSize().height)
  );
  addChild(label, 1);


/*
  cocos2d::Sprite* moon = cocos2d::Sprite::createWithSpriteFrameName("moon.png");
  moon->setPosition(
    cocos2d::Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y)
    );
  addChild(moon, 0);*/
  
  CustomSprite* moon = new CustomSprite("moon.png", cocos2d::Vec2(200,200), cocos2d::Vec2(250, 250));
  moon->addToNode(this, 0);
  drawables.push_back(moon);
  
  std::vector<std::string> birdFrames;
  birdFrames.reserve(4);
  birdFrames.push_back("redBird1.png");
  birdFrames.push_back("redBird2.png");
  birdFrames.push_back("redBird3.png");
  birdFrames.push_back("redBird4.png");
  
  for(int i = 0; i < 100; ++i){
  MultiSprite* bird = new BidirectionalMultiSprite(birdFrames, 0.2F, cocos2d::Vec2(50,50), cocos2d::Vec2(100+i*20,100+5*i));
  bird->addToNode(this, 0);
  drawables.push_back(bird);
  }
  
 //cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("redBird1.png");
 
 
 
 
 
 
  //addChild( star->getSprite() );
  schedule( schedule_selector(FlockingScene::update));
  CocosDenshion::SimpleAudioEngine::
      getInstance()->preloadEffect("audio/thud.mp3");
    
  return true;
}


void FlockingScene::menuCloseCallback(Ref* pSender) {
  cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}
