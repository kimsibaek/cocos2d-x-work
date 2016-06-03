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
	void doClick(Ref *pSender);
	void randcomputer(int num);
	void result(int num1, int num2);
	int score1;
	int score2;
	cocos2d::LabelTTF* pLabel1;
	cocos2d::LabelTTF* pLabel2;
	char coinScore[100] = { 0 };
	char coinScore1[100] = { 0 };
};

#endif // __HELLOWORLD_SCENE_H__

