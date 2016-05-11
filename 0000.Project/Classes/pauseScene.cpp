#include "pauseScene.h"
#include "MainScene.h"
#include "sqlite3.h"
USING_NS_CC;

Scene* pauseScene::createScene()
{
	auto scene = Scene::create();
	auto layer = pauseScene::create();
	scene->addChild(layer);
	return scene;
}

bool pauseScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	auto popLayer = CCLayerColor::create(Color4B(0, 0, 0, 100), 600, 400);
	popLayer->setAnchorPoint(Vec2(0, 0));
	popLayer->setPosition(Vec2((winSize.width - popLayer->getContentSize().width) / 2, (winSize.height - popLayer->getContentSize().height) / 2));

	this->addChild(popLayer);

	MenuItemFont::setFontSize(14.0f);
	
	auto pMenuItem1 = MenuItemImage::create("Images/Scene/pause_button1.png", "Images/Scene/pause_button1.png", CC_CALLBACK_1(pauseScene::doContinue, this));
	//pMenuItem1->setPosition(Vec2(100, 660));
	pMenuItem1->setScale(2);
	pMenuItem1->setTag(1);
	auto pMenuItem2 = MenuItemImage::create("Images/Scene/pause_button2.png", "Images/Scene/pause_button2.png", CC_CALLBACK_1(pauseScene::doClose, this));
	//pMenuItem2->setPosition(Vec2(1200, 650));
	pMenuItem2->setScale(2);
	pMenuItem2->setTag(2);
	auto pMenuItem3 = MenuItemImage::create("Images/Scene/pause_button3.png", "Images/Scene/pause_button3.png", CC_CALLBACK_1(pauseScene::doSendMsg, this));
	//pMenuItem3->setPosition(Vec2(1200, 650));
	pMenuItem3->setScale(2);
	pMenuItem3->setTag(3);
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);
	pMenu->alignItemsVerticallyWithPadding(20.0f);
	pMenu->setPosition(Vec2(300, 200));
	popLayer->addChild(pMenu, 4);



	std::string str1 = "0";
	char str2[20] = { 0 };
	sprintf(str2, "%s", str1.c_str());
	NotificationCenter::getInstance()->postNotification("TouchStatus", (Ref*)str2);

	return true;
}
void pauseScene::doContinue(Ref* pSender) {
	std::string str1 = "1";
	char str2[20] = { 0 };
	sprintf(str2, "%s", str1.c_str());
	NotificationCenter::getInstance()->postNotification("TouchStatus", (Ref*)str2);
	this->removeFromParentAndCleanup(true);
}
void pauseScene::doSendMsg(Ref* pSender) {
	//option Scene
}
void pauseScene::doClose(Ref* pSender) {
	
	std::string str1 = "2";
	char str2[20] = { 0 };
	sprintf(str2, "%s", str1.c_str());
	NotificationCenter::getInstance()->postNotification("TouchStatus", (Ref*)str2);

	this->removeFromParentAndCleanup(true);

}