#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>
#include "vrope-x/vrope.h"
#include "vrope-x/vstick.h"
#include "vrope-x/vpoint.h"
#include "ContactListener.h"

//#define PTM_RATIO 32

class VRope;

class HelloWorld : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	~HelloWorld();

	bool createBox2dWorld(bool debug);
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
		
	b2Body* addNewSpriteAt(cocos2d::Vec2 point);
	void createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body* bodyB, b2Vec2 anchorB, float32 sag);
	void tick(float dt);
	bool checkLineIntersection(cocos2d::Vec2 p1, cocos2d::Vec2 p2, cocos2d::Vec2 p3, cocos2d::Vec2 p4);
	b2Body* createRopeTipBody();
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
	
	cocos2d::Size winSize;
	cocos2d::Texture2D* texture;
	b2World* _world;
	GLESDebugDraw* m_debugDraw;

	std::vector<VRope *> *ropes;
	std::vector<b2Body *> *candies;

	cocos2d::SpriteBatchNode *ropeSpriteSheet;

	//ContactListener* myContactListener;

	cocos2d::Sprite* sprite_pine;

	b2Body* body1;
	cocos2d::Sprite* sprite1;
	cocos2d::Sprite* croc_;
	b2Body* crocMouth_;
	b2Fixture* crocMouthBottom_;
	bool crocMouthOpened;


	b2Body *groundBody;

	//void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__
