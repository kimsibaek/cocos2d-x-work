#include "SecondScene.h"

USING_NS_CC;

Scene* SecondScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SecondScene::create();
    scene->addChild(layer);
    return scene;
}

bool SecondScene::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 100) ))
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();

	auto popLayer = CCLayerColor::create(Color4B(0, 255, 0, 255), 300, 200);
	popLayer->setAnchorPoint(Vec2(0, 0));
	popLayer->setPosition(Vec2((winSize.width - popLayer->getContentSize().width) / 2, (winSize.height - popLayer->getContentSize().height) / 2));
	
	this->addChild(popLayer);

	MenuItemFont::setFontSize(14.0f);
	auto pMenuItem1 = MenuItemFont::create("Notification Center Test", CC_CALLBACK_1(SecondScene::doSendMsg, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));

	auto pMenuItem2 = MenuItemFont::create("창닫기", CC_CALLBACK_1(SecondScene::doClose, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	pMenu->alignItemsVerticallyWithPadding(20.0f);
	pMenu->setPosition(Vec2(150, 100));
	popLayer->addChild(pMenu);

    return true;
}

void SecondScene::doSendMsg(Ref* pSender) {
	std::string str1 = "홍길동";
	char str2[20] = { 0 };
	sprintf(str2, "%s", str1.c_str());

	NotificationCenter::getInstance()->postNotification("TouchStatus", (Ref*)str2);
}
void SecondScene::doClose(Ref* pSender) {
	this->removeFromParentAndCleanup(true);
}