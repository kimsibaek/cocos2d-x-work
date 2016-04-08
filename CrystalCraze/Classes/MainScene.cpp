#include "MainScene.h"
#include "GameScene.h"
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
	int score = UserDefault::getInstance()->getIntegerForKey("int_key");
	log("int is %d", score);
	char png[25];
	sprintf(png, "%d", score);
	log("%s", png);
	auto pLabel3 = Label::createWithCharMap("fonts/scorefont.png", 26, 35, '6');
	pLabel3->setString(png);
	pLabel3->setPosition(Vec2(winSize.width/2, 30));
	this->addChild(pLabel3);

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
}