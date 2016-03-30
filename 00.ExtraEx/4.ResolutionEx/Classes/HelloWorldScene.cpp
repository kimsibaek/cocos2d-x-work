#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

Vec2 HelloWorld::Vec21(float x, float y) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	return Vec2(x + origin.x, y + origin.y);
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255) ))
    {
        return false;
    }

	Size size1 = Director::getInstance()->getWinSize();
	Size size2 = Director::getInstance()->getVisibleSize();

	log("Size1 : %f...%f", size1.width, size1.height);
	log("Size2 : %f...%f", size2.width, size2.height);

	auto pBack = Sprite::create("Images/HelloWorld.png");
	pBack->setPosition(Vec2(size1.width / 2, size1.height / 2));
	this->addChild(pBack);

	auto pBox1 = Sprite::create("Images/blocks.png");
	pBox1->setPosition(Vec2(0, size1.height / 2));
	this->addChild(pBox1);
    
	auto pBox2 = Sprite::create("Images/blocks.png");
	pBox2->setPosition(Vec2(size1.width, size1.height / 2));
	this->addChild(pBox2);

	auto pBox31 = Sprite::create("Images/blocks.png");
	pBox31->setPosition(Vec2(size1.width/2-100, 0));
	this->addChild(pBox31);

	auto pBox32 = Sprite::create("Images/blocks.png");
	pBox32->setPosition(Vec21(size1.width/2+100, 0));
	this->addChild(pBox32);

	auto pBox41 = Sprite::create("Images/blocks.png");
	pBox41->setPosition(Vec2(size1.width/2 -100, size1.height));
	this->addChild(pBox41);

	auto pBox42 = Sprite::create("Images/blocks.png");
	pBox42->setPosition(Vec21(size1.width/2 +100, size2.height));
	this->addChild(pBox42);
	return true;
}

