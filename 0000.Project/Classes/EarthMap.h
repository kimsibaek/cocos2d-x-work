#ifndef __EarthMap_H__
#define __EarthMap_H__

#include "cocos2d.h"
#include "stdafx.h"

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
	bool SecondCharacterClick;

	std::string dbfileName;

	cocos2d::SpriteFrameCache *cache;
	
	//효과음 변수
	unsigned int m_nSoundId;

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

		bool PositionView;

		int type;
	};

	Position *pos;
	int posSize = 0;
	
	Position *Emypos;
	int EmyposSize = 0;

	Position *EmyposAttack;
	int EmyposAttackSize = 0;

	Position *shortpass;
	int shortpassSize = 0;

	//이동 경로 표시
	//cocos2d::Vector<cocos2d::Sprite*> MovePosition;
	//적 표시
	//cocos2d::Vector<cocos2d::Sprite*> EmyMovePosition;

	

	cocos2d::Sprite* pause;
	cocos2d::Sprite* EndButton;
	cocos2d::Sprite* createMonster;
	cocos2d::Sprite* Items;
	cocos2d::Sprite* attack;
	cocos2d::Sprite* dispel;
	cocos2d::Sprite* cancel;

	bool ReturnState;
	int ReturnMove_tx;
	int ReturnMove_ty;

	int Moving_tx;
	int Moving_ty;

	bool status;
	bool statuschar;
	bool touchMove;

	bool statusAttack;

	void doMsgReceived(Ref* obj);
	void doMsgReceivedTurnEnd(Ref* obj);
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
	

	int ClickEmyMonster;

	int GrobalTempsize;

	void doClick1(Ref *pSender);
	virtual void onEnter();
	virtual void onExit();
	cocos2d::Vec2 StartDragPosition;
	cocos2d::Vec2 EndDragPosition;
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 FindCoordPosition(cocos2d::Vec2 pos);
	void createDatabase();
	void onCreateCharacter();
	void onCreateEmyCharacter();

	//bool ChecksPosition(int num1, int num2);
	//Position* ChecksPosition(cocos2d::Vec2 charactor, Position *pos_temp, int tempSize, int Count, int move);
	bool CheckPosition(int num1, int num2, int monSize, Monster_num *monster, int EmyMonSize, Monster_num *EmyMonster);
	Position* CheckPosition(cocos2d::Vec2 charactor, Position *pos_temp, int tempSize, int Count, int move, int monSize, Monster_num *monster, int EmyMonSize, Monster_num *EmyMonster);

	bool checkcoordinate(cocos2d::Vec2 click); 

	//bool                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             (cocos2d::Vec2 click);
	bool checkEmyMonsterCoordinate(cocos2d::Vec2 click, Monster_num *EmyMon, int EmyMonSize);

	bool BufTileCheck(cocos2d::Vec2 vec);
	int SynastryCheck(int s1, int s2);
	void ExpCheck();
	int MaxExp(int type, int level);
	void LevelUpCheck(Monster_num *monster);

	//void SpriteCoordinateChange(cocos2d::Vec2 m_pos);
	void SpriteCoordinateChange(cocos2d::Vec2 m_pos, Monster_num *monster, int mon_num);

	void DisplayEmyMonsterAttack(cocos2d::Vec2 pos);
	bool MoveTileCheck(cocos2d::Vec2 vec);
	Position *VecPosition;
	int VecPositionSize = 0;
	void EmyTurn(float f);
	void EmyMoveAttack(float f);
	void EmyMove(float f);
	void ShortistMove(cocos2d::Vec2 v_pos, Position *temppos, int tempposSize, Monster_num *monster);
	int emynum;
	int monsterNum;
	void Attack(Monster_num *monster, Monster_num *Emymonster);
	void FocusMonster(Monster_num *monster);
	void deleytime(float f);
	void EndGame(int num);
	void DistelMonsterSave(Monster_num *monster);
	void doChange(float f);
	bool ChageSchedule;
	void UpdateMonsterDB();
	void UpdateItemDB(int num);
	bool Msgerror;
	bool CreateMonsterPositionCheck();
	bool CheckOnePositionMonster(cocos2d::Vec2 mon_pos);
	int Coin;
	void AttackAction();
	bool L_R;
	int attackdamage;
	void callbackrepeatforever(float delta);
	void MonsterAdd(int num, cocos2d::Sprite *st);
	void EmyMonsterAttackAction();
	void callbackrepeatforeverAmy(float delta);
	int attackMonster;
};

#endif // __EarthMap_SCENE_H__
