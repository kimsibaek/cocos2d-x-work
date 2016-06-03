﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	cocos2d::Sprite* pWoman1;
	cocos2d::Sprite* pWoman2;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void SpriteProgressToRadial();
	void SpriteProgressToHorizontal();
	void SpriteProgressToVertical();
	void SpriteProgressToRadialMidpointChanged();
	void SpriteProgressBarVarious();
	void SpriteProgressBarTintAndFade();
};

#endif // __HELLOWORLD_SCENE_H__