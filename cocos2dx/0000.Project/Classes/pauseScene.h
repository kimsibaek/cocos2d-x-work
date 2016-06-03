#ifndef __pauseScene_H__
#define __pauseScene_H__

#include "cocos2d.h"

class pauseScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(pauseScene);
	void doContinue(Ref* pSender);
	void doSendMsg(Ref* pSender);
	void doClose(Ref* pSender);
};

#endif // __pauseScene_SCENE_H__
