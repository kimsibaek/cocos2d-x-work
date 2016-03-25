#include "HelloWorldScene.h"

static std::string fontList[] = {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	"A DAMN Mess",
	"Abberancy",
	"Abduction",
	"Paint Boy",
	"Schwarzwald Regular",
	"Scissor Cuts",
#else
	"fonts/A DAMN Mess.ttf",
	"fonts/Abberancy.ttf",
	"fonts/Abduction.ttf",
	"fonts/Paint Boy.ttf",
	"fonts/Schwarzwald Regular.ttf",
	"fonts/Scissor Cuts.ttf",
#endif

};

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
	auto pLabel1 = LabelTTF::create("Hello Gikimi",
		"Arial",
		34,
		Size(300, 200),
		TextHAlignment::CENTER,
		TextVAlignment::CENTER);
	//위치지정한곳부터 레이블 생성
	//pLabel->setAnchorPoint(Vec2(0, 0.5));
	//레이블의 위치 지정
	pLabel1->setPosition(Vec2(240, 200));
	//레이블의 색 지정
	pLabel1->setColor(Color3B(0, 0, 0));
	//레이블의 투명도 지정
	//pLabel1->setOpacity(100.0f);
	//레이어에 레이블 객체 추가
	this->addChild(pLabel1);

	auto pLabel2 = LabelTTF::create("Hello Gikimi",
		fontList[5].c_str(),
		34,
		Size(300, 200),
		TextHAlignment::CENTER,
		TextVAlignment::CENTER);
	//위치지정한곳부터 레이블 생성
	//pLabel->setAnchorPoint(Vec2(0, 0.5));
	//레이블의 위치 지정
	pLabel2->setPosition(Vec2(240, 100));
	//레이블의 색 지정
	pLabel2->setColor(Color3B(0, 0, 0));
	//레이블의 투명도 지정
	//pLabel2->setOpacity(100.0f);
	//레이어에 레이블 객체 추가
	this->addChild(pLabel2);
    return true;
}

