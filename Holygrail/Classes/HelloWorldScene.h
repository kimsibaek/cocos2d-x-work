#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void createDragon(cocos2d::Vec2 vector);
	void createMenubar();
	cocos2d::Sprite* ItemsMenu;
	cocos2d::RepeatForever* rep;
	cocos2d::Animation* animation;
	cocos2d::Animate* animate;
	cocos2d::Texture2D* texture;
	cocos2d::Sprite* Resetbar;
	cocos2d::Size winSize;
	cocos2d::Vec2 dragonPosition;
	cocos2d::Sprite* dragon;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* items;
	cocos2d::TMXLayer* metainfo;
	bool sword;
	bool right_sword;
	bool mase;
	bool key;
	int item;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	//virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void setViewpointCenter(cocos2d::Vec2 position);
	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
};

#endif // __HELLOWORLD_SCENE_H__
