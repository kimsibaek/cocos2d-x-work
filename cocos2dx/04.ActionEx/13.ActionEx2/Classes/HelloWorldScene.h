#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	cocos2d::Sprite* pMan;
	cocos2d::JumpBy* myAction;
	void doAction(Ref* pSender);
	void doAction2(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
