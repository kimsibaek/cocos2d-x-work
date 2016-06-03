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
	this->createBackgroundParallax();
	this->createDragon();
    return true;
}

void HelloWorld::createBackgroundParallax() {
	auto background1 = Sprite::create("Images/background1.png");
	background1->setAnchorPoint(Vec2(0, 0));

	auto background2 = Sprite::create("Images/background2.png");
	background2->setAnchorPoint(Vec2(0, 0));

	background1->getTexture()->setAliasTexParameters();
	background2->getTexture()->setAliasTexParameters();

	auto voidNode = ParallaxNode::create();
	
	//ParallaxNode->addChild(이미지, 이미지순서, 속도, 위치)
	voidNode->addChild(background1, 1, Vec2(1.0f, 0.0f), Vec2(-512, 0));
	voidNode->addChild(background2, 1, Vec2(1.0f, 0.0f), Vec2(0, 0));
	//voidNode->setPosition(Vec2(512, 0));
	auto go = MoveBy::create(4, Vec2(512, 0));
	auto goBack = Place::create(Vec2(0, 0));
	auto seq = Sequence::create(go, goBack, nullptr);
	auto act = RepeatForever::create(seq);

	voidNode->runAction(act);

	this->addChild(voidNode);
}

void HelloWorld::createDragon() {
	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/dragon_animation.png");
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 6; i++) {
		int index = i % 4;
		int rowIndex = i / 4;

		animation->addSpriteFrameWithTexture(texture, Rect(index*130, rowIndex*140, 130, 140));
	}



	auto dragon = Sprite::createWithTexture(texture, Rect(0, 0, 130, 140));
	dragon->setPosition(Vec2(240, 160));
	this->addChild(dragon);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	dragon->runAction(rep);
}
