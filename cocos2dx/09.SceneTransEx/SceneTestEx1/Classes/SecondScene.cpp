#include "SecondScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFOAM_ANDROID)
#define EFFECT_FILE		"Sounds/effect2.ogg"
#elif (CC_TARGET_PLATFORM == CC_PLATFOAM_MARMALADE)
#define EFFECT_FILE		"Sounds/effect1.raw"
#else
#define EFFECT_FILE		"Sounds/effect1.wav"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFOAM_WIN32)
#define MUSIC_FILE		"Sounds/music.mid"
#elif (CC_TARGET_PLATFORM == CC_PLATFOAM_BLACKBERRY)
#define MUSIC_FILE		"Sounds/background.oggw"
#else
#define MUSIC_FILE		"Sounds/background.mp3"
#endif

using namespace cocos2d;
using namespace CocosDenshion;

Scene* SecondScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SecondScene::create();
    scene->addChild(layer);
    return scene;
}

bool SecondScene::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 255, 0, 255) ))
    {
        return false;
    }
	auto item2 = MenuItemFont::create("Play Sound", CC_CALLBACK_1(SecondScene::doSoundAction, this));
	item2->setColor(Color3B(0, 0, 0));
	auto item1 = MenuItemFont::create("Close Scene2", CC_CALLBACK_1(SecondScene::doClose, this));
	item1->setColor(Color3B(0, 0, 0));
	auto pMenu = Menu::create(item1, item2, nullptr);
	pMenu->alignItemsVertically();
	this->addChild(pMenu);
	
	auto pWoman = Sprite::createWithSpriteFrameName("blocks9.png");
	pWoman->setPosition(Vec2(120, 220));
	this->addChild(pWoman);
	log("SecondScene :: init");
    return true;
}

void SecondScene::imageLoaded(Ref *pSender) {
	auto tex = static_cast<Texture2D*>(pSender);
	auto sprite = Sprite::createWithTexture(tex);
	sprite->setPosition(Vec2(360, 100));
	this->addChild(sprite);

	log("Image loaded : %p", pSender);
}

void SecondScene::doSoundAction(Ref* pSender) {
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);
}

void SecondScene::onEnter() {
	Layer::onEnter();
	log("SecondScene :: onEnter");
}
void SecondScene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	log("SecondScene :: onEnterTransitionDidFinish");
}
void SecondScene::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	log("SecondScene :: onExitTransitionDidStart");
}
void SecondScene::onExit() {
	Layer::onExit();
	log("SecondScene :: onExit");
}

SecondScene::~SecondScene() {

	log("SecondScene :: dealloc");
}

void SecondScene::doClose(Ref* pSender) {
	//Director::getInstance()->popScene();
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}
