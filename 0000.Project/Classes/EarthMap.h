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

	cocos2d::EventListenerTouchOneByOne* listener;

	cocos2d::Size winSize;
	cocos2d::Sprite* BG;

	float MovePositionX;
	float MovePositionY;

	float MovePositionDX;
	float MovePositionDY;

	bool CharacterClick;

	std::string dbfileName;

	cocos2d::SpriteFrameCache *cache;
	

	struct Position {
		Position *pos2;
		int pos2Size;
		int num;
		int x;
		int y;
		int tempsize;
		int front_x;
		int front_y;
		int front_front_x;
		int front_front_y;
		int front_front_front_x;
		int front_front_front_y;
	};

	Position *pos;
	int posSize = 0;
	
	Position *Emypos;
	int EmyposSize = 0;

	Position *shortpass;
	int shortpassSize = 0;

	//이동 경로 표시
	//cocos2d::Vector<cocos2d::Sprite*> MovePosition;
	//적 표시
	cocos2d::Vector<cocos2d::Sprite*> EmyMovePosition;

	int mons;

	cocos2d::Sprite* pause;
	cocos2d::Sprite* createMonster;
	cocos2d::Sprite* Items;

	bool status;
	bool touchMove;

	void doMsgReceived(Ref* obj);
	void doMsgReceivedMonster(Ref* obj);
	void doMsgReceivedTool(Ref* obj);

	int createMonsterNum;
	int ToolNum;

	int movement;
	cocos2d::Vec2 VPos;
	void createUpgrade();
	Position *createMonsterPos;
	int createPosSize;

	cocos2d::Sprite* st;
	void RemoveSprite();

	bool b_CreateMonster;

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
	Position* ChecksPosition(cocos2d::Vec2 charactor, Position *pos_temp, int tempSize, int Count);
	bool checkcoordinate(cocos2d::Vec2 click);
};

#endif // __EarthMap_SCENE_H__
