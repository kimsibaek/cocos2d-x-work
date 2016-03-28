﻿#include "TestScene2.h"

USING_NS_CC;
int num2 = 0;

Scene* TestScene2::createScene()
{
    auto scene = Scene::create();
    auto layer = TestScene2::create();
    scene->addChild(layer);
    return scene;
}

bool TestScene2::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 255, 0, 255) ))
    {
        return false;
    }
	auto item1 = MenuItemFont::create("Close Scene2", CC_CALLBACK_1(TestScene2::doClose, this));
	item1->setColor(Color3B(0, 0, 0));
	auto pMenu = Menu::create(item1, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);
    return true;
}

void TestScene2::doClose(Ref* pSender) {
	Director::getInstance()->popScene();
}
