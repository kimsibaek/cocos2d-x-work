//
//  HelloWorldScene.h
//  CuteAPultCocos2D-x
//
//  Created by Clawoo on 9/8/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//
#ifndef __HELLO_m_worldH__
#define __HELLO_m_worldH__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define PTM_RATIO 32

class HelloWorld : public cocos2d::Layer {
public:
    
	static cocos2d::Scene* createScene();

	virtual bool init();
    // returns a Scene that contains the HelloWorld as the only child
	~HelloWorld();
    // adds a new sprite at a given coordinate
   // virtual void draw();
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	CREATE_FUNC(HelloWorld);
    void tick(float dt);
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    void createBullets(int count);
    bool attachBullet();
    void resetBullet();
    void resetGame();
    
    void createTargets();
    void createTarget(const char *imageName, cocos2d::Vec2 position, float rotation, bool isCircle, bool isStatic, bool isEnemy);


	cocos2d::Size winSize;

private:
    std::vector<b2Body *> m_bullets;
    std::vector<b2Body *> m_targets;
    std::vector<b2Body *> m_enemies;

    int m_currentBullet;
    b2World* m_world;
    b2Body* m_groundBody;
    b2Fixture *m_armFixture;
    b2Body *m_armBody;
    b2RevoluteJoint *m_armJoint;
    b2MouseJoint *m_mouseJoint;
    
    b2Body *m_bulletBody;
    b2WeldJoint *m_bulletJoint;
    
    
    bool m_releasingArm;
};

#endif // __HELLO_m_worldH__
