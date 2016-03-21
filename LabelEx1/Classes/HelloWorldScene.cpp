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
	/////////////////////
	//레이블 생성 및 초기화 1
	auto pLabel = LabelTTF::create("Hello World", "Arial", 64);
	//레이블의 위치 지정
	pLabel->setPosition(Vec2(240, 160));
	//레이블의 색 지정
	pLabel->setColor(Color3B::BLACK);
	//레이블의 투명도 지정
	pLabel->setOpacity(100.0);
	//레이어에 레이블 객체 추가
	this->addChild(pLabel);

    return true;
}

