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

	auto pMenuItem = MenuItemImage::create("Images/btn-play-normal.png", "Images/btn-play-selected.png", CC_CALLBACK_1(HelloWorld::menuSelect, this));
	pMenuItem->setPosition(Vec2(100, 100));

	auto pMenu = Menu::create(pMenuItem, nullptr);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);

    return true;
}

void HelloWorld::menuSelect(Ref *pSender) {
	log("메뉴가 선택되었습니다.");
}