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
	auto pMenuItem1 = MenuItemFont::create("Menu-1", CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));
	auto pMenuItem2 = MenuItemFont::create("Menu-2", CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));
	auto pMenuItem3 = MenuItemFont::create("Menu-3", CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem3->setColor(Color3B(0, 0, 0));
	pMenuItem1->setTag(1);
	pMenuItem2->setTag(2);
	pMenuItem3->setTag(3);
	
	auto pMenuItem4 = MenuItemFont::create("Menu-4", CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem4->setColor(Color3B(0, 0, 0));
	auto pMenuItem5 = MenuItemFont::create("Menu-5", CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem5->setColor(Color3B(0, 0, 0));
	pMenuItem4->setTag(4);
	pMenuItem5->setTag(5);

	auto pMenu2 = Menu::create(pMenuItem4, pMenuItem5, nullptr);
	pMenu2->setPosition(200, 100);
	pMenu2->alignItemsHorizontally();;
	this->addChild(pMenu2);

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);
	pMenu->alignItemsHorizontally();;
	this->addChild(pMenu);

    return true;
}

void HelloWorld::doClick(Ref *pSender) {
	auto tItem = (MenuItem *)pSender;

	int i = tItem->getTag();

	log("%d번째 메뉴가 선택되었습니다.", i);

}