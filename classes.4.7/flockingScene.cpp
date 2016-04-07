#include "flockingScene.h"
#include "SimpleAudioEngine.h"
#include "customSprite.h"
#include "multiSprite.h"
#include "bidirectionalMultiSprite.h"
#include "flock.h"
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
    cocos2d::Label::createWithTTF(Gamedata::getInstance().getXmlStr("screenTitle"), "fonts/Marker Felt.ttf", 24);

  label->setPosition(
    cocos2d::Vec2(origin.x + visibleSize.width/2,
         origin.y + visibleSize.height - label->getContentSize().height)
  );
  addChild(label, 1);

  try{
    CustomSprite* sky = new CustomSprite("sky");
    sky->addToNode(this, 0);
    sky->setAnchorPoint(cocos2d::Vec2(0,0));
    drawables.push_back(sky);
    CustomSprite* city = new CustomSprite("skyline");
    city->setAnchorPoint(cocos2d::Vec2(0,0));
    city->addToNode(this, 0);
    drawables.push_back(city);
    CustomSprite* moon = new CustomSprite("moon");
    moon->addToNode(this, 0);
    drawables.push_back(moon);
    
    
    MultiSprite* bird = new BidirectionalMultiSprite("grayBird");
    bird->addToNode(this, 0);
    drawables.push_back(bird); 

    Flock* flock = new Flock("redBirds", BidirectionalMultiSprite("redBird"));
    flock->addToNode(this, 0);
    drawables.push_back(flock);
    
    
    
    
    
    
  }catch(std::string ex){
    removeChild(label);
    cocos2d::Label* 
    e = 
      cocos2d::Label::createWithTTF(ex, "fonts/Marker Felt.ttf", 24);

    e->setPosition(
      cocos2d::Vec2(origin.x + visibleSize.width/2,
           origin.y + visibleSize.height - e->getContentSize().height)
    );
    addChild(e, 1);
  }

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
