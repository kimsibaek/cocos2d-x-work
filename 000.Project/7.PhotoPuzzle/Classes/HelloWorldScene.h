#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
	cocos2d::Size winSize;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* background;
	cocos2d::Texture2D* texture;
	cocos2d::Vector<cocos2d::Sprite*> Photo;
	int num;
	void MixingPhoto();
	void CreatePhoto();
	int blank;
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void FinishCheck();
};

#endif // __HELLOWORLD_SCENE_H__
