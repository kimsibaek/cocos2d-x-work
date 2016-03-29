#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	cocos2d::Layer* layer1;
	cocos2d::Layer* layer2;

	cocos2d::Sprite* dragon;
	cocos2d::Sprite* rightSprite;
	cocos2d::Sprite* rightPressedSprite;
	cocos2d::Sprite* leftSprite;
	cocos2d::Sprite* leftPressedSprite;

	cocos2d::Size winSize;
	bool isLeftPressed;
	bool isRightPressed;

	void createBackgroundParallax();
	void createDragon();
	void createArrowButtons();
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	bool isTouchInside(cocos2d::Sprite* sprite, cocos2d::Touch* touch);
	void startMovingBackground();
	void stopMovingBackground();
	void moveBackground(float t);

};

#endif // __HELLOWORLD_SCENE_H__
