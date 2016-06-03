#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Joystick.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>

#define PTM_RATIO 32


class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	bool createBox2dWorld(bool debug);
	b2Body* addNewSprite(cocos2d::Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type);
	
	Joystick* joystick;
	cocos2d::Sprite* pMan;
	void tick(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	cocos2d::Size winSize;
	cocos2d::Texture2D* texture;
	b2World* _world;

	GLESDebugDraw* m_debugDraw;

	bool bDrag;
	b2Body *dragBody;
	b2MouseJoint *mouseJoint;
	b2Body *gbody;

	b2Body *body;
	bool touchbegin;
};

#endif // __HELLOWORLD_SCENE_H__
