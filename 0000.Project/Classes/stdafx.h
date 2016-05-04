#pragma once

#include "cocos2d.h"


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
	int move;
	
	int range;

	bool _turn;

	bool upgrade;

	cocos2d::Sprite *sprite;
	//화면이동좌표
	float xMovePosition;
	float yMovePosition;
	//본좌표
	float xPosition;
	float yPosition;
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