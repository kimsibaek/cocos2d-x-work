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

	m_pStreak = MotionStreak::create(1.0f, 1.0f, 10.0f, Color3B::GREEN, "Images/streak.png");
	this->addChild(m_pStreak);
    return true;
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}


bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	m_pStreak->reset();

	auto touchPoint = touch->getLocation();

	m_pStreak->setPosition(touchPoint);

	return true;
}
void HelloWorld::onTouchMoved(Touch* touch, Event* event) {
	auto touchPoint = touch->getLocation();
	m_pStreak->setPosition(touchPoint);
}