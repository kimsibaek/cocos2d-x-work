#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__



#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>

#define PTM_RATIO 32

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	bool createBox2dWorld(bool debug);
	~HelloWorld();
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);



	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	//virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
	//virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
	void tick(float dt);
	b2Body* addNewSprite(cocos2d::Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type);

	b2Body* getBodyAtTab(cocos2d::Vec2 p);
	
	cocos2d::Size winSize;
	cocos2d::Texture2D* texture;
	b2World* _world;

	GLESDebugDraw* m_debugDraw;

	/*bool bDrag;
	b2Body *dragBody;
	b2MouseJoint *mouseJoint;
	b2Body *gbody;*/

};

#endif // __HELLOWORLD_SCENE_H__
