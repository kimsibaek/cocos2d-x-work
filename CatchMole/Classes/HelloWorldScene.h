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
	cocos2d::CCSprite *pMan1;
	cocos2d::CCSprite *pMan2;
	cocos2d::CCSprite *pMan3;
	
	void doAction1(float f);
	void doAction2(float f);
	void doAction3(float f);
};

#endif // __HELLOWORLD_SCENE_H__
