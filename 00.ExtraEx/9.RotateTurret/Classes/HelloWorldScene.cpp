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

	player = Sprite::create("Images/turret.png");
	player->setPosition(Vec2(player->getContentSize().width/2+80, winSize.height/2));
	this->addChild(player);

	projectiles.clear();

	bProjectile = false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	//auto touchPoint = touch->getLocation();
	if (bProjectile) {
		return true;
	}
	else {
		bProjectile = true;
	}
	auto touchPoint = touch->getLocation();

	auto nextProjectile = Sprite::create("Images/bullet2.png");

	Vec2 shootVector = touchPoint - player->getPosition();
	float shootAngle = shootVector.getAngle();
	float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);

	float curAngle = player->getRotation();
	float rotateDiff = cocosAngle - curAngle;
	if (rotateDiff > 180)
		rotateDiff -= 360;
	if (rotateDiff < -180)
		rotateDiff += 360;
	float rotateSpeed = 0.5f / 180;
	float rotateDuration = fabsf(rotateDiff * rotateSpeed);

	auto actRotate1 = RotateTo::create(rotateDuration, cocosAngle);
	auto seqAct1 = Sequence::create(actRotate1, CallFunc::create(CC_CALLBACK_0(HelloWorld::finishRotate, this, nextProjectile)), nullptr);
	player->runAction(seqAct1);

	shootVector.normalize();
	Vec2 overshotVector = shootVector * 420;

	nextProjectile->setRotation(cocosAngle);

	auto actMove2 = MoveBy::create(1.0f, overshotVector);
	auto seqAct2 = Sequence::create(actMove2, CallFunc::create(CC_CALLBACK_0(HelloWorld::spriteMoveFinished, this, nextProjectile)), nullptr);
	
	nextProjectile->runAction(seqAct2);
	return true;
}

void HelloWorld::finishRotate(Ref* sender) {
	Sprite* sprite = (Sprite*)sender;

	Vec2 nPos1 = Vec2(player->getContentSize().width, player->getContentSize().height / 2);
	Vec2 nPos2 = player->convertToWorldSpace(nPos1);

	sprite->setPosition(nPos2);

	this->addChild(sprite);

	projectiles.pushBack(sprite);

	bProjectile = false;
}
void HelloWorld::spriteMoveFinished(Ref* sender) {
	Sprite* sprite = (Sprite *)sender;
	this->removeChild(sprite, true);
	projectiles.eraseObject(sprite);
}