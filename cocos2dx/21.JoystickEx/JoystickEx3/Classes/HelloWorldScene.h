#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "Entity.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	cocos2d::Sprite* pMan;
	void update(float deltaTime);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	virtual void onTouchesBegan(const std::vector < cocos2d::Touch*>& touches, cocos2d::Event* event);
	virtual void onTouchesMoved(const std::vector < cocos2d::Touch*>& touches, cocos2d::Event* event);
	virtual void onTouchesEnded(const std::vector < cocos2d::Touch*>& touches, cocos2d::Event* event);
	virtual void onTouchesCancelled(const std::vector < cocos2d::Touch*>& touches, cocos2d::Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
