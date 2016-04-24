#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"

class GameScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__
