﻿#ifndef __EarthMap_H__
#define __EarthMap_H__

#include "cocos2d.h"

class EarthMap : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(EarthMap);
	cocos2d::Size winSize;
	cocos2d::Sprite* BG;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* items;
	cocos2d::TMXLayer* metainfo;

	float MovePositionX;
	float MovePositionY;

	std::string dbfileName;

	cocos2d::SpriteFrameCache *cache;

	//Map test character;
	void onMapCharacter();
	cocos2d::Vector<cocos2d::Sprite*> TestPosition;

	void onCreateCharacter();

	cocos2d::Vec2 ChecksPosition(int num1, int num2);

	cocos2d::Sprite* pause;

	void doMsgReceived(Ref* obj);

	virtual void onEnter();
	virtual void onExit();
	cocos2d::Vec2 StartDragPosition;
	cocos2d::Vec2 EndDragPosition;
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
};

#endif // __EarthMap_SCENE_H__
