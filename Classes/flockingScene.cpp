#include "flockingScene.h"
#include "SimpleAudioEngine.h"

FlockingScene::FlockingScene() : 
  visibleSize(),
  origin()
{ }

void FlockingScene::update(float dt) {
  //star->update(dt);
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
    
  // position the background on the center of the screen
  label->setPosition(
    cocos2d::Vec2(origin.x + visibleSize.width/2,
         origin.y + visibleSize.height - label->getContentSize().height)
  );

  // add the label as a child to this layer
  addChild(label, 1);

  // add "BouncingStars" splash screen"
  //cocos2d::Sprite* sprite = cocos2d::Sprite::create("checkerboard.png");
  cocos2d::Sprite* sprite = cocos2d::Sprite::createWithSpriteFrameName("moon.png");
  // position the sprite on the center of the screen
  sprite->setPosition(
    cocos2d::Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y)
    );

  // add the sprite as a child to this layer
  addChild(sprite, 0);

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
