#pragma once

#include "cocos2d.h"


struct Monster_num {
	int ID;
	int Type;
	int level;
	int Item1;
	int Item2;
	int Item3;

	cocos2d::Sprite *sprite;

	float xMovePosition;
	float yMovePosition;

	float xPosition;
	float yPosition;
	
};

//객체 생성
extern Monster_num *monster_char;
extern int monsterSize;

extern Monster_num *EmyMonster_char;
extern int EmyMonsterSize;