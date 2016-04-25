#ifndef __MainScene_H__
#define __MainScene_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
	void doClick1(Ref *pSender);
};

#endif // __MainScene_SCENE_H__
