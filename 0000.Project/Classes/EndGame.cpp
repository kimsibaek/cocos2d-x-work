#include "EndGame.h"
#include "stdafx.h"
#include "MainScene.h"
#include "IntroScene.h"
USING_NS_CC;

Scene* EndGame::createScene()
{
	auto scene = Scene::create();
	auto layer = EndGame::create();
	scene->addChild(layer);
	return scene;
}

bool EndGame::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
	{
		return false;
	}
	winSize = Director::getInstance()->getWinSize();
	
	//DB불러오기
	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";
	
	createDatabase();
	selectData(this);
	insertData(this);
	auto popLayer = CCLayerColor::create(Color4B(0, 0, 0, 255), 640, 480);
	popLayer->setAnchorPoint(Vec2(0, 0));
	popLayer->setPosition(Vec2((winSize.width - popLayer->getContentSize().width) / 2, (winSize.height - popLayer->getContentSize().height) / 2));

	this->addChild(popLayer);

	Sprite *bg1 = Sprite::create("Images/Scene/EndGameBG1.png");
	bg1->setAnchorPoint(Vec2(0, 0));
	bg1->setPosition(Vec2((winSize.width - bg1->getContentSize().width) / 2, (winSize.height - bg1->getContentSize().height) / 2));
	this->addChild(bg1, 2);

	if (EndGame_Num == 1) {
		Sprite *bg2 = Sprite::create("Images/Scene/EndGameBG2.png");
		bg2->setAnchorPoint(Vec2(0, 0));
		bg2->setPosition(Vec2((winSize.width - bg2->getContentSize().width) / 2, (winSize.height - bg2->getContentSize().height) / 2));
		this->addChild(bg2, 1);

		Sprite *bg3 = Sprite::create("Images/Scene/EndGameText1.png");
		bg3->setAnchorPoint(Vec2(0, 0));
		bg3->setPosition(Vec2((winSize.width - bg3->getContentSize().width) / 2, (winSize.height - bg3->getContentSize().height) / 2));
		this->addChild(bg3, 3);
	}
	else {
		Sprite *bg2 = Sprite::create("Images/Scene/EndGameBG3.png");
		bg2->setAnchorPoint(Vec2(0, 0));
		bg2->setPosition(Vec2((winSize.width - bg2->getContentSize().width) / 2, (winSize.height - bg2->getContentSize().height) / 2));
		this->addChild(bg2, 1);

		Sprite *bg3 = Sprite::create("Images/Scene/EndGameText2.png");
		bg3->setAnchorPoint(Vec2(0, 0));
		bg3->setPosition(Vec2((winSize.width - bg3->getContentSize().width) / 2, (winSize.height - bg3->getContentSize().height) / 2));
		this->addChild(bg3, 3);
	}
	wait = true;
	this->schedule(schedule_selector(EndGame::WaitClick), 1.0f);

	return true;
}




void EndGame::onEnter() {
	Layer::onEnter();
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(EndGame::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void EndGame::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Layer::onExit();
}

bool EndGame::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (wait) {

	}
	else {
		if (EndGame_Num == 1) {
			auto pScene = MainScene::createScene();
			Director::getInstance()->replaceScene(pScene);
		}
		else {
			auto pScene = IntroScene::createScene();
			Director::getInstance()->replaceScene(pScene);
		}
	}
	return true;
}

void EndGame::createDatabase()
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

	//
}

void EndGame::insertData(Ref* pSender)
{
	if (DistelMonsterListSize) {
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
		char sqlstr[200];
		
		for (int i = 0; i < DistelMonsterListSize; i++) {
			//Monster table
			int ID = MonsterListSize + 1;
			int type;
			int level;
			int Item1;
			int Item2;
			int Item3;
			type = Distel_Monster_List[i].Type;
			level = Distel_Monster_List[i].level;
			Item1 = Distel_Monster_List[i].Item1;
			Item2 = Distel_Monster_List[i].Item2;
			Item3 = Distel_Monster_List[i].Item3;
			ID = ID + i;
			sprintf(sqlstr, "insert into Monster(Monster_Id, Type, level, Item1, Item2, Item3, Exp) values (%d, %d, %d, %d, %d, %d, 0)", ID, type, level, Item1, Item2, Item3);
			//log(sqlstr);
			sqlStr = sqlstr;
			result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);


			if (result != SQLITE_OK)
			{
				log("Insert Error : Code:%d  Msg:%s", result, errMsg);
			}
		}
		
		
		sqlite3_close(pDB);

		free(Distel_Monster_List);
		DistelMonsterListSize = 0;
	}
}

void EndGame::selectData(Ref* pSender)
{
	sqlite3* pDB = NULL;
	char* errMsg = nullptr;
	int result;

	if (MonsterListSize) {
		free(Monster_List);
		
	}
	MonsterListSize = 0;
	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d   Msg:%s", result, errMsg);
	}

	// select data
	std::string sqlStr;
	sqlStr = "select Monster_Id, Type, level, Item1, Item2, Item3, Exp from Monster";

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		std::string str1 = "";
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			int ID = sqlite3_column_int(statement, 0);
			int Type = sqlite3_column_int(statement, 1);
			int level = sqlite3_column_int(statement, 2);
			int Item1 = sqlite3_column_int(statement, 3);
			int Item2 = sqlite3_column_int(statement, 4);
			int Item3 = sqlite3_column_int(statement, 5);
			int Exp = sqlite3_column_int(statement, 6);

			if (ID != 0) {
				if (MonsterListSize)	Monster_List = (Monster_num*)realloc(Monster_List, sizeof(Monster_num) * (MonsterListSize + 1));
				else					Monster_List = (Monster_num*)malloc(sizeof(Monster_num) * (MonsterListSize + 1));
				Monster_List[MonsterListSize].ID = ID;
				Monster_List[MonsterListSize].Type = Type;
				Monster_List[MonsterListSize].level = level;
				Monster_List[MonsterListSize].Item1 = Item1;
				Monster_List[MonsterListSize].Item2 = Item2;
				Monster_List[MonsterListSize].Item3 = Item3;
				Monster_List[MonsterListSize].exp = Exp;

				MonsterListSize++;
			}
		}

		//lblStatus->setString(str1);
	}
	sqlite3_finalize(statement);

	sqlite3_close(pDB);
}

void EndGame::WaitClick(float f) {
	wait = false;
}