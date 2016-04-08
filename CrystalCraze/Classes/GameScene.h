#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	cocos2d::Size winSize;

	void onPressPlay(Ref *pSender);
	void onPressAbout(Ref *pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__
