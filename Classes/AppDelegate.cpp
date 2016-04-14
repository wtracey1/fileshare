#include "AppDelegate.h"
#include "flockingScene.h"
#include "hud.h"

static cocos2d::Size mediumResolutionSize = cocos2d::Size(
                                              Gamedata::getInstance().getXmlInt("view/width"), 
                                              Gamedata::getInstance().getXmlInt("view/height"));

AppDelegate::AppDelegate() { }

AppDelegate::~AppDelegate() { }

void AppDelegate::initGLContextAttrs() {
  //set OpenGL context attributions, now can only set six attributions:
  //red,green,blue,alpha,depth,stencil
  GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

  cocos2d::GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages() {
  return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  cocos2d::Director* director = cocos2d::Director::getInstance();
  cocos2d::GLView *  glview = director->getOpenGLView();
  if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    glview = cocos2d::GLViewImpl::createWithRect(
                                    Gamedata::getInstance().getXmlStr("view/name"), 
                                    cocos2d::Rect(0, 0, mediumResolutionSize.width, 
                                    mediumResolutionSize.height));
#else
    glview = GLViewImpl::create(Gamedata::getInstance().getXmlStr("view/name"));
#endif
    director->setOpenGLView(glview);
  }

  // turn on display FPS
  director->setDisplayStats(false);

  // set FPS. the default value is 1.0/60 if you don't call this
  director->setAnimationInterval(1.0 / Gamedata::getInstance().getXmlInt("frameCap"));

  register_all_packages();

  /////

  //cocos2d::Scene* scene = FlockingScene::createScene();
  cocos2d::Scene* scene = cocos2d::Scene::create();
  cocos2d::Layer* gameLayer = FlockingScene::createLayer();
  scene->addChild(gameLayer);
  
  //Add the HUD interface
  cocos2d::Layer* hudLayer = HUD::createLayer();
  scene->addChild(hudLayer);
  
  // run
  director->runWithScene(scene);

  return true;
}

// This function will be called when the app is inactive. 
// When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  cocos2d::Director::getInstance()->stopAnimation();

  // if you use SimpleAudioEngine, it must be pause
  // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  cocos2d::Director::getInstance()->startAnimation();

  // if you use SimpleAudioEngine, it must resume here
  // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
