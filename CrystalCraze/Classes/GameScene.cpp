#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init())
    {
        return false;
    }
	winSize = Director::getInstance()->getWinSize();

	auto pSprite = Sprite::create("Images/about-fade.png");
	pSprite->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(pSprite);

	auto pSprite1 = Sprite::create("Images/about-bg.png");
	pSprite1->setPosition(winSize.width / 2, winSize.height / 2);
	pSprite1->setScale(0.65);
	this->addChild(pSprite1);

	auto pSprite2 = Sprite::create("Images/logo.png");
	pSprite2->setPosition(winSize.width / 2, winSize.height*2 / 3);
	pSprite2->setScale(0.55);
	this->addChild(pSprite2);

	auto pMenuItem1 = MenuItemImage::create("Images/btn-play1.png", "Images/btn-play-down1.png", CC_CALLBACK_1(GameScene::onPressPlay, this));
	pMenuItem1->setScale(0.6);
	auto pMenuItem2 = MenuItemImage::create("Images/btn-about1.png", "Images/btn-about-down1.png", CC_CALLBACK_1(GameScene::onPressAbout, this));
	pMenuItem2->setScale(0.6);
	//auto pMenuItem3 = MenuItemImage::create("Images/btn-done.png", "Images/btn-done-down.png", CC_CALLBACK_1(GameScene::doClick3, this));
	
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	pMenu->setPosition(winSize.width / 2, winSize.height * 1 / 3);
	pMenu->alignItemsVertically();
	this->addChild(pMenu);
	
	// Setup callback for completed animations
	//this.rootNode.animationManager.setCompletedAnimationCallback(this, this.onAnimationComplete);
	//this.lblLastScore.setString("" + gLastScore);

	//// Setup falling gems
	//this.fallingGems = [];

	//// Schedule callback
	//this.rootNode.onUpdate = function(dt) {
	//	this.controller.onUpdate();
	//};
	//this.rootNode.schedule(this.rootNode.onUpdate);

	//// Load sprite sheets
	//cc.SpriteFrameCache.getInstance().addSpriteFrames("crystals.plist");

	//// Setup sound
	//gAudioEngine = cc.AudioEngine.getInstance();
	//gAudioEngine.playMusic("sounds/loop.mp3");

    return true;
}

void GameScene::onPressPlay(Ref *pSender) {

}
void GameScene::onPressAbout(Ref *pSender) {

}
