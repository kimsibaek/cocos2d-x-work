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
	auto pLabel1 = LabelTTF::create("Hello World",
		"Arial",
		34);
	//위치지정한곳부터 레이블 생성
	//pLabel->setAnchorPoint(Vec2(0, 0.5));
	//레이블의 위치 지정
	pLabel1->setPosition(Vec2(240, 250));
	//레이블의 색 지정
	pLabel1->setColor(Color3B(0, 0, 0));
	//레이블의 투명도 지정
	//pLabel1->setOpacity(100.0f);
	//레이어에 레이블 객체 추가
	this->addChild(pLabel1);

	auto pLabel2 = LabelBMFont::create("Hello", "futura-48.fnt");
	//위치지정한곳부터 레이블 생성
	//pLabel->setAnchorPoint(Vec2(0, 0.5));
	//레이블의 위치 지정
	pLabel2->setPosition(Vec2(240, 150));
	//레이블의 색 지정
	//pLabel2->setColor(Color3B(0, 0, 0));
	//레이블의 투명도 지정
	//pLabel2->setOpacity(100.0f);
	//레이어에 레이블 객체 추가
	this->addChild(pLabel2);

	auto pLabel3 = LabelAtlas::create("1234","fps_images.png", 12, 32, '.');
	//위치지정한곳부터 레이블 생성
	//pLabel->setAnchorPoint(Vec2(0, 0.5));
	//레이블의 위치 지정
	pLabel3->setPosition(Vec2(240, 50));
	//레이블의 색 지정
	//pLabel3->setColor(Color3B(0, 0, 0));
	//레이블의 투명도 지정
	//pLabel2->setOpacity(100.0f);
	//레이어에 레이블 객체 추가
	this->addChild(pLabel3);

    return true;
}

