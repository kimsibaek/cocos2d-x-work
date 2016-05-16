#include "ClassChange.h"
#include "MainScene.h"
#include "sqlite3.h"
#include "stdafx.h"
USING_NS_CC;

Scene* ClassChange::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ClassChange::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ClassChange::init()
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

	cache->addSpriteFramesWithFile("Plist/EarthUpgrade.plist");
	cache->addSpriteFramesWithFile("Plist/FireUpgrade.plist");
	cache->addSpriteFramesWithFile("Plist/WindUpgrade.plist");
	cache->addSpriteFramesWithFile("Plist/WaterUpgrade.plist");

	winSize = Director::getInstance()->getWinSize();

	CCSprite* title = CCSprite::create("Images/Scene/ClassChangeMap.png");
	title->setPosition(Vec2(640, 360));
	this->addChild(title);


	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";

	selectData(this);
	//CheckMonster();

	tableView1 = TableView::create(this, Size(800, 600));
	tableView1->setDirection(ScrollView::Direction::VERTICAL);
	//tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2((winSize.width - 1200) / 2, (winSize.height - 600) / 2));
	tableView1->setAnchorPoint(Vec2(0, 0));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	//tableView1->setBounceable(false);
	tableView1->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	
	this->addChild(tableView1);
	tableView1->reloadData();
	Cell_Num = -1;
	MonsterCellNum = -1;

	MenuItemFont::setFontSize(64);
	auto pMenuItem2 = MenuItemFont::create("진화", CC_CALLBACK_1(ClassChange::doContinue, this));
	pMenuItem2->setColor(Color3B(255, 255, 255));
	/*
	auto pMenuItem3 = MenuItemFont::create("방출", CC_CALLBACK_1(ClassChange::doClose, this));
	pMenuItem3->setColor(Color3B(255, 255, 255));
*/
	auto pMenu = Menu::create(pMenuItem2, nullptr);
	pMenu->alignItemsVerticallyWithPadding(100.0f);
	pMenu->setPosition(Vec2(1000, 360));
	this->addChild(pMenu);

	auto pMenuItem1 = MenuItemImage::create("Images/Scene/Back.png", "Images/Scene/Back_click.png", CC_CALLBACK_1(ClassChange::doClick1, this));
	pMenuItem1->setPosition(Vec2(1230, 670));
	pMenuItem1->setScale(0.2);
	pMenuItem1->setTag(1);
	//auto pMenuItem7 = MenuItemImage::create("Images/Scene/Exit.png", "Images/Scene/Exit_click.png", CC_CALLBACK_1(MainScene::doClick1, this));
	auto pMenu1 = Menu::create(pMenuItem1, nullptr);
	pMenu1->setPosition(Vec2(0, 0));
	this->addChild(pMenu1);

	return true;
}


void ClassChange::doClick1(Ref *pSender) {
	auto tItem = (MenuItem *)pSender;

	int i = tItem->getTag();
	log("%d번째 메뉴가 선택되었습니다.", i);
	if (i == 1) {
		auto pScene = MainScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	
}

void ClassChange::onEnter() {
	Layer::onEnter();
	listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(ClassChange::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//_eventDispatcher->addEventListenerWithFixedPriority(listener, 2);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, 30);
}

void ClassChange::onExit() {
	_eventDispatcher->removeEventListener(listener);
	if (MonsterListSize) {
		free(Monster_List);
		MonsterListSize = 0;
	}
	Layer::onExit();
}

bool ClassChange::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	//log("onTouchBegan... ");
	return true;
}

void ClassChange::selectData(Ref* pSender)
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

void ClassChange::UpdateMonsterDB(int num, int Type) {
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

	sprintf(sqlstr, "update Monster set Type = %d, level = 1, Exp = 0  where Monster_Id = %d", Type, num + 1);
	log(sqlstr);
	sqlStr = sqlstr;
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);


	if (result != SQLITE_OK)
	{
		log("update Error : Code:%d  Msg:%s", result, errMsg);
	}

	sqlite3_close(pDB);
}

void ClassChange::doContinue(Ref* pSender) {
	if (Monster_List[MonsterCellNum].level != 10) {
		log("Monster_List[%d] = %d 레벨이 부족합니다.", MonsterCellNum, Monster_List[MonsterCellNum].level);
		return;
	}
	else {
		if (CheckClass(Monster_List[MonsterCellNum].Type)) {
			Monster_List[MonsterCellNum].Type++;
			Monster_List[MonsterCellNum].level = 1;
			UpdateMonsterDB(MonsterCellNum, Monster_List[MonsterCellNum].Type);
			TableViewCell *cell1 = tableView1->cellAtIndex(MonsterCellNum/4);
			Sprite *st = (Sprite *)cell1->getChildByTag(MonsterCellNum/4);
			Sprite *st1 = (Sprite *)st->getChildByTag(MonsterCellNum);
			st1->removeAllChildren();
			
			/////////////////////////////////진화액션/////////////////////////////////////////////////////////
			char str1[100];
			char str2[100];
			Vector<SpriteFrame*> animFrame;
			if (Monster_List[MonsterCellNum].Type > 0 && Monster_List[MonsterCellNum].Type < 10) {
				//log("대지속성");
				Upgrade = Sprite::createWithSpriteFrameName("EarthUpgrade1.png");
				sprintf(str1, "EarthUpgrade");
				for (int i = 1; i < 13; i++) {
					sprintf(str2, "%s%d.png", str1, i);
					SpriteFrame* frame = cache->getSpriteFrameByName(str2);
					animFrame.pushBack(frame);
				}
			}
			if (Monster_List[MonsterCellNum].Type > 10 && Monster_List[MonsterCellNum].Type < 20) {
				//log("불속성");
				Upgrade = Sprite::createWithSpriteFrameName("FireUpgrade1.png");
				sprintf(str1, "FireUpgrade");
				for (int i = 1; i < 13; i++) {
					sprintf(str2, "%s%d.png", str1, i);
					SpriteFrame* frame = cache->getSpriteFrameByName(str2);
					animFrame.pushBack(frame);
				}
			}
			if (Monster_List[MonsterCellNum].Type > 20 && Monster_List[MonsterCellNum].Type < 30) {
				//log("물속성");
				Upgrade = Sprite::createWithSpriteFrameName("WaterUpgrade1.png");
				sprintf(str1, "WaterUpgrade");
				for (int i = 1; i < 13; i++) {
					sprintf(str2, "%s%d.png", str1, i);
					SpriteFrame* frame = cache->getSpriteFrameByName(str2);
					animFrame.pushBack(frame);
				}
			}
			if (Monster_List[MonsterCellNum].Type > 30 && Monster_List[MonsterCellNum].Type < 40) {
				//log("바람속성");
				Upgrade = Sprite::createWithSpriteFrameName("WindUpgrade1.png");
				sprintf(str1, "WindUpgrade");
				for (int i = 1; i < 13; i++) {
					sprintf(str2, "%s%d.png", str1, i);
					SpriteFrame* frame = cache->getSpriteFrameByName(str2);
					animFrame.pushBack(frame);
				}
			}
			Upgrade->setScale(1.5);
			Upgrade->setAnchorPoint(Vec2(0.5, 0.5));
			Upgrade->setPosition(Vec2(st1->getContentSize().width/2, st1->getContentSize().height / 2));


			auto animation = Animation::createWithSpriteFrames(animFrame, 0.1f);
			auto animate = Animate::create(animation);
			auto cbSound = CallFunc::create(CC_CALLBACK_0(ClassChange::RemoveSprite, this));
			auto seq = Sequence::create(animate, cbSound, NULL);
			Upgrade->runAction(seq);
			st1->addChild(Upgrade, 5);
			////////////////////////////////////////////////////////////////////////////////////////////
			
			MonsterAdd(MonsterCellNum, st1);
		}
		else {
			log("더이상 진화 할수 없습니다.");
		}
	}
}

void ClassChange::RemoveSprite() {
	TableViewCell *cell1 = tableView1->cellAtIndex(MonsterCellNum / 4);
	Sprite *st = (Sprite *)cell1->getChildByTag(MonsterCellNum / 4);
	Sprite *st1 = (Sprite *)st->getChildByTag(MonsterCellNum);
	st1->removeChild(Upgrade, true);
}

bool ClassChange::CheckClass(int num) {
	if (num == 3 || num == 6 || num == 9 || num == 13 || num == 16 || num == 19 || num == 23 || num == 26 || num == 29 || num == 33 || num == 36 || num == 39) {
		return false;
	}
	return true;
}

void ClassChange::doSendMsg(Ref* pSender) {
	//option Scene
}

void ClassChange::doClose(Ref* pSender) {

}


void ClassChange::tableCellTouched(TableView* table, TableViewCell* cell) {
	Cell_Num = cell->getIdx();
	
	log("cell = %d, MonsterCellNum = %d", Cell_Num, MonsterCellNum);
	
	
	for (int i = 0; i < MonsterListSize; i++) {
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

Size ClassChange::tableCellSizeForIndex(TableView *table, ssize_t idx) {
	return CCSizeMake(150, 275);
}

TableViewCell* ClassChange::tableCellAtIndex(TableView *table, ssize_t idx) {
	//num = idx;
	
	char png[25];
	int ViewNum = idx;
	TableViewCell *cell = table->dequeueCell();
	tableViewSprite = Sprite::createWithSpriteFrameName("char_bg_earth.png");
	for (int i = 0; i < 4; i++) {
		if (ViewNum * 4 + i < MonsterListSize) {
			temp[i] = new MonsterCell();
			if (Monster_List[ViewNum * 4 + i].Type > 0 && Monster_List[ViewNum * 4 + i].Type < 10) {
				temp[i]->setTexture("Images/Scene/char_bg_earth.png");
				//sprite_1 = Sprite::createWithSpriteFrameName("char_bg_earth.png");
			}
			else if (Monster_List[ViewNum * 4 + i].Type > 10 && Monster_List[ViewNum * 4 + i].Type < 20) {
				temp[i]->setTexture("Images/Scene/char_bg_fire.png");
				//sprite_1 = Sprite::createWithSpriteFrameName("char_bg_fire.png");
			}
			else if (Monster_List[ViewNum * 4 + i].Type > 20 && Monster_List[ViewNum * 4 + i].Type < 30) {
				temp[i]->setTexture("Images/Scene/char_bg_water.png");
				//sprite_1 = Sprite::createWithSpriteFrameName("char_bg_water.png");
			}
			else if (Monster_List[ViewNum * 4 + i].Type > 30 && Monster_List[ViewNum * 4 + i].Type < 40) {
				temp[i]->setTexture("Images/Scene/char_bg_wind.png");
				//sprite_1 = Sprite::createWithSpriteFrameName("char_bg_wind.png");
			}
			temp[i]->setAnchorPoint(Vec2::ZERO);
			temp[i]->setTag(ViewNum * 4 + i);
			temp[i]->setPosition(Vec2(i * 100, 0));
			temp[i]->setPriority(ViewNum * 4 + i);
			temp[i]->setPriorityWithThis(true);
			tableViewSprite->addChild(temp[i]);
			//sprite_1->setAnchorPoint(Vec2::ZERO);
			//sprite_1->setScale(1.0);
			//sprite_1->setTag(ViewNum * 4 + i);
			//sprite_1->setPosition(Vec2(i * 100, 0));
			//sprite_vector.pushBack(sprite_1);
			//tableViewSprite->addChild(sprite_1);
			Monster(ViewNum * 4 + i, i);
		}
	}
	tableViewSprite->setScale(2);
	tableViewSprite->setPosition(Vec2(0,0));
	tableViewSprite->setAnchorPoint(Vec2(0, 0));
	cell = new CustomTableViewCell();
	cell->autorelease();

	cell->addChild(tableViewSprite, 0, idx);

	return cell;
}

ssize_t ClassChange::numberOfCellsInTableView(TableView *table) {
	int num1 = 0;
	if (MonsterListSize % 4 == 0) {
		num1 = MonsterListSize / 4;
	}
	else {
		num1 = MonsterListSize / 4 + 1;
	}
	return num1;
}

void ClassChange::Monster(int num, int row) {
	//땅질퍽이
	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;
	if (Monster_List[num].Type == 1) {
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
	auto pLabel3 = LabelAtlas::create(level, "MonsterLevel.png", 7, 9, '0');
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

void ClassChange::MonsterAdd(int num, Sprite *st) {
	//땅질퍽이
	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;
	if (Monster_List[num].Type == 1) {
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
	Monster_List[num].sprite->setPosition(Vec2(st->getContentSize().width / 2, st->getContentSize().height / 2));

	st->addChild(Monster_List[num].sprite, 3);


	char level[3];
	sprintf(level, "%d", Monster_List[num].level);
	auto pLabel3 = LabelAtlas::create(level, "MonsterLevel.png", 7, 9, '0');
	pLabel3->setAnchorPoint(Vec2(0, 0));
	pLabel3->setScale(1.5);
	pLabel3->setPosition(Vec2(st->getContentSize().width / 2 + 8, 10));
	st->addChild(pLabel3, 4);

	Sprite* Lv = Sprite::create("Images/Scene/Level.png");
	Lv->setAnchorPoint(Vec2(0, 0));
	Lv->setScale(1.5);
	Lv->setPosition(Vec2(st->getContentSize().width / 2 - 15, 10));
	st->addChild(Lv, 4);

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