#include "CreateMonster.h"
#include "sqlite3.h"
#include "stdafx.h"
#include "CustomTableViewCell.h"

USING_NS_CC;

Scene* CreateMonster::createScene()
{
	auto scene = Scene::create();
	auto layer = CreateMonster::create();
	scene->addChild(layer);
	return scene;
}

bool CreateMonster::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
	{
		return false;
	}
	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Plist/char_bg.plist");

	winSize = Director::getInstance()->getWinSize();

	auto popLayer = CCLayerColor::create(Color4B(0, 0, 0, 255), 600, 400);
	popLayer->setAnchorPoint(Vec2(0, 0));
	popLayer->setPosition(Vec2((winSize.width - popLayer->getContentSize().width) / 2, (winSize.height - popLayer->getContentSize().height) / 2));

	this->addChild(popLayer);

	//DB불러오기
	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";

	selectData(this);
	CheckMonster();

	tableView1 = TableView::create(this, Size(500, 200));
	tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2((600 - 500) / 2, (400 - 200) / 2));
	tableView1->setAnchorPoint(Vec2(0, 0));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	popLayer->addChild(tableView1);
	tableView1->reloadData();
	num = 0;

	auto pMenuItem2 = MenuItemFont::create("선택", CC_CALLBACK_1(CreateMonster::doContinue, this));
	pMenuItem2->setColor(Color3B(255, 255, 255));
	auto pMenuItem3 = MenuItemFont::create("나가기", CC_CALLBACK_1(CreateMonster::doClose, this));
	pMenuItem3->setColor(Color3B(255, 255, 255));

	auto pMenu = Menu::create(pMenuItem2, pMenuItem3, nullptr);
	pMenu->alignItemsHorizontallyWithPadding(100.0f);
	pMenu->setPosition(Vec2(300, 50));
	popLayer->addChild(pMenu);

	return true;
}

void CreateMonster::onEnter() {
	Layer::onEnter();

}

void CreateMonster::onExit() {
	Layer::onExit();
}

void CreateMonster::selectData(Ref* pSender)
{
	sqlite3* pDB = NULL;
	char* errMsg = nullptr;
	int result;

	if (MonsterListSize) {
		free(Monster_List);
		MonsterListSize = 0;
	}

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
				if (MonsterListSize)	Monster_List = (Monster_num*)realloc(Monster_List,	sizeof(Monster_num) * (MonsterListSize + 1));
				else					Monster_List = (Monster_num*)malloc(				sizeof(Monster_num) * (MonsterListSize + 1));
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

void CreateMonster::doContinue(Ref* pSender) {
	//std::string str1 = "1";
	int ViewNum = -1;
	for (int i = 0; i < MonsterListSize; i++) {
		if (Monster_List[i].ViewNum == num) {
			ViewNum = i;
			break;
		}
	}

	char str2[20] = { 0 };
	sprintf(str2, "%d", ViewNum +1);
	if (ViewNum == -1) {
		log("소환할 몬스터가 없습니다.");
	}

	NotificationCenter::getInstance()->postNotification("TouchMonster", (Ref*)str2);
	this->removeFromParentAndCleanup(true);
}

void CreateMonster::doSendMsg(Ref* pSender) {
	//option Scene
}

void CreateMonster::doClose(Ref* pSender) {
	
	std::string str1 = "0";
	char str2[20] = { 0 };
	sprintf(str2, "%s", str1.c_str());
	NotificationCenter::getInstance()->postNotification("TouchMonster", (Ref*)str2);

	this->removeFromParentAndCleanup(true);
}


void CreateMonster::tableCellTouched(TableView* table, TableViewCell* cell) {
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

Size CreateMonster::tableCellSizeForIndex(TableView *table, ssize_t idx) {
	return CCSizeMake(150, 200);
}

TableViewCell* CreateMonster::tableCellAtIndex(TableView *table, ssize_t idx) {
	//num = idx;
	int ViewNum = idx;
	for (int i = 0; i < MonsterListSize; i++) {
		if (Monster_List[i].ViewNum == idx) {
			ViewNum = i;
		}
	}
	char png[25];
	TableViewCell *cell = table->dequeueCell();
	if (Monster_List[ViewNum].Type > 0 && Monster_List[ViewNum].Type < 10) {
		sprite_1 = Sprite::createWithSpriteFrameName("char_bg_earth.png");
	}
	else if (Monster_List[ViewNum].Type > 10 && Monster_List[ViewNum].Type < 20) {
		sprite_1 = Sprite::createWithSpriteFrameName("char_bg_fire.png");
	}
	else if (Monster_List[ViewNum].Type > 20 && Monster_List[ViewNum].Type < 30) {
		sprite_1 = Sprite::createWithSpriteFrameName("char_bg_water.png");
	}
	else if (Monster_List[ViewNum].Type > 30 && Monster_List[ViewNum].Type < 40) {
		sprite_1 = Sprite::createWithSpriteFrameName("char_bg_wind.png");
	}
	
	

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

	//몬스터 뷰
	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;
	//땅질퍽이
	if (Monster_List[ViewNum].Type == 1) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Earth1-1.png");
		sprintf(str1, "Earth1-");
	}
	else if (Monster_List[ViewNum].Type == 2) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Earth2-1.png");
		sprintf(str1, "Earth2-");
	}
	else if (Monster_List[ViewNum].Type == 3) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Earth3-1.png");
		sprintf(str1, "Earth3-");
	}
	//모닥픽
	else if (Monster_List[ViewNum].Type == 4) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Earth4-1.png");
		sprintf(str1, "Earth4-");
	}
	else if (Monster_List[ViewNum].Type == 5) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Earth5-1.png");
		sprintf(str1, "Earth5-");
	}
	else if (Monster_List[ViewNum].Type == 6) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Earth6-1.png");
		sprintf(str1, "Earth6-");
	}
	//모래두지
	else if (Monster_List[ViewNum].Type == 7) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Earth7-1.png");
		sprintf(str1, "Earth7-");
	}
	else if (Monster_List[ViewNum].Type == 8) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Earth8-1.png");
		sprintf(str1, "Earth8-");
	}
	else if (Monster_List[ViewNum].Type == 9) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Earth9-1.png");
		sprintf(str1, "Earth9-");
	}
	//파이뤼
	else if (Monster_List[ViewNum].Type == 11) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Fire1-1.png");
		sprintf(str1, "Fire1-");
	}
	else if (Monster_List[ViewNum].Type == 12) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Fire2-1.png");
		sprintf(str1, "Fire2-");
	}
	else if (Monster_List[ViewNum].Type == 13) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Fire3-1.png");
		sprintf(str1, "Fire3-");
	}
	//팬템
	else if (Monster_List[ViewNum].Type == 14) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Fire4-1.png");
		sprintf(str1, "Fire4-");
	}
	else if (Monster_List[ViewNum].Type == 15) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Fire5-1.png");
		sprintf(str1, "Fire5-");
	}
	else if (Monster_List[ViewNum].Type == 16) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Fire6-1.png");
		sprintf(str1, "Fire6-");
	}
	//블랙매직숀
	else if (Monster_List[ViewNum].Type == 17) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Fire7-1.png");
		sprintf(str1, "Fire7-");
	}
	else if (Monster_List[ViewNum].Type == 18) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Fire8-1.png");
		sprintf(str1, "Fire8-");
	}
	else if (Monster_List[ViewNum].Type == 19) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Fire9-1.png");
		sprintf(str1, "Fire9-");
	}
	//물질퍽이
	else if (Monster_List[ViewNum].Type == 21) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Water1-1.png");
		sprintf(str1, "Water1-");
	}
	else if (Monster_List[ViewNum].Type == 22) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Water2-1.png");
		sprintf(str1, "Water2-");
	}
	else if (Monster_List[ViewNum].Type == 23) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Water3-1.png");
		sprintf(str1, "Water3-");
	}
	//꼬북이
	else if (Monster_List[ViewNum].Type == 24) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Water4-1.png");
		sprintf(str1, "Water4-");
	}
	else if (Monster_List[ViewNum].Type == 25) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Water5-1.png");
		sprintf(str1, "Water5-");
	}
	else if (Monster_List[ViewNum].Type == 26) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Water6-1.png");
		sprintf(str1, "Water6-");
	}
	//리아커
	else if (Monster_List[ViewNum].Type == 27) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Water7-1.png");
		sprintf(str1, "Water7-");
	}
	else if (Monster_List[ViewNum].Type == 28) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Water8-1.png");
		sprintf(str1, "Water8-");
	}
	else if (Monster_List[ViewNum].Type == 29) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Water9-1.png");
		sprintf(str1, "Water9-");
	}
	//코이
	else if (Monster_List[ViewNum].Type == 31) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Wind1-1.png");
		sprintf(str1, "Wind1-");
	}
	else if (Monster_List[ViewNum].Type == 32) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Wind2-1.png");
		sprintf(str1, "Wind2-");
	}
	else if (Monster_List[ViewNum].Type == 33) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Wind3-1.png");
		sprintf(str1, "Wind3-");
	}
	//피젼
	else if (Monster_List[ViewNum].Type == 34) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Wind4-1.png");
		sprintf(str1, "Wind4-");
	}
	else if (Monster_List[ViewNum].Type == 35) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Wind5-1.png");
		sprintf(str1, "Wind5-");
	}
	else if (Monster_List[ViewNum].Type == 36) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Wind6-1.png");
		sprintf(str1, "Wind6-");
	}
	//코이
	else if (Monster_List[ViewNum].Type == 37) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Wind7-1.png");
		sprintf(str1, "Wind7-");
	}
	else if (Monster_List[ViewNum].Type == 38) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Wind8-1.png");
		sprintf(str1, "Wind8-");
	}
	else if (Monster_List[ViewNum].Type == 39) {
		Monster_List[ViewNum].sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
		sprintf(str1, "Wind9-");
	}

	Monster_List[ViewNum].sprite->setScale(0.75);
	Monster_List[ViewNum].sprite->setPosition(Vec2(sprite_1->getContentSize().width/2, sprite_1->getContentSize().height/2));
	
	sprite_1->addChild(Monster_List[ViewNum].sprite, 3);
	

	char level[3];
	sprintf(level, "%d", Monster_List[ViewNum].level);
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
	Monster_List[ViewNum].sprite->runAction(rep);

	return cell;
}

ssize_t CreateMonster::numberOfCellsInTableView(TableView *table) {
	return MonsterListSize - EarthSize - FireSize - WaterSize - WindSize;
}

void CreateMonster::CheckMonster() {
	int ViewNum = 0;
	for (int i = 0; i < MonsterListSize; i++) {
		Monster_List[i].View = true;
		for (int m = 0; m < monsterSize; m++) {
			if (Monster_List[i].ID == monster_char[m].ID) {
				Monster_List[i].View = false;
				if (Monster_List[i].Type > 0 && Monster_List[i].Type < 10) {
					EarthSize++;
				}
				else if (Monster_List[i].Type > 10 && Monster_List[i].Type < 20) {
					FireSize++;
				}
				else if (Monster_List[i].Type > 20 && Monster_List[i].Type < 30) {
					WaterSize++;
				}
				else if (Monster_List[i].Type > 30 && Monster_List[i].Type < 40) {
					WindSize++;
				}
				break;
			}
			else if(m == monsterSize - 1){
				Monster_List[i].ViewNum = ViewNum;
				ViewNum++;
			}
		}
	}
}