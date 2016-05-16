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

	winSize = Director::getInstance()->getWinSize();

	CCSprite* title = CCSprite::create("Images/Scene/ClassChangeMap.png");
	title->setPosition(Vec2(640, 360));
	this->addChild(title);


	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";

	selectData(this);
	//CheckMonster();

	tableView1 = TableView::create(this, Size(700, 400));
	tableView1->setDirection(ScrollView::Direction::VERTICAL);
	//tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2((winSize.width - 700) / 2, (winSize.height - 400) / 2));
	tableView1->setAnchorPoint(Vec2(0, 0));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	//tableView1->setBounceable(false);
	tableView1->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	
	this->addChild(tableView1);
	tableView1->reloadData();
	num = 0;

	auto pMenuItem2 = MenuItemFont::create("선택", CC_CALLBACK_1(ClassChange::doContinue, this));
	pMenuItem2->setColor(Color3B(255, 255, 255));
	auto pMenuItem3 = MenuItemFont::create("나가기", CC_CALLBACK_1(ClassChange::doClose, this));
	pMenuItem3->setColor(Color3B(255, 255, 255));

	auto pMenu = Menu::create(pMenuItem2, pMenuItem3, nullptr);
	pMenu->alignItemsHorizontallyWithPadding(100.0f);
	pMenu->setPosition(Vec2(300, 50));
	title->addChild(pMenu);

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
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(ClassChange::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void ClassChange::onExit() {
	_eventDispatcher->removeEventListener(listener);
	
	Layer::onExit();
}

bool ClassChange::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode)) {
		//reZorder(target);
		log("sprite onTouchBegan... x= %f, y= %f", locationInNode.x, locationInNode.y);
		target->setOpacity(180);
		return true;
	}
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

void ClassChange::doContinue(Ref* pSender) {
	
}

void ClassChange::doSendMsg(Ref* pSender) {
	//option Scene
}

void ClassChange::doClose(Ref* pSender) {

}


void ClassChange::tableCellTouched(TableView* table, TableViewCell* cell) {
	num = cell->getIdx();
	log("%d", num);

}

Size ClassChange::tableCellSizeForIndex(TableView *table, ssize_t idx) {
	return CCSizeMake(100, 200);
}

TableViewCell* ClassChange::tableCellAtIndex(TableView *table, ssize_t idx) {
	//num = idx;
	
	char png[25];
	int ViewNum = idx;
	TableViewCell *cell = table->dequeueCell();
	tableViewSprite = Sprite::createWithSpriteFrameName("char_bg_earth.png");
	for (int i = 0; i < 4; i++) {
		if (ViewNum * 4 + i < MonsterListSize) {
			if (Monster_List[ViewNum * 4 + i].Type > 0 && Monster_List[ViewNum * 4 + i].Type < 10) {
				sprite_1 = Sprite::createWithSpriteFrameName("char_bg_earth.png");
			}
			else if (Monster_List[ViewNum * 4 + i].Type > 10 && Monster_List[ViewNum * 4 + i].Type < 20) {
				sprite_1 = Sprite::createWithSpriteFrameName("char_bg_fire.png");
			}
			else if (Monster_List[ViewNum * 4 + i].Type > 20 && Monster_List[ViewNum * 4 + i].Type < 30) {
				sprite_1 = Sprite::createWithSpriteFrameName("char_bg_water.png");
			}
			else if (Monster_List[ViewNum * 4 + i].Type > 30 && Monster_List[ViewNum * 4 + i].Type < 40) {
				sprite_1 = Sprite::createWithSpriteFrameName("char_bg_wind.png");
			}
			//290~433
			//440~583
			//590~733
			//740~833
			sprite_1->setAnchorPoint(Vec2::ZERO);
			sprite_1->setScale(1.0);
			sprite_1->setTag(ViewNum * 4 + i);
			sprite_1->setPosition(Vec2(i * 100, 0));
			sprite_vector.pushBack(sprite_1);
			tableViewSprite->addChild(sprite_1);

			Monster(ViewNum * 4 + i);
		}
	}
	tableViewSprite->setScale(1.5);
	tableViewSprite->setPosition(Vec2(0,0));
	tableViewSprite->setAnchorPoint(Vec2(0, 0));
	cell = new CustomTableViewCell();
	cell->autorelease();

	cell->addChild(tableViewSprite);

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

void ClassChange::Monster(int num) {
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
	Monster_List[num].sprite->setPosition(Vec2(sprite_1->getContentSize().width / 2, sprite_1->getContentSize().height / 2));

	sprite_1->addChild(Monster_List[num].sprite, 3);


	char level[3];
	sprintf(level, "%d", Monster_List[num].level);
	auto pLabel3 = LabelAtlas::create(level, "MonsterLevel.png", 7, 9, '0');
	pLabel3->setAnchorPoint(Vec2(0, 0));
	pLabel3->setScale(1.5);
	pLabel3->setPosition(Vec2(sprite_1->getContentSize().width / 2 + 8, 10));
	sprite_1->addChild(pLabel3);

	Sprite* Lv = Sprite::create("Images/Scene/Level.png");
	Lv->setAnchorPoint(Vec2(0, 0));
	Lv->setScale(1.5);
	Lv->setPosition(Vec2(sprite_1->getContentSize().width / 2 - 15, 10));
	sprite_1->addChild(Lv);

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