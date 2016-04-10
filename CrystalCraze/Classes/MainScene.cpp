#include "MainScene.h"
#include "GameScene.h"
#include "stdafx.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

//android effect only support ogg
#define EFFECT_FILE		"sounds/click.wav"
#define MUSIC_FILE		"sounds/loop.mp3"

using namespace cocos2d;
using namespace CocosDenshion;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init())
    {
        return false;
    }
	winSize = Director::getInstance()->getWinSize();

	auto pSprite = Sprite::create("Images/background.png");
	pSprite->setPosition(winSize.width / 2, winSize.height / 2);
	pSprite->setScale(0.5);
	pSprite->setZOrder(0);
	this->addChild(pSprite);

	//auto pSprite1 = Sprite::create("Images/about-bg.png");
	//pSprite1->setPosition(winSize.width / 2, winSize.height / 2);
	//pSprite1->setScale(0.65);
	//this->addChild(pSprite1);

	auto pSprite2 = Sprite::create("Images/logo.png");
	pSprite2->setPosition(winSize.width / 2, winSize.height*2 / 3);
	pSprite2->setScale(0.55);
	pSprite2->setZOrder(1);
	this->addChild(pSprite2);

	auto pMenuItem1 = MenuItemImage::create("Images/btn-play.png", "Images/btn-play-down.png", CC_CALLBACK_1(MainScene::onPressPlay, this));
	pMenuItem1->setScale(0.42);

	auto pMenuItem2 = MenuItemImage::create("Images/btn-about1.png", "Images/btn-about-down1.png", CC_CALLBACK_1(MainScene::onPressAbout, this));
	pMenuItem2->setScale(0.6);
	//auto pMenuItem3 = MenuItemImage::create("Images/btn-done.png", "Images/btn-done-down.png", CC_CALLBACK_1(MainScene::doClick3, this));
	
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	pMenu->setPosition(winSize.width / 2, winSize.height * 1 / 3  -20);
	pMenu->alignItemsVertically();
	pMenu->setZOrder(1);
	this->addChild(pMenu);
	
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FILE);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);

	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_FILE);
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);

	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);


	this->schedule(schedule_selector(MainScene::onUpdate), 0.4f);

	//UserDefault::getInstance()->setIntegerForKey("int_key", 10);
	gLastScore = UserDefault::getInstance()->getIntegerForKey("int_key");
	log("int is %d", gLastScore);
	char png[25];
	sprintf(png, "%d", gLastScore);
	log("%s", png);

	auto label = Label::createWithBMFont("fonts/scorefont.fnt", png, TextHAlignment::CENTER, 10);
	label->setScale(0.5f);
	label->setPosition(Vec2(winSize.width / 2, 30));
	this->addChild(label);

	auto pLabel = LabelTTF::create("HIGH SCORE", "fonts1/Paint Boy.ttf", 10);
	//레이블의 위치 지정
	pLabel->setPosition(Vec2(winSize.width / 2, 20));
	//레이블의 색 지정
	pLabel->setColor(Color3B::WHITE);
	//레이블의 투명도 지정
	//pLabel->setOpacity(100.0);
	//레이어에 레이블 객체 추가
	this->addChild(pLabel);


    return true;
}

void MainScene::onPressPlay(Ref *pSender) {
	auto pScene = GameScene::createScene();
	Director::getInstance()->replaceScene(pScene);
	m_nSoundId = SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE);
}
void MainScene::onPressAbout(Ref *pSender) {
	m_nSoundId = SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE);
}

void MainScene::onUpdate(float f) {
	int randomNum = rand() % 5;
	int randomPosition = rand() % 320;
	int randomScale = rand() % 5 + 2;
	char png[25];
	sprintf(png, "Images/%d.png", randomNum);

	auto pSprite = Sprite::create(png);
	float x = randomPosition * winSize.width / 320;
	float y = winSize.height;
	float scale = randomScale;
	float speed = 3 * scale / 5;
	pSprite->setPosition(x, y);
	pSprite->setScale(1/scale);
	pSprite->setZOrder(0.5);
	this->addChild(pSprite);
	
	auto myAction = MoveTo::create(speed, Vec2(x, -20));
	pSprite->runAction(myAction);

	int randomNum1 = rand() % 5;
	int randomPosition1 = rand() % 320;
	int randomPosition2 = rand() % 480;
	int randomScale1 = rand() % 5 + 2;
	float x1 = randomPosition1 * winSize.width / 320;
	float y1 = randomPosition2 * winSize.height / 480;
	auto pSprite1 = Sprite::create("Images/p1.png");
	pSprite1->setPosition(x1, y1);
	pSprite1->setScale(1+(randomScale1/7));
	pSprite1->setZOrder(0.5);
	this->addChild(pSprite1);
	int randomPosition3 = rand() % 50 + 10;
	int randomPosition4 = rand() % 50 + 10;
	int PM = rand() % 2;
	int PM2 = rand() % 2;
	if (PM == 1) {
		randomPosition3 = -randomPosition3;
	}
	else if(PM2 == 1){
		randomPosition4 = -randomPosition4;
	}
	auto myAction3 = MoveBy::create(7, Vec2(randomPosition3, randomPosition4));
	auto myAction1 = FadeOut::create(7.0f);
	auto myAction2 = Spawn::create(myAction3, myAction1, nullptr);
	pSprite1->runAction(myAction2);
}