#include "pauseScene.h"
#include "MainScene.h"
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

	auto popLayer = CCLayerColor::create(Color4B(0, 255, 0, 255), 300, 200);
	popLayer->setAnchorPoint(Vec2(0, 0));
	popLayer->setPosition(Vec2((winSize.width - popLayer->getContentSize().width) / 2, (winSize.height - popLayer->getContentSize().height) / 2));

	this->addChild(popLayer);

	MenuItemFont::setFontSize(14.0f);
	

	auto pMenuItem1 = MenuItemFont::create("계속하기", CC_CALLBACK_1(pauseScene::doContinue, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));
	auto pMenuItem2 = MenuItemFont::create("옵션", CC_CALLBACK_1(pauseScene::doSendMsg, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));
	auto pMenuItem3 = MenuItemFont::create("나가기", CC_CALLBACK_1(pauseScene::doClose, this));
	pMenuItem3->setColor(Color3B(0, 0, 0));
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);
	pMenu->alignItemsVerticallyWithPadding(20.0f);
	pMenu->setPosition(Vec2(150, 100));
	popLayer->addChild(pMenu);


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