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
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255) ))
    {
        return false;
    }
	winSize = Director::getInstance()->getWinSize();

	texture = Director::getInstance()->getTextureCache()->addImage("Images/CloseNormal.png");

	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	_world = new b2World(gravity);

	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

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

	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	this->schedule(schedule_selector(HelloWorld::tick));

	/*b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.5f, .5f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.f;
	groundBody->CreateFixture(&fixtureDef);
*/
/*
	b2PolygonShape dynamicBox;
	b2Vec2 tri[3];

	tri[0].x = -.5;
	tri[0].y = 0.0;

	tri[1].x = .5;
	tri[1].y = 0.0;

	tri[2].x = 0;
	tri[2].y = 1.0;

	dynamicBox.Set(tri, 3);


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.f;
	groundBody->CreateFixture(&fixtureDef);
*/
    return true;
}

HelloWorld::~HelloWorld() {
	delete _world;
	_world = nullptr;
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

	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != nullptr) {
			Sprite * spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}
void HelloWorld::addNewSpriteAtPosition(cocos2d::Vec2 location) {
	Sprite* pSprite = Sprite::createWithTexture(texture, Rect(0, 0, 37, 37));
	pSprite->setPosition(Vec2(location.x, location.y));
	this->addChild(pSprite);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	bodyDef.userData = pSprite;

	b2Body * body = _world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 0.55f;

	b2FixtureDef fixtrueDef;
	fixtrueDef.shape = &circle;
	fixtrueDef.density = -1.0;
	fixtrueDef.friction = 2.0f;
	fixtrueDef.restitution = 0.7f;
	body->CreateFixture(&fixtrueDef);
}