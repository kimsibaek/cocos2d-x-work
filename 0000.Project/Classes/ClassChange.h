#ifndef __ClassChange_H__
#define __ClassChange_H__

#include "cocos2d.h"

class ClassChange : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(ClassChange);
	void doClick1(Ref *pSender);
};

#endif // __ClassChange_SCENE_H__
