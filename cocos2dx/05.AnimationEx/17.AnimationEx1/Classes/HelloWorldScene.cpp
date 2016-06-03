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
	auto pMan = Sprite::create("Images/grossini_dance_01.png");
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	animation->addSpriteFrameWithFile("Images/grossini_dance_01.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_02.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_03.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_04.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_05.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_06.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_07.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_08.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_09.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_10.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_11.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_12.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_13.png");
	animation->addSpriteFrameWithFile("Images/grossini_dance_14.png");

	auto animate = Animate::create(animation);

	pMan->runAction(animate);

	auto rep = RepeatForever::create(animate);
	pMan->runAction(rep);
    return true;
}

