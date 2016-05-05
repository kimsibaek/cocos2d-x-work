#include "EarthMap.h"
#include "pauseScene.h"
#include "CreateMonster.h"
#include "MainScene.h"
#include "sqlite3.h"
#include "stdafx.h"
#include <time.h>
USING_NS_CC;

Scene* EarthMap::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = EarthMap::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool EarthMap::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	////////////////////
	srand(time(NULL));

	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Plist/Person1.plist");
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
	cache->addSpriteFramesWithFile("Plist/HexInfo.plist");
	cache->addSpriteFramesWithFile("Plist/etc.plist");

	BG = Sprite::create("Images/Scene/EarthMap.png");
	BG->setPosition(Vec2(1006.5, 767.5));
	this->addChild(BG, 1);

	this->setPosition(Vec2(0, 0));

	tmap = TMXTiledMap::create("Images/Scene/EarthMapTest.tmx");
	tmap->setPosition(Vec2(-33, -16));
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap, 2, 11);

	MovePositionX = tmap->getPosition().x;
	MovePositionY = tmap->getPosition().y;
	//pause
	pause = Sprite::create("Images/Scene/pause.png");
	pause->setPosition(Vec2(1230, 670));
	pause->setScale(0.4);
	this->addChild(pause, 4);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(EarthMap::doMsgReceived), "TouchStatus", nullptr);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(EarthMap::doMsgReceivedMonster), "TouchMonster", nullptr);

	//DB불러오기
	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";
	//log("%s", dbfileName.c_str());
	
	onCreateCharacter();
	onCreateEmyCharacter();
	//주인공이 화면의 센터로
	FocusCharacter();

	//주인공 클릭상태
	CharacterClick = false;

	//아군몬스터가 도구, 소환 작업 상태
	status = false;
	touchMove = true;
	//몬스터 소환상태
	b_CreateMonster = false;
	return true;
}

//주인공 생성
void EarthMap::onCreateCharacter() {
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
		if (monsterSize) {
			free(monster_char);
			monsterSize = 0;
		}
		
		std::string str1 = "";
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//객체생성
			if (monsterSize)	monster_char = (Monster_num*)realloc(monster_char,	sizeof(Monster_num) * (monsterSize + 1));
			else				monster_char = (Monster_num*)malloc(				sizeof(Monster_num) * (monsterSize + 1));
			int	ID = sqlite3_column_int(statement, 0);
			int	Type = sqlite3_column_int(statement, 1);
			int	level = sqlite3_column_int(statement, 2);
			int	Item1 = sqlite3_column_int(statement, 3);
			int	Item2 = sqlite3_column_int(statement, 4);
			int	Item3 = sqlite3_column_int(statement, 5);
			int	Exp = sqlite3_column_int(statement, 6);

			monster_char[monsterSize].ID = ID;
			monster_char[monsterSize].Type = Type;
			monster_char[monsterSize].level = level;
			monster_char[monsterSize].Item1 = Item1;
			monster_char[monsterSize].Item2 = Item2;
			monster_char[monsterSize].Item3 = Item3;
			monster_char[monsterSize].exp = Exp;

			monster_char[monsterSize]._turn = true;
			monsterSize++;
			break;
		}
	}

	sqlite3_finalize(statement);

	sqlite3_close(pDB);
	
	if (monster_char[0].ID == 0) {
		monster_char[0].atk = 20 + ((monster_char[0].level - 1) * 2);
		monster_char[0].def = 10 + ((monster_char[0].level - 1) * 1);
		monster_char[0].hp = 40 + ((monster_char[0].level - 1) * 4);
		monster_char[0].move = 3;
		monster_char[0].HPbarPosition = 21.5;
	}

	int num1 = rand() % 30 + 1;
	int num2 = rand() % 30 + 1;

	while (!ChecksPosition(num1, num2)) {
		num1 = rand() % 30 + 1;
		num2 = rand() % 30 + 1;
	}
	monster_char[0].tx = num1;
	monster_char[0].ty = num2;
	log("monster = %d, %d", num1, num2);
	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;
	//log("monster_char[i].Type : %d", monster_char[i].Type);
	if (monster_char[0].Type == 0) {
			
		monster_char[0].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
	}

	monster_char[0].sprite->setScale(1.5);
	if (num2 % 2 == 0) {
		monster_char[0].sprite->setPosition(64 * num1, 1551 - (37 + 48 * num2));
		monster_char[0].xPosition = 64 * num1;
		monster_char[0].yPosition = 1551 - (37 + 48 * num2);
		monster_char[0].xMovePosition = 64 * num1;
		monster_char[0].yMovePosition = 1551 - (37 + 48 * num2);
	}
	else {
		monster_char[0].sprite->setPosition(32 + 64 * num1, 1551 - (37 + 48 * num2));
		monster_char[0].xPosition = 32 + 64 * num1;
		monster_char[0].yPosition = 1551 - (37 + 48 * num2);
		monster_char[0].xMovePosition = 32 + 64 * num1;
		monster_char[0].yMovePosition = 1551 - (37 + 48 * num2);
	}
	//log("monster_char[i] = %f, %f", monster_char[i].xPosition, monster_char[i].yPosition);
	this->addChild(monster_char[0].sprite, 3);

	Sprite* st = Sprite::createWithSpriteFrameName("HP_bar.png");
	st->setPosition(0, -5);
	st->setScaleX(monster_char[0].HPbarPosition / 25 * 2);
	st->setAnchorPoint(Vec2(0, 0.5));
	monster_char[0].sprite->addChild(st, 4);

	Sprite* hp = Sprite::createWithSpriteFrameName("Monster_HP.png");
	hp->setPosition(1, 0);
	hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
	hp->setAnchorPoint(Vec2(0, 0));
	st->addChild(hp, 4);
	
	char level[3];
	sprintf(level, "%d", monster_char[0].level);
	auto pLabel3 = LabelAtlas::create(level, "Images/monsterLevel.png", 7, 9, '0');
	pLabel3->setAnchorPoint(Vec2(0, 0));
	pLabel3->setPosition(Vec2(hp->getContentSize().width*(monster_char[0].HPbarPosition / 25 * 2), -5));
	monster_char[0].sprite->addChild(pLabel3);

	Sprite* End = Sprite::createWithSpriteFrameName("End.png");
	End->setAnchorPoint(Vec2(0, 0));
	End->setPosition(Vec2(0, 0));
	if (monster_char[0].move) {

	}
	else {
		monster_char[0].sprite->addChild(End);
	}
	

	for (int i = 1; i < 5; i++) {
		sprintf(str2, "%s%d.png", str1, i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str2);
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	monster_char[0].sprite->runAction(rep);

}

void EarthMap::onCreateEmyCharacter() {
	if (EmyMonsterSize) {
		free(EmyMonster_char);
		EmyMonsterSize = 0;
	}

	std::string str1 = "";
	for(int i=0; i<10; i++)
	{
		//객체생성
		int num = rand() % 39 + 1;
		while (num == 10 || num == 20 || num == 30) {
			num = rand() % 39 + 1;
		}
		
		if (EmyMonsterSize)	EmyMonster_char = (Monster_num*)realloc(EmyMonster_char, sizeof(Monster_num) * (EmyMonsterSize + 1));
		else				EmyMonster_char = (Monster_num*)malloc(sizeof(Monster_num) * (EmyMonsterSize + 1));
		int	ID = i;
		int	Type = num;
		int	level = 1;
		int	Item1 = 0;
		int	Item2 = 0;
		int	Item3 = 0;

		EmyMonster_char[EmyMonsterSize].ID = ID;
		EmyMonster_char[EmyMonsterSize].Type = Type;
		EmyMonster_char[EmyMonsterSize].level = level;
		EmyMonster_char[EmyMonsterSize].Item1 = Item1;
		EmyMonster_char[EmyMonsterSize].Item2 = Item2;
		EmyMonster_char[EmyMonsterSize].Item3 = Item3;

		EmyMonster_char[EmyMonsterSize].exp = 0;

		EmyMonster_char[EmyMonsterSize]._turn = false;
		EmyMonsterSize++;
	}

	for (int i = 0; i < EmyMonsterSize; i++) {
		int num1 = rand() % 30 + 1;
		int num2 = rand() % 30 + 1;

		while (!ChecksPosition(num1, num2)) {
			num1 = rand() % 30 + 1;
			num2 = rand() % 30 + 1;
		}
		EmyMonster_char[i].tx = num1;
		EmyMonster_char[i].ty = num2;
		log("EmyMonster[%d] = %d, %d", i, num1, num2);
		char str1[100];
		char str2[100];
		Vector<SpriteFrame*> animFrames;
		//땅질퍽이
		if (EmyMonster_char[i].Type == 1) {
			EmyMonster_char[i].atk = 15 + ((EmyMonster_char[i].level - 1) * 1.5);
			EmyMonster_char[i].def = 3 + ((EmyMonster_char[i].level - 1) * 0.3);
			EmyMonster_char[i].hp = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 14.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth1-1.png");
			sprintf(str1, "Earth1-");
		}
		else if (EmyMonster_char[i].Type == 2) {
			EmyMonster_char[i].atk = 20 + ((EmyMonster_char[i].level - 1) * 2);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 45 + ((EmyMonster_char[i].level - 1) * 4.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 17;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth2-1.png");
			sprintf(str1, "Earth2-");
		}
		else if (EmyMonster_char[i].Type == 3) {
			EmyMonster_char[i].atk = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].def = 5 + ((EmyMonster_char[i].level - 1) * 0.5);
			EmyMonster_char[i].hp = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 25;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth3-1.png");
			sprintf(str1, "Earth3-");
		}
		//모닥픽
		else if (EmyMonster_char[i].Type == 4) {
			EmyMonster_char[i].atk = 10 + ((EmyMonster_char[i].level - 1) * 1.0);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 9;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth4-1.png");
			sprintf(str1, "Earth4-");
		}
		else if (EmyMonster_char[i].Type == 5) {
			EmyMonster_char[i].atk = 20 + ((EmyMonster_char[i].level - 1) * 2);
			EmyMonster_char[i].def = 5 + ((EmyMonster_char[i].level - 1) * 0.5);
			EmyMonster_char[i].hp = 45 + ((EmyMonster_char[i].level - 1) * 4.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 12.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth5-1.png");
			sprintf(str1, "Earth5-");
		}
		else if (EmyMonster_char[i].Type == 6) {
			EmyMonster_char[i].atk = 30 + ((EmyMonster_char[i].level - 1) * 3.0);
			EmyMonster_char[i].def = 6 + ((EmyMonster_char[i].level - 1) * 0.6);
			EmyMonster_char[i].hp = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 20;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth6-1.png");
			sprintf(str1, "Earth6-");
		}
		//모래두지
		else if (EmyMonster_char[i].Type == 7) {
			EmyMonster_char[i].atk = 10 + ((EmyMonster_char[i].level - 1) * 1.0);
			EmyMonster_char[i].def = 2 + ((EmyMonster_char[i].level - 1) * 0.2);
			EmyMonster_char[i].hp = 20 + ((EmyMonster_char[i].level - 1) * 2);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 19;    			
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth7-1.png");
			sprintf(str1, "Earth7-");
		}
		else if (EmyMonster_char[i].Type == 8) {
			EmyMonster_char[i].atk = 15 + ((EmyMonster_char[i].level - 1) * 1.5);
			EmyMonster_char[i].def = 3 + ((EmyMonster_char[i].level - 1) * 0.3);
			EmyMonster_char[i].hp = 35 + ((EmyMonster_char[i].level - 1) * 3.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 20;   
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth8-1.png");
			sprintf(str1, "Earth8-");
		}
		else if (EmyMonster_char[i].Type == 9) {
			EmyMonster_char[i].atk = 25 + ((EmyMonster_char[i].level - 1) * 2.5);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 17;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth9-1.png");
			sprintf(str1, "Earth9-");
		}
		//파이뤼
		else if (EmyMonster_char[i].Type == 11) {
			EmyMonster_char[i].atk = 15 + ((EmyMonster_char[i].level - 1) * 1.5);
			EmyMonster_char[i].def = 3 + ((EmyMonster_char[i].level - 1) * 0.3);
			EmyMonster_char[i].hp = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 13.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire1-1.png");
			sprintf(str1, "Fire1-");
		}
		else if (EmyMonster_char[i].Type == 12) {
			EmyMonster_char[i].atk = 20 + ((EmyMonster_char[i].level - 1) * 2);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 45 + ((EmyMonster_char[i].level - 1) * 4.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 21;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire2-1.png");
			sprintf(str1, "Fire2-");
		}
		else if (EmyMonster_char[i].Type == 13) {
			EmyMonster_char[i].atk = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].def = 5 + ((EmyMonster_char[i].level - 1) * 0.5);
			EmyMonster_char[i].hp = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 23.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire3-1.png");
			sprintf(str1, "Fire3-");
		}
		//팬템
		else if (EmyMonster_char[i].Type == 14) {
			EmyMonster_char[i].atk = 10 + ((EmyMonster_char[i].level - 1) * 1.0);
			EmyMonster_char[i].def = 3 + ((EmyMonster_char[i].level - 1) * 0.3);
			EmyMonster_char[i].hp = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 19;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire4-1.png");
			sprintf(str1, "Fire4-");
		}
		else if (EmyMonster_char[i].Type == 15) {
			EmyMonster_char[i].atk = 20 + ((EmyMonster_char[i].level - 1) * 2);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 45 + ((EmyMonster_char[i].level - 1) * 4.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 23.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire5-1.png");
			sprintf(str1, "Fire5-");
		}
		else if (EmyMonster_char[i].Type == 16) {
			EmyMonster_char[i].atk = 35 + ((EmyMonster_char[i].level - 1) * 3.5);
			EmyMonster_char[i].def = 5 + ((EmyMonster_char[i].level - 1) * 0.5);
			EmyMonster_char[i].hp = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 23.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire6-1.png");
			sprintf(str1, "Fire6-");
		}
		//블랙매직숀
		else if (EmyMonster_char[i].Type == 17) {
			EmyMonster_char[i].atk = 10 + ((EmyMonster_char[i].level - 1) * 1);
			EmyMonster_char[i].def = 3 + ((EmyMonster_char[i].level - 1) * 0.3);
			EmyMonster_char[i].hp = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 22;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire7-1.png");
			sprintf(str1, "Fire7-");
		}
		else if (EmyMonster_char[i].Type == 18) {
			EmyMonster_char[i].atk = 15 + ((EmyMonster_char[i].level - 1) * 1.5);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 45 + ((EmyMonster_char[i].level - 1) * 4.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 25.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire8-1.png");
			sprintf(str1, "Fire8-");
		}
		else if (EmyMonster_char[i].Type == 19) {
			EmyMonster_char[i].atk = 25 + ((EmyMonster_char[i].level - 1) * 2.5);
			EmyMonster_char[i].def = 5 + ((EmyMonster_char[i].level - 1) * 0.5);
			EmyMonster_char[i].hp = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 21;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire9-1.png");
			sprintf(str1, "Fire9-");
		}
		//물질퍽이
		else if (EmyMonster_char[i].Type == 21) {
			EmyMonster_char[i].atk = 15 + ((EmyMonster_char[i].level - 1) * 1.5);
			EmyMonster_char[i].def = 3 + ((EmyMonster_char[i].level - 1) * 0.3);
			EmyMonster_char[i].hp = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 14.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water1-1.png");
			sprintf(str1, "Water1-");
		}
		else if (EmyMonster_char[i].Type == 22) {
			EmyMonster_char[i].atk = 20 + ((EmyMonster_char[i].level - 1) * 2);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 45 + ((EmyMonster_char[i].level - 1) * 4.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 13.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water2-1.png");
			sprintf(str1, "Water2-");
		}
		else if (EmyMonster_char[i].Type == 23) {
			EmyMonster_char[i].atk = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].def = 5 + ((EmyMonster_char[i].level - 1) * 0.5);
			EmyMonster_char[i].hp = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 25;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water3-1.png");
			sprintf(str1, "Water3-");
		}
		//꼬북이
		else if (EmyMonster_char[i].Type == 24) {
			EmyMonster_char[i].atk = 10 + ((EmyMonster_char[i].level - 1) * 1.0);
			EmyMonster_char[i].def = 3 + ((EmyMonster_char[i].level - 1) * 0.3);
			EmyMonster_char[i].hp = 35 + ((EmyMonster_char[i].level - 1) * 3.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 20;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water4-1.png");
			sprintf(str1, "Water4-");
		}
		else if (EmyMonster_char[i].Type == 25) {
			EmyMonster_char[i].atk = 20 + ((EmyMonster_char[i].level - 1) * 2);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 22.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water5-1.png");
			sprintf(str1, "Water5-");
		}
		else if (EmyMonster_char[i].Type == 26) {
			EmyMonster_char[i].atk = 35 + ((EmyMonster_char[i].level - 1) * 3.5);
			EmyMonster_char[i].def = 5 + ((EmyMonster_char[i].level - 1) * 0.5);
			EmyMonster_char[i].hp = 65 + ((EmyMonster_char[i].level - 1) * 6.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 25;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water6-1.png");
			sprintf(str1, "Water6-");
		}
		//리아커
		else if (EmyMonster_char[i].Type == 27) {
			EmyMonster_char[i].atk = 10 + ((EmyMonster_char[i].level - 1) * 1.0);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 20;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water7-1.png");
			sprintf(str1, "Water7-");
		}
		else if (EmyMonster_char[i].Type == 28) {
			EmyMonster_char[i].atk = 20 + ((EmyMonster_char[i].level - 1) * 2);
			EmyMonster_char[i].def = 5 + ((EmyMonster_char[i].level - 1) * 0.5);
			EmyMonster_char[i].hp = 45 + ((EmyMonster_char[i].level - 1) * 4.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 22.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water8-1.png");
			sprintf(str1, "Water8-");
		}
		else if (EmyMonster_char[i].Type == 29) {
			EmyMonster_char[i].atk = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].def = 6 + ((EmyMonster_char[i].level - 1) * 0.6);
			EmyMonster_char[i].hp = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 28;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water9-1.png");
			sprintf(str1, "Water9-");
		}
		//코이
		else if (EmyMonster_char[i].Type == 31) {
			EmyMonster_char[i].atk = 15 + ((EmyMonster_char[i].level - 1) * 1.5);
			EmyMonster_char[i].def = 3 + ((EmyMonster_char[i].level - 1) * 0.3);
			EmyMonster_char[i].hp = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 19; 
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind1-1.png");
			sprintf(str1, "Wind1-");
		}
		else if (EmyMonster_char[i].Type == 32) {
			EmyMonster_char[i].atk = 20 + ((EmyMonster_char[i].level - 1) * 2);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 45 + ((EmyMonster_char[i].level - 1) * 4.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 18.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind2-1.png");
			sprintf(str1, "Wind2-");
		}
		else if (EmyMonster_char[i].Type == 33) {
			EmyMonster_char[i].atk = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].def = 5 + ((EmyMonster_char[i].level - 1) * 0.5);
			EmyMonster_char[i].hp = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 19.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind3-1.png");
			sprintf(str1, "Wind3-");
		}
		//피젼
		else if (EmyMonster_char[i].Type == 34) {
			EmyMonster_char[i].atk = 10 + ((EmyMonster_char[i].level - 1) * 1.0);
			EmyMonster_char[i].def = 3 + ((EmyMonster_char[i].level - 1) * 0.3);
			EmyMonster_char[i].hp = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 11.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind4-1.png");
			sprintf(str1, "Wind4-");
		}
		else if (EmyMonster_char[i].Type == 35) {
			EmyMonster_char[i].atk = 20 + ((EmyMonster_char[i].level - 1) * 2);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 45 + ((EmyMonster_char[i].level - 1) * 4.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 17.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind5-1.png");
			sprintf(str1, "Wind5-");
		}
		else if (EmyMonster_char[i].Type == 36) {
			EmyMonster_char[i].atk = 35 + ((EmyMonster_char[i].level - 1) * 3.5);
			EmyMonster_char[i].def = 5 + ((EmyMonster_char[i].level - 1) * 0.5);
			EmyMonster_char[i].hp = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 20;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind6-1.png");
			sprintf(str1, "Wind6-");
		}
		//코이
		else if (EmyMonster_char[i].Type == 37) {
			EmyMonster_char[i].atk = 10 + ((EmyMonster_char[i].level - 1) * 1.0);
			EmyMonster_char[i].def = 3 + ((EmyMonster_char[i].level - 1) * 0.3);
			EmyMonster_char[i].hp = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 20;   
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind7-1.png");
			sprintf(str1, "Wind7-");
		}
		else if (EmyMonster_char[i].Type == 38) {
			EmyMonster_char[i].atk = 15 + ((EmyMonster_char[i].level - 1) * 1.5);
			EmyMonster_char[i].def = 4 + ((EmyMonster_char[i].level - 1) * 0.4);
			EmyMonster_char[i].hp = 45 + ((EmyMonster_char[i].level - 1) * 4.5);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 17;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind8-1.png");
			sprintf(str1, "Wind8-");
		}
		else if (EmyMonster_char[i].Type == 39) {
			EmyMonster_char[i].atk = 25 + ((EmyMonster_char[i].level - 1) * 2.5);
			EmyMonster_char[i].def = 5 + ((EmyMonster_char[i].level - 1) * 0.5);
			EmyMonster_char[i].hp = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 23.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
			sprintf(str1, "Wind9-");
		}
		
		EmyMonster_char[i].sprite->setScale(1.5);
		if (num2 % 2 == 0) {
			EmyMonster_char[i].sprite->setPosition(64 * num1, 1551 - (37 + 48 * num2));
			EmyMonster_char[i].xPosition = 64 * num1;
			EmyMonster_char[i].yPosition = 1551 - (37 + 48 * num2);
			EmyMonster_char[i].xMovePosition = 64 * num1;
			EmyMonster_char[i].yMovePosition = 1551 - (37 + 48 * num2);
		}
		else {
			EmyMonster_char[i].sprite->setPosition(32 + 64 * num1, 1551 - (37 + 48 * num2));
			EmyMonster_char[i].xPosition = 32 + 64 * num1;
			EmyMonster_char[i].yPosition = 1551 - (37 + 48 * num2);
			EmyMonster_char[i].xMovePosition = 32 + 64 * num1;
			EmyMonster_char[i].yMovePosition = 1551 - (37 + 48 * num2);
		}
		this->addChild(EmyMonster_char[i].sprite, 3);
		Sprite* st = Sprite::createWithSpriteFrameName("HP_bar.png");
		st->setPosition(0, -5);
		st->setScaleX(EmyMonster_char[i].HPbarPosition / 25 * 2);
		st->setAnchorPoint(Vec2(0, 0.5));
		EmyMonster_char[i].sprite->addChild(st, 4);

		Sprite* hp = Sprite::createWithSpriteFrameName("EmyMonseter_HP.png");
		hp->setPosition(1, 0);
		hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
		hp->setAnchorPoint(Vec2(0, 0));
		st->addChild(hp, 4);

		char level[3];
		sprintf(level, "%d", EmyMonster_char[i].level);
		auto pLabel3 = LabelAtlas::create(level, "Images/EmyMonsterLevel.png", 7, 9, '0');
		pLabel3->setAnchorPoint(Vec2(0, 0));
		pLabel3->setPosition(Vec2(hp->getContentSize().width*(EmyMonster_char[i].HPbarPosition / 25 * 2), -10));
		EmyMonster_char[i].sprite->addChild(pLabel3);
		
		Sprite* End = Sprite::createWithSpriteFrameName("End.png");
		End->setAnchorPoint(Vec2(0, 0));
		End->setPosition(Vec2(0, 0));
		EmyMonster_char[i].sprite->addChild(End);

		for (int i = 1; i < 5; i++) {
			sprintf(str2, "%s%d.png", str1, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str2);
			animFrames.pushBack(frame);
		}

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		EmyMonster_char[i].sprite->runAction(rep);
	}
}

void EarthMap::FocusCharacter() {
	winSize = Director::getInstance()->getWinSize();
	
	//주인공 포지션
	
	float dx=0;
	float dy=0;
	dx = monster_char[0].xPosition - 640;
	dy = monster_char[0].yPosition - 360;

	if (dx > 733) {
		dx = 733;
	}
	if (dy > 799.5) {
		dy = 799.5;
	}

	MovePositionDX = dx;
	MovePositionDY = dy;
	if (dx < 0) {
		MovePositionDX = 0;
	}
	if (dy < 0) {
		MovePositionDY = 0;
	}
	//아군 몬스터
	for (int i = 0; i < monsterSize; i++) {
		monster_char[i].xMovePosition = monster_char[i].xPosition - dx;
		monster_char[i].yMovePosition = monster_char[i].yPosition - dy;
		if (monster_char[i].xMovePosition < monster_char[i].xPosition - 733) {
			monster_char[i].xMovePosition = monster_char[i].xPosition - 733;
		}
		else if (monster_char[i].xMovePosition > monster_char[i].xPosition) {
			monster_char[i].xMovePosition = monster_char[i].xPosition;
		}
		if (monster_char[i].yMovePosition < monster_char[i].yPosition - 799.5) {
			monster_char[i].yMovePosition = monster_char[i].yPosition - 799.5;
		}
		else if (monster_char[i].yMovePosition > monster_char[i].yPosition) {
			monster_char[i].yMovePosition = monster_char[i].yPosition;
		}
		monster_char[i].sprite->setPosition(Vec2(monster_char[i].xMovePosition, monster_char[i].yMovePosition));
	}

	//적군 몬스터
	for (int i = 0; i < EmyMonsterSize; i++) {
		EmyMonster_char[i].xMovePosition = EmyMonster_char[i].xPosition - dx;
		EmyMonster_char[i].yMovePosition = EmyMonster_char[i].yPosition - dy;
		if (EmyMonster_char[i].xMovePosition < EmyMonster_char[i].xPosition - 733) {
			EmyMonster_char[i].xMovePosition = EmyMonster_char[i].xPosition - 733;
		}
		else if (EmyMonster_char[i].xMovePosition > EmyMonster_char[i].xPosition) {
			EmyMonster_char[i].xMovePosition = EmyMonster_char[i].xPosition;
		}
		if (EmyMonster_char[i].yMovePosition < EmyMonster_char[i].yPosition - 799.5) {
			EmyMonster_char[i].yMovePosition = EmyMonster_char[i].yPosition - 799.5;
		}
		else if (EmyMonster_char[i].yMovePosition > EmyMonster_char[i].yPosition) {
			EmyMonster_char[i].yMovePosition = EmyMonster_char[i].yPosition;
		}
		EmyMonster_char[i].sprite->setPosition(Vec2(EmyMonster_char[i].xMovePosition, EmyMonster_char[i].yMovePosition));
	}

	//배경화면
	float x = BG->getPosition().x - dx;
	float y = BG->getPosition().y - dy;
	if (x < winSize.width - 1006.5) {
		x = winSize.width - 1006.5;
	}
	else if (x > 1006.5) {
		x = 1006.5;
	}
	if (y < 7.75 + winSize.height - 759.75) {
		y = 7.75 + winSize.height - 759.75;
	}
	else if (y > 767.5) {
		y = 767.5;
	}

	BG->setPosition(Vec2(x, y));
	float tx = tmap->getPosition().x - dx;
	float ty = tmap->getPosition().y - dy;
	if (tx < -1039.5 + winSize.width - 1006.5) {
		tx = -1039.5 + winSize.width - 1006.5;
	}
	else if (tx > -33) {
		tx = -33;
	}
	if (ty < -775.5 + winSize.height - 759.75) {
		ty = -775.5 + winSize.height - 759.75;
	}
	else if (ty > -16) {
		ty = -16;
	}
	//움직인 타일맵의 위치를 가지고 클릭좌표를 계산
	MovePositionX = tx;
	MovePositionY = ty;
	tmap->setPosition(Vec2(tx, ty));
}

void EarthMap::doMsgReceived(Ref* obj) {
	char *inputStr = (char*)obj;
	char testText[20];
	sprintf(testText, "%s", inputStr);
	if (!strcmp(testText, "0")) {
		Director::getInstance()->pause();
	}
	else if (!strcmp(testText, "1")) {
		Director::getInstance()->resume();
	}
	else {
		Director::getInstance()->resume();
		auto pScene = MainScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	
}

void EarthMap::doMsgReceivedMonster(Ref* obj) {
	char *inputStr = (char*)obj;
	char testText[20];
	sprintf(testText, "%s", inputStr);
	if (!strcmp(testText, "0")) {
		Director::getInstance()->resume();
		touchMove = true;
	}
	else {
		createMonsterNum = atoi(testText);
		log("소환 : %d", createMonsterNum);
		Director::getInstance()->resume();
		b_CreateMonster = true;
		touchMove = true;

		for (int i = 0; i < MovePosition.size(); i++) {
			this->removeChild(MovePosition.at(i));
		}
		MovePosition.clear();
		for (int i = 0; i < EmyMovePosition.size(); i++) {
			this->removeChild(EmyMovePosition.at(i));
		}
		EmyMovePosition.clear();
		createMonsterPos = ChecksPosition(VPos, createMonsterPos, 0, 1);
		createPosSize = _msize((void*)createMonsterPos) / sizeof(*createMonsterPos);

		//한칸
		for (int m = 0; m < createPosSize; m++) {
			Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
			Vec2 posit = FindCoordPosition(Vec2(createMonsterPos[m].x, createMonsterPos[m].y));
			log("pos[%d] = %d", m, createMonsterPos[m].num);
			sp->setPosition(posit.x - 2, posit.y + 17);
			MovePosition.pushBack(sp);
		}
		//이동경로 sprite 띄우기
		for (int i = 0; i < MovePosition.size(); i++) {
			this->addChild(MovePosition.at(i), 2);
		}
	}

}

void EarthMap::onEnter() {
	Layer::onEnter();

	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(EarthMap::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(EarthMap::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(EarthMap::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void EarthMap::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Layer::onExit();
}

bool EarthMap::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (!touchMove) {
		return false;
	}

	auto touchPoint = touch->getLocation();
	StartDragPosition = touchPoint;
	
	return true;
}

void EarthMap::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (!touchMove) {
		return;
	}

	winSize = Director::getInstance()->getWinSize();

	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	EndDragPosition = touchPoint;

	MovePositionDX -= (EndDragPosition.x - StartDragPosition.x);
	if (MovePositionDX < 0 ) {
		MovePositionDX = 0;
	}
	else if (MovePositionDX > 733) {
		MovePositionDX = 733;
	}
	MovePositionDY -= (EndDragPosition.y - StartDragPosition.y);
	if (MovePositionDY < 0) {
		MovePositionDY = 0;
	}
	else if (MovePositionDY > 799.5) {
		MovePositionDY = 799.5;
	}
	for (int i = 0; i < monsterSize; i++) {
		monster_char[i].xMovePosition = monster_char[i].xMovePosition + (EndDragPosition.x - StartDragPosition.x);
		monster_char[i].yMovePosition = monster_char[i].yMovePosition + (EndDragPosition.y - StartDragPosition.y);
		if (monster_char[i].xMovePosition < monster_char[i].xPosition-733) {
			monster_char[i].xMovePosition = monster_char[i].xPosition-733;
		}
		else if (monster_char[i].xMovePosition > monster_char[i].xPosition) {
			monster_char[i].xMovePosition = monster_char[i].xPosition;
		}
		if (monster_char[i].yMovePosition < monster_char[i].yPosition-799.5) {
			monster_char[i].yMovePosition = monster_char[i].yPosition - 799.5;
		}
		else if (monster_char[i].yMovePosition > monster_char[i].yPosition) {
			monster_char[i].yMovePosition = monster_char[i].yPosition;
		}
		monster_char[i].sprite->setPosition(Vec2(monster_char[i].xMovePosition, monster_char[i].yMovePosition));
	}
	
	for (int i = 0; i < EmyMonsterSize; i++) {
		EmyMonster_char[i].xMovePosition = EmyMonster_char[i].xMovePosition + (EndDragPosition.x - StartDragPosition.x);
		EmyMonster_char[i].yMovePosition = EmyMonster_char[i].yMovePosition + (EndDragPosition.y - StartDragPosition.y);
		if (EmyMonster_char[i].xMovePosition < EmyMonster_char[i].xPosition - 733) {
			EmyMonster_char[i].xMovePosition = EmyMonster_char[i].xPosition - 733;
		}
		else if (EmyMonster_char[i].xMovePosition > EmyMonster_char[i].xPosition) {
			EmyMonster_char[i].xMovePosition = EmyMonster_char[i].xPosition;
		}
		if (EmyMonster_char[i].yMovePosition < EmyMonster_char[i].yPosition - 799.5) {
			EmyMonster_char[i].yMovePosition = EmyMonster_char[i].yPosition - 799.5;
		}
		else if (EmyMonster_char[i].yMovePosition > EmyMonster_char[i].yPosition) {
			EmyMonster_char[i].yMovePosition = EmyMonster_char[i].yPosition;
		}
		EmyMonster_char[i].sprite->setPosition(Vec2(EmyMonster_char[i].xMovePosition, EmyMonster_char[i].yMovePosition));
	}

	float x = BG->getPosition().x + (EndDragPosition.x - StartDragPosition.x);
	float y = BG->getPosition().y + (EndDragPosition.y - StartDragPosition.y);
	if (x < winSize.width - 1006.5) {
		x = winSize.width - 1006.5;
	}
	else if (x > 1006.5) {
		x = 1006.5;
	}
	if (y < 7.75 + winSize.height - 759.75) {
		y = 7.75 + winSize.height - 759.75;
	}
	else if (y > 767.5) {
		y = 767.5;
	}
	BG->setPosition(Vec2(x, y));
	float tx = tmap->getPosition().x + (EndDragPosition.x - StartDragPosition.x);
	float ty = tmap->getPosition().y + (EndDragPosition.y - StartDragPosition.y);
	if (tx < -1039.5 + winSize.width - 1006.5) {
		tx = -1039.5 + winSize.width - 1006.5;
	}
	else if (tx > -33) {
		tx = -33;
	}
	if (ty < -775.5 + winSize.height - 759.75) {
		ty = -775.5 + winSize.height - 759.75;
	}
	else if (ty > -16) {
		ty = -16;
	}
	tmap->setPosition(Vec2(tx, ty));

	MovePositionX = tx;
	MovePositionY = ty;

	StartDragPosition = EndDragPosition;
}

void EarthMap::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	if (b_CreateMonster) {
		touchPoint = this->convertToNodeSpace(touchPoint);
		Vec2 m_pos = tileCoordForPosition(touchPoint);
		for (int i = 0; i < createPosSize; i++) {
			if (m_pos == Vec2(createMonsterPos[i].x, createMonsterPos[i].y)) {
				//아군몬스터 소환 createMonsterNum

			}
		}
		b_CreateMonster = false;
		for (int i = 0; i < MovePosition.size(); i++) {
			this->removeChild(MovePosition.at(i));
		}
		MovePosition.clear();
		return;
	}

	if (!touchMove) {
		return;
	}
	
	for (int i = 0; i < MovePosition.size(); i++) {
		this->removeChild(MovePosition.at(i));
	}
	MovePosition.clear();
	for (int i = 0; i < EmyMovePosition.size(); i++) {
		this->removeChild(EmyMovePosition.at(i));
	}
	EmyMovePosition.clear();

	char str1[100];
	char str2[100];
	
	Vector<SpriteFrame*> animFrames;
	
	
	bool bTouch1 = pause->getBoundingBox().containsPoint(touchPoint);
	if (bTouch1) {
		Scene* popWin;
		popWin = pauseScene::createScene();
		this->addChild(popWin, 2000, 2000);
	}
	if (status) {
		//소환
		bool bTouch2 = createMonster->getBoundingBox().containsPoint(touchPoint);
		if (bTouch2) {
			touchMove = false;
			Scene* popWin;
			popWin = CreateMonster::createScene();
			this->addChild(popWin, 2000, 2000);
		}
		//도구
		bool bTouch3 = Items->getBoundingBox().containsPoint(touchPoint);
		if (bTouch3) {
			touchMove = false;
			Scene* popWin;
			popWin = pauseScene::createScene();
			this->addChild(popWin, 2000, 2000);
		}
		status = false;
		removeChild(createMonster);
		removeChild(Items);
		return;
	}
	
	
	touchPoint = this->convertToNodeSpace(touchPoint);
	//클릭타일좌표
	Vec2 m_pos = tileCoordForPosition(touchPoint);
	if (ChecksPosition(m_pos.x, m_pos.y)) {
		//몬스터 위치 중복체크
		//장애물 클릭체크
	}
	else {
		//몬스터 위치 클릭됨
		//장애물 클릭됨
	}

	
	//아군몬스터가 클릭상태일 경우
	if (CharacterClick) {
		//아군몬스터 선택시
		Vec2 mon_pos = tileCoordForPosition(Vec2(monster_char[mons].xMovePosition, monster_char[mons].yMovePosition));
		//아군몬스터를 클릭시
		if (m_pos == mon_pos) {
			if (monster_char[mons].Type == 0) {
				status = true;
				log("소환, 도구");
				//create 소환
				createMonster = Sprite::create("Images/Scene/createMonster.png");
				createMonster->setPosition(Vec2(monster_char[mons].xMovePosition, monster_char[mons].yMovePosition - 28));
				createMonster->setScale(2.0f);
				addChild(createMonster, 4);
				//create 도구
				Items = Sprite::create("Images/Scene/Items.png");
				Items->setPosition(Vec2(monster_char[mons].xMovePosition, monster_char[mons].yMovePosition + 28));
				Items->setScale(2.0f);
				addChild(Items, 4);
			}
			else {
				log("도구");
				status = true;
				//create 도구
				Items = Sprite::create("Images/Scene/Items1.png");
				Items->setPosition(Vec2(0, 0));
				monster_char[mons].sprite->addChild(Items, 4);
			}
			VPos = mon_pos;
		}
		//아군몬스터 범위내 클릭시
		else if (checkcoordinate(m_pos)) {
			//오른쪽 스프라이트
			if (fmodf(mon_pos.y, 2) == 0 && mon_pos.x == m_pos.x || mon_pos.x < m_pos.x) {
				monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Person1-5.png"));
				sprintf(str1, "Person1-");
				for (int i = 5; i < 9; i++) {
					sprintf(str2, "%s%d.png", str1, i);
					SpriteFrame* frame = cache->getSpriteFrameByName(str2);
					animFrames.pushBack(frame);
				}
				
				auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
				auto animate = Animate::create(animation);
				auto rep = RepeatForever::create(animate);
				monster_char[mons].sprite->stopAllActions();
				monster_char[mons].sprite->runAction(rep);
			}
			//왼쪽 스프라이트
			else {
				monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Person1-1.png"));
				sprintf(str1, "Person1-");
				for (int i = 1; i < 5; i++) {
					sprintf(str2, "%s%d.png", str1, i);
					SpriteFrame* frame = cache->getSpriteFrameByName(str2);
					animFrames.pushBack(frame);
				}

				auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
				auto animate = Animate::create(animation);
				auto rep = RepeatForever::create(animate);
				monster_char[mons].sprite->stopAllActions();
				monster_char[mons].sprite->runAction(rep);
			}
			
			//이동
			//초기화
			if (shortpassSize) {
				free(shortpass);
				shortpassSize = 0;
			}
			//이동 가능 경로 저장
			for (int m = 0; m < posSize; m++) {
				if (pos[m].x == m_pos.x && pos[m].y == m_pos.y) {
					if (shortpassSize)	shortpass = (Position*)realloc(shortpass,	sizeof(Position) * (shortpassSize + 1));
					else				shortpass = (Position*)malloc(				sizeof(Position) * (shortpassSize + 1));
					shortpass[shortpassSize].num = pos[m].num;
					shortpass[shortpassSize].x = pos[m].x;
					shortpass[shortpassSize].y = pos[m].y;
					shortpassSize++;
				}
				if (pos[m].pos2Size) {
					for (int k = 0; k < pos[m].pos2Size; k++) {
						if (pos[m].pos2[k].x == m_pos.x && pos[m].pos2[k].y == m_pos.y) {
							if (shortpassSize)	shortpass = (Position*)realloc(shortpass, sizeof(Position) * (shortpassSize + 1));
							else				shortpass = (Position*)malloc(sizeof(Position) * (shortpassSize + 1));
							shortpass[shortpassSize].num = pos[m].pos2[k].num;
							shortpass[shortpassSize].front_x = pos[m].x;
							shortpass[shortpassSize].front_y = pos[m].y;
							shortpass[shortpassSize].x = pos[m].pos2[k].x;
							shortpass[shortpassSize].y = pos[m].pos2[k].y;
							shortpassSize++;
						}
						if (pos[m].pos2[k].pos2Size) {
							for (int z = 0; z < pos[m].pos2[k].pos2Size; z++) {
								if (pos[m].pos2[k].pos2[z].x == m_pos.x && pos[m].pos2[k].pos2[z].y == m_pos.y) {
									if (shortpassSize)	shortpass = (Position*)realloc(shortpass, sizeof(Position) * (shortpassSize + 1));
									else				shortpass = (Position*)malloc(sizeof(Position) * (shortpassSize + 1));
									shortpass[shortpassSize].num = pos[m].pos2[k].pos2[z].num;
									shortpass[shortpassSize].front_front_x = pos[m].x;
									shortpass[shortpassSize].front_front_y = pos[m].y;
									shortpass[shortpassSize].front_x = pos[m].pos2[k].x;
									shortpass[shortpassSize].front_y = pos[m].pos2[k].y;
									shortpass[shortpassSize].x = pos[m].pos2[k].pos2[z].x;
									shortpass[shortpassSize].y = pos[m].pos2[k].pos2[z].y;
									shortpassSize++;
								}
								if (pos[m].pos2[k].pos2[z].pos2Size) {
									for (int i = 0; i < pos[m].pos2[k].pos2[z].pos2Size; i++) {
										if (pos[m].pos2[k].pos2[z].pos2[i].x == m_pos.x && pos[m].pos2[k].pos2[z].pos2[i].y == m_pos.y) {
											if (shortpassSize)	shortpass = (Position*)realloc(shortpass, sizeof(Position) * (shortpassSize + 1));
											else				shortpass = (Position*)malloc(sizeof(Position) * (shortpassSize + 1));
											shortpass[shortpassSize].num = pos[m].pos2[k].pos2[z].pos2[i].num;
											shortpass[shortpassSize].front_front_front_x = pos[m].x;
											shortpass[shortpassSize].front_front_front_y = pos[m].y;
											shortpass[shortpassSize].front_front_x = pos[m].pos2[k].x;
											shortpass[shortpassSize].front_front_y = pos[m].pos2[k].y;
											shortpass[shortpassSize].front_x = pos[m].pos2[k].pos2[z].x;
											shortpass[shortpassSize].front_y = pos[m].pos2[k].pos2[z].y;
											shortpass[shortpassSize].x = pos[m].pos2[k].pos2[z].pos2[i].x;
											shortpass[shortpassSize].y = pos[m].pos2[k].pos2[z].pos2[i].y;
											shortpassSize++;
										}
									}
								}
							}
						}
					}
				}
			}

			bool pass = false;
			//최단경로 이동
			if (!pass) {
				for (int k = 0; k < shortpassSize; k++) {
					if (shortpass[k].num + movement == 4) {
						log("shortpass[%d] = %d, xy = %d, %d", k, shortpass[k].num, shortpass[k].x, shortpass[k].y);
						Vec2 vec = FindCoordPosition(Vec2(shortpass[k].x, shortpass[k].y));
						auto animate = MoveTo::create(0.25, Vec2(vec.x, vec.y + 30));
						monster_char[mons].sprite->runAction(animate);
						pass = true;
						//이동 좌표 저장
						monster_char[mons].tx = shortpass[k].x;
						monster_char[mons].ty = shortpass[k].y;

						monster_char[mons].xPosition += vec.x - monster_char[mons].xMovePosition;
						monster_char[mons].yPosition += vec.y + 30 - monster_char[mons].yMovePosition;

						monster_char[mons].xMovePosition = vec.x;
						monster_char[mons].yMovePosition = vec.y + 30;

						break;
					}
				}
			}
			if (!pass) {
				for (int k = 0; k < shortpassSize; k++) {
					if (shortpass[k].num + movement == 3) {
						log("shortpass[%d] = %d, front = %d, %d, xy = %d, %d", k, shortpass[k].num, shortpass[k].front_x, shortpass[k].front_y, shortpass[k].x, shortpass[k].y);
						Vec2 vec = FindCoordPosition(Vec2(shortpass[k].front_x, shortpass[k].front_y));
						auto animate = MoveTo::create(0.25, Vec2(vec.x, vec.y + 30));

						monster_char[mons].tx = shortpass[k].front_x;
						monster_char[mons].ty = shortpass[k].front_y;

						monster_char[mons].xPosition += vec.x - monster_char[mons].xMovePosition;
						monster_char[mons].yPosition += vec.y + 30 - monster_char[mons].yMovePosition;

						monster_char[mons].xMovePosition = vec.x;
						monster_char[mons].yMovePosition = vec.y + 30;

						Vec2 vec1 = FindCoordPosition(Vec2(shortpass[k].x, shortpass[k].y));
						auto animate1 = MoveTo::create(0.25, Vec2(vec1.x, vec1.y + 30));

						monster_char[mons].tx = shortpass[k].x;
						monster_char[mons].ty = shortpass[k].y;

						monster_char[mons].xPosition += vec1.x - monster_char[mons].xMovePosition;
						monster_char[mons].yPosition += vec1.y + 30 - monster_char[mons].yMovePosition;

						monster_char[mons].xMovePosition = vec1.x;
						monster_char[mons].yMovePosition = vec1.y + 30;

						auto myAction = Sequence::create(animate, animate1, nullptr);
						monster_char[mons].sprite->runAction(myAction);
						pass = true;
						break;
					}
				}
			}
			if (!pass) {
				for (int k = 0; k < shortpassSize; k++) {
					if (shortpass[k].num + movement == 2) {
						log("shortpass[%d] = %d, frontfront = %d, %d, front = %d, %d, xy = %d, %d", k, shortpass[k].num, shortpass[k].front_front_x, shortpass[k].front_front_y, shortpass[k].front_x, shortpass[k].front_y, shortpass[k].front_x, shortpass[k].front_y);
						Vec2 vec = FindCoordPosition(Vec2(shortpass[k].front_front_x, shortpass[k].front_front_y));
						auto animate = MoveTo::create(0.25, Vec2(vec.x, vec.y + 30));

						monster_char[mons].tx = shortpass[k].front_front_x;
						monster_char[mons].ty = shortpass[k].front_front_y;

						monster_char[mons].xPosition += vec.x - monster_char[mons].xMovePosition;
						monster_char[mons].yPosition += vec.y + 30 - monster_char[mons].yMovePosition;

						monster_char[mons].xMovePosition = vec.x;
						monster_char[mons].yMovePosition = vec.y + 30;

						Vec2 vec1 = FindCoordPosition(Vec2(shortpass[k].front_x, shortpass[k].front_y));
						auto animate1 = MoveTo::create(0.25, Vec2(vec1.x, vec1.y + 30));

						monster_char[mons].tx = shortpass[k].front_x;
						monster_char[mons].ty = shortpass[k].front_y;

						monster_char[mons].xPosition += vec1.x - monster_char[mons].xMovePosition;
						monster_char[mons].yPosition += vec1.y + 30 - monster_char[mons].yMovePosition;

						monster_char[mons].xMovePosition = vec1.x;
						monster_char[mons].yMovePosition = vec1.y + 30;

						Vec2 vec2 = FindCoordPosition(Vec2(shortpass[k].x, shortpass[k].y));
						auto animate2 = MoveTo::create(0.25, Vec2(vec2.x, vec2.y + 30));

						monster_char[mons].tx = shortpass[k].x;
						monster_char[mons].ty = shortpass[k].y;

						monster_char[mons].xPosition += vec2.x - monster_char[mons].xMovePosition;
						monster_char[mons].yPosition += vec2.y + 30 - monster_char[mons].yMovePosition;

						monster_char[mons].xMovePosition = vec2.x;
						monster_char[mons].yMovePosition = vec2.y + 30;

						auto myAction = Sequence::create(animate, animate1, animate2, nullptr);
						monster_char[mons].sprite->runAction(myAction);
						pass = true;
						break;
					}
				}
			}		
			if (!pass) {
				for (int k = 0; k < shortpassSize; k++) {
					if (shortpass[k].num + movement == 1) {
						log("shortpass[%d] = %d, frontfrontfront = %d, %d, frontfront = %d, %d, front = %d, %d, xy = %d, %d", k, shortpass[k].num, shortpass[k].front_front_front_x, shortpass[k].front_front_front_y, shortpass[k].front_front_x, shortpass[k].front_front_y, shortpass[k].front_x, shortpass[k].front_y, shortpass[k].front_x, shortpass[k].front_y);
						Vec2 vec_1 = FindCoordPosition(Vec2(shortpass[k].front_front_front_x, shortpass[k].front_front_front_y));
						auto animate_1 = MoveTo::create(0.25, Vec2(vec_1.x, vec_1.y + 30));

						monster_char[mons].tx = shortpass[k].front_front_front_x;
						monster_char[mons].ty = shortpass[k].front_front_front_y;

						monster_char[mons].xPosition += vec_1.x - monster_char[mons].xMovePosition;
						monster_char[mons].yPosition += vec_1.y + 30 - monster_char[mons].yMovePosition;

						monster_char[mons].xMovePosition = vec_1.x;
						monster_char[mons].yMovePosition = vec_1.y + 30;

						Vec2 vec = FindCoordPosition(Vec2(shortpass[k].front_front_x, shortpass[k].front_front_y));
						auto animate = MoveTo::create(0.25, Vec2(vec.x, vec.y + 30));

						monster_char[mons].tx = shortpass[k].front_front_x;
						monster_char[mons].ty = shortpass[k].front_front_y;

						monster_char[mons].xPosition += vec.x - monster_char[mons].xMovePosition;
						monster_char[mons].yPosition += vec.y + 30 - monster_char[mons].yMovePosition;

						monster_char[mons].xMovePosition = vec.x;
						monster_char[mons].yMovePosition = vec.y + 30;

						Vec2 vec1 = FindCoordPosition(Vec2(shortpass[k].front_x, shortpass[k].front_y));
						auto animate1 = MoveTo::create(0.25, Vec2(vec1.x, vec1.y + 30));

						monster_char[mons].tx = shortpass[k].front_x;
						monster_char[mons].ty = shortpass[k].front_y;

						monster_char[mons].xPosition += vec1.x - monster_char[mons].xMovePosition;
						monster_char[mons].yPosition += vec1.y + 30 - monster_char[mons].yMovePosition;

						monster_char[mons].xMovePosition = vec1.x;
						monster_char[mons].yMovePosition = vec1.y + 30;

						Vec2 vec2 = FindCoordPosition(Vec2(shortpass[k].x, shortpass[k].y));
						auto animate2 = MoveTo::create(0.25, Vec2(vec2.x, vec2.y + 30));

						monster_char[mons].tx = shortpass[k].x;
						monster_char[mons].ty = shortpass[k].y;

						monster_char[mons].xPosition += vec2.x - monster_char[mons].xMovePosition;
						monster_char[mons].yPosition += vec2.y + 30 - monster_char[mons].yMovePosition;

						monster_char[mons].xMovePosition = vec2.x;
						monster_char[mons].yMovePosition = vec2.y + 30;

						auto myAction = Sequence::create(animate_1, animate, animate1, animate2, nullptr);
						monster_char[mons].sprite->runAction(myAction);
						pass = true;
						break;
					}
				}
			}
			
		}
		//적군몬스터 범위내 클릭시
		else if (true) {

		}
		CharacterClick = false;
	}
	else {
		//아군몬스터 선택시
		mons = -1;
		for (int m = 0; m < monsterSize; m++) {
			if (monster_char[m].tx == m_pos.x && monster_char[m].ty == m_pos.y) {
				mons = m;
				break;
			}
		}
		if (mons == -1) {
			return;
		}
		Vec2 mon_pos = tileCoordForPosition(Vec2(monster_char[mons].xMovePosition, monster_char[mons].yMovePosition));
		//이동경로 표시
		if (m_pos == mon_pos) {
			if (posSize) {
				free(pos);
				posSize = 0;
			}
			
			if (EmyposSize) {
				free(Emypos);
				EmyposSize = 0;
			}
			//이동가능한 경로 체크하기
			if (monster_char[mons].move == 4) {
				movement = 0;
			}
			if (monster_char[mons].move == 3) {
				movement = 1;
			}
			if (monster_char[mons].move == 2) {
				movement = 2;
			}
			if (monster_char[mons].move == 1) {
				movement = 0;
			}
			pos = ChecksPosition(mon_pos, pos, posSize, monster_char[mons].move);
			posSize = _msize((void*)pos) / sizeof(*pos);
			//한칸
			for (int m = 0; m < posSize; m++) {
				Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
				Vec2 posit = FindCoordPosition(Vec2(pos[m].x, pos[m].y));
				log("pos[%d] = %d", m, pos[m].num);
				sp->setPosition(posit.x - 2, posit.y + 17);
				MovePosition.pushBack(sp);
				//두칸
				if (pos[m].pos2Size) {
					for (int k = 0; k < pos[m].pos2Size; k++) {
						Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
						Vec2 posit2 = FindCoordPosition(Vec2(pos[m].pos2[k].x, pos[m].pos2[k].y));
						log("pos[%d].pos2[%d] = %d", m, k, pos[m].pos2[k].num);
						sp->setPosition(posit2.x - 2, posit2.y + 17);
						MovePosition.pushBack(sp);
						//세칸
						if (pos[m].pos2[k].pos2Size) {
							for (int z = 0; z < pos[m].pos2[k].pos2Size; z++) {
								Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
								Vec2 posit2 = FindCoordPosition(Vec2(pos[m].pos2[k].pos2[z].x, pos[m].pos2[k].pos2[z].y));
								log("pos[%d].pos2[%d].pos2[%d] = %d", m, k, z, pos[m].pos2[k].pos2[z].num);
								sp->setPosition(posit2.x - 2, posit2.y + 17);
								MovePosition.pushBack(sp);
								//네칸
								if (pos[m].pos2[k].pos2[z].pos2Size) {
									for (int i = 0; i < pos[m].pos2[k].pos2[z].pos2Size; i++) {
										Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
										Vec2 posit2 = FindCoordPosition(Vec2(pos[m].pos2[k].pos2[z].pos2[i].x, pos[m].pos2[k].pos2[z].pos2[i].y));
										log("pos[%d].pos2[%d].pos2[%d].pos2[i] = %d", m, k, z, i, pos[m].pos2[k].pos2[z].pos2[i].num);
										sp->setPosition(posit2.x - 2, posit2.y + 17);
										MovePosition.pushBack(sp);
									}
								}
							}
						}
					}
				}
				
			}
			//클릭상태표시
			CharacterClick = true;
			//이동경로 sprite 띄우기
			for (int i = 0; i < MovePosition.size(); i++) {
				this->addChild(MovePosition.at(i), 2);
			}

			//적 표시
			for (int m = 0; m < EmyposSize; m++) {
				int type;
				for (int k = 0; k < EmyMonsterSize; k++) {
					if (EmyMonster_char[k].tx == Emypos[m].x && EmyMonster_char[k].ty == Emypos[m].y) {
						type = EmyMonster_char[k].Type;
					}
				}
				Sprite* sp;
				//선택한 몬스터는 불속성
				if (monster_char[mons].Type == 0 || (monster_char[mons].Type > 10 && monster_char[mons].Type < 20)) {
					if (type > 0 && type < 10) {
						sp = Sprite::createWithSpriteFrameName("HexInfo1.png");
					}
					else if (type > 30 && type < 40) {
						sp = Sprite::createWithSpriteFrameName("HexInfo2.png");
					}
					else {
						sp = Sprite::createWithSpriteFrameName("HexInfo3.png");
					}
				}
				//선택한 몬스터는 대지속성
				if (monster_char[mons].Type > 0 && monster_char[mons].Type < 10) {
					if (type > 20 && type < 30) {
						sp = Sprite::createWithSpriteFrameName("HexInfo1.png");
					}
					else if (type > 10 && type < 20) {
						sp = Sprite::createWithSpriteFrameName("HexInfo2.png");
					}
					else {
						sp = Sprite::createWithSpriteFrameName("HexInfo3.png");
					}
				}
				//선택한 몬스터는 물속성
				if (monster_char[mons].Type > 20 && monster_char[mons].Type < 30) {
					if (type > 30 && type < 40) {
						sp = Sprite::createWithSpriteFrameName("HexInfo1.png");
					}
					else if (type > 0 && type < 10) {
						sp = Sprite::createWithSpriteFrameName("HexInfo2.png");
					}
					else {
						sp = Sprite::createWithSpriteFrameName("HexInfo3.png");
					}
				}
				//선택한 몬스터는 바람속성
				if (monster_char[mons].Type > 30 && monster_char[mons].Type < 40) {
					if (type > 10 && type < 20) {
						sp = Sprite::createWithSpriteFrameName("HexInfo1.png");
					}
					else if (type > 20 && type < 30) {
						sp = Sprite::createWithSpriteFrameName("HexInfo2.png");
					}
					else {
						sp = Sprite::createWithSpriteFrameName("HexInfo3.png");
					}
				}
				Vec2 posit = FindCoordPosition(Vec2(Emypos[m].x, Emypos[m].y));
				sp->setPosition(posit.x - 2, posit.y + 17);
				EmyMovePosition.pushBack(sp);
			}
			for (int i = 0; i < EmyMovePosition.size(); i++) {
				this->addChild(EmyMovePosition.at(i), 2);
			}
		}
	}
}

bool EarthMap::checkcoordinate(Vec2 click) {
	for (int m = 0; m < posSize; m++) {
		if (pos[m].x == click.x && pos[m].y == click.y) {
			return true;
		}
		if (pos[m].pos2Size) {
			for (int k = 0; k < pos[m].pos2Size; k++) {
				if (pos[m].pos2[k].x == click.x && pos[m].pos2[k].y == click.y) {
					return true;
				}
				if (pos[m].pos2[k].pos2Size) {
					for (int z = 0; z < pos[m].pos2[k].pos2Size; z++) {
						if (pos[m].pos2[k].pos2[z].x == click.x && pos[m].pos2[k].pos2[z].y == click.y) {
							return true;
						}
						if (pos[m].pos2[k].pos2[z].pos2Size) {
							for (int i = 0; i < pos[m].pos2[k].pos2[z].pos2Size; i++) {
								if (pos[m].pos2[k].pos2[z].pos2[i].x == click.x && pos[m].pos2[k].pos2[z].pos2[i].y == click.y) {
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

Vec2 EarthMap::FindCoordPosition(Vec2 pos) {
	float x;
	float y;
	y = 46 + ((30 - pos.y) * 48);
	if (fmodf(pos.x, 2) == 0) {
		if (fmodf(pos.y, 2) == 0) {
			
			x = pos.x * 64;
		}
		else {
			x = pos.x * 64 + 32;
		}
	}
	else {
		if (fmodf(pos.y, 2) == 0) {
			x = pos.x * 64; 
		}
		else {
			x = pos.x * 64 + 32;
		}
	}
	

	return Vec2(x - MovePositionDX, y - MovePositionDY);
	//pos.x;
	//MovePositionX;
	//MovePositionY;
}

bool EarthMap::ChecksPosition(int num1, int num2) {
	//Vec2 pos; 
	if (num1 > 30 || num1 < 1 || num2 > 30 || num2 < 1) {
		return false;
	}
	for (int i = 0; i < monsterSize; i++) {
		if (monster_char[i].tx == num1 && monster_char[i].ty == num2) {
			return false;
		}
	}

	for (int i = 0; i < EmyMonsterSize; i++) {
		if (EmyMonster_char[i].tx == num1 && EmyMonster_char[i].ty == num2) {
			if (EmyposSize) {
				for (int m = 0; m < EmyposSize; m++) {
					if (Emypos[m].x == num1 && Emypos[m].y == num2) {
						
						return false;
					}
					else if (m == EmyposSize-1) {
						Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						Emypos[EmyposSize].num = 1;
						Emypos[EmyposSize].x = num1;
						Emypos[EmyposSize].y = num2;
						EmyposSize++;
						return false;
					}
				}
			}
			else {
				Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
				Emypos[EmyposSize].num = 1;
				Emypos[EmyposSize].x = num1;
				Emypos[EmyposSize].y = num2;
				EmyposSize++;
				return false;
			}
		}
	}
	Vec2 tileCoord = Vec2(num1, num2);
	int tileGid = this->metainfo->getTileGIDAt(tileCoord);
	if (tileGid) {
		Value properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull()) {
			std::string item1 = properties.asValueMap()["Items"].asString();
			if (item1 == "wall") {
				log("wall....");
				return false;
			}
		}
	}
	return true;
}

EarthMap::Position* EarthMap::ChecksPosition(Vec2 charactor, Position *pos_temp, int tempSize, int Count) {
	if (Count > 0) {
		//Vec2(charactor.x, charactor.y - 1);
		if (ChecksPosition(charactor.x, charactor.y - 1)) {
			if (tempSize)	pos_temp = (Position*)realloc(pos_temp,	sizeof(Position) * (tempSize + 1));
			else			pos_temp = (Position*)malloc(			sizeof(Position) * (tempSize + 1));
			pos_temp[tempSize].num = Count;
			pos_temp[tempSize].x = charactor.x;
			pos_temp[tempSize].y = charactor.y - 1;
			pos_temp[tempSize].pos2Size = 0;
			pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count-1);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = _msize((void*)pos_temp[tempSize].pos2) / sizeof(*pos_temp[tempSize].pos2);
			}
			tempSize++;
		}
		//Vec2(charactor.x, charactor.y + 1);
		if (ChecksPosition(charactor.x, charactor.y + 1)) {
			if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
			else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
			pos_temp[tempSize].num = Count;
			pos_temp[tempSize].x = charactor.x;
			pos_temp[tempSize].y = charactor.y + 1;
			pos_temp[tempSize].pos2Size = 0;
			pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = _msize((void*)pos_temp[tempSize].pos2) / sizeof(*pos_temp[tempSize].pos2);
			}
			tempSize++;
		}
		//Vec2(charactor.x - 1, charactor.y);
		if (ChecksPosition(charactor.x - 1, charactor.y)) {
			if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
			else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
			pos_temp[tempSize].num = Count;
			pos_temp[tempSize].x = charactor.x - 1;
			pos_temp[tempSize].y = charactor.y;
			pos_temp[tempSize].pos2Size = 0;
			pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = _msize((void*)pos_temp[tempSize].pos2) / sizeof(*pos_temp[tempSize].pos2);
			}
			tempSize++;
		}
		//Vec2(charactor.x + 1, charactor.y);
		if (ChecksPosition(charactor.x + 1, charactor.y)) {
			if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
			else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
			pos_temp[tempSize].num = Count;
			pos_temp[tempSize].x = charactor.x + 1;
			pos_temp[tempSize].y = charactor.y;
			pos_temp[tempSize].pos2Size = 0;
			pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = _msize((void*)pos_temp[tempSize].pos2) / sizeof(*pos_temp[tempSize].pos2);
			}
			tempSize++;
		}
		if (fmodf(charactor.y, 2) == 0) {
			//Vec2(charactor.x - 1, charactor.y - 1);
			if (ChecksPosition(charactor.x - 1, charactor.y - 1)) {
				if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
				else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
				pos_temp[tempSize].num = Count;
				pos_temp[tempSize].x = charactor.x - 1;
				pos_temp[tempSize].y = charactor.y - 1;
				pos_temp[tempSize].pos2Size = 0;
				pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1);
				if (Count != 1) {
					pos_temp[tempSize].pos2Size = _msize((void*)pos_temp[tempSize].pos2) / sizeof(*pos_temp[tempSize].pos2);
				}
				tempSize++;
			}
			//Vec2(charactor.x - 1, charactor.y + 1);
			if (ChecksPosition(charactor.x - 1, charactor.y + 1)) {
				if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
				else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
				pos_temp[tempSize].num = Count;
				pos_temp[tempSize].x = charactor.x - 1;
				pos_temp[tempSize].y = charactor.y + 1;
				pos_temp[tempSize].pos2Size = 0;
				pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1);
				if (Count != 1) {
					pos_temp[tempSize].pos2Size = _msize((void*)pos_temp[tempSize].pos2) / sizeof(*pos_temp[tempSize].pos2);
				}
				tempSize++;
			}
		}
		else {
			//Vec2(charactor.x + 1, charactor.y + 1);
			if (ChecksPosition(charactor.x + 1, charactor.y + 1)) {
				if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
				else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
				pos_temp[tempSize].num = Count;
				pos_temp[tempSize].x = charactor.x + 1;
				pos_temp[tempSize].y = charactor.y + 1;
				pos_temp[tempSize].pos2Size = 0;
				pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1);
				if (Count != 1) {
					pos_temp[tempSize].pos2Size = _msize((void*)pos_temp[tempSize].pos2) / sizeof(*pos_temp[tempSize].pos2);
				}
				tempSize++;
			}
			//Vec2(charactor.x + 1, charactor.y - 1);
			if (ChecksPosition(charactor.x + 1, charactor.y - 1)) {
				if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
				else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
				pos_temp[tempSize].num = Count;
				pos_temp[tempSize].x = charactor.x + 1;
				pos_temp[tempSize].y = charactor.y - 1;
				pos_temp[tempSize].pos2Size = 0;
				pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1);
				if (Count != 1) {
					pos_temp[tempSize].pos2Size = _msize((void*)pos_temp[tempSize].pos2) / sizeof(*pos_temp[tempSize].pos2);
				}
				tempSize++;
			}
		}
	}
	//
	//if (Count == 2) {
	//	if (ChecksPosition(charactor.x, charactor.y - 1)) {
	//		if (check) {
	//			if (posSize)	pos = (Position*)realloc(pos, sizeof(Position) * (posSize + 1));
	//			else			pos = (Position*)malloc(sizeof(Position) * (posSize + 1));
	//			pos[posSize].num = 1;
	//			pos[posSize].x = charactor.x;
	//			pos[posSize].y = charactor.y - 1;
	//			pos[posSize].pos2Size = 0;
	//			ChecksPosition(Vec2(pos[posSize].x, pos[posSize].y), posSize, false, 2);
	//			posSize++;
	//		}
	//		else {
	//			if (pos[pose].pos2Size)	pos[pose].pos2 = (Position*)realloc(pos[pose].pos2, sizeof(Position) * (pos[pose].pos2Size + 1));
	//			else					pos[pose].pos2 = (Position*)malloc(sizeof(Position) * (pos[pose].pos2Size + 1));
	//			pos[pose].pos2[pos[pose].pos2Size].num = 2;
	//			pos[pose].pos2[pos[pose].pos2Size].x = charactor.x;
	//			pos[pose].pos2[pos[pose].pos2Size].y = charactor.y - 1;
	//			pos[pose].pos2Size++;
	//		}
	//	}
	//	//Vec2(charactor.x, charactor.y + 1);
	//	if (ChecksPosition(charactor.x, charactor.y + 1)) {
	//		if (check) {
	//			if (posSize)	pos = (Position*)realloc(pos, sizeof(Position) * (posSize + 1));
	//			else			pos = (Position*)malloc(sizeof(Position) * (posSize + 1));
	//			pos[posSize].num = 1;
	//			pos[posSize].x = charactor.x;
	//			pos[posSize].y = charactor.y + 1;
	//			pos[posSize].pos2Size = 0;
	//			ChecksPosition(Vec2(pos[posSize].x, pos[posSize].y), posSize, false, 2);
	//			posSize++;
	//		}
	//		else {
	//			if (pos[pose].pos2Size)	pos[pose].pos2 = (Position*)realloc(pos[pose].pos2, sizeof(Position) * (pos[pose].pos2Size + 1));
	//			else					pos[pose].pos2 = (Position*)malloc(sizeof(Position) * (pos[pose].pos2Size + 1));
	//			pos[pose].pos2[pos[pose].pos2Size].num = 2;
	//			pos[pose].pos2[pos[pose].pos2Size].x = charactor.x;
	//			pos[pose].pos2[pos[pose].pos2Size].y = charactor.y + 1;
	//			pos[pose].pos2Size++;
	//		}
	//	}
	//	//Vec2(charactor.x - 1, charactor.y);
	//	if (ChecksPosition(charactor.x - 1, charactor.y)) {
	//		if (check) {
	//			if (posSize)	pos = (Position*)realloc(pos, sizeof(Position) * (posSize + 1));
	//			else			pos = (Position*)malloc(sizeof(Position) * (posSize + 1));
	//			pos[posSize].num = 1;
	//			pos[posSize].x = charactor.x - 1;
	//			pos[posSize].y = charactor.y;
	//			pos[posSize].pos2Size = 0;
	//			ChecksPosition(Vec2(pos[posSize].x, pos[posSize].y), posSize, false, 2);
	//			posSize++;
	//		}
	//		else {
	//			if (pos[pose].pos2Size)	pos[pose].pos2 = (Position*)realloc(pos[pose].pos2, sizeof(Position) * (pos[pose].pos2Size + 1));
	//			else					pos[pose].pos2 = (Position*)malloc(sizeof(Position) * (pos[pose].pos2Size + 1));
	//			pos[pose].pos2[pos[pose].pos2Size].num = 2;
	//			pos[pose].pos2[pos[pose].pos2Size].x = charactor.x - 1;
	//			pos[pose].pos2[pos[pose].pos2Size].y = charactor.y;
	//			pos[pose].pos2Size++;
	//		}
	//	}
	//	//Vec2(charactor.x + 1, charactor.y);
	//	if (ChecksPosition(charactor.x + 1, charactor.y)) {
	//		if (check) {
	//			if (posSize)	pos = (Position*)realloc(pos, sizeof(Position) * (posSize + 1));
	//			else			pos = (Position*)malloc(sizeof(Position) * (posSize + 1));
	//			pos[posSize].num = 1;
	//			pos[posSize].x = charactor.x + 1;
	//			pos[posSize].y = charactor.y;
	//			pos[posSize].pos2Size = 0;
	//			ChecksPosition(Vec2(pos[posSize].x, pos[posSize].y), posSize, false, 2);
	//			posSize++;
	//		}
	//		else {
	//			if (pos[pose].pos2Size)	pos[pose].pos2 = (Position*)realloc(pos[pose].pos2, sizeof(Position) * (pos[pose].pos2Size + 1));
	//			else					pos[pose].pos2 = (Position*)malloc(sizeof(Position) * (pos[pose].pos2Size + 1));
	//			pos[pose].pos2[pos[pose].pos2Size].num = 2;
	//			pos[pose].pos2[pos[pose].pos2Size].x = charactor.x + 1;
	//			pos[pose].pos2[pos[pose].pos2Size].y = charactor.y;
	//			pos[pose].pos2Size++;
	//		}
	//	}
	//	if (fmodf(charactor.y, 2) == 0) {
	//		//Vec2(charactor.x - 1, charactor.y - 1);
	//		if (ChecksPosition(charactor.x - 1, charactor.y - 1)) {
	//			if (check) {
	//				if (posSize)	pos = (Position*)realloc(pos, sizeof(Position) * (posSize + 1));
	//				else			pos = (Position*)malloc(sizeof(Position) * (posSize + 1));
	//				pos[posSize].num = 1;
	//				pos[posSize].x = charactor.x - 1;
	//				pos[posSize].y = charactor.y - 1;
	//				pos[posSize].pos2Size = 0;
	//				ChecksPosition(Vec2(pos[posSize].x, pos[posSize].y), posSize, false, 2);
	//				posSize++;
	//			}
	//			else {
	//				if (pos[pose].pos2Size)	pos[pose].pos2 = (Position*)realloc(pos[pose].pos2, sizeof(Position) * (pos[pose].pos2Size + 1));
	//				else					pos[pose].pos2 = (Position*)malloc(sizeof(Position) * (pos[pose].pos2Size + 1));
	//				pos[pose].pos2[pos[pose].pos2Size].num = 2;
	//				pos[pose].pos2[pos[pose].pos2Size].x = charactor.x - 1;
	//				pos[pose].pos2[pos[pose].pos2Size].y = charactor.y - 1;
	//				pos[pose].pos2Size++;
	//			}
	//		}
	//		//Vec2(charactor.x - 1, charactor.y + 1);
	//		if (ChecksPosition(charactor.x - 1, charactor.y + 1)) {
	//			if (check) {
	//				if (posSize)	pos = (Position*)realloc(pos, sizeof(Position) * (posSize + 1));
	//				else			pos = (Position*)malloc(sizeof(Position) * (posSize + 1));
	//				pos[posSize].num = 1;
	//				pos[posSize].x = charactor.x - 1;
	//				pos[posSize].y = charactor.y + 1;
	//				pos[posSize].pos2Size = 0;
	//				ChecksPosition(Vec2(pos[posSize].x, pos[posSize].y), posSize, false, 2);
	//				posSize++;
	//			}
	//			else {
	//				if (pos[pose].pos2Size)	pos[pose].pos2 = (Position*)realloc(pos[pose].pos2, sizeof(Position) * (pos[pose].pos2Size + 1));
	//				else					pos[pose].pos2 = (Position*)malloc(sizeof(Position) * (pos[pose].pos2Size + 1));
	//				pos[pose].pos2[pos[pose].pos2Size].num = 2;
	//				pos[pose].pos2[pos[pose].pos2Size].x = charactor.x - 1;
	//				pos[pose].pos2[pos[pose].pos2Size].y = charactor.y + 1;
	//				pos[pose].pos2Size++;
	//			}
	//		}
	//	}
	//	else {
	//		//Vec2(charactor.x + 1, charactor.y + 1);
	//		if (ChecksPosition(charactor.x + 1, charactor.y + 1)) {
	//			if (check) {
	//				if (posSize)	pos = (Position*)realloc(pos, sizeof(Position) * (posSize + 1));
	//				else			pos = (Position*)malloc(sizeof(Position) * (posSize + 1));
	//				pos[posSize].num = 1;
	//				pos[posSize].x = charactor.x + 1;
	//				pos[posSize].y = charactor.y + 1;
	//				pos[posSize].pos2Size = 0;
	//				ChecksPosition(Vec2(pos[posSize].x, pos[posSize].y), posSize, false, 2);
	//				posSize++;
	//			}
	//			else {
	//				if (pos[pose].pos2Size)	pos[pose].pos2 = (Position*)realloc(pos[pose].pos2, sizeof(Position) * (pos[pose].pos2Size + 1));
	//				else					pos[pose].pos2 = (Position*)malloc(sizeof(Position) * (pos[pose].pos2Size + 1));
	//				pos[pose].pos2[pos[pose].pos2Size].num = 2;
	//				pos[pose].pos2[pos[pose].pos2Size].x = charactor.x + 1;
	//				pos[pose].pos2[pos[pose].pos2Size].y = charactor.y + 1;
	//				pos[pose].pos2Size++;
	//			}
	//		}
	//		//Vec2(charactor.x + 1, charactor.y - 1);
	//		if (ChecksPosition(charactor.x + 1, charactor.y - 1)) {
	//			if (check) {
	//				if (posSize)	pos = (Position*)realloc(pos, sizeof(Position) * (posSize + 1));
	//				else			pos = (Position*)malloc(sizeof(Position) * (posSize + 1));
	//				pos[posSize].num = 1;
	//				pos[posSize].x = charactor.x + 1;
	//				pos[posSize].y = charactor.y - 1;
	//				pos[posSize].pos2Size = 0;
	//				ChecksPosition(Vec2(pos[posSize].x, pos[posSize].y), posSize, false, 2);
	//				posSize++;
	//			}
	//			else {
	//				if (pos[pose].pos2Size)	pos[pose].pos2 = (Position*)realloc(pos[pose].pos2, sizeof(Position) * (pos[pose].pos2Size + 1));
	//				else					pos[pose].pos2 = (Position*)malloc(sizeof(Position) * (pos[pose].pos2Size + 1));
	//				pos[pose].pos2[pos[pose].pos2Size].num = 2;
	//				pos[pose].pos2[pos[pose].pos2Size].x = charactor.x + 1;
	//				pos[pose].pos2[pos[pose].pos2Size].y = charactor.y - 1;
	//				pos[pose].pos2Size++;
	//			}
	//		}
	//	}
	//}

	return pos_temp;
}

Vec2 EarthMap::tileCoordForPosition(cocos2d::Vec2 position) {
	position.x = position.x - MovePositionX;
	position.y = (1535.25 + MovePositionY) - position.y;
	//log("position.x = %f, position.y = %f", position.x, position.y);
	int x = position.x / 64;
	float rx = fmodf(position.x, 64);
	//log("nx = %d, rx = %f", x, rx);

	int nx = position.x / 32;

	int ny = (position.y) / 48;
	float ry = fmodf((position.y), 48);
	//log("ny = %d, ry = %f", ny, ry);

	Vec2 p1, p2;
	//직선의 방정식 활용
	if (32 < ry) {
		if (ny % 2 == 0) {		//ny 가 짝수일 때
			if (nx % 2 == 0) {	//nx 가 짝수일 때
				p1 = Vec2(32 * nx + 32, 48 * (ny + 1));
				p2 = Vec2(32 * (nx + 1) - 32, 48 * ny + 32);
			}
			else {				//nx 가 홀수일 때
				p1 = Vec2(32 * nx + 32, 48 * ny + 32);
				p2 = Vec2(32 * (nx + 1) - 32, 48 * (ny + 1));
			}
		}
		else {					//ny 가 홀수일 때
			if (nx % 2 == 0) {	//nx 가 짝수일 때
				p1 = Vec2(32 * nx + 32, 48 * ny + 32);
				p2 = Vec2(32 * (nx + 1) - 32, 48 * (ny + 1));
			}
			else {				//nx 가 홀수일 때
				p1 = Vec2(32 * nx + 32, 48 * (ny + 1));
				p2 = Vec2(32 * (nx + 1) - 32, 48 * ny + 32);
			}
		}
		//log("p1 = (%f, %f), p2 = (%f, %f)", p1.x, p1.y, p2.x, p2.y);

		//직선의 방정식
		float tempy = (p2.y - p1.y) / (p2.x - p1.x) * (position.x - p1.x) + p1.y;
		//log("tempy = %f, position.y = %f", tempy, position.y);
		if (tempy < position.y) {
			//log("plus 1");
			ny++;
		}
		else {
			//log("minus 1");
		}
	}
	if (ny % 2 == 1) {
		x = (position.x - 32) / 64;
	}
	return Vec2(x, ny);
}

