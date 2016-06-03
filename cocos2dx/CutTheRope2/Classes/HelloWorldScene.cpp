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
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	ropes = new std::vector<VRope*>;

	winSize = Director::getInstance()->getWinSize();
	this->createBox2dWorld(false);

	SpriteFrameCache *frameCache = SpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("Images/CutTheVerlet.plist");

	Sprite* sprite = Sprite::createWithSpriteFrameName("bg.png");
	sprite->setPosition(160, 240);
	this->addChild(sprite);

	sprite1 = Sprite::createWithSpriteFrameName("croc_front_mouthclosed.png");
	sprite1->setPosition(280, 50);
	this->addChild(sprite1);



	ropeSpriteSheet = SpriteBatchNode::create("Images/rope_texture.png");
	this->addChild(ropeSpriteSheet);

	

	body1 = this->addNewSpriteAt(Vec2(winSize.width / 2, winSize.height * 2 / 3));

	this->createRope(groundBody, b2Vec2((winSize.width / 5) / PTM_RATIO, winSize.height * 3 / 4 / PTM_RATIO), body1, body1->GetLocalCenter(), 1.1f);
	this->createRope(groundBody, b2Vec2((winSize.width*4 / 5) / PTM_RATIO, winSize.height*3/4 / PTM_RATIO), body1, body1->GetLocalCenter(), 1.1f);
	this->createRope(groundBody, b2Vec2((winSize.width*4 / 5) / PTM_RATIO, winSize.height/2 / PTM_RATIO), body1, body1->GetLocalCenter(), 1.1f);

	this->schedule(schedule_selector(HelloWorld::tick));
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
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
void HelloWorld::onExit() {
	_eventDispatcher->removeAllEventListeners();
	Layer::onExit();
}

void HelloWorld::tick(float dt) {
	int velocityIterations = 8;
	int positionIterations = 1;

	_world->Step(dt, velocityIterations, positionIterations);

	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != nullptr) {
			Sprite * spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));

			//b->GetContactList()
		}
	}
	std::vector<VRope *>::iterator rope;
	for (rope = ropes->begin(); rope != ropes->end(); ++rope) {
		(*rope)->update(dt);
		(*rope)->updateSprites();
	}
	/*Rect rect1 = body1->getTextureRect();
	Rect rect2 = sprite1->getTextureRect();
	if (rect1.intersectsRect(rect2)) {
		log("충돌");
	}*/

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

	groundBody = _world->CreateBody(&groundBodyDef);

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

	//body = this->addNewSprite(Vec2(240, 160), Size(32, 32), b2_dynamicBody, "test", 0);

	return true;
}

b2Body* HelloWorld::addNewSpriteAt(Vec2 point) {
	Sprite* sprite_pine = Sprite::createWithSpriteFrameName("pineapple.png");
	sprite_pine->setTag(1);
	this->addChild(sprite_pine);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO);
	bodyDef.userData = sprite_pine;
	bodyDef.linearDamping = 0.3f;
	b2Body* body = _world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2PolygonShape spriteShape;

	b2Vec2 verts[] = {
		b2Vec2(-7.6f / PTM_RATIO, -34.4f / PTM_RATIO),
		b2Vec2(8.3f / PTM_RATIO, -34.4f / PTM_RATIO),
		b2Vec2(15.55f / PTM_RATIO, -27.15f / PTM_RATIO),
		b2Vec2(13.8f / PTM_RATIO, 23.05f / PTM_RATIO),
		b2Vec2(-3.35f / PTM_RATIO, 35.25f / PTM_RATIO),
		b2Vec2(-16.25f / PTM_RATIO, 25.55f / PTM_RATIO),
		b2Vec2(-15.55f / PTM_RATIO, -23.95f / PTM_RATIO)
	};

	spriteShape.Set(verts, 7);

	fixtureDef.shape = &spriteShape;
	fixtureDef.density = 30.0f;
	fixtureDef.filter.categoryBits = 0x01;
	fixtureDef.filter.maskBits = 0x01;

	body->CreateFixture(&fixtureDef);
	return body;
}

void HelloWorld::createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body* bodyB, b2Vec2 anchorB, float32 sag) {
	b2RopeJointDef jd;
	jd.bodyA = bodyA;
	jd.bodyB = bodyB;
	jd.localAnchorA = anchorA;
	jd.localAnchorB = anchorB;

	float32 ropeLength = (bodyA->GetWorldPoint(anchorA) - bodyB->GetWorldPoint(anchorB)).Length()*sag;
	jd.maxLength = ropeLength;

	b2RopeJoint* ropeJoint = (b2RopeJoint*)_world->CreateJoint(&jd);

	VRope* newRope = new VRope(ropeJoint, ropeSpriteSheet);

	ropes->push_back(newRope);
}

bool HelloWorld::checkLineIntersection(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4) {
	float denominator = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);

	if (denominator == 0.0f) {
		return false;
	}
	float ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / denominator;
	float ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denominator;

	if (ua >= 0.0 && ua <= 1.0 && ub>= 0.0 && ub <= 1.0) {
		return true;
	}
	return false;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event * event) {
	
	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event * event) {
	Vec2 pt0 = touch->getPreviousLocation();
	Vec2 pt1 = touch->getLocation();

	std::vector<VRope *>::iterator rope;

	for (rope = ropes->begin(); rope != ropes->end(); ++rope) {
		std::vector<VStick *>::iterator stick;
		for (stick = (*rope)->getSticks().begin(); stick != (*rope)->getSticks().end(); ++stick) {
			Vec2 pa = (*stick)->getPointA()->point();
			Vec2 pb = (*stick)->getPointB()->point();
			if (this->checkLineIntersection(pt0, pt1, pa, pb)) {
				b2Body *newBodyA = createRopeTipBody();
				b2Body *newBodyB = createRopeTipBody();

				VRope *newRope = (*rope)->cutRopeInStick((*stick), newBodyA, newBodyB);
				ropes->push_back(newRope);

				return;
			}
		}
	}
}

b2Body* HelloWorld::createRopeTipBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.5f;
	b2Body *bodys = _world->CreateBody(&bodyDef);

	b2FixtureDef circleDef;
	b2CircleShape circle;
	circle.m_radius = 1.0f / PTM_RATIO;
	circleDef.shape = &circle;
	circleDef.density = 10.0f;

	circleDef.filter.maskBits = 0;
	bodys->CreateFixture(&circleDef);

	return bodys;
}