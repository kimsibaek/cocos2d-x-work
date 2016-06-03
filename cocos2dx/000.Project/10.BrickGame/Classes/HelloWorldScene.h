#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	cocos2d::Texture2D* texture;
	cocos2d::Sprite* ball;
	cocos2d::Sprite* paddle;
	cocos2d::Vector<cocos2d::Sprite*> targets;

	int BRICKS_HEIGHT;
	int BRICKS_WIDTH;

	bool isPlaying;
	bool isPaddleTouched;
	cocos2d::Vec2 ballMovement;
	~HelloWorld();
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);
	cocos2d::Sprite* m_pBall;
	cocos2d::Size winSize;
	void initializeBricks();
	void initializeBall();
	void initializePaddle();
	void startGame(float dt);
	void gameLogic(float dt);
	void processCollision(cocos2d::Sprite* brick);

};

#endif // __HELLOWORLD_SCENE_H__
