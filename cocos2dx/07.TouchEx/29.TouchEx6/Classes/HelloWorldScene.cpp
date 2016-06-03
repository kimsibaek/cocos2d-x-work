#include "HelloWorldScene.h"
#include "TouchPoint.h"
USING_NS_CC;

static Map<int, TouchPoint*> s_map;

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
    return true;
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchAllAtOnce::create();
	//listener->setSwallowTouches(true);

	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);
	Layer::onExit();
}


void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
	for (auto &item : touches)
	{
		auto touch = item;
		auto location = touch->getLocation();
		auto touchPoint = TouchPoint::touchPointWithParent(this, location, *s_TouchColors[touch->getID() % 5]);

		addChild(touchPoint);
		s_map.insert(touch->getID(), touchPoint);
	}
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
	for (auto &item : touches)
	{
		auto touch = item;
		auto pTP = s_map.at(touch->getID());
		auto location = touch->getLocation();

		removeChild(pTP, true);
		s_map.erase(touch->getID());

		auto touchPointNew = TouchPoint::touchPointWithParent(this, location, *s_TouchColors[touch->getID() % 5]);
		addChild(touchPointNew);
		s_map.insert(touch->getID(), touchPointNew);
	}
}

void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
	for (auto &item : touches)
	{
		auto touch = item;
		auto pTP = s_map.at(touch->getID());
		removeChild(pTP, true);
		s_map.erase(touch->getID());
	}
}