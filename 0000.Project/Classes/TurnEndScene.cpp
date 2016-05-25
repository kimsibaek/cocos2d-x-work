#include "TurnEndScene.h"
USING_NS_CC;

Scene* TurnEndScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TurnEndScene::create();
	scene->addChild(layer);
	return scene;
}

bool TurnEndScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	auto popLayer = CCLayerColor::create(Color4B(255, 255, 255, 0), 772, 268);
	popLayer->setAnchorPoint(Vec2(0, 0));
	popLayer->setPosition(Vec2((winSize.width - popLayer->getContentSize().width) / 2, (winSize.height - popLayer->getContentSize().height) / 2));

	this->addChild(popLayer);

	MenuItemFont::setFontSize(32.0f);
	
	Sprite *BG;
	BG = Sprite::create("Images/Scene/TexScene2.png");
	BG->setAnchorPoint(Vec2(0, 0));
	BG->setScale(2.0f);
	BG->setPosition(Vec2((winSize.width - popLayer->getContentSize().width) / 2, (winSize.height - popLayer->getContentSize().height) / 2));
	this->addChild(BG, 1);

	auto pMenuItem = MenuItemFont::create("턴을 종료하시겠습니까?");
	pMenuItem->setColor(Color3B(0, 0, 0));
	pMenuItem->setPosition(Vec2(200, 80));
	BG->addChild(pMenuItem, 2);

	auto pMenuItem1 = MenuItemFont::create("예", CC_CALLBACK_1(TurnEndScene::doContinue, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));
	auto pMenuItem2 = MenuItemFont::create("아니오", CC_CALLBACK_1(TurnEndScene::doClose, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	pMenu->alignItemsHorizontallyWithPadding(20.0f);
	pMenu->setPosition(Vec2(200, 25));
	BG->addChild(pMenu, 2);


	std::string str1 = "0";
	char str2[20] = { 0 };
	sprintf(str2, "%s", str1.c_str());
	NotificationCenter::getInstance()->postNotification("TouchTurnEnd", (Ref*)str2);

	return true;
}
void TurnEndScene::doContinue(Ref* pSender) {
	std::string str1 = "1";
	char str2[20] = { 0 };
	sprintf(str2, "%s", str1.c_str());
	NotificationCenter::getInstance()->postNotification("TouchTurnEnd", (Ref*)str2);
	this->removeFromParentAndCleanup(true);
}
void TurnEndScene::doSendMsg(Ref* pSender) {
	//option Scene
}
void TurnEndScene::doClose(Ref* pSender) {
	
	std::string str1 = "2";
	char str2[20] = { 0 };
	sprintf(str2, "%s", str1.c_str());
	NotificationCenter::getInstance()->postNotification("TouchTurnEnd", (Ref*)str2);

	this->removeFromParentAndCleanup(true);

}