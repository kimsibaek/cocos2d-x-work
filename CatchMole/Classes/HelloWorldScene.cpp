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
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
	{
		return false;
	}
	CCSprite* grass_upper = CCSprite::create("Images/grass_upper.png");
	grass_upper->setPosition(Vec2(240, 240));
	grass_upper->getTexture()->setAliasTexParameters();
	this->addChild(grass_upper);

	pMan1 = Sprite::create("Images/mole_1.png");
	pMan1->setPosition(Vec2(95, 90));

	this->addChild(pMan1);

	pMan2 = Sprite::create("Images/mole_1.png");
	pMan2->setPosition(Vec2(240, 90));
	this->addChild(pMan2);

	pMan3 = Sprite::create("Images/mole_1.png");
	pMan3->setPosition(Vec2(385, 90));
	this->addChild(pMan3);

	CCSprite* grass_lower = CCSprite::create("Images/grass_lower.png");
	grass_lower->setPosition(Vec2(240, 80));
	grass_lower->getTexture()->setAliasTexParameters();
	this->addChild(grass_lower);
	//doStart(this);
	this->schedule(schedule_selector(HelloWorld::doAction1));
    return true;
}


void HelloWorld::doAction1(float f) {
	auto myAction = MoveBy::create(0.1, Vec2(0, 90));
	auto myAction1 = MoveBy::create(0.1, Vec2(0, -90));
	auto myAction2 = Sequence::create(myAction, DelayTime::create(0.3), myAction1, nullptr);
	auto rep1 = RepeatForever::create(myAction2);
	pMan1->runAction(myAction2);
}

void HelloWorld::doAction2(float f) {
	auto myAction3 = MoveBy::create(0.1, Vec2(0, 90));
	auto myAction4 = MoveBy::create(0.1, Vec2(0, -90));
	auto myAction5 = Sequence::create(myAction3, DelayTime::create(0.3), myAction4, nullptr);
	auto rep2 = RepeatForever::create(myAction5);
	pMan2->runAction(myAction5);
}

void HelloWorld::doAction3(float f) {
	auto myAction6 = MoveBy::create(0.1, Vec2(0, 90));
	auto myAction7 = MoveBy::create(0.1, Vec2(0, -90));
	auto myAction8 = Sequence::create(myAction6, DelayTime::create(0.3), myAction7, nullptr);
	auto rep3 = RepeatForever::create(myAction8);
	pMan3->runAction(myAction8);
}