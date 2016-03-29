#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"

#define RANDOM_INT(MIN, MAX) ((MIN) + rand() % ((MAX + 1) - (MIN)))

USING_NS_CC;

#define MAX_MISSILE		2

class GameScene : public cocos2d::LayerColor
{
public:
	GameScene();
	
    virtual bool init();
    static cocos2d::Scene* createScene();
    void menuCloseCallback(Ref* pSender);
	CREATE_FUNC(GameScene);

	void onEnter();
	void onExit();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	
	
	void RegenEnemy(float time);
	void Shooting(float time);
	void tick1(float time);
	void PutCrashEffect(const cocos2d::Vec2 &pos);
	
	void AddEnemy(const Vec2& position);
	CCSprite *player_;//주인공 플레이어
	Array *missile_[MAX_MISSILE];
	Array *enemy_;//적비행기 CCArray(배열, 리스트 구조)
	Sprite *enemy;
	Vec2 distance_;
	Size size_;
	CCSprite *spr;
	Ref *obj;
	int a;
	CCSprite *missile;
	float regenCheckTime_;

private:
	
};

#endif // __HELLOWORLD_SCENE_H__
