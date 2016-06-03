#ifndef __SecondScene_SCENE_H__
#define __SecondScene_SCENE_H__

#include "cocos2d.h"


class SecondScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	
    // implement the "static create()" method manually
    CREATE_FUNC(SecondScene);
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void onExit();
	~SecondScene(void);
	void doClose(Ref* pSender);
};

#endif // __SecondScene_SCENE_H__
