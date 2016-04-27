#include "MainScene.h"
#include "IntroScene.h"
#include "WindMap.h"
#include "WaterMap.h"
#include "FireMap.h"
#include "EarthMap.h"
#include "ClassChange.h"

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
	CCSprite* title = CCSprite::create("Images/Scene/mapScene2.png");
	title->setPosition(Vec2(640, 360));
	this->addChild(title);

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Plist/blue.plist");
	cache->addSpriteFramesWithFile("Plist/green.plist");
	cache->addSpriteFramesWithFile("Plist/red.plist");
	cache->addSpriteFramesWithFile("Plist/yellow.plist");
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
	sprite_red->setPosition(870, 565);
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
	sprite_yellow->setPosition(430, 520);
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

	auto pMenuItem1 = MenuItemImage::create("Images/Scene/EarthLand.png", "Images/Scene/EarthLand_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem1->setPosition(Vec2(565, 260));
	pMenuItem1->setScale(1.5);
	pMenuItem1->setTag(1);
	auto pMenuItem2 = MenuItemImage::create("Images/Scene/FireLand.png", "Images/Scene/FireLand_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem2->setPosition(Vec2(975, 565));
	pMenuItem2->setScale(1.5);
	pMenuItem2->setTag(2);
	auto pMenuItem3 = MenuItemImage::create("Images/Scene/WaterLand.png", "Images/Scene/WaterLand_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem3->setPosition(Vec2(955, 290));
	pMenuItem3->setScale(1.5);
	pMenuItem3->setTag(3);
	auto pMenuItem4 = MenuItemImage::create("Images/Scene/WindLand.png", "Images/Scene/WindLand_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem4->setPosition(Vec2(535, 520));
	pMenuItem4->setScale(1.5);
	pMenuItem4->setTag(4);
	auto pMenuItem5 = MenuItemImage::create("Images/Scene/Store.png", "Images/Scene/Store_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem5->setPosition(Vec2(620, 60));
	pMenuItem5->setScale(1.5);
	pMenuItem5->setTag(5);
	auto pMenuItem6 = MenuItemImage::create("Images/Scene/Classchange.png", "Images/Scene/Classchange_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem6->setPosition(Vec2(80, 80));
	pMenuItem6->setScale(1.5);
	pMenuItem6->setTag(6);
	auto pMenuItem7 = MenuItemImage::create("Images/Scene/Back.png", "Images/Scene/Back_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	pMenuItem7->setPosition(Vec2(1230, 670));
	pMenuItem7->setScale(0.2);
	pMenuItem7->setTag(7);
	//auto pMenuItem7 = MenuItemImage::create("Images/Scene/Exit.png", "Images/Scene/Exit_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, pMenuItem4, pMenuItem5, pMenuItem6, pMenuItem7, nullptr);
	pMenu->setPosition(Vec2(0, 0));
	this->addChild(pMenu);


	


	lblStatus = LabelTTF::create("",
		"Arial",
		16,
		Size(50, 50),
		TextHAlignment::CENTER,
		TextVAlignment::CENTER);
	lblStatus->setPosition(Vec2(1100, 650));
	lblStatus->setColor(Color3B(0, 0, 0));  // 255, 0, 0
	this->addChild(lblStatus, 4);


	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	log("%s", dbfileName.c_str());
	//dbfileName = "C:\\cocos2d-x-work\\0000.Project\\SpiritualSoul\\Resources\\";
	//dbfileName = "C:\\cocos2d-x-work\\SpiritualSoul\\Resources\\";
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";
	log("%s", dbfileName.c_str());

	// 데이타베이스 생성
	//this->createDatabase();
	selectData(this);
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
	sqlStr = "create table IF NOT EXISTS TestTabel( \
                             ID integer primary key autoincrement, \
                             name nvarchar(32), \
                             class nvarchar(32))";

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
	sqlStr = "insert into TestTabel(name, class) values ('이재환', '프로그래머')";

	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	if (result != SQLITE_OK)
	{
		log("Insert Error : Code:%d  Msg:%s", result, errMsg);
	}

	sqlite3_close(pDB);
}
void MainScene::selectData(Ref* pSender)
{
	sqlite3* pDB = NULL;
	char* errMsg = nullptr;
	int result;

	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d   Msg:%s", result, errMsg);
	}

	// select data
	std::string sqlStr;
	sqlStr = "select Coin from Player";

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		std::string str1 = "";
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			int   row1 = sqlite3_column_int(statement, 0);

			log("%d", row1);

			char str2[50] = { 0 };
			sprintf(str2, "%d", row1);
			str1 = str1 + str2;
		}

		lblStatus->setString(str1);
	}
	sqlite3_finalize(statement);

	sqlite3_close(pDB);
}

void MainScene::doClick1(Ref *pSender) {
	auto tItem = (MenuItem *)pSender;

	int i = tItem->getTag();
	log("%d번째 메뉴가 선택되었습니다.", i);
	if (i == 1) {
		auto pScene = EarthMap::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 2) {
		auto pScene = FireMap::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 3) {
		auto pScene = WaterMap::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 4) {
		auto pScene = WindMap::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 5) {
		//상점
	}
	else if (i == 6) {
		//class change
		auto pScene = ClassChange::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 7) {
		//초기화면
		auto pScene = IntroScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
}