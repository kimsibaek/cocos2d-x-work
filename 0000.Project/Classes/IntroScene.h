#ifndef __IntroScene_H__
#define __IntroScene_H__

#include "cocos2d.h"

class IntroScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(IntroScene);
	void myTickInce(float f);
	void tick(float dt);
	void doClick(Ref *pSender);
};

#endif // __IntroScene_SCENE_H__
