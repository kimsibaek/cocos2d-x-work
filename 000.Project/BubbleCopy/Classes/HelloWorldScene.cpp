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
	CCSize _screenSize = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite* Fish_003 = CCSprite::create("Images/Fish_001.png");
	Fish_003->setPosition(ccp(-200, 240));
	this->addChild(Fish_003);

	CCSprite* Fish_004 = CCSprite::create("Images/Fish_002.png");
	Fish_004->setPosition(ccp(640 + 200, 360));
	this->addChild(Fish_004);


	// back ground image
	CCSprite* background = CCSprite::create("Images/Background.png");
	background->setPosition(ccp(320, _screenSize.height * 0.5f));
	this->addChild(background);

	CCSprite* Logo_Light = CCSprite::create("Images/Logo_Light.png");
	Logo_Light->setPosition(340, _screenSize.height * 0.8f);
	this->addChild(Logo_Light);

	CCSprite* Bubble_Logo = CCSprite::create("Images/Bubble_Logo.png");
	Bubble_Logo->setPosition(ccp(320, _screenSize.height * 0.8f));
	this->addChild(Bubble_Logo);

	

	auto Play_Button_01 = MenuItemImage::create("Images/Play_Button_01.png", "Images/Play_Button_02.png", CC_CALLBACK_1(HelloWorld::doAction, this));
	//Play_Button_01->setPosition(320, 300);
	//this->addChild(Play_Button_01);
	auto pMenu = Menu::create(Play_Button_01, nullptr);
	//pMenu->alignItemsHorizontally();
	pMenu->setPosition(320, 300);
	this->addChild(pMenu);

	auto Vibration_ON = MenuItemImage::create("Images/Vibration_ON.png", "Images/Vibration_OFF.png", CC_CALLBACK_1(HelloWorld::doAction1, this));
	//Vibration_ON->setPosition(455, 175);
	//this->addChild(Vibration_ON);
	auto pMenu1 = Menu::create(Vibration_ON, nullptr);
	//pMenu->alignItemsHorizontally();
	pMenu1->setPosition(455, 175);
	this->addChild(pMenu1);

	CCSprite* Fish_001 = CCSprite::create("Images/Fish_001.png");
	Fish_001->setPosition(ccp(-200, 450));
	this->addChild(Fish_001);

	CCSprite* Fish_002 = CCSprite::create("Images/Fish_002.png");
	Fish_002->setPosition(ccp(640+200, 480));
	this->addChild(Fish_002);

	

	CCSprite* Base = CCSprite::create("Images/Base.png");
	Base->setPosition(350, 275);
	this->addChild(Base);
	
	CCSprite* Background_001 = CCSprite::create("Images/Background_001.png");
	Background_001->setPosition(320, 480);
	this->addChild(Background_001);

	CCSprite* Background_002 = CCSprite::create("Images/Background_002.png");
	Background_002->setPosition(320, 480);
	this->addChild(Background_002);
	
	CCSprite* All_Light = CCSprite::create("Images/All_Light.png");
	All_Light->setPosition(ccp(320, 480));
	this->addChild(All_Light);
	
	CCSprite* Flash_001 = CCSprite::create("Images/Flash_001.png");
	Flash_001->setPosition(ccp(320, 480));
	this->addChild(Flash_001);

	CCSprite* Flash_002 = CCSprite::create("Images/Flash_002.png");
	Flash_002->setPosition(ccp(320, 480));
	this->addChild(Flash_002);

	auto Create_Button_01 = MenuItemImage::create("Images/Create_Button_01.png", "Images/Create_Button_02.png", CC_CALLBACK_1(HelloWorld::doAction2, this));
	//Create_Button_01->setPosition(ccp(_screenSize.width * 0.95f, _screenSize.height * 0.05f));
	//this->addChild(Create_Button_01);
	auto pMenu2 = Menu::create(Create_Button_01, NULL);
	//pMenu->alignItemsHorizontally();
	pMenu2->setPosition(ccp(_screenSize.width * 0.95f, _screenSize.height * 0.05f));
	this->addChild(pMenu2);

	CCSprite* Create_base = CCSprite::create("Images/Create_base.png");
	Create_base->setPosition(ccp(_screenSize.width * 0.95f, _screenSize.height * 0.05f));
	this->addChild(Create_base);


	CCSprite* Title_Bubble_001 = CCSprite::create("Images/Title_Bubble_001.png");
	Title_Bubble_001->setPosition(ccp(320, -200));
	this->addChild(Title_Bubble_001);

	CCSprite* Title_Bubble_002 = CCSprite::create("Images/Title_Bubble_002.png");
	Title_Bubble_002->setPosition(ccp(320, -200));
	this->addChild(Title_Bubble_002);
	
	CCSprite* Title_Bubble_003 = CCSprite::create("Images/Title_Bubble_003.png");
	Title_Bubble_003->setPosition(ccp(320, -200));
	this->addChild(Title_Bubble_003);

	CCSprite* Title_Bubble_004 = CCSprite::create("Images/Title_Bubble_004.png");
	Title_Bubble_004->setPosition(ccp(320, -200));
	this->addChild(Title_Bubble_004);

	CCSprite* Lighting_Background = CCSprite::create("Images/Lighting_Background.png");
	Lighting_Background->setPosition(ccp(320, _screenSize.height-150));
	this->addChild(Lighting_Background);

	CCSprite* Blue_Star = CCSprite::create("Images/Blue_Star.png");
	Blue_Star->setPosition(ccp(_screenSize.width * 0.15f, _screenSize.height * 0.15f));
	this->addChild(Blue_Star);

	CCSprite* Gold_Star = CCSprite::create("Images/Gold_Star.png");
	Gold_Star->setPosition(ccp(_screenSize.width * 0.55f, _screenSize.height * 0.05f));
	this->addChild(Gold_Star);

	CCSprite* Purple_Star = CCSprite::create("Images/Purple_Star.png");
	Purple_Star->setPosition(ccp(_screenSize.width * 0.95f, _screenSize.height * 0.09f));
	this->addChild(Purple_Star);


	//////////////액션
	auto myAction = MoveTo::create(4, Vec2(320, _screenSize.height+960));
	auto myAction1 = Place::create(Vec2(320, -200));
	auto myAction2 = Sequence::create(myAction, myAction1, nullptr);
	auto rep1 = RepeatForever::create(myAction2);
	Title_Bubble_001->runAction(rep1);

	auto myAction3 = MoveTo::create(5, Vec2(320, _screenSize.height + 960));
	auto myAction4 = Place::create(Vec2(320, -200));
	auto myAction5 = Sequence::create(myAction3, myAction4, nullptr);
	auto rep2 = RepeatForever::create(myAction5);
	Title_Bubble_002->runAction(rep2);

	auto myAction6 = MoveTo::create(6, Vec2(320, _screenSize.height + 960));
	auto myAction7 = Place::create(Vec2(320, -200));
	auto myAction8 = Sequence::create(myAction6, myAction7, nullptr);
	auto rep3 = RepeatForever::create(myAction8);
	Title_Bubble_003->runAction(rep3);

	auto myAction9 = MoveTo::create(10, Vec2(640+200, 450));
	auto myAction10 = Place::create(Vec2(-200, 450));
	auto myAction11 = Sequence::create(myAction9, myAction10, nullptr);
	auto rep4 = RepeatForever::create(myAction11);
	Fish_001->runAction(rep4);

	auto myAction12 = MoveTo::create(11, Vec2(-200, 480));
	auto myAction13 = Place::create(Vec2(640+200, 480));
	auto myAction14 = Sequence::create(myAction12, myAction13, nullptr);
	auto rep5 = RepeatForever::create(myAction14);
	Fish_002->runAction(rep5);

	auto myAction15 = RotateBy::create(3, 360);
	auto rep6 = RepeatForever::create(myAction15);
	Blue_Star->runAction(rep6);

	auto myAction16 = RotateBy::create(3, 360);
	auto rep7 = RepeatForever::create(myAction16);
	Gold_Star->runAction(rep7);

	auto myAction17 = RotateBy::create(3, 360);
	auto rep8 = RepeatForever::create(myAction17);
	Purple_Star->runAction(rep8);

	auto myAction18 = FadeOut::create(1.5f);
	auto myAction19 = FadeIn::create(1.5f);
	auto myAction20 = Sequence::create(myAction18, myAction19, nullptr);
	auto rep9 = RepeatForever::create(myAction20);
	Base->runAction(rep9);

	auto myAction21 = RotateBy::create(3, 360);
	auto rep10 = RepeatForever::create(myAction21);
	Create_base->runAction(rep10);

	auto myAction22 = MoveTo::create(3, Vec2(320, _screenSize.height * 0.75f));
	//pMan->runAction(action);
	auto myAction23 = MoveTo::create(3, Vec2(320, _screenSize.height * 0.8f));
	auto myAction24 = Sequence::create(myAction22, myAction23, nullptr);
	auto rep11 = RepeatForever::create(myAction24);
	Bubble_Logo->runAction(rep11);


	auto myAction25 = FadeOut::create(1.5f);
	auto myAction26 = FadeIn::create(1.5f);
	auto myAction27 = Sequence::create(myAction25, myAction26, nullptr);
	auto rep12 = RepeatForever::create(myAction27);
	Base->runAction(rep12);

	auto myAction28 = FadeOut::create(1.5f);
	auto myAction29 = FadeIn::create(1.5f);
	auto myAction30 = Sequence::create(myAction28, myAction29, nullptr);
	auto rep13 = RepeatForever::create(myAction30);
	Lighting_Background->runAction(rep13);
	
	auto myAction31 = FadeOut::create(1.5f);
	auto myAction32 = FadeIn::create(1.5f);
	auto myAction33 = Sequence::create(myAction31, myAction32, nullptr);
	auto rep14 = RepeatForever::create(myAction33);
	Background_001->runAction(rep14);

	auto myAction34 = FadeOut::create(1.5f);
	auto myAction35 = FadeIn::create(1.5f);
	auto myAction36 = Sequence::create(myAction34, myAction35, nullptr);
	auto rep15 = RepeatForever::create(myAction36);
	Background_002->runAction(rep15);

	auto myAction37 = FadeOut::create(1.5f);
	auto myAction38 = FadeIn::create(1.5f);
	auto myAction39 = Sequence::create(myAction37, myAction38, nullptr);
	
	auto myAction40 = MoveTo::create(3, Vec2(320, _screenSize.height * 0.75f));
	auto myAction41 = MoveTo::create(3, Vec2(320, _screenSize.height * 0.8f));
	auto myAction42 = Sequence::create(myAction40, myAction41, nullptr);
	auto myAction43 = Spawn::create(myAction39, myAction42, nullptr);
	auto rep16 = RepeatForever::create(myAction43);
	Logo_Light->runAction(rep16);

	auto myAction44 = MoveTo::create(6, Vec2(320, _screenSize.height + 960));
	auto myAction45 = Place::create(Vec2(320, -200));
	auto myAction46 = Sequence::create(myAction44, myAction45, nullptr);
	auto rep17 = RepeatForever::create(myAction46);
	Title_Bubble_004->runAction(rep17);

	auto myAction47 = MoveTo::create(9, Vec2(600, 240));
	auto myAction48 = Place::create(Vec2(-200, 240));
	auto myAction49 = Sequence::create(myAction47, myAction48, nullptr);
	auto rep18 = RepeatForever::create(myAction49);
	Fish_003->runAction(rep18);

	auto myAction50 = MoveTo::create(10, Vec2(200, 360));
	auto myAction51 = Place::create(Vec2(640 + 200, 360));
	auto myAction52 = Sequence::create(myAction50, myAction51, nullptr);
	auto rep19 = RepeatForever::create(myAction52);
	Fish_004->runAction(rep19);


	auto myAction53 = FadeOut::create(2.5f);
	auto myAction54 = FadeIn::create(2.5f);
	auto myAction55 = Sequence::create(myAction53, myAction54, nullptr);
	auto rep20 = RepeatForever::create(myAction55);
	All_Light->runAction(rep20);

	auto myAction59 = FadeOut::create(2.0f);
	auto myAction60 = FadeIn::create(2.0f);
	auto myAction61 = Sequence::create(myAction59, myAction60, nullptr);
	auto rep22 = RepeatForever::create(myAction61);
	Flash_001->runAction(rep22);

	auto myAction56 = FadeOut::create(3.0f);
	auto myAction57 = FadeIn::create(3.0f);
	auto myAction58 = Sequence::create(myAction56, myAction57, nullptr);
	auto rep21 = RepeatForever::create(myAction58);
	Flash_002->runAction(rep21);

    return true;
}

void HelloWorld::doAction(Ref* pSender) {
	
	


}

void HelloWorld::doAction1(Ref* pSender) {


	

}

void HelloWorld::doAction2(Ref* pSender) {
	

}