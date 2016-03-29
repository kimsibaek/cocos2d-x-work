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

	/*
	auto background1 = Sprite::create("Images/background1.png");
	background1->setAnchorPoint(Vec2(0, 0));

	auto background2 = Sprite::create("Images/background2.png");
	background2->setAnchorPoint(Vec2(0, 0));

	background1->getTexture()->setAliasTexParameters();
	background2->getTexture()->setAliasTexParameters();

	auto voidNode = ParallaxNode::create();
	//ParallaxNode->addChild(이미지, 이미지순서, 속도, 이동방향)
	voidNode->addChild(background1, 1, Vec2(1.0f, 0.0f), Vec2(0, 0));
	voidNode->addChild(background2, 1, Vec2(1.0f, 0.0f), Vec2(512, 0));

	auto go = MoveBy::create(4, Vec2(-512, 0));
	auto goBack = go->reverse();
	auto seq = Sequence::create(go, goBack, nullptr);
	auto act = RepeatForever::create(seq);

	voidNode->runAction(act);

	this->addChild(voidNode);
    */

	auto background1 = Sprite::create("Images/background1.png");
	background1->setPosition(Vec2(256, 160));
	this->addChild(background1);

	auto go = MoveBy::create(4, Vec2(-512, 0));
	auto goBack = go->reverse();
	auto seq = Sequence::create(go, goBack, nullptr);
	auto act = RepeatForever::create(seq);
	background1->runAction(act);
	
	auto background2 = Sprite::create("Images/background2.png");
	background2->setPosition(Vec2(768, 160));
	this->addChild(background2);

	auto go1 = MoveBy::create(4, Vec2(-512, 0));
	auto goBack1 = go1->reverse();
	auto seq1 = Sequence::create(go1, goBack1, nullptr);
	auto act1 = RepeatForever::create(seq1);
	background2->runAction(act1);
	return true;
}

