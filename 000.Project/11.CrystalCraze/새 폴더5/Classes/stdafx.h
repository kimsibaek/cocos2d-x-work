#pragma once

#include "cocos2d.h"

extern int gLastScore;

struct Sprite_num {
	int gemType;
	cocos2d::Sprite* sprite;
	float xPos;
	float yPos;
	float xSpeed;
	float ySpeed;
};

struct Sprite_number {
	Sprite_num* sprite_num;
};

extern Sprite_number* gFallingGems;
extern int* gFallingGemsSize;
extern Sprite_num* gGameOverGems;
extern int gGameOverGemsSize;