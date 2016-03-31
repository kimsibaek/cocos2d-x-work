#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void createWomen();

	cocos2d::Size winSize;
	cocos2d::Vec2 WomenPosition;
	cocos2d::Sprite* Women;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* background;
	cocos2d::ValueMap spawnPoint;
	cocos2d::TMXLayer* metainfo;
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	void tick1(float f);
	void setPlayerPosition(cocos2d::Vec2 position);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
