#ifndef __EndGame_H__
#define __EndGame_H__

#include "cocos2d.h"
#include "sqlite3.h"

using namespace cocos2d;

class EndGame : 
	public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(EndGame);

	std::string dbfileName;
	virtual void onEnter();
	virtual void onExit();

	cocos2d::Size winSize;

	cocos2d::EventListenerTouchOneByOne* listener;

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void createDatabase();
	void insertData(Ref* pSender);
	void selectData(Ref* pSender);
	void WaitClick(float f);
	bool wait;
};

#endif // __EndGame_SCENE_H__
