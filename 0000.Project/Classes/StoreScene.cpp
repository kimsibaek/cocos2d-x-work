#include "StoreScene.h"
#include "MainScene.h"
#include "sqlite3.h"
#include "stdafx.h"
USING_NS_CC;

Scene* StoreScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StoreScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StoreScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	////////////////////
	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Plist/char_bg.plist");
	cache->addSpriteFramesWithFile("Plist/Earth1.plist");
	cache->addSpriteFramesWithFile("Plist/Earth2.plist");
	cache->addSpriteFramesWithFile("Plist/Earth3.plist");
	cache->addSpriteFramesWithFile("Plist/Earth4.plist");
	cache->addSpriteFramesWithFile("Plist/Earth5.plist");
	cache->addSpriteFramesWithFile("Plist/Earth6.plist");
	cache->addSpriteFramesWithFile("Plist/Earth7.plist");
	cache->addSpriteFramesWithFile("Plist/Earth8.plist");
	cache->addSpriteFramesWithFile("Plist/Earth9.plist");
	cache->addSpriteFramesWithFile("Plist/Fire1.plist");
	cache->addSpriteFramesWithFile("Plist/Fire2.plist");
	cache->addSpriteFramesWithFile("Plist/Fire3.plist");
	cache->addSpriteFramesWithFile("Plist/Fire4.plist");
	cache->addSpriteFramesWithFile("Plist/Fire5.plist");
	cache->addSpriteFramesWithFile("Plist/Fire6.plist");
	cache->addSpriteFramesWithFile("Plist/Fire7.plist");
	cache->addSpriteFramesWithFile("Plist/Fire8.plist");
	cache->addSpriteFramesWithFile("Plist/Fire9.plist");
	cache->addSpriteFramesWithFile("Plist/Water1.plist");
	cache->addSpriteFramesWithFile("Plist/Water2.plist");
	cache->addSpriteFramesWithFile("Plist/Water3.plist");
	cache->addSpriteFramesWithFile("Plist/Water4.plist");
	cache->addSpriteFramesWithFile("Plist/Water5.plist");
	cache->addSpriteFramesWithFile("Plist/Water6.plist");
	cache->addSpriteFramesWithFile("Plist/Water7.plist");
	cache->addSpriteFramesWithFile("Plist/Water8.plist");
	cache->addSpriteFramesWithFile("Plist/Water9.plist");
	cache->addSpriteFramesWithFile("Plist/Wind1.plist");
	cache->addSpriteFramesWithFile("Plist/Wind2.plist");
	cache->addSpriteFramesWithFile("Plist/Wind3.plist");
	cache->addSpriteFramesWithFile("Plist/Wind4.plist");
	cache->addSpriteFramesWithFile("Plist/Wind5.plist");
	cache->addSpriteFramesWithFile("Plist/Wind6.plist");
	cache->addSpriteFramesWithFile("Plist/Wind7.plist");
	cache->addSpriteFramesWithFile("Plist/Wind8.plist");
	cache->addSpriteFramesWithFile("Plist/Wind9.plist");
	cache->addSpriteFramesWithFile("Plist/Item.plist");
	cache->addSpriteFramesWithFile("Plist/EarthUpgrade.plist");
	cache->addSpriteFramesWithFile("Plist/FireUpgrade.plist");
	cache->addSpriteFramesWithFile("Plist/WindUpgrade.plist");
	cache->addSpriteFramesWithFile("Plist/WaterUpgrade.plist");
	cache->addSpriteFramesWithFile("Plist/etc.plist");

	winSize = Director::getInstance()->getWinSize();

	Sprite* title = Sprite::create("Images/Scene/Store_bg.png");
	title->setPosition(Vec2(640, 360));
	this->addChild(title);

	//StoreItem_text
	Sprite* StoreItem_text = Sprite::create("Images/Scene/StoreItem_text.png");
	StoreItem_text->setPosition(Vec2(35, 670 - 20));
	StoreItem_text->setScale(3.0);
	StoreItem_text->setAnchorPoint(Vec2(0, 0));
	this->addChild(StoreItem_text);

	//YourItem_text
	Sprite* YourItem_text = Sprite::create("Images/Scene/YourItem_text.png");
	YourItem_text->setPosition(Vec2(660, 670 - 20));
	YourItem_text->setScale(3.0);
	YourItem_text->setAnchorPoint(Vec2(0, 0));
	this->addChild(YourItem_text);


	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";

	selectData(this);

	//상점테이블
	setUpdateItemproperty = true;
	tableView1 = TableView::create(this, Size(600, 500));
	tableView1->setDirection(ScrollView::Direction::VERTICAL);
	//tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2((winSize.width - 1230) / 2, (winSize.height - 400) / 2 - 20));
	tableView1->setAnchorPoint(Vec2(0, 0));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	//tableView1->setBounceable(false);
	tableView1->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView1->reloadData();
	this->addChild(tableView1);

	//인벤토리 테이블
	setUpdateItemproperty = false;
	tableView2 = TableView::create(this, Size(600, 500));
	tableView2->setDirection(ScrollView::Direction::VERTICAL);
	//tableView2->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView2->setPosition(Vec2(630 + (winSize.width - 1230) / 2, (winSize.height - 400) / 2 - 20));
	tableView2->setAnchorPoint(Vec2(0, 0));
	tableView2->setDelegate(this);
	tableView2->setTag(200);
	//tableView2->setBounceable(false);
	tableView2->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView2->reloadData();
	this->addChild(tableView2);
	
	Cell_Num = -1;
	MonsterCellNum = -1;

	MenuItemFont::setFontSize(64);
	auto pMenuItem2 = MenuItemFont::create("구매", CC_CALLBACK_1(StoreScene::doBuy, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));
	
	auto pMenuItem3 = MenuItemFont::create("판매", CC_CALLBACK_1(StoreScene::doSell, this));
	pMenuItem3->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem2, pMenuItem3, nullptr);
	pMenu->alignItemsHorizontallyWithPadding(300.0f);
	pMenu->setPosition(Vec2(640, 50));
	this->addChild(pMenu);

	auto pMenuItem1 = MenuItemImage::create("Images/Scene/BackButton_click.png", "Images/Scene/BackButton.png", CC_CALLBACK_1(StoreScene::doClick1, this));
	pMenuItem1->setPosition(Vec2(1230, 670));
	pMenuItem1->setScale(0.4);
	//pMenuItem1->setScaleX(1.5f);
	pMenuItem1->setTag(1);
	//auto pMenuItem7 = MenuItemImage::create("Images/Scene/Exit.png", "Images/Scene/Exit_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	auto pMenu1 = Menu::create(pMenuItem1, nullptr);
	pMenu1->setPosition(Vec2(0, 0));
	this->addChild(pMenu1);


	selectGoldData(this);
	return true;
}

void StoreScene::doClick1(Ref *pSender) {
	auto tItem = (MenuItem *)pSender;

	int i = tItem->getTag();
	log("%d번째 메뉴가 선택되었습니다.", i);
	if (i == 1) {
		auto pScene = MainScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	
}

void StoreScene::onEnter() {
	Layer::onEnter();
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(StoreScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//_eventDispatcher->addEventListenerWithFixedPriority(listener, 2);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, 30);
}

void StoreScene::onExit() {
	_eventDispatcher->removeEventListener(listener);
	if (ItemsListSize) {
		free(Items_List);
		ItemsListSize = 0;
	}
	Layer::onExit();
}

bool StoreScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	this->removeChild(TexScene);
	if (winSize.width / 2 < touchPoint.x) {
		setUpdateItemproperty = false;
	}
	else {
		setUpdateItemproperty = true;
	}

	return true;
}

void StoreScene::selectData(Ref* pSender)
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
	sqlStr = "select _ID, Num from Items";

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		std::string str1 = "";
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			int ID = sqlite3_column_int(statement, 0);
			int Num = sqlite3_column_int(statement, 1);
			

			if (ItemsListSize)	Items_List = (Items_num*)realloc(Items_List, sizeof(Items_num) * (ItemsListSize + 1));
			else				Items_List = (Items_num*)malloc(sizeof(Items_num) * (ItemsListSize + 1));
			Items_List[ItemsListSize]._ID = ID;
			Items_List[ItemsListSize].Num = Num;

			ItemsListSize++;
			
		}

		//lblStatus->setString(str1);
	}
	sqlite3_finalize(statement);

	sqlite3_close(pDB);

}

void StoreScene::selectGoldData(Ref* pSender)
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
	int row1;
	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		std::string str1 = "";
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			row1 = sqlite3_column_int(statement, 0);

			log("%d", row1);
			Gold = row1;
			char str2[50] = { 0 };
			sprintf(str2, "%d", row1);
			str1 = str1 + str2;
		}

		//lblStatus->setString(str1);
	}
	sqlite3_finalize(statement);

	sqlite3_close(pDB);

	Gold_text = Sprite::create("Images/Scene/gold_text.png");
	Gold_text->setAnchorPoint(Vec2(1, 0));
	Gold_text->setScale(3);
	Gold_text->setPosition(Vec2(100, 100));
	this->addChild(Gold_text, 4);

	char Num[20];
	sprintf(Num, "%d", row1);
	Gold_Label = LabelAtlas::create(Num, "Images/Scene/ML.png", 7, 9, '0');
	Gold_Label->setAnchorPoint(Vec2(0, 0));
	Gold_Label->setScale(1.4);
	Gold_Label->setPosition(Vec2(30, 0));
	Gold_text->addChild(Gold_Label, 4, 10);

	Gold_Img = Sprite::create("Images/Scene/Gold_Img.png");
	Gold_Img->setAnchorPoint(Vec2(0, 0));
	Gold_Img->setScale(0.45);
	Gold_Img->setPosition(Vec2(Gold_Label->getContentSize().width+2, 0));
	Gold_Label->addChild(Gold_Img, 4);
}

void StoreScene::UpdatePlayerDB() {
	sqlite3* pDB = nullptr;
	char* errMsg = nullptr;
	int result;

	std::string sqlStr;
	
	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d  Msg:%s", result, errMsg);
	}

	char sqlstr[200];

	sprintf(sqlstr, "update Player set Coin = %d  where _Id = 1", Gold);
	//log(sqlstr);
	sqlStr = sqlstr;
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);


	if (result != SQLITE_OK)
	{
		log("update Error : Code:%d  Msg:%s", result, errMsg);
	}

	sqlite3_close(pDB);

	//
	removeChild(Gold_text);

	Gold_text = Sprite::create("Images/Scene/gold_text.png");
	Gold_text->setAnchorPoint(Vec2(1, 0));
	Gold_text->setScale(3);
	Gold_text->setPosition(Vec2(100, 100));
	this->addChild(Gold_text, 4);

	char Num[20];
	sprintf(Num, "%d", Gold);
	Gold_Label = LabelAtlas::create(Num, "Images/Scene/ML.png", 7, 9, '0');
	Gold_Label->setAnchorPoint(Vec2(0, 0));
	Gold_Label->setScale(1.4);
	Gold_Label->setPosition(Vec2(30, 0));
	Gold_text->addChild(Gold_Label, 4, 10);

	Gold_Img = Sprite::create("Images/Scene/Gold_Img.png");
	Gold_Img->setAnchorPoint(Vec2(0, 0));
	Gold_Img->setScale(0.45);
	Gold_Img->setPosition(Vec2(Gold_Label->getContentSize().width + 2, 0));
	Gold_Label->addChild(Gold_Img, 4);

}

void StoreScene::UpdateItemsDB(int num) {
	sqlite3* pDB = nullptr;
	char* errMsg = nullptr;
	int result;

	std::string sqlStr;

	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d  Msg:%s", result, errMsg);
	}

	char sqlstr[200];
	sprintf(sqlstr, "update Items set Num = %d  where _ID = %d", Items_List[num].Num, num);
	//log(sqlstr);
	sqlStr = sqlstr;
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);


	if (result != SQLITE_OK)
	{
		log("update Error : Code:%d  Msg:%s", result, errMsg);
	}

	sqlite3_close(pDB);
}

void StoreScene::doBuy(Ref* pSender) {
	if (MonsterCellNum == 0) {
		if (Gold - 30 < 0) {
			doSendMsg(0);
			return;
		}
		Gold -= 30;
	}
	else if (MonsterCellNum == 1) {
		if (Gold - 60 < 0) {
			doSendMsg(0);
			return;
		}
		Gold -= 60;
	}
	else if (MonsterCellNum == 2) {
		if (Gold - 90 < 0) {
			doSendMsg(0);
			return;
		}
		Gold -= 90;
	}
	else if (MonsterCellNum == 3) {
		if (Gold - 30 < 0) {
			doSendMsg(0);
			return;
		}
		Gold -= 30;
	}
	else if (MonsterCellNum == 4) {
		if (Gold - 60 < 0) {
			doSendMsg(0);
			return;
		}
		Gold -= 60;
	}
	else if (MonsterCellNum == 5) {
		if (Gold - 90 < 0) {
			doSendMsg(0);
			return;
		}
		Gold -= 90;
	}
	else if (MonsterCellNum == 6) {
		if (Gold - 5 < 0) {
			doSendMsg(0);
			return;
		}
		Gold -= 5;
	}
	else if (MonsterCellNum == 7) {
		if (Gold - 10 < 0) {
			doSendMsg(0);
			return;
		}
		Gold -= 10;
	}
	else if (MonsterCellNum == 8) {
		if (Gold - 20 < 0) {
			doSendMsg(0);
			return;
		}
		Gold -= 20;
	}

	Items_List[MonsterCellNum].Num++;
	TableViewCell *cell1 = tableView2->cellAtIndex(MonsterCellNum / 4);
	Sprite *st = (Sprite *)cell1->getChildByTag(MonsterCellNum / 4);
	Sprite *st1 = (Sprite *)st->getChildByTag(MonsterCellNum);
	st1->removeChildByTag(50);

	char Num[3];
	sprintf(Num, "%d", Items_List[MonsterCellNum].Num);
	auto pLabel2 = LabelAtlas::create(Num, "Images/Scene/ML.png", 7, 9, '0');
	pLabel2->setAnchorPoint(Vec2(1, 0));
	pLabel2->setScale(1.8);
	pLabel2->setPosition(Vec2(st1->getContentSize().width / 2 + 8, 10));
	st1->addChild(pLabel2, 4, 50);

	UpdatePlayerDB();
	UpdateItemsDB(MonsterCellNum);
}

void StoreScene::doSell(Ref* pSender) {
	if (Items_List[MonsterCellNum2].Num < 1) {
		doSendMsg(1);
		return;
	}

	if (MonsterCellNum2 == 0) {
		Gold += 15;
	}
	else if (MonsterCellNum2 == 1) {
		Gold += 30;
	}
	else if (MonsterCellNum2 == 2) {
		Gold += 45;
	}
	else if (MonsterCellNum2 == 3) {
		Gold += 15;
	}
	else if (MonsterCellNum2 == 4) {
		Gold += 30;
	}
	else if (MonsterCellNum2 == 5) {
		Gold += 45;
	}
	else if (MonsterCellNum2 == 6) {
		Gold += 2;
	}
	else if (MonsterCellNum2 == 7) {
		Gold += 5;
	}
	else if (MonsterCellNum2 == 8) {
		Gold += 10;
	}

	Items_List[MonsterCellNum2].Num--;
	TableViewCell *cell1 = tableView2->cellAtIndex(MonsterCellNum2 / 4);
	Sprite *st = (Sprite *)cell1->getChildByTag(MonsterCellNum2 / 4);
	Sprite *st1 = (Sprite *)st->getChildByTag(MonsterCellNum2);
	st1->removeChildByTag(50);

	char Num[3];
	sprintf(Num, "%d", Items_List[MonsterCellNum2].Num);
	auto pLabel2 = LabelAtlas::create(Num, "Images/Scene/ML.png", 7, 9, '0');
	pLabel2->setAnchorPoint(Vec2(1, 0));
	pLabel2->setScale(1.8);
	pLabel2->setPosition(Vec2(st1->getContentSize().width / 2 + 8, 10));
	st1->addChild(pLabel2, 4, 50);

	UpdatePlayerDB();
	UpdateItemsDB(MonsterCellNum2);
}

void StoreScene::doSendMsg(int num) {
	//option Scene
	this->removeChild(TexScene);

	TexScene = Sprite::create("Images/Scene/TexScene.png");
	TexScene->setAnchorPoint(Vec2(0.5, 0.5));
	TexScene->setScale(2.0f);
	TexScene->setPosition(Vec2((winSize.width) / 2, (winSize.height) / 2));
	this->addChild(TexScene, 100);
	MenuItemFont::setFontSize(30.0f);
	if (num == 0) {
		auto pMenuItem = MenuItemFont::create("Gold가 부족합니다.");
		pMenuItem->setColor(Color3B(0, 0, 0));
		pMenuItem->setPosition(Vec2(200, 80));
		TexScene->addChild(pMenuItem, 2);
	}
	else {
		auto pMenuItem = MenuItemFont::create("아이템이 부족합니다.");
		pMenuItem->setColor(Color3B(0, 0, 0));
		pMenuItem->setPosition(Vec2(200, 80));
		TexScene->addChild(pMenuItem, 2);
	}
}

void StoreScene::tableCellTouched(TableView* table, TableViewCell* cell) {
	Cell_Num = cell->getIdx();
	if (setUpdateItemproperty) {
		//상점선택
		log("cell = %d, MonsterCellNum = %d", Cell_Num, MonsterCellNum);

		for (int i = 0; i < 9; i++) {
			int num1;
			num1 = i / 4;
			TableViewCell *cell1 = table->cellAtIndex(num1);
			Sprite *st = (Sprite *)cell1->getChildByTag(num1);
			Sprite *st1 = (Sprite *)st->getChildByTag(i);
			if (i == MonsterCellNum) {
				st1->setColor(Color3B::RED);
			}
			else {
				st1->setColor(Color3B::WHITE);
			}
		}
	}
	else {
		//인벤토리 선택
		log("cell = %d, MonsterCellNum2 = %d", Cell_Num, MonsterCellNum2);

		for (int i = 0; i < 9; i++) {
			int num1;
			num1 = i / 4;
			TableViewCell *cell1 = table->cellAtIndex(num1);
			Sprite *st = (Sprite *)cell1->getChildByTag(num1);
			Sprite *st1 = (Sprite *)st->getChildByTag(i);
			if (i == MonsterCellNum2) {
				st1->setColor(Color3B::RED);
			}
			else {
				st1->setColor(Color3B::WHITE);
			}
		}
	}
	
}

Size StoreScene::tableCellSizeForIndex(TableView *table, ssize_t idx) {
	return CCSizeMake(100, 200);
}

TableViewCell* StoreScene::tableCellAtIndex(TableView *table, ssize_t idx) {
	//num = idx;
	
	char png[25];
	int ViewNum = idx;
	TableViewCell *cell = table->dequeueCell();
	tableViewSprite = Sprite::createWithSpriteFrameName("char_bg_Item.png");
	for (int i = 0; i < 4; i++) {
		if (ViewNum * 4 + i < 9) {
			temp[i] = new MonsterCell();
			temp[i]->setTexture("Images/Scene/char_bg_Item.png");
			
			temp[i]->setAnchorPoint(Vec2::ZERO);
			temp[i]->setTag(ViewNum * 4 + i);
			temp[i]->setPosition(Vec2(i * 100, 0));
			if (setUpdateItemproperty) {
				temp[i]->setPriority(ViewNum * 4 + i);
			}
			else {
				temp[i]->setPriority2(ViewNum * 4 + i);
			}
			temp[i]->setPriorityWithThis(true);
			tableViewSprite->addChild(temp[i]);
			Monster(ViewNum * 4 + i, i);


		}
	}
	tableViewSprite->setScale(1.5);
	tableViewSprite->setPosition(Vec2(0,0));
	tableViewSprite->setAnchorPoint(Vec2(0, 0));
	cell = new CustomTableViewCell();
	cell->autorelease();

	cell->addChild(tableViewSprite, 0, idx);

	return cell;
}

ssize_t StoreScene::numberOfCellsInTableView(TableView *table) {
	int num1 = 0;
	if (ItemsListSize % 4 == 0) {
		num1 = ItemsListSize / 4;
	}
	else {
		num1 = ItemsListSize / 4 + 1;
	}
	return num1;
}

void StoreScene::Monster(int num, int row) {
	Sprite *Items;
	char Num[5];
	int price = 0;
	int ADH = 0;
	if (num == 0) {
		Items = Sprite::createWithSpriteFrameName("items0.png");
		price = 30;
		ADH = 30;
	}
	if (num == 1) {
		Items = Sprite::createWithSpriteFrameName("items1.png");
		price = 60;
		ADH = 60;
	}
	if (num == 2) {
		Items = Sprite::createWithSpriteFrameName("items2.png");
		price = 90;
		ADH = 90;
	}
	if (num == 3) {
		Items = Sprite::createWithSpriteFrameName("items3.png");
		price = 30;
		ADH = 30;
	}
	if (num == 4) {
		Items = Sprite::createWithSpriteFrameName("items4.png");
		price = 60;
		ADH = 60;
	}
	if (num == 5) {
		Items = Sprite::createWithSpriteFrameName("items5.png");
		price = 90;
		ADH = 90;
	}
	if (num == 6) {
		Items = Sprite::createWithSpriteFrameName("items6.png");
		price = 5;
		ADH = 100;
	}
	if (num == 7) {
		Items = Sprite::createWithSpriteFrameName("items7.png");
		price = 10;
		ADH = 200;
	}
	if (num == 8) {
		Items = Sprite::createWithSpriteFrameName("items8.png");
		price = 20;
		ADH = 300;
	}
	if (setUpdateItemproperty) {
		sprintf(Num, "%d", price);
		auto pLabel3 = LabelAtlas::create(Num, "Images/Scene/ML.png", 7, 9, '0');
		pLabel3->setAnchorPoint(Vec2(1, 0));
		pLabel3->setScale(1.8);
		pLabel3->setPosition(Vec2(temp[row]->getContentSize().width / 2 + 8, 10));
		temp[row]->addChild(pLabel3, 4, 10);

		Sprite* Gold_Img = Sprite::create("Images/Scene/Gold_Img.png");
		Gold_Img->setAnchorPoint(Vec2(0, 0));
		Gold_Img->setScale(0.8);
		Gold_Img->setPosition(Vec2(temp[row]->getContentSize().width / 2 + 12, 10));
		temp[row]->addChild(Gold_Img, 4);
		if (num == 0 || num == 1 || num == 2) {
			Sprite* String_Img = Sprite::create("Images/Scene/AttackSprite.png");
			String_Img->setAnchorPoint(Vec2(0, 0));
			String_Img->setScale(1);
			String_Img->setPosition(Vec2(temp[row]->getContentSize().width / 3 - 12, temp[row]->getContentSize().height - 20));
			temp[row]->addChild(String_Img, 5);
		}
		else if (num == 3 || num == 4 || num == 5) {
			Sprite* String_Img = Sprite::create("Images/Scene/DefenceSprite.png");
			String_Img->setAnchorPoint(Vec2(0, 0));
			String_Img->setScale(1);
			String_Img->setPosition(Vec2(temp[row]->getContentSize().width / 3 - 12, temp[row]->getContentSize().height - 20));
			temp[row]->addChild(String_Img, 5);
		}
		else if (num == 6 || num == 7 || num == 8) {
			Sprite* String_Img = Sprite::create("Images/Scene/HPSprite.png");
			String_Img->setAnchorPoint(Vec2(0, 0));
			String_Img->setScale(1);
			String_Img->setPosition(Vec2(temp[row]->getContentSize().width / 3 - 22, temp[row]->getContentSize().height - 20));
			temp[row]->addChild(String_Img, 5);
		}
		sprintf(Num, "%d", ADH);
		auto pLabel4 = LabelAtlas::create(Num, "Images/Scene/ML.png", 7, 9, '0');
		pLabel4->setAnchorPoint(Vec2(1, 0));
		pLabel4->setScale(1.4);
		pLabel4->setPosition(Vec2(temp[row]->getContentSize().width * 2 / 3 + 17, temp[row]->getContentSize().height - 20));
		temp[row]->addChild(pLabel4, 4, 10);
	}
	else {
		char Num[3];
		sprintf(Num, "%d", Items_List[num].Num);
		auto pLabel2 = LabelAtlas::create(Num, "Images/Scene/ML.png", 7, 9, '0');
		pLabel2->setAnchorPoint(Vec2(1, 0));
		pLabel2->setScale(1.8);
		pLabel2->setPosition(Vec2(temp[row]->getContentSize().width / 2 + 8, 10));
		temp[row]->addChild(pLabel2, 4, 50);
	}

	Items->setScale(2.0f);
	Items->setPosition(Vec2(temp[row]->getContentSize().width / 2, temp[row]->getContentSize().height / 2));

	temp[row]->addChild(Items, 3);

}