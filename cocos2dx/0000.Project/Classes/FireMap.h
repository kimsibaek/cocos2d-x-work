#ifndef __FireMap_H__
#define __FireMap_H__

#include "cocos2d.h"

class FireMap : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(FireMap);

	cocos2d::Size winSize;
	cocos2d::Sprite* BG;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* metainfo;

	float MovePositionX;
	float MovePositionY;

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

#endif // __FireMap_SCENE_H__
