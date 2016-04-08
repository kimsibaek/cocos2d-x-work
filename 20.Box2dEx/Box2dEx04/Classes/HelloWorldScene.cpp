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
	srand((int)time(nullptr));
	winSize = Director::getInstance()->getWinSize();

	texture = Director::getInstance()->getTextureCache()->addImage("Images/blocks.png");

	if (this->createBox2dWorld(true)) {
		this->schedule(schedule_selector(HelloWorld::tick));
	}

	return true;
}

void HelloWorld::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
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


	Sprite* pSprite1 = Sprite::createWithTexture(texture, Rect(0, 0, 64, 64));
	pSprite1->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(pSprite1);

	b2BodyDef bodyDef1;
	bodyDef1.type = b2_staticBody;
	bodyDef1.position.Set(winSize.width/2/PTM_RATIO, winSize.height/2/PTM_RATIO);
	bodyDef1.userData = pSprite1;

	b2Body* body1 = _world->CreateBody(&bodyDef1);

	b2PolygonShape staticBox;

	staticBox.SetAsBox((pSprite1->getContentSize().width / 2) / PTM_RATIO, (pSprite1->getContentSize().height / 2) / PTM_RATIO);

	b2FixtureDef fixtureDef1;
	fixtureDef1.shape = &staticBox;
	fixtureDef1.density = 1.0f;

	body1->CreateFixture(&fixtureDef1);

	Sprite* pSprite2 = Sprite::createWithTexture(texture, Rect(0, 0, 64, 32));
	pSprite2->setPosition(Vec2(0, 100));
	this->addChild(pSprite2);

	b2BodyDef bodyDef2;
	bodyDef2.type = b2_kinematicBody;
	bodyDef2.position.Set(0, 100.0f / PTM_RATIO);
	bodyDef2.linearVelocity = b2Vec2(1.0f, 0);
	bodyDef2.userData = pSprite2;

	b2Body* body2 = _world->CreateBody(&bodyDef2);

	b2PolygonShape kinematicBox;

	kinematicBox.SetAsBox((pSprite2->getContentSize().width / 2) / PTM_RATIO, (pSprite2->getContentSize().height / 2) / PTM_RATIO);

	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &kinematicBox;
	fixtureDef2.density = 1.0f;

	body2->CreateFixture(&fixtureDef2);


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

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
void HelloWorld::onExit() {
	_eventDispatcher->removeAllEventListeners();
	Layer::onExit();
}
bool HelloWorld::onTouchBegan(Touch *touch, Event* event) {
	auto touchPoint = touch->getLocation();

	addNewSpriteAtPosition(touchPoint);
	return true;
}
void HelloWorld::tick(float dt) {
	int velocityIterations = 8;
	int positionIterations = 3;

	_world->Step(dt, velocityIterations, positionIterations);
	b2Body *b;
	for (b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != nullptr) {
			Sprite * spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}

	if (b->GetType() == b2_kinematicBody) {
		b2Vec2 v = b->GetPosition();
		if (v.x*PTM_RATIO > winSize.width) {
			b->SetLinearVelocity(b2Vec2(-1.0f, 0));
		}
		else if (v.x <0) {
			b->SetLinearVelocity(b2Vec2(1.0f, 0));
		}
	}

}
void HelloWorld::addNewSpriteAtPosition(cocos2d::Vec2 location) {

	int nNum = rand() % 3;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	bodyDef.userData = nullptr;

	b2Body * body = _world->CreateBody(&bodyDef);

	if (nNum == 0) {
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(0.8f, 0.8f);

		b2FixtureDef fixtrueDef;
		fixtrueDef.shape = &dynamicBox;
		fixtrueDef.density = 1.0f;
		fixtrueDef.friction = 0.3f;
		fixtrueDef.restitution = 0.0f;
		body->CreateFixture(&fixtrueDef);
	}
	else if (nNum == 1) {
		b2PolygonShape dynamicBox;
		b2Vec2 tri[3];

		tri[0].x = -0.5;
		tri[0].y = 0.0;

		tri[1].x = 0.5;
		tri[1].y = 0.0;

		tri[2].x = 0;
		tri[2].y = 1.0;

		dynamicBox.Set(tri, 3);

		b2FixtureDef fixtrueDef;
		fixtrueDef.shape = &dynamicBox;
		fixtrueDef.density = 1.0f;
		fixtrueDef.friction = 0.3f;
		fixtrueDef.restitution = 1.0f;
		body->CreateFixture(&fixtrueDef);
	}
	else {
		b2CircleShape circle;
		circle.m_radius = 1.0f;

		b2FixtureDef fixtrueDef;
		fixtrueDef.shape = &circle;
		fixtrueDef.density = 1.0f;
		fixtrueDef.friction = 0.2f;
		fixtrueDef.restitution = 1.0f;
		body->CreateFixture(&fixtrueDef);
	}
	
}