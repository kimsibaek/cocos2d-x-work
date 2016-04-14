#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getWinSize();

	texture = Director::getInstance()->getTextureCache()->addImage("Images/blocks.png");

	if (this->createBox2dWorld(true)) {
		this->schedule(schedule_selector(HelloWorld::tick));
	}


	return true;
}


bool HelloWorld::createBox2dWorld(bool debug) {

	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	if (debug) {
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_world->SetDebugDraw(m_debugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		m_debugDraw->SetFlags(flags);
	}


	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	b2Body *groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//bDrag = false;

	//gbody = this->addNewSprite(Vec2(0, 0), Size(0, 0), b2_staticBody, nullptr, 0);

	//this->addNewSprite(Vec2(240, 160), Size(32, 32), b2_dynamicBody, "test", 0);
	b2RopeJointDef ropeJointDef1;
	b2RopeJointDef ropeJointDef2;
	b2RopeJointDef ropeJointDef3;
	b2RopeJointDef ropeJointDef4;

	b2Body *body1 = this->addNewSprite(Vec2(100, 260), Size(20, 20), b2_staticBody, "test", 0);
	b2Body *body2 = this->addNewSprite(Vec2(160, 260), Size(20, 20), b2_dynamicBody, "test", 0);
	b2Body *body3 = this->addNewSprite(Vec2(220, 260), Size(20, 20), b2_dynamicBody, "test", 0);
	b2Body *body4 = this->addNewSprite(Vec2(280, 260), Size(20, 20), b2_dynamicBody, "test", 0);
	b2Body *body5 = this->addNewSprite(Vec2(340, 260), Size(20, 20), b2_staticBody, "test", 0);

	ropeJointDef1.bodyA = body1;
	ropeJointDef1.bodyB = body2;
	ropeJointDef1.localAnchorA = b2Vec2(1.0f, 0.0f);
	ropeJointDef1.localAnchorB = b2Vec2(-1.0f, 0.0f);
	ropeJointDef1.maxLength = 1.0f;
	ropeJointDef1.collideConnected = false;
	_world->CreateJoint(&ropeJointDef1);

	ropeJointDef2.bodyA = body2;
	ropeJointDef2.bodyB = body3;
	ropeJointDef2.localAnchorA = b2Vec2(1.0f, 0.0f);
	ropeJointDef2.localAnchorB = b2Vec2(-1.0f, 0.0f);
	ropeJointDef2.maxLength = 1.0f;
	ropeJointDef2.collideConnected = false;
	_world->CreateJoint(&ropeJointDef2);

	ropeJointDef3.bodyA = body3;
	ropeJointDef3.bodyB = body4;
	ropeJointDef3.localAnchorA = b2Vec2(1.0f, 0.0f);
	ropeJointDef3.localAnchorB = b2Vec2(-1.0f, 0.0f);
	ropeJointDef3.maxLength = 1.0f;
	ropeJointDef3.collideConnected = false;
	_world->CreateJoint(&ropeJointDef3);

	ropeJointDef4.bodyA = body4;
	ropeJointDef4.bodyB = body5;
	ropeJointDef4.localAnchorA = b2Vec2(1.0f, 0.0f);
	ropeJointDef4.localAnchorB = b2Vec2(-1.0f, 0.0f);
	ropeJointDef4.maxLength = 1.0f;
	ropeJointDef4.collideConnected = false;
	_world->CreateJoint(&ropeJointDef4);

	return true;
}

HelloWorld::~HelloWorld() {
	delete _world;
	_world = nullptr;
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);

	kmGLPushMatrix();

	_world->DrawDebugData();

	kmGLPopMatrix();
}


void HelloWorld::onEnter() {
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
void HelloWorld::onExit() {
	_eventDispatcher->removeAllEventListeners();
	Layer::onExit();
}
bool HelloWorld::onTouchBegan(Touch *touch, Event* event) {
	auto touchPoint = touch->getLocation();

	if (b2Body *b = this->getBodyAtTab(touchPoint)) {
		b2JointEdge* joints = b->GetJointList();

		while (joints) {
			b2Joint *joint = joints->joint;
			joints = joints->next;
			_world->DestroyJoint(joint);
		}
		
	}
	return true;
}
//
//void HelloWorld::onTouchMoved(Touch *touch, Event* event) {
//	Vec2 touchPoint = touch->getLocation();
//
//	if (bDrag) {
//		mouseJoint->SetTarget(b2Vec2(touchPoint.x / PTM_RATIO, touchPoint.y / PTM_RATIO));
//	}
//}
//
//void HelloWorld::onTouchEnded(Touch *touch, Event* event) {
//	if (bDrag) {
//		_world->DestroyJoint(mouseJoint);
//		mouseJoint = nullptr;
//
//		dragBody->SetAwake(true);
//	}
//	bDrag = false;
//}
void HelloWorld::tick(float dt) {
	int velocityIterations = 8;
	int positionIterations = 3;

	_world->Step(dt, velocityIterations, positionIterations);

	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != nullptr) {
			Sprite * spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}
b2Body* HelloWorld::addNewSprite(cocos2d::Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type) {


	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);
	
	if (spriteName) {
		if (strcmp(spriteName, "test") == 0) {
			int idx = (CCRANDOM_0_1() > .5 ? 0 : 1);
			int idy = (CCRANDOM_0_1() > .5 ? 0 : 1);

			Sprite* sprite = Sprite::createWithTexture(texture, Rect(32 * idx, 32 * idy, 32, 32));
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
		else {
			Sprite* sprite = Sprite::create(spriteName);
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
	}

	b2Body *body = _world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	b2CircleShape circle;

	if (type == 0) {
		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);
		fixtureDef.shape = &dynamicBox;
	}
	else {
		circle.m_radius = (size.width / 2) / PTM_RATIO;

		fixtureDef.shape = &circle;
	}

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* HelloWorld::getBodyAtTab(Vec2 p) {
	b2Fixture *fix;
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != nullptr) {
			if (b->GetType() == b2_staticBody) {
				continue;
			}
			fix = b->GetFixtureList();
			if (fix->TestPoint(b2Vec2(p.x / PTM_RATIO, p.y/PTM_RATIO))) {
				return b;
			}
		}
	}
	return nullptr;
}