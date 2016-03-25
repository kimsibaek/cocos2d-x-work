#include "HelloWorldScene.h"

USING_NS_CC;

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

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/grossini_family.plist");

	cache->addSpriteFramesWithFile("Images/grossini.plist");

	auto pSprite = SpriteFrame::create("Images/blocks9.png", Rect(0, 0, 96, 96));
	cache->addSpriteFrame(pSprite, "blocks9.png");

	auto pWoman = Sprite::createWithSpriteFrameName("grossinis_sister1.png");
	pWoman->setPosition(Vec2(120, 220));
	this->addChild(pWoman);

	auto pMan = Sprite::createWithSpriteFrameName("grossini_dance_01.png");
	pMan->setPosition(Vec2(240, 220));
	this->addChild(pMan);

	auto pBox = Sprite::createWithSpriteFrameName("blocks9.png");
	pBox->setPosition(Vec2(3660, 220));
	this->addChild(pBox);

	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas.png");
	auto pMan2 = Sprite::createWithTexture(texture, Rect(0, 0, 85, 121));
	pMan2->setPosition(Vec2(120, 100));
	this->addChild(pMan2);

	texture = Director::getInstance()->getTextureCache()->addImage("Images/dragon_animation.png");
	auto pDragon = Sprite::createWithTexture(texture, Rect(0, 0, 130, 140));
	pDragon->setPosition(Vec2(240, 100));
	this->addChild(pDragon);

	Director::getInstance()->getTextureCache()->addImageAsync("Images/blocks9.png", CC_CALLBACK_1(HelloWorld::imageLoaded, this));
    
	return true;
}

void HelloWorld::imageLoaded(Ref *pSender) {
	auto tex = static_cast<Texture2D*>(pSender);
	auto sprite = Sprite::createWithTexture(tex);
	sprite->setPosition(Vec2(360, 100));
	this->addChild(sprite);

	log("Image loaded : %p", pSender);
}
