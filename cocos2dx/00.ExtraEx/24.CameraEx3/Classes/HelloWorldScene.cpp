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

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::changeCameraAngle, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto bgSprite = Sprite::create("Images/Hello.png");
	bgSprite->setPosition(Vec2(240, 160));
	this->addChild(bgSprite);

	camera = new ActionCamera;
	camera->startWithTarget(this);
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	
	return true;
}
void HelloWorld::changeCameraAngle(cocos2d::Touch* touch, cocos2d::Event* event) {
	kmVec3 eye = camera->getEye();
	eye.x -= touch->getDelta().x * 0.00000001;
	eye.y -= touch->getDelta().y * 0.00000001;
	camera->setEye(eye);
}
