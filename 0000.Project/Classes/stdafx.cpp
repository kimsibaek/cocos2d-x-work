#include "stdafx.h"

Monster_num *monster_char;
int monsterSize = 0;

Monster_num *EmyMonster_char;
int EmyMonsterSize=0;

Monster_num *Monster_List;
int MonsterListSize = 0;

Monster_num *Death_Monster_List;
int DeathMonsterListSize = 0;

Monster_num *Distel_Monster_List;
int DistelMonsterListSize = 0;

Items_num *Items_List;
int ItemsListSize = 0;

float VPosX = 0;
float VPosY = 0;

cocos2d::TMXTiledMap* tmap;
cocos2d::TMXLayer* metainfo;

cocos2d::Vector<cocos2d::Sprite*> MovePosition;
cocos2d::Vector<cocos2d::Sprite*> EmyMovePosition;

int EndGame_Num = 0;

int mons = 0;

int ToolUseMonster = 0;

int MonsterCellNum = -1;
int MonsterCellNum2 = -1;
