#include "Toolbag.h"
#include "sqlite3.h"
#include "stdafx.h"
#include "CustomTableViewCell.h"

USING_NS_CC;

Scene* Toolbag::createScene()
{
	auto scene = Scene::create();
	auto layer = Toolbag::create();
	scene->addChild(layer);
	return scene;
}

bool Toolbag::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
	{
		return false;
	}

	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Plist/char_bg.plist");
	cache->addSpriteFramesWithFile("Plist/Item.plist");

	winSize = Director::getInstance()->getWinSize();

	popLayer = LayerColor::create(Color4B(0, 0, 0, 255), 600, 400);
	popLayer->setAnchorPoint(Vec2(0, 0));
	popLayer->setPosition(Vec2((winSize.width - popLayer->getContentSize().width) / 2, (winSize.height - popLayer->getContentSize().height) / 2));

	this->addChild(popLayer);

	//DB불러오기
	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";

	selectData(this);

	tableView1 = TableView::create(this, Size(500, 200));
	tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2((600 - 500) / 2, (400 - 200) / 2));
	tableView1->setAnchorPoint(Vec2(0, 0));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	popLayer->addChild(tableView1);
	tableView1->reloadData();
	num = 0;

	auto pMenuItem2 = MenuItemFont::create("선택", CC_CALLBACK_1(Toolbag::doContinue, this));
	pMenuItem2->setColor(Color3B(255, 255, 255));
	auto pMenuItem3 = MenuItemFont::create("나가기", CC_CALLBACK_1(Toolbag::doClose, this));
	pMenuItem3->setColor(Color3B(255, 255, 255));

	auto pMenu = Menu::create(pMenuItem2, pMenuItem3, nullptr);
	pMenu->alignItemsHorizontallyWithPadding(100.0f);
	pMenu->setPosition(Vec2(300, 50));
	popLayer->addChild(pMenu);

	return true;
}

void Toolbag::selectData(Ref* pSender)
{
	sqlite3* pDB = NULL;
	char* errMsg = nullptr;
	int result;

	if (ItemsListSize) {
		free(Items_List);
		ItemsListSize = 0;
	}

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

			if (ID > 5) {
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
}

void Toolbag::doContinue(Ref* pSender) {
	//std::string str1 = "1";
	for (int i = 0; i < ItemsListSize; i++) {
		if (Items_List[i]._ID == num + 6) {
			if (Items_List[i].Num <= 0) {
				//아이템 없음
				MenuItemFont::setFontSize(24);
				Sprite *BG = Sprite::create("Images/Scene/TexScene.png");
				BG->setAnchorPoint(Vec2(0.5, 0.5));
				BG->setScale(2.0f);
				BG->setPosition(Vec2((winSize.width) / 2, (winSize.height) / 2));
				this->addChild(BG, 10, 10);

				auto pMenuItem = MenuItemFont::create("선택한 아이템이 부족합니다.");
				pMenuItem->setColor(Color3B(0, 0, 0));
				pMenuItem->setPosition(Vec2(200, 80));
				BG->addChild(pMenuItem, 11, 11);

				return;
			}
		}
	}
	
	char str2[20] = { 0 };
	sprintf(str2, "%d", num + 1);
	NotificationCenter::getInstance()->postNotification("TouchTool", (Ref*)str2);
	this->removeFromParentAndCleanup(true);
}

void Toolbag::onEnter() {
	Layer::onEnter();

	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Toolbag::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Toolbag::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Layer::onExit();
}

bool Toolbag::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	this->removeChildByTag(10);
	
	return true;
}

void Toolbag::doSendMsg(Ref* pSender) {
	//option Scene
}

void Toolbag::doClose(Ref* pSender) {

	std::string str1 = "0";
	char str2[20] = { 0 };
	sprintf(str2, "%s", str1.c_str());
	NotificationCenter::getInstance()->postNotification("TouchTool", (Ref*)str2);

	this->removeFromParentAndCleanup(true);
}


void Toolbag::tableCellTouched(TableView* table, TableViewCell* cell) {
	num = cell->getIdx();
	for (int i = 0; i < sprite_vector.size(); i++) {
		if (cell->getChildByTag(num)->getTag() == sprite_vector.at(i)->getTag()) {
			sprite_vector.at(i)->setPosition(Vec2(0, 10));
		}
		else {
			sprite_vector.at(i)->setPosition(Vec2(0, 0));
		}
	}
}

Size Toolbag::tableCellSizeForIndex(TableView *table, ssize_t idx) {
	return CCSizeMake(150, 200);
}

TableViewCell* Toolbag::tableCellAtIndex(TableView *table, ssize_t idx) {
	//num = idx;
	char png[25];
	if (Items_List[idx]._ID == 6) {
		sprite_1 = Sprite::createWithSpriteFrameName("char_bg_earth.png");
	}
	if (Items_List[idx]._ID == 7) {
		sprite_1 = Sprite::createWithSpriteFrameName("char_bg_water.png");
	}
	if (Items_List[idx]._ID == 8) {
		sprite_1 = Sprite::createWithSpriteFrameName("char_bg_fire.png");
	}
	TableViewCell *cell = table->dequeueCell();

	cell = new CustomTableViewCell();
	cell->autorelease();

	sprite_1->setAnchorPoint(Vec2::ZERO);
	if (num == idx) {
		sprite_1->setPosition(Vec2(0, 10));
	}
	else {
		sprite_1->setPosition(Vec2(0, 0));
	}
	sprite_1->setScale(1.5);
	sprite_1->setTag(idx);
	sprite_vector.pushBack(sprite_1);
	cell->addChild(sprite_1);


	if (Items_List[idx]._ID == 6) {
		Items_List[idx].sprite = Sprite::createWithSpriteFrameName("items6.png");
	}
	else if (Items_List[idx]._ID == 7) {
		Items_List[idx].sprite = Sprite::createWithSpriteFrameName("items7.png");
	}
	else if (Items_List[idx]._ID == 8) {
		Items_List[idx].sprite = Sprite::createWithSpriteFrameName("items8.png");
	}
	Items_List[idx].sprite->setScale(1.5);
	Items_List[idx].sprite->setPosition(Vec2(sprite_1->getContentSize().width / 2, sprite_1->getContentSize().height / 2));

	sprite_1->addChild(Items_List[idx].sprite, 3);


	char level[3];
	sprintf(level, "%d", Items_List[idx].Num);
	auto pLabel3 = LabelAtlas::create(level, "Images/Scene/ML.png", 7, 9, '0');
	pLabel3->setAnchorPoint(Vec2(0, 0));
	pLabel3->setScale(1.5);
	pLabel3->setPosition(Vec2(sprite_1->getContentSize().width / 2 + 8, 10));
	sprite_1->addChild(pLabel3);

	return cell;
}

ssize_t Toolbag::numberOfCellsInTableView(TableView *table) {
	return ItemsListSize;
}
