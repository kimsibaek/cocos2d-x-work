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

	this->createBackgroundParallax();

	this->createDragon();

	this->createArrowButtons();
    return true;
}


void HelloWorld::createBackgroundParallax() {
	auto background1 = Sprite::create("Images/background1.png");
	background1->setAnchorPoint(Vec2(0, 0));

	auto background2 = Sprite::create("Images/background2.png");
	background2->setAnchorPoint(Vec2(0, 0));

	//background1->getTexture()->setAliasTexParameters();
	//background2->getTexture()->setAliasTexParameters();

	auto voidNode = ParallaxNode::create();

	//ParallaxNode->addChild(이미지, 이미지순서, 속도, 위치)
	voidNode->addChild(background1, 1, Vec2(1.0f, 0.0f), Vec2(0, 0));
	voidNode->addChild(background2, 1, Vec2(1.0f, 0.0f), Vec2(512, 0));
	//voidNode->setPosition(Vec2(512, 0));
	
	voidNode->setTag(1);

	this->addChild(voidNode, 0);
}

void HelloWorld::createDragon() {
	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/dragon_animation.png");
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 6; i++) {
		int index = i % 4;
		int rowIndex = i / 4;

		animation->addSpriteFrameWithTexture(texture, Rect(index * 130, rowIndex * 140, 130, 140));
	}



	auto dragon = Sprite::createWithTexture(texture, Rect(0, 0, 130, 140));
	dragon->setPosition(Vec2(240, 160));
	this->addChild(dragon);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	dragon->runAction(rep);
}

void HelloWorld::createArrowButtons() {
	leftSprite = Sprite::create("Images/b1.png");
	leftSprite->setPosition(Vec2(180, 30));

	this->addChild(leftSprite, 2);

	leftPressedSprite = Sprite::create("Images/b2.png");
	leftPressedSprite->setPosition(leftSprite->getPosition());
	this->addChild(leftPressedSprite, 1);

	rightSprite = Sprite::create("Images/f1.png");
	rightSprite->setPosition(Vec2(300, 30));

	this->addChild(rightSprite, 2);

	rightPressedSprite = Sprite::create("Images/f2.png");
	rightPressedSprite->setPosition(rightSprite->getPosition());
	this->addChild(rightPressedSprite, 1);

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
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}

#pragma mark -
#pragma mark Touch Event Handling

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	isLeftPressed = false;
	isRightPressed = false;

	if (this->isTouchInside(leftSprite, touch) == true) {
		leftSprite->setVisible(false);
		isLeftPressed = true;
	}
	else if (this->isTouchInside(rightSprite, touch) == true) {
		rightSprite->setVisible(false);
		isRightPressed = true;
	}

	if (isLeftPressed == true || isRightPressed == true) {
		this->startMovingBackground();
	}
	return true;
}
void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (isLeftPressed == true && this->isTouchInside(leftSprite, touch) == false) {
		leftSprite->setVisible(true);
		this->stopMovingBackground();
	}
	else if (isRightPressed == true && this->isTouchInside(rightSprite, touch) == false) {
		rightSprite->setVisible(true);
		this->stopMovingBackground();
	}
}
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (isLeftPressed == true || isRightPressed == true) {
		this->stopMovingBackground();
	}
	if (isLeftPressed == true) {
		leftSprite->setVisible(true);
	}
	if (isRightPressed == true) {
		rightSprite->setVisible(true);
	}
}

#pragma mark -
#pragma mark Game Play

bool HelloWorld::isTouchInside(cocos2d::Sprite* sprite, cocos2d::Touch* touch) {
	auto touchPoint = touch->getLocation();

	bool bTouch = sprite->getBoundingBox().containsPoint(touchPoint);
	return bTouch;
}
void HelloWorld::startMovingBackground() {
	log("start moving");
}
void HelloWorld::stopMovingBackground() {
	log("stop moving");
}
void HelloWorld::moveBackground(float t) {
	log("moving background...");
}