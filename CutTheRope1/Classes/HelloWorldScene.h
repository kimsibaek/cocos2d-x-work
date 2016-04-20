#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>
#include "vrope-x/vrope.h"
#include "vrope-x/vstick.h"
#include "vrope-x/vpoint.h"

//#define PTM_RATIO 32

class VRope;

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	bool createBox2dWorld(bool debug);
	cocos2d::SpriteBatchNode *ropeSpriteSheet;
	b2Body* addNewSpriteAt(cocos2d::Vec2 point);
	void createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body* bodyB, b2Vec2 anchorB, float32 sag);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void tick(float dt);
	cocos2d::Size winSize;
	cocos2d::Texture2D* texture;
	b2World* _world;
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	GLESDebugDraw* m_debugDraw;
	std::vector<VRope *> *ropes;
	bool bDrag;
	b2Body *groundBody;
	b2Body *dragBody;
	b2MouseJoint *mouseJoint;
	b2Body *gbody;

	b2Body *body;
	bool touchbegin;
};

#endif // __HELLOWORLD_SCENE_H__
