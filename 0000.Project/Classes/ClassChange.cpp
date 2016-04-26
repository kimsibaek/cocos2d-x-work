#include "ClassChange.h"
#include "MainScene.h"
USING_NS_CC;

Scene* ClassChange::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ClassChange::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ClassChange::init()
{
	if (!Layer::init())
	{
		return false;
	}
	////////////////////
	CCSprite* title = CCSprite::create("Images/Scene/ClassChangeMap.png");
	title->setPosition(Vec2(640, 360));
	this->addChild(title);

	auto pMenuItem1 = MenuItemImage::create("Images/Scene/Back.png", "Images/Scene/Back_click.png", CC_CALLBACK_1(ClassChange::doClick1, this));
	pMenuItem1->setPosition(Vec2(1230, 670));
	pMenuItem1->setScale(0.2);
	pMenuItem1->setTag(1);
	//auto pMenuItem7 = MenuItemImage::create("Images/Scene/Exit.png", "Images/Scene/Exit_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	auto pMenu = Menu::create(pMenuItem1, nullptr);
	pMenu->setPosition(Vec2(0, 0));
	this->addChild(pMenu);

	return true;
}

void ClassChange::doClick1(Ref *pSender) {
	auto tItem = (MenuItem *)pSender;

	int i = tItem->getTag();
	log("%d번째 메뉴가 선택되었습니다.", i);
	if (i == 1) {
		auto pScene = MainScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	
}