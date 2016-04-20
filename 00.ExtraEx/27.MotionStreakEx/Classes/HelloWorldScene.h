#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	cocos2d::MotionStreak *m_pStreak;

	void onEnter();
	void onExit();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
