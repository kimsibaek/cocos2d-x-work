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
	cocos2d::Sprite* pSprite1;
	cocos2d::Sprite* pSprite2;
	void doFrontFlip(Ref* sender);
	void doBackFlip(Ref* sender);


	void onCaptured(Ref*);
	void afterCaptured(bool succeed, const std::string& outputFile);
	std::string _filename;
	static const int childTag = 119;

};

#endif // __HELLOWORLD_SCENE_H__
