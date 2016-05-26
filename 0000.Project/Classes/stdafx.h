#pragma once

#include "cocos2d.h"

extern int Mapdata;

struct Monster_num {
	int ID;
	int Type;
	int level;
	int Item1;
	int Item2;
	int Item3;
	int exp;

	int atk;
	int def;
	int hp;
	int Fullhp;
	int move;
	
	int range;

	bool _turn;
	bool upgrade;
	bool View;
	int ViewNum;
	cocos2d::Sprite *sprite;
	////화면이동좌표
	//float xMovePosition;
	//float yMovePosition;
	////본좌표
	//float xPosition;
	//float yPosition;
	//타일좌표
	int tx=0;
	int ty=0;

	float HPbarPosition;

};

//객체 생성
extern Monster_num *monster_char;
extern int monsterSize;

extern Monster_num *EmyMonster_char;
extern int EmyMonsterSize;

extern Monster_num *Monster_List;
extern int MonsterListSize;

extern Monster_num *Death_Monster_List;
extern int DeathMonsterListSize;

extern Monster_num *Distel_Monster_List;
extern int DistelMonsterListSize;

struct Items_num {
	int _ID;
	int Num;

	cocos2d::Sprite *sprite;
};

extern Items_num *Items_List;
extern int ItemsListSize;

extern float VPosX;
extern float VPosY;

extern cocos2d::TMXTiledMap* tmap;
extern cocos2d::TMXLayer* metainfo;

extern cocos2d::Vector<cocos2d::Sprite*> MovePosition;
extern cocos2d::Vector<cocos2d::Sprite*> EmyMovePosition;

extern int EndGame_Num;

extern int mons;

extern int ToolUseMonster;

extern int MonsterCellNum;
extern int MonsterCellNum2;