#include <iostream>
#include <cmath>
#include "star.h"
#include "SimpleAudioEngine.h"

float getVelocity() {
  float x = rand() % 5 + 1;
  x = (rand()%2?-1:1)*x;
  return x;
}

Star::Star() : 
  velocity(200, 200),
  playSound(true),
  viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
  origin( cocos2d::Director::getInstance()->getVisibleOrigin() ),
  sprite( cocos2d::Sprite::create("yellowstar.png") ),
  starWidth( sprite->getContentSize().width )
{
  float newX = viewSize.width/2 + origin.x;
  float newY = viewSize.height/2 + origin.y;
  sprite->setPosition( cocos2d::Point(newX, newY) ); 
  //addChild( sprite );

  // Rotate the star a quarter turn every second
  cocos2d::RepeatForever* rotateAction = 
    cocos2d::RepeatForever::create(cocos2d::RotateBy::create(1, 90));
  sprite->runAction(rotateAction);

  CocosDenshion::SimpleAudioEngine::
    getInstance()->preloadEffect("audio/thud.mp3");
}


void Star::update(float dt) {
  auto position = sprite->getPosition();
  cocos2d::Vec2 incr = velocity * dt;
  sprite->setPosition(position.x + incr.x, position.y + incr.y );

  cocos2d::Point location = sprite->getPosition();
  if ( location.x > viewSize.width - starWidth/2 ) {
    velocity.x = -abs(velocity.x);
    if ( playSound ) {
      CocosDenshion::SimpleAudioEngine::
        getInstance()->playEffect("audio/thud.mp3");
      playSound = false;
    }
  }
  else if ( location.x < starWidth/2 ) {
    velocity.x = abs(velocity.x);
    if ( playSound ) {
      CocosDenshion::SimpleAudioEngine::
        getInstance()->playEffect("audio/thud.mp3");
      playSound = false;
    }
  }
  else if ( location.y > viewSize.height - starWidth/2 ) {
    velocity.y = -abs(velocity.y);
    if ( playSound ) {
      CocosDenshion::SimpleAudioEngine::
        getInstance()->playEffect("audio/thud.mp3");
      playSound = false;
    }
  }
  else if ( location.y < starWidth/2 ) {
    velocity.y = abs(velocity.y);
    if ( playSound ) {
      CocosDenshion::SimpleAudioEngine::
        getInstance()->playEffect("audio/thud.mp3");
      playSound = false;
    }
  }
  else {
    playSound = true;
  }
}

