#ifndef __TurnEndScene_H__
#define __TurnEndScene_H__

#include "cocos2d.h"

class TurnEndScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(TurnEndScene);
	void doContinue(Ref* pSender);
	void doSendMsg(Ref* pSender);
	void doClose(Ref* pSender);
};

#endif // __TurnEndScene_H__
