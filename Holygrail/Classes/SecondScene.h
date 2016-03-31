#ifndef __SecondScene_SCENE_H__
#define __SecondScene_SCENE_H__

#include "cocos2d.h"


class SecondScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void createDragon();
	cocos2d::Size winSize;
	cocos2d::Vec2 dragonPosition;
	cocos2d::Sprite* dragon;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* items2;
	cocos2d::TMXLayer* metainfo;
    // implement the "static create()" method manually
    CREATE_FUNC(SecondScene);
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	//virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void setViewpointCenter(cocos2d::Vec2 position);
	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
};

#endif // __SecondScene_SCENE_H__
