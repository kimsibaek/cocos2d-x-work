#ifndef __EarthMap_H__
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

	float MovePositionDX;
	float MovePositionDY;

	bool CharacterClick;

	std::string dbfileName;

	cocos2d::SpriteFrameCache *cache;
	//이동 경로 표시
	cocos2d::Vector<cocos2d::Sprite*> MovePosition;

	struct Position {
		Position *pos2;
		int pos2Size;
		int num;
		int x;
		int y;

		int front_x;
		int front_y;
	};
	Position *pos;
	int posSize = 0;
	
	Position *shortpass;
	int shortpassSize = 0;

	int mons;

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
	cocos2d::Vec2 FindCoordPosition(cocos2d::Vec2 pos);
	void onCreateCharacter();
	void onCreateEmyCharacter();
	void FocusCharacter();

	bool ChecksPosition(int num1, int num2);
	bool ChecksPosition(cocos2d::Vec2 charactor, int pose, bool check);
	bool checkcoordinate(cocos2d::Vec2 click);
};

#endif // __EarthMap_SCENE_H__
