﻿#include "HelloWorldScene.h"

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

	bSelect = false;

    return true;
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void HelloWorld::onExit() {
	_eventDispatcher->removeAllEventListeners();
	Layer::onExit();
}
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	//log("onTouchBegan id = %d, x=%f, y=%f", touch->getID(), touchPoint.x, touchPoint.y);
	
	bSelect = pMan->getBoundingBox().containsPoint(touchPoint);
	return true;
}
void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (bSelect) {
		Vec2 oldPoint = touch->getPreviousLocation();
		Vec2 nowPoint = touch->getLocation();

		Vec2 firstVector = oldPoint - pMan->getPosition();
		float firstRotateAngle = -firstVector.getAngle();
		float previousTouch = CC_RADIANS_TO_DEGREES(firstRotateAngle);

		Vec2 secondVector = nowPoint - pMan->getPosition();
		float secondRotateAngle = -secondVector.getAngle();
		float currentTouch = CC_RADIANS_TO_DEGREES(secondRotateAngle);

		gRotation += currentTouch - previousTouch;
		gRotation = fmod(gRotation, 360.0f);

		pMan->setRotation(gRotation);
	}
	//log("onTouchMoved id = %d, x=%f, y=%f", touch->getID(), touchPoint.x, touchPoint.y);
}
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	bSelect = false;
}