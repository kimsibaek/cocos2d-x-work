#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	cocos2d::TMXTiledMap *map;
	cocos2d::Size s;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Vec2 HelloWorld::touchToXY(cocos2d::Vec2 touch, int mapsize);
};

#endif // __HELLOWORLD_SCENE_H__
