#include "MainScene.h"
#include "IntroScene.h"
#include "WindMap.h"
#include "WaterMap.h"
#include "FireMap.h"
#include "EarthMap.h"
#include "ClassChange.h"
#include "StoreScene.h"
#include "ItemsEquip.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	////////////////////
	CCSprite* title = CCSprite::create("Images/Scene/mapScene.png");
	title->setPosition(Vec2(640, 360));
	this->addChild(title);

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Plist/Color.plist");
	char str[100];

	//blue
	Vector<SpriteFrame*> animFrames1;
	Sprite* sprite_blue = Sprite::createWithSpriteFrameName("blue1.png");
	sprite_blue->setPosition(850, 290);
	sprite_blue->setScale(1.5);
	this->addChild(sprite_blue);
	for (int i = 1; i < 5; i++) {
		sprintf(str, "blue%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames1.pushBack(frame);
	}

	auto animation1 = Animation::createWithSpriteFrames(animFrames1, 0.2f);
	auto animate1 = Animate::create(animation1);
	auto rep1 = RepeatForever::create(animate1);
	sprite_blue->runAction(rep1);


	//green
	Vector<SpriteFrame*> animFrames2;
	Sprite* sprite_green = Sprite::createWithSpriteFrameName("green1.png");
	sprite_green->setPosition(460, 260);
	sprite_green->setScale(1.5);
	this->addChild(sprite_green);
	for (int i = 1; i < 5; i++) {
		sprintf(str, "green%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames2.pushBack(frame);
	}

	auto animation2 = Animation::createWithSpriteFrames(animFrames2, 0.2f);
	auto animate2 = Animate::create(animation2);
	auto rep2 = RepeatForever::create(animate2);
	sprite_green->runAction(rep2);

	//red
	Vector<SpriteFrame*> animFrames3;
	Sprite* sprite_red = Sprite::createWithSpriteFrameName("red1.png");
	sprite_red->setPosition(870, 555);
	sprite_red->setScale(1.5);
	this->addChild(sprite_red);
	for (int i = 1; i < 5; i++) {
		sprintf(str, "red%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames3.pushBack(frame);
	}

	auto animation3 = Animation::createWithSpriteFrames(animFrames3, 0.2f);
	auto animate3 = Animate::create(animation3);
	auto rep3 = RepeatForever::create(animate3);
	sprite_red->runAction(rep3);

	//yellow
	Vector<SpriteFrame*> animFrames4;
	Sprite* sprite_yellow = Sprite::createWithSpriteFrameName("yellow1.png");
	sprite_yellow->setPosition(430, 500);
	sprite_yellow->setScale(1.5);
	this->addChild(sprite_yellow);
	for (int i = 1; i < 5; i++) {
		sprintf(str, "yellow%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames4.pushBack(frame);
	}

	auto animation4 = Animation::createWithSpriteFrames(animFrames4, 0.2f);
	auto animate4 = Animate::create(animation4);
	auto rep4 = RepeatForever::create(animate4);
	sprite_yellow->runAction(rep4);

	//black
	Vector<SpriteFrame*> animFrames5;
	Sprite* sprite_black = Sprite::createWithSpriteFrameName("black1.png");
	sprite_black->setPosition(580, 60);
	sprite_black->setScale(1.5);
	this->addChild(sprite_black);
	for (int i = 1; i < 5; i++) {
		sprintf(str, "black%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames5.pushBack(frame);
	}

	auto animation5 = Animation::createWithSpriteFrames(animFrames5, 0.2f);
	auto animate5 = Animate::create(animation5);
	auto rep5 = RepeatForever::create(animate5);
	sprite_black->runAction(rep5);

	//purple
	Vector<SpriteFrame*> animFrames6;
	Sprite* sprite_purple = Sprite::createWithSpriteFrameName("purple1.png");
	sprite_purple->setPosition(70, 80);
	sprite_purple->setScale(1.5);
	this->addChild(sprite_purple);
	for (int i = 1; i < 5; i++) {
		sprintf(str, "purple%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames6.pushBack(frame);
	}

	auto animation6 = Animation::createWithSpriteFrames(animFrames6, 0.2f);
	auto animate6 = Animate::create(animation6);
	auto rep6 = RepeatForever::create(animate6);
	sprite_purple->runAction(rep6);

	//orange
	Vector<SpriteFrame*> animFrames7;
	Sprite* sprite_orange = Sprite::createWithSpriteFrameName("orange1.png");
	sprite_orange->setPosition(200, 380);
	sprite_orange->setScale(1.5);
	this->addChild(sprite_orange);
	for (int i = 1; i < 5; i++) {
		sprintf(str, "orange%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames7.pushBack(frame);
	}

	auto animation7 = Animation::createWithSpriteFrames(animFrames7, 0.2f);
	auto animate7 = Animate::create(animation7);
	auto rep7 = RepeatForever::create(animate7);
	sprite_orange->runAction(rep7);


	auto pMenuItem1 = MenuItemImage::create("Images/Scene/EarthLand.png", "Images/Scene/EarthLand_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem1->setPosition(Vec2(565, 210));
	pMenuItem1->setScale(3);
	pMenuItem1->setTag(1);
	auto pMenuItem2 = MenuItemImage::create("Images/Scene/FireLand.png", "Images/Scene/FireLand_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem2->setPosition(Vec2(975, 505));
	pMenuItem2->setScale(3);
	pMenuItem2->setTag(2);
	auto pMenuItem3 = MenuItemImage::create("Images/Scene/WaterLand.png", "Images/Scene/WaterLand_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem3->setPosition(Vec2(955, 240));
	pMenuItem3->setScale(3);
	pMenuItem3->setTag(3);
	auto pMenuItem4 = MenuItemImage::create("Images/Scene/WindLand.png", "Images/Scene/WindLand_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem4->setPosition(Vec2(535, 450));
	pMenuItem4->setScale(3);
	pMenuItem4->setTag(4);
	auto pMenuItem5 = MenuItemImage::create("Images/Scene/Store.png", "Images/Scene/Store_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem5->setPosition(Vec2(730, 60));
	pMenuItem5->setScale(3);
	pMenuItem5->setTag(5);
	auto pMenuItem6 = MenuItemImage::create("Images/Scene/CC.png", "Images/Scene/CCC.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem6->setPosition(Vec2(200, 80));
	pMenuItem6->setScale(3);
	pMenuItem6->setTag(6);
	auto pMenuItem7 = MenuItemImage::create("Images/Scene/BackButton_click.png", "Images/Scene/BackButton.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem7->setPosition(Vec2(1210, 650));
	pMenuItem7->setScale(0.5);
	pMenuItem7->setTag(7);
	auto pMenuItem8 = MenuItemImage::create("Images/Scene/Itemmanagement.png", "Images/Scene/Itemmanagement_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem8->setPosition(Vec2(250, 330));
	pMenuItem8->setScale(3);
	pMenuItem8->setTag(8);
	//auto pMenuItem7 = MenuItemImage::create("Images/Scene/Exit.png", "Images/Scene/Exit_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, pMenuItem4, pMenuItem5, pMenuItem6, pMenuItem7, pMenuItem8, nullptr);
	pMenu->setPosition(Vec2(0, 0));
	this->addChild(pMenu);


	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	dbfileName = dbfileName + "SpiritualSoul.sqlite";
	//log("%s", dbfileName.c_str());

	// 데이타베이스 생성
	this->createDatabase();
	return true;
}

void MainScene::createDatabase()
{
	sqlite3* pDB = nullptr;
	char* errMsg;
	int result;

	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d  Msg:%s", result, errMsg);
	}

	
	// create database
	std::string sqlStr;
	sqlStr = "create table IF NOT EXISTS Items( \
                             _ID integer primary key autoincrement, \
                             Num integer)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	
	sqlStr = "create table IF NOT EXISTS Monster( \
								Monster_Id integer, \
								Type integer, \
								level integer, \
								Item1 integer, \
								Item2 integer, \
								Item3 integer, \
								Exp integer)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	
	sqlStr = "create table IF NOT EXISTS Player( \
                             _Id integer primary key autoincrement, \
                             Coin integer)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	
	if (result != SQLITE_OK)
	{
		log("Create Error : Code:%d  Msg:%s", result, errMsg);
	}
	else
	{
		log("Database created successfully!");
	}
	sqlite3_close(pDB);


	//데이터 있는지 확인 후 없으면 초기화 데이터 삽입
	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d   Msg:%s", result, errMsg);
	}

	// select data
	sqlStr = "select Coin from Player";

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		std::string str1 = "";
		if (sqlite3_step(statement) != SQLITE_ROW)
		{
			insertData(this);
		}
	}
	sqlite3_finalize(statement);
	sqlite3_close(pDB);
	//
	int Coin = 1000;
	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d   Msg:%s", result, errMsg);
	}

	// select data
	sqlStr = "select _Id, Coin from Player";

	//sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			int ID = sqlite3_column_int(statement, 0);
			Coin = sqlite3_column_int(statement, 1);
			
		}
	}
	sqlite3_finalize(statement);
	sqlite3_close(pDB);
	
	/*char level[10];
	sprintf(level, "%d", Coin);
	auto pLabel3 = LabelAtlas::create(level, "Images/Scene/ML.png", 7, 9, '0');
	pLabel3->setAnchorPoint(Vec2(0, 0));
	pLabel3->setScale(1.5);
	pLabel3->setPosition(Vec2(1000, 650));
	this->addChild(pLabel3, 100);*/
}

void MainScene::insertData(Ref* pSender)
{
	sqlite3* pDB = nullptr;
	char* errMsg = nullptr;
	int result;

	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d  Msg:%s", result, errMsg);
	}

	// insert data
	std::string sqlStr;
	//Items table
	sqlStr = "insert into Items(_ID, Num) values (0, 0)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	sqlStr = "insert into Items(_ID, Num) values (1, 0)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	sqlStr = "insert into Items(_ID, Num) values (2, 0)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	sqlStr = "insert into Items(_ID, Num) values (3, 0)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	sqlStr = "insert into Items(_ID, Num) values (4, 0)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	sqlStr = "insert into Items(_ID, Num) values (5, 0)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	sqlStr = "insert into Items(_ID, Num) values (6, 1)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	sqlStr = "insert into Items(_ID, Num) values (7, 1)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	sqlStr = "insert into Items(_ID, Num) values (8, 1)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	//Monster table
	sqlStr = "insert into Monster(Monster_Id, Type, level, Item1, Item2, Item3, Exp) values (0, 0, 1, -1, -1, -1, 0)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	//Player table
	sqlStr = "insert into Player(_id, Coin) values (1, 0)";
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);

	if (result != SQLITE_OK)
	{
		log("Insert Error : Code:%d  Msg:%s", result, errMsg);
	}

	sqlite3_close(pDB);
}



void MainScene::doClick1(Ref *pSender) {
	auto tItem = (MenuItem *)pSender;

	int i = tItem->getTag();
	log("%d번째 메뉴가 선택되었습니다.", i);
	if (i == 1) {
		
		auto pScene = TransitionFade::create(1.0f, EarthMap::createScene());
		Director::getInstance()->pushScene(pScene);
		//Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 2) {
		auto pScene = TransitionFade::create(1.0f, FireMap::createScene());
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 3) {
		auto pScene = TransitionFade::create(1.0f, WaterMap::createScene());
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 4) {
		auto pScene = TransitionFade::create(1.0f, WindMap::createScene());
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 5) {
		//상점
		auto pScene = TransitionFade::create(1.0f, StoreScene::createScene());
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 6) {
		//class change
		auto pScene = TransitionFade::create(1.0f, ClassChange::createScene());
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 7) {
		//초기화면
		auto pScene = TransitionFade::create(1.0f, IntroScene::createScene());
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 8) {
		//아이템 장착화면
		auto pScene = TransitionFade::create(1.0f, ItemsEquip::createScene());
		Director::getInstance()->replaceScene(pScene);
	}
}