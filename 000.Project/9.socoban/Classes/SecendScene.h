#ifndef __SecendScene_SCENE_H__
#define __SecendScene_SCENE_H__

#include "cocos2d.h"

class SecendScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(SecendScene);
	cocos2d::Size winSize;
	cocos2d::Vec2 PenguinPosition;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* IceTile;
	cocos2d::TMXLayer* FinishPoint;
	cocos2d::TMXLayer* metainfo;
	void createPenguin(cocos2d::Vec2 vector);
	cocos2d::Texture2D* texture;
	cocos2d::Sprite* Penguin;
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void Right_button_Action(Ref* pSender);
	void Left_button_Action(Ref* pSender);
	void Up_button_Action(Ref* pSender);
	void Down_button_Action(Ref* pSender);
	void Back_button_Action(Ref* pSender);
	void Retset_button_Action(Ref* pSender);
	cocos2d::Vec2 AfterPosition;
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	bool setPlayerPosition(cocos2d::Vec2 position, int num);
	bool setIcePosition(cocos2d::Vec2 position, int num);
	int AfterCheck;
	bool IceMove;
	bool PenguinMove;
	int TagNum;
	int TagNum2;
	cocos2d::Sprite *Ice;
	cocos2d::Sprite *Finish;
	cocos2d::Vector<cocos2d::Sprite*> IceVector;
	cocos2d::Vector<cocos2d::Sprite*> FinishVector;
	cocos2d::Vector<cocos2d::Sprite*> BackPosition;
	void FinishCheck();
};

#endif // __SecendScene_SCENE_H__
