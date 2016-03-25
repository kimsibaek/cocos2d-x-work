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
	pMenuItem1->setTag(1);
	pMenuItem2->setTag(2);
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	pMenu->alignItemsVertically();;
	this->addChild(pMenu);
    return true;
}

void HelloWorld::doClick(Ref *pSender) {
	auto tItem = (MenuItem *)pSender;

	int i = tItem->getTag();

	if (i==1) {
		auto pMan = Sprite::create("Images/grossini.png");
		pMan->setPosition(Vec2(100, 160));
		pMan->setTag(11);
		this->addChild(pMan);
	}
	else {
		auto pMan = (Sprite *)getChildByTag(11);
		this->removeChild(pMan, true);
	}
	log("%d번째 메뉴가 선택되었습니다.", i);

}