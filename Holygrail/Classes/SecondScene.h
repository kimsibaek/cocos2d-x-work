#ifndef __SecondScene_SCENE_H__
#define __SecondScene_SCENE_H__

#include "cocos2d.h"


class SecondScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
	bool sword;
	bool right_sword;
	bool mase;
	bool key;
	int item;
    virtual bool init();
	void createDragon(cocos2d::Vec2 vector);
	void createMenubar();
	cocos2d::Sprite *wolf;
	cocos2d::Sprite *devil;
	cocos2d::Sprite *water;
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
	cocos2d::TMXLayer* items2;
	cocos2d::TMXLayer* Tree;
	cocos2d::TMXLayer* metainfo;
	cocos2d::Vector<cocos2d::Sprite*> MonsterVector;
	int TagNum;
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
