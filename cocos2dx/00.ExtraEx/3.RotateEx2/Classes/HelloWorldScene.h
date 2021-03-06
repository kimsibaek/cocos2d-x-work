﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	virtual void onEnter();
	virtual void onExit();
	virtual void onTouchesBegan(const std::vector < cocos2d::Touch*>& touches, cocos2d::Event* event);
	virtual void onTouchesMoved(const std::vector < cocos2d::Touch*>& touches, cocos2d::Event* event);
	cocos2d::Sprite * pMan;
	bool bSelect;
	float gRotation;
	virtual void onTouchesEnded(const std::vector < cocos2d::Touch*>& touches, cocos2d::Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
