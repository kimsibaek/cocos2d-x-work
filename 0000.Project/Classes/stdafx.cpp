#include "stdafx.h"

Monster_num *monster_char;
int monsterSize = 0;

Monster_num *EmyMonster_char;
int EmyMonsterSize=0;

Monster_num *Monster_List;
int MonsterListSize = 0;

Items_num *Items_List;
int ItemsListSize = 0;

float VPosX = 0;
float VPosY = 0;

cocos2d::TMXTiledMap* tmap;
cocos2d::TMXLayer* metainfo;

cocos2d::Vector<cocos2d::Sprite*> MovePosition;