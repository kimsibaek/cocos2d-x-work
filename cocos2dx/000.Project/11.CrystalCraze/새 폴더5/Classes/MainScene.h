#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	virtual void onExit();

	cocos2d::Size winSize;
	unsigned int m_nSoundId;
	void onPressPlay(Ref *pSender);
	void onPressAbout(Ref *pSender);
	void onUpdate(float f);
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
};

#endif // __MainScene_SCENE_H__
