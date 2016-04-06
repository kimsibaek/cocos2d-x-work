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

	cocos2d::EventListenerTouchAllAtOnce* listener;
	cocos2d::Size winSize;
	cocos2d::RenderTexture* m_pTarget;
	cocos2d::Vector<cocos2d::Sprite*> m_pBrush;

	~HelloWorld();
	virtual void onEnter();
	virtual void onExit();
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void saveImage(Ref* sender);
	void clearImage(Ref* sender);

};

#endif // __HELLOWORLD_SCENE_H__
