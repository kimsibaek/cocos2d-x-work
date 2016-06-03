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

	auto cocosImage = Sprite::create("Images/powered.png");
	cocosImage->setAnchorPoint(Vec2(0, 0));

	auto background = Sprite::create("Images/background.png");
	background->setAnchorPoint(Vec2(0, 0));

	auto gubun1 = LabelTTF::create("Start", "Arial", 64);
	gubun1->setPosition(Vec2(0, 240));
	gubun1->setAnchorPoint(Vec2(0.0f, 0.5f));

	auto gubun2 = LabelTTF::create("End", "Arial", 64);
	gubun2->setPosition(Vec2(640, 240));
	gubun2->setAnchorPoint(Vec2(1.0f, 0.5f));

	auto gubun3 = LabelTTF::create("80 Pixel", "Arial", 24);
	gubun3->setPosition(Vec2(80, 240));
	gubun3->setAnchorPoint(Vec2(0.0f, 0.5f));


	auto voidNode = ParallaxNode::create();
	//ParallaxNode->addChild(이미지, 이미지순서, 속도, 이동방향)
	voidNode->addChild(background, 1, Vec2(1.0f, 1.0f), Vec2(0, -160));
	voidNode->addChild(cocosImage, 2, Vec2(2.0f, 0.0f), Vec2(240, 0));

	auto go = MoveBy::create(4, Vec2(-160, 0));
	auto goBack = go->reverse();
	auto seq = Sequence::create(go, goBack, nullptr);
	auto act = RepeatForever::create(seq);

	voidNode->runAction(act);

	background->addChild(gubun1);
	background->addChild(gubun2);


	cocosImage->addChild(gubun3);

	this->addChild(voidNode);
    return true;
}

