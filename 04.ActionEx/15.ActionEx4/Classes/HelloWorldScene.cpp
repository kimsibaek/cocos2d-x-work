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
	auto pMenuItem = MenuItemFont::create("Action", CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem, NULL);

	//pMenu->alignItemsHorizontally();

	pMenu->setPosition(Vec2(240, 50));

	this->addChild(pMenu);

	pBall = Sprite::create("Images/r1.png");
	pBall->setPosition(Vec2(50, 100));
	pBall->setScale(0.7f);
	this->addChild(pBall);
	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 150));
	pMan->setScale(0.5f);
	this->addChild(pMan);
	pWomen1 = Sprite::create("Images/grossinis_sister1.png");
	pWomen1->setPosition(Vec2(50, 220));
	pWomen1->setScale(0.5f);
	this->addChild(pWomen1);
	pWomen2 = Sprite::create("Images/grossinis_sister2.png");
	pWomen2->setPosition(Vec2(50, 280));
	pWomen2->setScale(0.5f);
	this->addChild(pWomen2);
    return true;
}

void HelloWorld::doAction(Ref* pSender) {
	doActionReset(this);

	auto move = MoveBy::create(3.0f, Vec2(400, 0));

	//auto ease_in = EaseIn::create(move->clone(), 4.0f);
	//auto ease_out = EaseOut::create(move->clone(), 4.0f);
	//auto ease_inout1 = EaseInOut::create(move->clone(), 4.0f);

	//auto ease_in = EaseExponentialIn::create(move->clone());
	//auto ease_out = EaseExponentialOut::create(move->clone());
	//auto ease_inout1 = EaseExponentialInOut::create(move->clone());

	// auto ease_in = EaseSineIn::create(move->clone());
	//auto ease_out = EaseSineOut::create(move->clone());
	//auto ease_inout1 = EaseSineInOut::create(move->clone());

	//auto ease_in = EaseElasticIn::create(move->clone(), 0.4f);
	//auto ease_out = EaseElasticOut::create(move->clone(), 0.4f);
	//auto ease_inout1 = EaseElasticInOut::create(move->clone(), 0.4f);
	
	//auto ease_in = EaseBounceIn::create(move->clone());
	//auto ease_out = EaseBounceOut::create(move->clone());
	//auto ease_inout1 = EaseBounceInOut::create(move->clone());
	
	auto ease_in = EaseBackIn::create(move->clone());
	auto ease_out = EaseBackOut::create(move->clone());
	auto ease_inout1 = EaseBackInOut::create(move->clone());

	//auto ease_in = Speed::create(move->clone(), 1.0f);
	//auto ease_out = Speed::create(move->clone(), 2.0f);
	//auto ease_inout1 = Speed::create(move->clone(), 3.0f);

	pBall->runAction(move);
	pMan->runAction(ease_in);
	pWomen1->runAction(ease_out);
	pWomen2->runAction(ease_inout1);
}

void HelloWorld::doActionReset(Ref* pSender) {
	pBall->setPosition(Vec2(50, 100));
	pBall->setScale(0.7f);
	pMan->setPosition(Vec2(50, 150));
	pMan->setScale(0.5f);
	pWomen1->setPosition(Vec2(50, 220));
	pWomen1->setScale(0.5f);
	pWomen2->setPosition(Vec2(50, 280));
	pWomen2->setScale(0.5f);
}