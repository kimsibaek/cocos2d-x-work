#ifndef __TestScene2_SCENE_H__
#define __TestScene2_SCENE_H__

#include "cocos2d.h"

extern int num2;

class TestScene2 : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	
    // implement the "static create()" method manually
    CREATE_FUNC(TestScene2);
	void doClose(Ref* pSender);
};

#endif // __TestScene2_SCENE_H__
