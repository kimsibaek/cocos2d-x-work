#include "ItemsEquip.h"
#include "MainScene.h"
#include "sqlite3.h"
#include "stdafx.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

Scene* ItemsEquip::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ItemsEquip::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ItemsEquip::init()
{
	if (!Layer::init())
	{
		return false;
	}
	////////////////////
	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Plist/char_bg.plist");
	cache->addSpriteFramesWithFile("Plist/Person.plist");
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

	////StoreItem_text
	//Sprite* StoreItem_text = Sprite::create("Images/Scene/StoreItem_text.png");
	//StoreItem_text->setPosition(Vec2(35, 670));
	//StoreItem_text->setScale(3.0);
	//StoreItem_text->setAnchorPoint(Vec2(0, 0));
	//this->addChild(StoreItem_text);

	//YourItem_text
	Sprite* YourItem_text = Sprite::create("Images/Scene/YourItem_text.png");
	YourItem_text->setPosition(Vec2(35, 670));
	YourItem_text->setScale(3.0);
	YourItem_text->setAnchorPoint(Vec2(0, 0));
	this->addChild(YourItem_text);


	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";

	selectData(this);
	
	//캐릭터 테이블
	setUpdateItemproperty = true;
	tableView1 = TableView::create(this, Size(500, 400));
	tableView1->setDirection(ScrollView::Direction::VERTICAL);
	//tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2(630 + (winSize.width - 1230) / 2, (winSize.height - 200) / 2));
	tableView1->setAnchorPoint(Vec2(0, 0));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	//tableView1->setBounceable(false);
	tableView1->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView1->reloadData();
	this->addChild(tableView1);

	//인벤토리 테이블
	setUpdateItemproperty = false;
	tableView2 = TableView::create(this, Size(500, 400));
	tableView2->setDirection(ScrollView::Direction::VERTICAL);
	//tableView2->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView2->setPosition(Vec2((winSize.width - 1230) / 2, (winSize.height - 200) / 2));
	tableView2->setAnchorPoint(Vec2(0, 0));
	tableView2->setDelegate(this);
	tableView2->setTag(200);
	//tableView2->setBounceable(false);
	tableView2->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView2->reloadData();
	this->addChild(tableView2);
	
	Cell_Num = -1;
	MonsterCellNum = -1;

	//MenuItemFont::setFontSize(64);
	auto pMenuItem2 = MenuItemImage::create("Images/Scene/WearString.png", "Images/Scene/WearString_click.png", CC_CALLBACK_1(ItemsEquip::doEquipment, this));
	//auto pMenuItem2 = MenuItemFont::create("장착", CC_CALLBACK_1(ItemsEquip::doEquipment, this));
	//pMenuItem2->setColor(Color3B(0, 0, 0));
	
	auto pMenu = Menu::create(pMenuItem2, nullptr);
	pMenu->alignItemsHorizontallyWithPadding(300.0f);
	pMenu->setPosition(Vec2(300, 100));
	this->addChild(pMenu);

	auto pMenuItem1 = MenuItemImage::create("Images/Scene/BackButton_click.png", "Images/Scene/BackButton.png", CC_CALLBACK_1(ItemsEquip::doClick1, this));
	pMenuItem1->setPosition(Vec2(1210, 650));
	pMenuItem1->setScale(0.5);
	pMenuItem1->setTag(1);
	//auto pMenuItem7 = MenuItemImage::create("Images/Scene/Exit.png", "Images/Scene/Exit_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	auto pMenu1 = Menu::create(pMenuItem1, nullptr);
	pMenu1->setPosition(Vec2(0, 0));
	this->addChild(pMenu1);


	//Items_BG1
	Items_BG1 = Sprite::create("Images/Scene/char_bg_Item.png");
	Items_BG1->setPosition(Vec2(655, 50));
	Items_BG1->setScale(1.5);
	Items_BG1->setAnchorPoint(Vec2(0, 0));
	this->addChild(Items_BG1);

	//Items_BG2
	Items_BG2 = Sprite::create("Images/Scene/char_bg_Item.png");
	Items_BG2->setPosition(Vec2(805, 50));
	Items_BG2->setScale(1.5);
	Items_BG2->setAnchorPoint(Vec2(0, 0));
	this->addChild(Items_BG2);

	//Items_BG3
	Items_BG3 = Sprite::create("Images/Scene/char_bg_Item.png");
	Items_BG3->setPosition(Vec2(955, 50));
	Items_BG3->setScale(1.5);
	Items_BG3->setAnchorPoint(Vec2(0, 0));
	this->addChild(Items_BG3);
	return true;
}

void ItemsEquip::doClick1(Ref *pSender) {
	auto tItem = (MenuItem *)pSender;
	m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/click.wav");
	int i = tItem->getTag();
	log("%d번째 메뉴가 선택되었습니다.", i);
	if (i == 1) {
		auto pScene = MainScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	
}

void ItemsEquip::onEnter() {
	Layer::onEnter();
	listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(ItemsEquip::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Items_BG1);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Items_BG2);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Items_BG3);
}

void ItemsEquip::onExit() {
	_eventDispatcher->removeEventListener(listener);
	if (ItemsListSize) {
		free(Items_List);
		ItemsListSize = 0;
	}

	if (MonsterListSize) {
		free(Monster_List);
		MonsterListSize = 0;
	}
	Layer::onExit();
}

bool ItemsEquip::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	this->removeChild(TexScene);
	if (winSize.width / 2 < touchPoint.x) {
		setUpdateItemproperty = true;
	}
	else {
		setUpdateItemproperty = false;
	}

	auto target = (Sprite*)event->getCurrentTarget();
	//ItemsEquipmentNum = 0;
	Vec2 pos = target->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
	if (rect.containsPoint(pos)) {
		if (target == Items_BG1) {
			Items_BG1->setColor(Color3B::RED);
			Items_BG2->setColor(Color3B::WHITE);
			Items_BG3->setColor(Color3B::WHITE);
			ItemsEquipmentNum = 1;
		}
		else if (target == Items_BG2) {
			Items_BG1->setColor(Color3B::WHITE);
			Items_BG2->setColor(Color3B::RED);
			Items_BG3->setColor(Color3B::WHITE);
			ItemsEquipmentNum = 2;
		}
		else if(target == Items_BG3) {
			Items_BG1->setColor(Color3B::WHITE);
			Items_BG2->setColor(Color3B::WHITE);
			Items_BG3->setColor(Color3B::RED);
			ItemsEquipmentNum = 3;
		}
	}

	
	return true;
}

void ItemsEquip::selectData(Ref* pSender)
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
			
			if (ID < 6) {
				if (ItemsListSize)	Items_List = (Items_num*)realloc(Items_List, sizeof(Items_num) * (ItemsListSize + 1));
				else				Items_List = (Items_num*)malloc(sizeof(Items_num) * (ItemsListSize + 1));
				Items_List[ItemsListSize]._ID = ID;
				Items_List[ItemsListSize].Num = Num;

				ItemsListSize++;
			}
			
		}

		//lblStatus->setString(str1);
	}
	sqlite3_finalize(statement);

	sqlite3_close(pDB);

	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d   Msg:%s", result, errMsg);
	}

	// select data
	sqlStr = "select Monster_Id, Type, level, Item1, Item2, Item3, Exp from Monster";

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

		//lblStatus->setString(str1);
	}
	sqlite3_finalize(statement);

	sqlite3_close(pDB);

}

void ItemsEquip::selectGoldData(Ref* pSender)
{
	
}

void ItemsEquip::UpdateMonsterDB(int num) {
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
	
	if (num == 1) {
		sprintf(sqlstr, "update Monster set Item1 = %d  where Monster_Id = %d", MonsterCellNum2, MonsterCellNum);
	}
	if (num == 2) {
		sprintf(sqlstr, "update Monster set Item2 = %d  where Monster_Id = %d", MonsterCellNum2, MonsterCellNum);
	}
	if (num == 3) {
		sprintf(sqlstr, "update Monster set Item3 = %d  where Monster_Id = %d", MonsterCellNum2, MonsterCellNum);
	}
	//log(sqlstr);
	sqlStr = sqlstr;
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);


	if (result != SQLITE_OK)
	{
		log("update Error : Code:%d  Msg:%s", result, errMsg);
	}

	sqlite3_close(pDB);

}

void ItemsEquip::UpdateItemsDB(int num) {
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

void ItemsEquip::doEquipment(Ref* pSender) {
	if (ItemsEquipmentNum == 0) {
		//장착할 위치 정하기
		return;
	}
	if (MonsterCellNum2 == -1) {
		//아이템 선택하기
		return;
	}
	if (MonsterCellNum == -1) {
		//몬스터 선택하기
		return;
	}
	if (Items_List[MonsterCellNum2].Num == 0) {
		//아이템 부족
		return;
	}
	m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/buy.wav");
	//아이템 테이블 최신화
	Items_List[MonsterCellNum2].Num--;
	TableViewCell *cell1 = tableView2->cellAtIndex(MonsterCellNum2 / 3);
	Sprite *st = (Sprite *)cell1->getChildByTag(MonsterCellNum2 / 3);
	Sprite *st1 = (Sprite *)st->getChildByTag(MonsterCellNum2);
	st1->removeChildByTag(50);

	char Num[3];
	sprintf(Num, "%d", Items_List[MonsterCellNum2].Num);
	auto pLabel2 = LabelAtlas::create(Num, "Images/Scene/ML.png", 7, 9, '0');
	pLabel2->setAnchorPoint(Vec2(1, 0));
	pLabel2->setScale(1.8);
	pLabel2->setPosition(Vec2(st1->getContentSize().width / 2 + 8, 10));
	st1->addChild(pLabel2, 4, 50);
	
	
	UpdateItemsDB(MonsterCellNum2);


	Sprite *Items;
	if (MonsterCellNum2 == 0) {
		Items = Sprite::createWithSpriteFrameName("items0.png");
	}
	if (MonsterCellNum2 == 1) {
		Items = Sprite::createWithSpriteFrameName("items1.png");
	}
	if (MonsterCellNum2 == 2) {
		Items = Sprite::createWithSpriteFrameName("items2.png");
	}
	if (MonsterCellNum2 == 3) {
		Items = Sprite::createWithSpriteFrameName("items3.png");
	}
	if (MonsterCellNum2 == 4) {
		Items = Sprite::createWithSpriteFrameName("items4.png");
	}
	if (MonsterCellNum2 == 5) {
		Items = Sprite::createWithSpriteFrameName("items5.png");
	}
	
	Items->setScale(2.0f);
	if (ItemsEquipmentNum == 1) {
		UpdateMonsterDB(1);
		Monster_List[MonsterCellNum].Item1 = MonsterCellNum2;
		Items_BG1->removeChildByTag(3);
		Items->setPosition(Vec2(Items_BG1->getContentSize().width / 2, Items_BG1->getContentSize().height / 2));
		Items_BG1->addChild(Items, 3, 3);
	}
	else if (ItemsEquipmentNum == 2) {
		UpdateMonsterDB(2);
		Monster_List[MonsterCellNum].Item2 = MonsterCellNum2;
		Items_BG2->removeChildByTag(3);
		Items->setPosition(Vec2(Items_BG2->getContentSize().width / 2, Items_BG2->getContentSize().height / 2));
		Items_BG2->addChild(Items, 3, 3);
	}
	else if (ItemsEquipmentNum == 3) {
		UpdateMonsterDB(3);
		Monster_List[MonsterCellNum].Item3 = MonsterCellNum2;
		Items_BG3->removeChildByTag(3);
		Items->setPosition(Vec2(Items_BG3->getContentSize().width / 2, Items_BG3->getContentSize().height / 2));
		Items_BG3->addChild(Items, 3, 3);
	}
}

void ItemsEquip::doSell(Ref* pSender) {
	
}

void ItemsEquip::doSendMsg(int num) {
	//option Scene
	this->removeChild(TexScene);

	TexScene = Sprite::create("Images/Scene/TexScene2.png");
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

void ItemsEquip::ItemsView(int num) {
	if (num == 1) {
		Sprite *Items;
		Items_BG1->removeChildByTag(3);
		if (Monster_List[MonsterCellNum].Item1 == -1) {
			return;
		}
		if (Monster_List[MonsterCellNum].Item1 == 0) {
			Items = Sprite::createWithSpriteFrameName("items0.png");
		}
		if (Monster_List[MonsterCellNum].Item1 == 1) {
			Items = Sprite::createWithSpriteFrameName("items1.png");
		}
		if (Monster_List[MonsterCellNum].Item1 == 2) {
			Items = Sprite::createWithSpriteFrameName("items2.png");
		}
		if (Monster_List[MonsterCellNum].Item1 == 3) {
			Items = Sprite::createWithSpriteFrameName("items3.png");
		}
		if (Monster_List[MonsterCellNum].Item1 == 4) {
			Items = Sprite::createWithSpriteFrameName("items4.png");
		}
		if (Monster_List[MonsterCellNum].Item1 == 5) {
			Items = Sprite::createWithSpriteFrameName("items5.png");
		}
		Items->setScale(2.0f);
		Items->setPosition(Vec2(Items_BG1->getContentSize().width / 2, Items_BG1->getContentSize().height / 2));
		Items_BG1->addChild(Items, 3, 3);
	}
	else if(num == 2) {
		Sprite *Items;
		Items_BG2->removeChildByTag(3);
		if (Monster_List[MonsterCellNum].Item2 == -1) {
			return;
		}
		if (Monster_List[MonsterCellNum].Item2 == 0) {
			Items = Sprite::createWithSpriteFrameName("items0.png");
		}
		if (Monster_List[MonsterCellNum].Item2 == 1) {
			Items = Sprite::createWithSpriteFrameName("items1.png");
		}
		if (Monster_List[MonsterCellNum].Item2 == 2) {
			Items = Sprite::createWithSpriteFrameName("items2.png");
		}
		if (Monster_List[MonsterCellNum].Item2 == 3) {
			Items = Sprite::createWithSpriteFrameName("items3.png");
		}
		if (Monster_List[MonsterCellNum].Item2 == 4) {
			Items = Sprite::createWithSpriteFrameName("items4.png");
		}
		if (Monster_List[MonsterCellNum].Item2 == 5) {
			Items = Sprite::createWithSpriteFrameName("items5.png");
		}
		Items->setScale(2.0f);
		Items->setPosition(Vec2(Items_BG2->getContentSize().width / 2, Items_BG2->getContentSize().height / 2));
		Items_BG2->addChild(Items, 3, 3);
	}
	else {
		Sprite *Items;
		Items_BG3->removeChildByTag(3);
		if (Monster_List[MonsterCellNum].Item3 == -1) {
			return;
		}
		if (Monster_List[MonsterCellNum].Item3 == 0) {
			Items = Sprite::createWithSpriteFrameName("items0.png");
		}
		if (Monster_List[MonsterCellNum].Item3 == 1) {
			Items = Sprite::createWithSpriteFrameName("items1.png");
		}
		if (Monster_List[MonsterCellNum].Item3 == 2) {
			Items = Sprite::createWithSpriteFrameName("items2.png");
		}
		if (Monster_List[MonsterCellNum].Item3 == 3) {
			Items = Sprite::createWithSpriteFrameName("items3.png");
		}
		if (Monster_List[MonsterCellNum].Item3 == 4) {
			Items = Sprite::createWithSpriteFrameName("items4.png");
		}
		if (Monster_List[MonsterCellNum].Item3 == 5) {
			Items = Sprite::createWithSpriteFrameName("items5.png");
		}
		Items->setScale(2.0f);
		Items->setPosition(Vec2(Items_BG3->getContentSize().width / 2, Items_BG3->getContentSize().height / 2));
		Items_BG3->addChild(Items, 3, 3);
	}
}

void ItemsEquip::tableCellTouched(TableView* table, TableViewCell* cell) {
	Cell_Num = cell->getIdx();
	if (setUpdateItemproperty) {
		//몬스터 선택
		log("cell = %d, MonsterCellNum = %d", Cell_Num, MonsterCellNum);

		//몬스터 선택 표시
		for (int i = 0; i < MonsterListSize; i++) {
			int num1;
			num1 = i / 3;
				if (table->cellAtIndex(num1)) {
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

		//몬스터 아이템 표시
		ItemsView(1);
		ItemsView(2);
		ItemsView(3);
		Items_BG1->setColor(Color3B::WHITE);
		Items_BG2->setColor(Color3B::WHITE);
		Items_BG3->setColor(Color3B::WHITE);
	}
	else {
		//인벤토리 선택
		log("cell = %d, MonsterCellNum2 = %d", Cell_Num, MonsterCellNum2);

		for (int i = 0; i < ItemsListSize; i++) {
			int num1;
			num1 = i / 3;
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

Size ItemsEquip::tableCellSizeForIndex(TableView *table, ssize_t idx) {
	return CCSizeMake(100, 200);
}

TableViewCell* ItemsEquip::tableCellAtIndex(TableView *table, ssize_t idx) {
	//num = idx;
	char png[25];
	int ViewNum = idx;
	TableViewCell *cell = table->dequeueCell();
	tableViewSprite = Sprite::createWithSpriteFrameName("char_bg_Item.png");
	if (setUpdateItemproperty) {
		
		for (int i = 0; i < 3; i++) {
			if (ViewNum * 3 + i < MonsterListSize) {
				temp[i] = new MonsterCell();
				if (Monster_List[ViewNum * 3 + i].Type > 0 && Monster_List[ViewNum * 3 + i].Type < 10) {
					temp[i]->setTexture("Images/Scene/char_bg_earth.png");
					//sprite_1 = Sprite::createWithSpriteFrameName("char_bg_earth.png");
				}
				else if ((Monster_List[ViewNum * 3 + i].Type > 10 && Monster_List[ViewNum * 3 + i].Type < 20) || Monster_List[ViewNum * 3 + i].Type == 0) {
					temp[i]->setTexture("Images/Scene/char_bg_fire.png");
					//sprite_1 = Sprite::createWithSpriteFrameName("char_bg_fire.png");
				}
				else if (Monster_List[ViewNum * 3 + i].Type > 20 && Monster_List[ViewNum * 3 + i].Type < 30) {
					temp[i]->setTexture("Images/Scene/char_bg_water.png");
					//sprite_1 = Sprite::createWithSpriteFrameName("char_bg_water.png");
				}
				else if (Monster_List[ViewNum * 3 + i].Type > 30 && Monster_List[ViewNum * 3 + i].Type < 40) {
					temp[i]->setTexture("Images/Scene/char_bg_wind.png");
					//sprite_1 = Sprite::createWithSpriteFrameName("char_bg_wind.png");
				}
				temp[i]->setAnchorPoint(Vec2::ZERO);
				temp[i]->setTag(ViewNum * 3 + i);
				temp[i]->setPosition(Vec2(i * 100, 0));
				temp[i]->setPriority(ViewNum * 3 + i);
				temp[i]->setPriorityWithThis(true);
				tableViewSprite->addChild(temp[i]);
				Monster(ViewNum * 3 + i, i);
			}
		}
	}
	else {
		
		for (int i = 0; i < 3; i++) {
			if (ViewNum * 3 + i < ItemsListSize) {
				temp[i] = new MonsterCell();
				temp[i]->setTexture("Images/Scene/char_bg_Item.png");

				temp[i]->setAnchorPoint(Vec2::ZERO);
				temp[i]->setTag(ViewNum * 3 + i);
				temp[i]->setPosition(Vec2(i * 100, 0));

				temp[i]->setPriority2(ViewNum * 3 + i);

				temp[i]->setPriorityWithThis(true);
				tableViewSprite->addChild(temp[i]);
				Monster(ViewNum * 3 + i, i);


			}
		}
		
	}
	tableViewSprite->setScale(1.5);
	tableViewSprite->setPosition(Vec2(0, 0));
	tableViewSprite->setAnchorPoint(Vec2(0, 0));
	cell = new CustomTableViewCell();
	cell->autorelease();

	cell->addChild(tableViewSprite, 0, idx);

	return cell;
}

ssize_t ItemsEquip::numberOfCellsInTableView(TableView *table) {
	if (table->getTag() == 200) {
		setUpdateItemproperty = false;
	}
	else {
		setUpdateItemproperty = true;
	}

	int num1 = 0;
	if (setUpdateItemproperty) {
		if (MonsterListSize % 3 == 0) {
			num1 = MonsterListSize / 3;
		}
		else {
			num1 = MonsterListSize / 3 + 1;
		}
	}
	else {
		if (ItemsListSize % 3 == 0) {
			num1 = ItemsListSize / 3;
		}
		else {
			num1 = ItemsListSize / 3 + 1;
		}
	}
	return num1;
}

void ItemsEquip::Monster(int num, int row) {
	if (setUpdateItemproperty) {
		//땅질퍽이
		char str1[100];
		char str2[100];
		Vector<SpriteFrame*> animFrames;
		if (Monster_List[num].Type == 0) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
			sprintf(str1, "Person1-");
		}
		else if (Monster_List[num].Type == 1) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Earth1-1.png");
			sprintf(str1, "Earth1-");
		}
		else if (Monster_List[num].Type == 2) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Earth2-1.png");
			sprintf(str1, "Earth2-");
		}
		else if (Monster_List[num].Type == 3) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Earth3-1.png");
			sprintf(str1, "Earth3-");
		}
		//모닥픽
		else if (Monster_List[num].Type == 4) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Earth4-1.png");
			sprintf(str1, "Earth4-");
		}
		else if (Monster_List[num].Type == 5) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Earth5-1.png");
			sprintf(str1, "Earth5-");
		}
		else if (Monster_List[num].Type == 6) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Earth6-1.png");
			sprintf(str1, "Earth6-");
		}
		//모래두지
		else if (Monster_List[num].Type == 7) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Earth7-1.png");
			sprintf(str1, "Earth7-");
		}
		else if (Monster_List[num].Type == 8) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Earth8-1.png");
			sprintf(str1, "Earth8-");
		}
		else if (Monster_List[num].Type == 9) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Earth9-1.png");
			sprintf(str1, "Earth9-");
		}
		//파이뤼
		else if (Monster_List[num].Type == 11) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Fire1-1.png");
			sprintf(str1, "Fire1-");
		}
		else if (Monster_List[num].Type == 12) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Fire2-1.png");
			sprintf(str1, "Fire2-");
		}
		else if (Monster_List[num].Type == 13) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Fire3-1.png");
			sprintf(str1, "Fire3-");
		}
		//팬템
		else if (Monster_List[num].Type == 14) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Fire4-1.png");
			sprintf(str1, "Fire4-");
		}
		else if (Monster_List[num].Type == 15) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Fire5-1.png");
			sprintf(str1, "Fire5-");
		}
		else if (Monster_List[num].Type == 16) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Fire6-1.png");
			sprintf(str1, "Fire6-");
		}
		//블랙매직숀
		else if (Monster_List[num].Type == 17) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Fire7-1.png");
			sprintf(str1, "Fire7-");
		}
		else if (Monster_List[num].Type == 18) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Fire8-1.png");
			sprintf(str1, "Fire8-");
		}
		else if (Monster_List[num].Type == 19) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Fire9-1.png");
			sprintf(str1, "Fire9-");
		}
		//물질퍽이
		else if (Monster_List[num].Type == 21) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Water1-1.png");
			sprintf(str1, "Water1-");
		}
		else if (Monster_List[num].Type == 22) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Water2-1.png");
			sprintf(str1, "Water2-");
		}
		else if (Monster_List[num].Type == 23) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Water3-1.png");
			sprintf(str1, "Water3-");
		}
		//꼬북이
		else if (Monster_List[num].Type == 24) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Water4-1.png");
			sprintf(str1, "Water4-");
		}
		else if (Monster_List[num].Type == 25) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Water5-1.png");
			sprintf(str1, "Water5-");
		}
		else if (Monster_List[num].Type == 26) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Water6-1.png");
			sprintf(str1, "Water6-");
		}
		//리아커
		else if (Monster_List[num].Type == 27) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Water7-1.png");
			sprintf(str1, "Water7-");
		}
		else if (Monster_List[num].Type == 28) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Water8-1.png");
			sprintf(str1, "Water8-");
		}
		else if (Monster_List[num].Type == 29) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Water9-1.png");
			sprintf(str1, "Water9-");
		}
		//코이
		else if (Monster_List[num].Type == 31) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Wind1-1.png");
			sprintf(str1, "Wind1-");
		}
		else if (Monster_List[num].Type == 32) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Wind2-1.png");
			sprintf(str1, "Wind2-");
		}
		else if (Monster_List[num].Type == 33) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Wind3-1.png");
			sprintf(str1, "Wind3-");
		}
		//피젼
		else if (Monster_List[num].Type == 34) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Wind4-1.png");
			sprintf(str1, "Wind4-");
		}
		else if (Monster_List[num].Type == 35) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Wind5-1.png");
			sprintf(str1, "Wind5-");
		}
		else if (Monster_List[num].Type == 36) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Wind6-1.png");
			sprintf(str1, "Wind6-");
		}
		//코이
		else if (Monster_List[num].Type == 37) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Wind7-1.png");
			sprintf(str1, "Wind7-");
		}
		else if (Monster_List[num].Type == 38) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Wind8-1.png");
			sprintf(str1, "Wind8-");
		}
		else if (Monster_List[num].Type == 39) {
			Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
			sprintf(str1, "Wind9-");
		}

		Monster_List[num].sprite->setScale(0.75);
		Monster_List[num].sprite->setPosition(Vec2(temp[row]->getContentSize().width / 2, temp[row]->getContentSize().height / 2));

		temp[row]->addChild(Monster_List[num].sprite, 3);


		char level[3];
		sprintf(level, "%d", Monster_List[num].level);
		auto pLabel3 = LabelAtlas::create(level, "Images/Scene/ML.png", 7, 9, '0');
		pLabel3->setAnchorPoint(Vec2(0, 0));
		pLabel3->setScale(1.5);
		pLabel3->setPosition(Vec2(temp[row]->getContentSize().width / 2 + 8, 10));
		temp[row]->addChild(pLabel3, 4);

		Sprite* Lv = Sprite::create("Images/Scene/Level.png");
		Lv->setAnchorPoint(Vec2(0, 0));
		Lv->setScale(1.5);
		Lv->setPosition(Vec2(temp[row]->getContentSize().width / 2 - 15, 10));
		temp[row]->addChild(Lv, 4);

		for (int i = 1; i < 5; i++) {
			sprintf(str2, "%s%d.png", str1, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str2);
			animFrames.pushBack(frame);
		}

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		Monster_List[num].sprite->runAction(rep);
	}
	else {
		Sprite *Items;
		int ADH = 0;
		if (num == 0) {
			Items = Sprite::createWithSpriteFrameName("items0.png");
			ADH = 30;
		}
		if (num == 1) {
			Items = Sprite::createWithSpriteFrameName("items1.png");
			ADH = 60;
		}
		if (num == 2) {
			Items = Sprite::createWithSpriteFrameName("items2.png");
			ADH = 90;
		}
		if (num == 3) {
			Items = Sprite::createWithSpriteFrameName("items3.png");
			ADH = 30;
		}
		if (num == 4) {
			Items = Sprite::createWithSpriteFrameName("items4.png");
			ADH = 60;
		}
		if (num == 5) {
			Items = Sprite::createWithSpriteFrameName("items5.png");
			ADH = 90;
		}
		if (setUpdateItemproperty) {

		}
		else {
			char Num[3];
			sprintf(Num, "%d", Items_List[num].Num);
			auto pLabel2 = LabelAtlas::create(Num, "Images/Scene/ML.png", 7, 9, '0');
			pLabel2->setAnchorPoint(Vec2(1, 0));
			pLabel2->setScale(1.8);
			pLabel2->setPosition(Vec2(temp[row]->getContentSize().width / 2 + 8, 10));
			temp[row]->addChild(pLabel2, 4, 50);

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
			sprintf(Num, "%d", ADH);
			auto pLabel4 = LabelAtlas::create(Num, "Images/Scene/ML.png", 7, 9, '0');
			pLabel4->setAnchorPoint(Vec2(1, 0));
			pLabel4->setScale(1.4);
			pLabel4->setPosition(Vec2(temp[row]->getContentSize().width * 2 / 3 + 17, temp[row]->getContentSize().height - 20));
			temp[row]->addChild(pLabel4, 4, 10);
		}

		Items->setScale(2.0f);
		Items->setPosition(Vec2(temp[row]->getContentSize().width / 2, temp[row]->getContentSize().height / 2));

		temp[row]->addChild(Items, 3);
	}
	

}