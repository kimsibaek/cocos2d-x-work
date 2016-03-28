#include "HelloWorldScene.h"
#include "SecondScene.h"
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
	auto item1 = MenuItemFont::create("pushScene", CC_CALLBACK_1(HelloWorld::doChangeScene, this));
	item1->setColor(Color3B(0, 0, 0));
	auto pMenu = Menu::create(item1, nullptr);

	this->addChild(pMenu);

	
	
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FILE);

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/grossini_family.plist");

	log("HelloWorld :: init");
    return true;
}

void HelloWorld::doChangeScene(Ref* pSender) {
	auto pScene = SecondScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void HelloWorld::onEnter() {
	Layer::onEnter();
	log("HelloWorld :: onEnter");
}
void HelloWorld::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	log("HelloWorld :: onEnterTransitionDidFinish");
}
void HelloWorld::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	log("HelloWorld :: onExitTransitionDidStart");
}
void HelloWorld::onExit() {
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	SimpleAudioEngine::getInstance()->end();
	
	Layer::onExit();
	log("HelloWorld :: onExit");
}

HelloWorld::~HelloWorld() {
	
	log("HelloWorld :: dealloc");
}