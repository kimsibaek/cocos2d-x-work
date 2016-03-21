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
	auto bg = LayerColor::create(Color4B(125, 125, 125, 255));
	this->addChild(bg);
	
	TTFConfig ttfConfig1("fonts/Scissor Cuts.ttf", 40);
	TTFConfig ttfConfig2("fonts/Scissor Cuts.ttf", 40, GlyphCollection::DYNAMIC, nullptr, true);

	auto label1 = Label::createWithTTF(ttfConfig1, 
		"Normal",
		TextHAlignment::CENTER,
		480);
	
	label1->setPosition(Vec2(240, 160));
	//레이블의 색 지정
	label1->setColor(Color3B::WHITE);
	//레이블의 투명도 지정
	//pLabel1->setOpacity(100.0f);
	//레이어에 레이블 객체 추가
	this->addChild(label1);

	auto label2 = Label::createWithTTF(ttfConfig2,
		"Glow",
		TextHAlignment::CENTER,
		480);

	label2->setPosition(Vec2(240, 160+50));
	//레이블의 색 지정
	label2->setColor(Color3B::GREEN);
	label2->enableGlow(Color4B::YELLOW);
	//레이블의 투명도 지정
	//pLabel1->setOpacity(100.0f);
	//레이어에 레이블 객체 추가
	this->addChild(label2);


	auto label3 = Label::createWithTTF(ttfConfig1,
		"Outline",
		TextHAlignment::CENTER,
		480);

	label3->setPosition(Vec2(240, 160 - 50));
	//레이블의 색 지정
	label3->setColor(Color3B::WHITE);
	label3->enableGlow(Color4B::BLUE);
	//레이블의 투명도 지정
	//pLabel1->setOpacity(100.0f);
	//레이어에 레이블 객체 추가
	this->addChild(label3);


	auto label4 = Label::createWithTTF(ttfConfig1,
		"Shadow",
		TextHAlignment::CENTER,
		480);

	label4->setPosition(Vec2(240, 160 - 100));
	//레이블의 색 지정
	label4->setColor(Color3B::RED);
	label4->enableGlow(Color4B::BLACK);
	//레이블의 투명도 지정
	//pLabel1->setOpacity(100.0f);
	//레이어에 레이블 객체 추가
	this->addChild(label4);
    return true;
}

