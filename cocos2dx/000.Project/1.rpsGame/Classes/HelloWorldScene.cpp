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
	//String str;
	int user = 0, computer = 0;
	pLabel1 = LabelTTF::create("Your score : 0",
		"Arial",
		15);
	pLabel1->setPosition(Vec2(160, 280));
	pLabel1->setFontSize(15);
	pLabel1->setColor(Color3B(0, 0, 255));
	this->addChild(pLabel1);

	
	pLabel2 = LabelTTF::create("Computer score : 0",
		"Arial",
		15);
	pLabel2->setPosition(Vec2(320, 280));
	pLabel2->setColor(Color3B(0, 0, 255));
	pLabel2->setFontSize(15);
	this->addChild(pLabel2);

	auto pMenuItem1 = MenuItemFont::create("[ 가위 ]", CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));
	auto pMenuItem2 = MenuItemFont::create("[ 바위 ]", CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));
	auto pMenuItem3 = MenuItemFont::create("[ 보 ]", CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem3->setColor(Color3B(0, 0, 0));
	
	pMenuItem1->setTag(1);
	pMenuItem2->setTag(2);
	pMenuItem3->setTag(3);

	auto pMenuItem4 = MenuItemFont::create("[ 다시하기 ]", CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem4->setColor(Color3B(0, 0, 0));
	pMenuItem4->setTag(4);

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);
	pMenu->alignItemsHorizontally();
	pMenu->setPosition(240, 70);
	this->addChild(pMenu);

	auto pMenu1 = Menu::create(pMenuItem4, nullptr);
	pMenu1->setPosition(240, 20);
	this->addChild(pMenu1);
    return true;
}

void HelloWorld::doClick(Ref *pSender) {
	auto tItem = (MenuItem *)pSender;
	auto pMan = (Sprite *)getChildByTag(11);
	this->removeChild(pMan, true);
	int i = tItem->getTag();
	int index = 0;
	index = rand() % 3 + 1;
	randcomputer(index);
	if (i == 1) {
		auto pMan = Sprite::create("Images/img1.png");
		pMan->setPosition(Vec2(160, 160));
		pMan->setFlippedX(true);
		pMan->setTag(11);
		this->addChild(pMan);
	}
	else if (i == 2) {
		auto pMan = Sprite::create("Images/img2.png");
		pMan->setPosition(Vec2(160, 160));
		pMan->setFlippedX(true);
		pMan->setTag(11);
		this->addChild(pMan);
	}
	else if (i == 3) {
		auto pMan = Sprite::create("Images/img3.png");
		pMan->setPosition(Vec2(160, 160));
		pMan->setFlippedX(true);
		pMan->setTag(11);
		this->addChild(pMan);
	}
	else {   //다시하기
		auto pMan = (Sprite *)getChildByTag(12);
		this->removeChild(pMan, true);
		auto pMan1 = (Sprite *)getChildByTag(13);
		this->removeChild(pMan1, true);
		score1 = 0;
		score2 = 0;
		sprintf(coinScore1, "Computer score : 0", score2);
		pLabel2->setString(coinScore1);
		sprintf(coinScore, "Your score : 0", score1);
		pLabel1->setString(coinScore);

	}
	//log("%d번째 메뉴가 선택되었습니다.", i);
	result(i, index);

}

void HelloWorld::randcomputer(int num) {
	auto pMan = (Sprite *)getChildByTag(12);
	this->removeChild(pMan, true);
	if (num == 1) {
		auto pMan = Sprite::create("Images/img1.png");
		
		pMan->setPosition(Vec2(320, 160));
		pMan->setTag(12);
		this->addChild(pMan);
	}
	else if (num == 2) {
		auto pMan = Sprite::create("Images/img2.png");
		
		pMan->setPosition(Vec2(320, 160));
		pMan->setTag(12);
		this->addChild(pMan);
	}
	else if (num == 3) {
		auto pMan = Sprite::create("Images/img3.png");
		
		pMan->setPosition(Vec2(320, 160));
		pMan->setTag(12);
		this->addChild(pMan);
	}
}

void HelloWorld::result(int num1, int num2) {
	auto pMan = (Sprite *)getChildByTag(13);
	this->removeChild(pMan, true);
	
	if ((num1 == 1 && num2 == 2) || (num1 == 2 && num2 == 3) || (num1 == 3 && num2 == 1)) {
		auto pLabel5 = LabelTTF::create("컴퓨터가 이겼습니다.",
			"Arial",
			15);
		pLabel5->setPosition(Vec2(240, 250));
		pLabel5->setColor(Color3B(255, 0, 0));
		pLabel5->setFontSize(20);
		pLabel5->setTag(13);
		this->addChild(pLabel5);
		score2++;
		sprintf(coinScore1, "Computer score : %d", score2);
		pLabel2->setString(coinScore1);
	}
	else if (num1 == num2) {
		auto pLabel5 = LabelTTF::create("비겼습니다.",
			"Arial",
			15);
		pLabel5->setPosition(Vec2(240, 250));
		pLabel5->setColor(Color3B(255, 0, 0));
		pLabel5->setFontSize(20);
		pLabel5->setTag(13);
		this->addChild(pLabel5);
	}
	else if ((num1 == 2 && num2 == 1) || (num1 == 3 && num2 == 2) || (num1 == 1 && num2 == 3)) {
		auto pLabel5 = LabelTTF::create("유저가 이겼습니다.",
			"Arial",
			15);
		pLabel5->setPosition(Vec2(240, 250));
		pLabel5->setColor(Color3B(255, 0, 0));
		pLabel5->setFontSize(20);
		pLabel5->setTag(13);
		this->addChild(pLabel5);
		score1++;
		sprintf(coinScore, "Your score : %d", score1);
		pLabel1->setString(coinScore);
	}
	
}