#ifndef __FirstScene_SCENE_H__
#define __FirstScene_SCENE_H__

#include "cocos2d.h"


class FirstScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void createDragon2(cocos2d::Vec2 vector);
	bool sword;
	bool right_sword;
	bool mase;
	bool key;
	int item;
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
	cocos2d::Size winSize2;
	cocos2d::Vec2 dragonPosition2;
	cocos2d::Sprite* dragon2;
	cocos2d::TMXTiledMap* tmap2;
	cocos2d::TMXLayer* background2;
	cocos2d::TMXLayer* Tree;
	cocos2d::TMXLayer* items2;
	cocos2d::TMXLayer* metainfo2;
	cocos2d::Vector<cocos2d::Sprite*> MonsterVector;
	int TagNum;
    // implement the "static create()" method manually
    CREATE_FUNC(FirstScene);
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	//virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void setViewpointCenter2(cocos2d::Vec2 position);
	void setPlayerPosition2(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordForPosition2(cocos2d::Vec2 position);
};

#endif // __FirstScene_SCENE_H__
