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
	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);
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
void HelloWorld::onTouchesBegan(const std::vector < cocos2d::Touch*>& touches, cocos2d::Event* event) {
	auto touch = touches[0];
	auto touchPoint = touch->getLocation();

	touchPoint = this->convertToWorldSpace(touchPoint);


	log("onTouchBegan id = %d, x=%f, y=%f", touch->getID(), touchPoint.x, touchPoint.y);


	//touch check------------------------------------------------------
	bool bTouch = pMan->getBoundingBox().containsPoint(touchPoint);
	if (bTouch) {
		log("Sprite clicked...");
	}

	/*
	for(auto &item : touches){
		auto touch = item;
		auto touchPoint = touch->getLocation();

		log("onTouchBegan id = %d, x=%f, y=%f", touch->getID(), touchPoint.x, touchPoint.y);
	}
	*/
}
void HelloWorld::onTouchesMoved(const std::vector < cocos2d::Touch*>& touches, cocos2d::Event* event) {
	auto touch = touches[0];
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToWorldSpace(touchPoint);

	log("onTouchMoved id = %d, x=%f, y=%f", touch->getID(), touchPoint.x, touchPoint.y);
	
	/*
	for(auto &item : touches){
	auto touch = item;
	auto touchPoint = touch->getLocation();

	log("onTouchMoved id = %d, x=%f, y=%f", touch->getID(), touchPoint.x, touchPoint.y);
	}
	*/
}
void HelloWorld::onTouchesEnded(const std::vector < cocos2d::Touch*>& touches, cocos2d::Event* event) {
	auto touch = touches[0];
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToWorldSpace(touchPoint);
	log("onTouchEnded id = %d, x=%f, y=%f", touch->getID(), touchPoint.x, touchPoint.y);
	/*
	for(auto &item : touches){
	auto touch = item;
	auto touchPoint = touch->getLocation();

	log("onTouchEnded id = %d, x=%f, y=%f", touch->getID(), touchPoint.x, touchPoint.y);
	}
	*/
}
void HelloWorld::onTouchesCancelled(const std::vector < cocos2d::Touch*>& touches, cocos2d::Event* event) {
	onTouchesEnded(touches, event);
}