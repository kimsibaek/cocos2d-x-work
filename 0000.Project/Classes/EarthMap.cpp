#include "EarthMap.h"
#include "pauseScene.h"
#include "CreateMonster.h"
#include "MainScene.h"
#include "sqlite3.h"
#include "stdafx.h"
#include <time.h>
#include "Toolbag.h"
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

	cache->addSpriteFramesWithFile("Plist/EarthUpgrade.plist");
	cache->addSpriteFramesWithFile("Plist/FireUpgrade.plist");
	cache->addSpriteFramesWithFile("Plist/WindUpgrade.plist");
	cache->addSpriteFramesWithFile("Plist/WaterUpgrade.plist");
	//cache->addSpriteFramesWithFile("Plist/UpgradeOK.plist");

	BG = Sprite::create("Images/Scene/Earthmap.png");
	BG->setPosition(Vec2(1006, 767));
	this->addChild(BG, 1);

	this->setPosition(Vec2(0, 0));

	tmap = TMXTiledMap::create("Images/Scene/EarthMap.tmx");
	tmap->setPosition(Vec2(-66, -32));
	metainfo = tmap->getLayer("MetaInfo");
	//metainfo->setVisible(false);
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

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(EarthMap::doMsgReceivedTool), "TouchTool", nullptr);

	//DB불러오기
	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";
	//log("%s", dbfileName.c_str());
	
	onCreateCharacter();
	onCreateEmyCharacter();
	//주인공이 화면의 센터로
	//FocusCharacter();

	//주인공 클릭상태
	CharacterClick = false;
	//몬스터 이동후 상태
	SecondCharacterClick = false;

	//아군몬스터가 도구, 소환 작업 상태
	status = false;
	statusAttack = false;
	touchMove = true;
	//몬스터 소환상태
	b_CreateMonster = false;
	createPosSize = 0;

	VPos = Vec2(0, 0);
	ToolUseMonster = 0;
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
		monster_char[0].atk = 200 + ((monster_char[0].level - 1) * 20);
		monster_char[0].def = 100 + ((monster_char[0].level - 1) * 10);
		monster_char[0].hp = 400 + ((monster_char[0].level - 1) * 40);
		monster_char[0].Fullhp = 400 + ((monster_char[0].level - 1) * 40);
		monster_char[0].move = 3;
		monster_char[0].range = 1;
		monster_char[0].HPbarPosition = 21.5;
	}

	int num1 = rand() % 14 + 1;
	int num2 = rand() % 14 + 1;

	while (!ChecksPosition(num1, num2)) {
		num1 = rand() % 14 + 1;
		num2 = rand() % 14 + 1;
	}

	log("%d, %d", num1, num2);
	monster_char[0].tx = num1;
	monster_char[0].ty = num2;
	//log("MonsterCreate = %d, %d", num1, num2);
	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;
	//log("monster_char[i].Type : %d", monster_char[i].Type);
	if (monster_char[0].Type == 0) {
			
		monster_char[0].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
	}

	monster_char[0].sprite->setScale(1);
	if (num2 % 2 == 0) {
		monster_char[0].sprite->setPosition(128 * num1, 1632 - (160 + 96 * num2));
		monster_char[0].xPosition = 128 * num1;
		monster_char[0].yPosition = 1632 - (160 + 96 * num2);
		monster_char[0].xMovePosition = 128 * num1;
		monster_char[0].yMovePosition = 1632 - (160 + 96 * num2);
	}
	else {
		monster_char[0].sprite->setPosition(62 + 128 * num1, 1632 - (160 + 96 * num2));
		monster_char[0].xPosition = 62 + 128 * num1;
		monster_char[0].yPosition = 1632 - (160 + 96 * num2);
		monster_char[0].xMovePosition = 62 + 128 * num1;
		monster_char[0].yMovePosition = 1632 - (160 + 96 * num2);
	}
	//log("monster_char[i] = %f, %f", monster_char[i].xPosition, monster_char[i].yPosition);
	this->addChild(monster_char[0].sprite, 5);

	Sprite* st = Sprite::createWithSpriteFrameName("HP_bar.png");
	st->setPosition(0, -5);
	st->setScaleX(monster_char[0].HPbarPosition / 25 * 2);
	st->setAnchorPoint(Vec2(0, 0.5));
	monster_char[0].sprite->addChild(st, 4, 1);

	Sprite* hp = Sprite::createWithSpriteFrameName("Monster_HP.png");
	hp->setPosition(2, -5);
	hp->setScaleX(monster_char[0].HPbarPosition / 25 * 2);
	//hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
	hp->setAnchorPoint(Vec2(0, 0.5));
	monster_char[0].sprite->addChild(hp, 4, 2);
	
	char level[3];
	sprintf(level, "%d", monster_char[0].level);
	auto pLabel3 = LabelAtlas::create(level, "Images/MonsterLevel.png", 7, 9, '0');
	pLabel3->setAnchorPoint(Vec2(0, 0));
	pLabel3->setPosition(Vec2(hp->getContentSize().width*(monster_char[0].HPbarPosition / 25 * 2) + 5, -10));
	monster_char[0].sprite->addChild(pLabel3, 4, 3);

	Sprite* End = Sprite::createWithSpriteFrameName("End.png");
	End->setAnchorPoint(Vec2(0, 0));
	End->setPosition(Vec2(0, 0));
	if (monster_char[0].move) {

	}
	else {
		monster_char[0].sprite->addChild(End, 4, 4);
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
		int num1 = rand() % 14 + 1;
		int num2 = rand() % 14 + 1;

		while (!ChecksPosition(num1, num2)) {
			num1 = rand() % 14 + 1;
			num2 = rand() % 14 + 1;
		}
		EmyMonster_char[i].tx = num1;
		EmyMonster_char[i].ty = num2;
		//log("EmyMonster[%d] = %d, %d", i, num1, num2);
		char str1[100];
		char str2[100];
		Vector<SpriteFrame*> animFrames;
		//땅질퍽이
		if (EmyMonster_char[i].Type == 1) {
			EmyMonster_char[i].atk = 150 + ((EmyMonster_char[i].level - 1) * 15);
			EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 14.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth1-1.png");
			sprintf(str1, "Earth1-");
		}
		else if (EmyMonster_char[i].Type == 2) {
			EmyMonster_char[i].atk = 200 + ((EmyMonster_char[i].level - 1) * 20);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 4);
			EmyMonster_char[i].hp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].Fullhp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 17;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth2-1.png");
			sprintf(str1, "Earth2-");
		}
		else if (EmyMonster_char[i].Type == 3) {
			EmyMonster_char[i].atk = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].def = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].hp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].Fullhp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 25;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth3-1.png");
			sprintf(str1, "Earth3-");
		}
		//모닥픽
		else if (EmyMonster_char[i].Type == 4) {
			EmyMonster_char[i].atk = 100 + ((EmyMonster_char[i].level - 1) * 10);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 4);
			EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 9;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth4-1.png");
			sprintf(str1, "Earth4-");
		}
		else if (EmyMonster_char[i].Type == 5) {
			EmyMonster_char[i].atk = 200 + ((EmyMonster_char[i].level - 1) * 20);
			EmyMonster_char[i].def = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].hp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].Fullhp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 12.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth5-1.png");
			sprintf(str1, "Earth5-");
		}
		else if (EmyMonster_char[i].Type == 6) {
			EmyMonster_char[i].atk = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].def = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].hp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].Fullhp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 20;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth6-1.png");
			sprintf(str1, "Earth6-");
		}
		//모래두지
		else if (EmyMonster_char[i].Type == 7) {
			EmyMonster_char[i].atk = 100 + ((EmyMonster_char[i].level - 1) * 10);
			EmyMonster_char[i].def = 20 + ((EmyMonster_char[i].level - 1) * 2);
			EmyMonster_char[i].hp = 200 + ((EmyMonster_char[i].level - 1) * 20);
			EmyMonster_char[i].Fullhp = 200 + ((EmyMonster_char[i].level - 1) * 20);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 19;    			
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth7-1.png");
			sprintf(str1, "Earth7-");
		}
		else if (EmyMonster_char[i].Type == 8) {
			EmyMonster_char[i].atk = 150 + ((EmyMonster_char[i].level - 1) * 15);
			EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].hp = 350 + ((EmyMonster_char[i].level - 1) * 35);
			EmyMonster_char[i].Fullhp = 350 + ((EmyMonster_char[i].level - 1) * 35);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 20;   
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth8-1.png");
			sprintf(str1, "Earth8-");
		}
		else if (EmyMonster_char[i].Type == 9) {
			EmyMonster_char[i].atk = 250 + ((EmyMonster_char[i].level - 1) * 25);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 4);
			EmyMonster_char[i].hp = 500 + ((EmyMonster_char[i].level - 1) * 50);
			EmyMonster_char[i].Fullhp = 500 + ((EmyMonster_char[i].level - 1) * 50);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 17;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth9-1.png");
			sprintf(str1, "Earth9-");
		}
		//파이뤼
		else if (EmyMonster_char[i].Type == 11) {
			EmyMonster_char[i].atk = 150 + ((EmyMonster_char[i].level - 1) * 15);
			EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 13.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire1-1.png");
			sprintf(str1, "Fire1-");
		}
		else if (EmyMonster_char[i].Type == 12) {
			EmyMonster_char[i].atk = 200 + ((EmyMonster_char[i].level - 1) * 20);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 4);
			EmyMonster_char[i].hp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].Fullhp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 21;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire2-1.png");
			sprintf(str1, "Fire2-");
		}
		else if (EmyMonster_char[i].Type == 13) {
			EmyMonster_char[i].atk = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].def = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].hp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].Fullhp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 23.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire3-1.png");
			sprintf(str1, "Fire3-");
		}
		//팬템
		else if (EmyMonster_char[i].Type == 14) {
			EmyMonster_char[i].atk = 100 + ((EmyMonster_char[i].level - 1) * 10);
			EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 19;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire4-1.png");
			sprintf(str1, "Fire4-");
		}
		else if (EmyMonster_char[i].Type == 15) {
			EmyMonster_char[i].atk = 200 + ((EmyMonster_char[i].level - 1) * 20);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 4);
			EmyMonster_char[i].hp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].Fullhp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 23.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire5-1.png");
			sprintf(str1, "Fire5-");
		}
		else if (EmyMonster_char[i].Type == 16) {
			EmyMonster_char[i].atk = 350 + ((EmyMonster_char[i].level - 1) * 35);
			EmyMonster_char[i].def = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].hp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].Fullhp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 23.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire6-1.png");
			sprintf(str1, "Fire6-");
		}
		//블랙매직숀
		else if (EmyMonster_char[i].Type == 17) {
			EmyMonster_char[i].atk = 100 + ((EmyMonster_char[i].level - 1) * 10);
			EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 22;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire7-1.png");
			sprintf(str1, "Fire7-");
		}
		else if (EmyMonster_char[i].Type == 18) {
			EmyMonster_char[i].atk = 150 + ((EmyMonster_char[i].level - 1) * 15);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 4);
			EmyMonster_char[i].hp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].Fullhp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 25.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire8-1.png");
			sprintf(str1, "Fire8-");
		}
		else if (EmyMonster_char[i].Type == 19) {
			EmyMonster_char[i].atk = 250 + ((EmyMonster_char[i].level - 1) * 25);
			EmyMonster_char[i].def = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].hp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].Fullhp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 21;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire9-1.png");
			sprintf(str1, "Fire9-");
		}
		//물질퍽이
		else if (EmyMonster_char[i].Type == 21) {
			EmyMonster_char[i].atk = 150 + ((EmyMonster_char[i].level - 1) * 15);
			EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].move = 30;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 14.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water1-1.png");
			sprintf(str1, "Water1-");
		}
		else if (EmyMonster_char[i].Type == 22) {
			EmyMonster_char[i].atk = 200 + ((EmyMonster_char[i].level - 1) * 20);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 4);
			EmyMonster_char[i].hp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].Fullhp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 13.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water2-1.png");
			sprintf(str1, "Water2-");
		}
		else if (EmyMonster_char[i].Type == 23) {
			EmyMonster_char[i].atk = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].def = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].hp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].Fullhp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 25;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water3-1.png");
			sprintf(str1, "Water3-");
		}
		//꼬북이
		else if (EmyMonster_char[i].Type == 24) {
			EmyMonster_char[i].atk = 100 + ((EmyMonster_char[i].level - 1) * 10);
			EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].hp = 350 + ((EmyMonster_char[i].level - 1) * 35);
			EmyMonster_char[i].Fullhp = 350 + ((EmyMonster_char[i].level - 1) * 35);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 20;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water4-1.png");
			sprintf(str1, "Water4-");
		}
		else if (EmyMonster_char[i].Type == 25) {
			EmyMonster_char[i].atk = 200 + ((EmyMonster_char[i].level - 1) * 20);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 4);
			EmyMonster_char[i].hp = 500 + ((EmyMonster_char[i].level - 1) * 50);
			EmyMonster_char[i].Fullhp = 500 + ((EmyMonster_char[i].level - 1) * 50);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 22.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water5-1.png");
			sprintf(str1, "Water5-");
		}
		else if (EmyMonster_char[i].Type == 26) {
			EmyMonster_char[i].atk = 350 + ((EmyMonster_char[i].level - 1) * 35);
			EmyMonster_char[i].def = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].hp = 650 + ((EmyMonster_char[i].level - 1) * 65);
			EmyMonster_char[i].Fullhp = 650 + ((EmyMonster_char[i].level - 1) * 65);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 25;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water6-1.png");
			sprintf(str1, "Water6-");
		}
		//리아커
		else if (EmyMonster_char[i].Type == 27) {
			EmyMonster_char[i].atk = 100 + ((EmyMonster_char[i].level - 1) * 10);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 4);
			EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 20;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water7-1.png");
			sprintf(str1, "Water7-");
		}
		else if (EmyMonster_char[i].Type == 28) {
			EmyMonster_char[i].atk = 200 + ((EmyMonster_char[i].level - 1) * 20);
			EmyMonster_char[i].def = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].hp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].Fullhp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 22.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water8-1.png");
			sprintf(str1, "Water8-");
		}
		else if (EmyMonster_char[i].Type == 29) {
			EmyMonster_char[i].atk = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].def = 60 + ((EmyMonster_char[i].level - 1) * 6);
			EmyMonster_char[i].hp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].Fullhp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 28;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water9-1.png");
			sprintf(str1, "Water9-");
		}
		//코이
		else if (EmyMonster_char[i].Type == 31) {
			EmyMonster_char[i].atk = 150 + ((EmyMonster_char[i].level - 1) * 15);
			EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 19; 
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind1-1.png");
			sprintf(str1, "Wind1-");
		}
		else if (EmyMonster_char[i].Type == 32) {
			EmyMonster_char[i].atk = 200 + ((EmyMonster_char[i].level - 1) * 20);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 4);
			EmyMonster_char[i].hp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].Fullhp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 18.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind2-1.png");
			sprintf(str1, "Wind2-");
		}
		else if (EmyMonster_char[i].Type == 33) {
			EmyMonster_char[i].atk = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].def = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].hp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].Fullhp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 19.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind3-1.png");
			sprintf(str1, "Wind3-");
		}
		//피젼
		else if (EmyMonster_char[i].Type == 34) {
			EmyMonster_char[i].atk = 100 + ((EmyMonster_char[i].level - 1) * 10);
			EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 11.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind4-1.png");
			sprintf(str1, "Wind4-");
		}
		else if (EmyMonster_char[i].Type == 35) {
			EmyMonster_char[i].atk = 200 + ((EmyMonster_char[i].level - 1) * 20);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 4);
			EmyMonster_char[i].hp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].Fullhp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 17.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind5-1.png");
			sprintf(str1, "Wind5-");
		}
		else if (EmyMonster_char[i].Type == 36) {
			EmyMonster_char[i].atk = 350 + ((EmyMonster_char[i].level - 1) * 35);
			EmyMonster_char[i].def = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].hp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].Fullhp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 1;
			EmyMonster_char[i].HPbarPosition = 20;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind6-1.png");
			sprintf(str1, "Wind6-");
		}
		//코이
		else if (EmyMonster_char[i].Type == 37) {
			EmyMonster_char[i].atk = 100 + ((EmyMonster_char[i].level - 1) * 10);
			EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
			EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 20;   
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind7-1.png");
			sprintf(str1, "Wind7-");
		}
		else if (EmyMonster_char[i].Type == 38) {
			EmyMonster_char[i].atk = 150 + ((EmyMonster_char[i].level - 1) * 15);
			EmyMonster_char[i].def = 40 + ((EmyMonster_char[i].level - 1) * 04);
			EmyMonster_char[i].hp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].Fullhp = 450 + ((EmyMonster_char[i].level - 1) * 45);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 17;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind8-1.png");
			sprintf(str1, "Wind8-");
		}
		else if (EmyMonster_char[i].Type == 39) {
			EmyMonster_char[i].atk = 250 + ((EmyMonster_char[i].level - 1) * 25);
			EmyMonster_char[i].def = 50 + ((EmyMonster_char[i].level - 1) * 5);
			EmyMonster_char[i].hp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].Fullhp = 600 + ((EmyMonster_char[i].level - 1) * 60);
			EmyMonster_char[i].move = 3;
			EmyMonster_char[i].range = 2;
			EmyMonster_char[i].HPbarPosition = 23.5;
			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
			sprintf(str1, "Wind9-");
		}
		
		EmyMonster_char[i].sprite->setScale(1);
		if (num2 % 2 == 0) {
			EmyMonster_char[i].sprite->setPosition(128 * num1, 1632 - (111 + 96 * num2));
			EmyMonster_char[i].xPosition = 128 * num1;
			EmyMonster_char[i].yPosition = 1632 - (111 + 96 * num2);
			EmyMonster_char[i].xMovePosition = 128 * num1;
			EmyMonster_char[i].yMovePosition = 1632 - (111 + 96 * num2);
		}
		else {
			EmyMonster_char[i].sprite->setPosition(62 + 128 * num1, 1632 - (111 + 96 * num2));
			EmyMonster_char[i].xPosition = 62 + 128 * num1;
			EmyMonster_char[i].yPosition = 1632 - (111 + 96 * num2);
			EmyMonster_char[i].xMovePosition = 62 + 128 * num1;
			EmyMonster_char[i].yMovePosition = 1632 - (111 + 96 * num2);
		}
		this->addChild(EmyMonster_char[i].sprite, 3);
		Sprite* st = Sprite::createWithSpriteFrameName("HP_bar.png");
		st->setPosition(0, -5);
		st->setScaleX(EmyMonster_char[i].HPbarPosition / 25 * 2);
		st->setAnchorPoint(Vec2(0, 0.5));
		EmyMonster_char[i].sprite->addChild(st, 4, 1);

		Sprite* hp = Sprite::createWithSpriteFrameName("EmyMonseter_HP.png");
		hp->setPosition(2, -5);
		hp->setScaleX(EmyMonster_char[i].HPbarPosition / 25 * 2);
		//hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
		hp->setAnchorPoint(Vec2(0, 0.5));
		EmyMonster_char[i].sprite->addChild(hp, 4, 2);

		char level[3];
		sprintf(level, "%d", EmyMonster_char[i].level);
		auto pLabel3 = LabelAtlas::create(level, "Images/EmyMonsterLevel.png", 7, 9, '0');
		pLabel3->setAnchorPoint(Vec2(0, 0));
		pLabel3->setPosition(Vec2(st->getContentSize().width*(EmyMonster_char[i].HPbarPosition / 25 * 2) + 5, -10));
		EmyMonster_char[i].sprite->addChild(pLabel3, 4, 3);
		
		Sprite* End = Sprite::createWithSpriteFrameName("End.png");
		End->setAnchorPoint(Vec2(0, 0));
		End->setPosition(Vec2(0, 0));
		EmyMonster_char[i].sprite->addChild(End, 4, 4);

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
		//적 몬스터 타일 표시
		for (int i = 0; i < EmyMovePosition.size(); i++) {
			this->addChild(EmyMovePosition.at(i), 2);
		}
		//
		for (int i = 0; i < MovePosition.size(); i++) {
			addChild(MovePosition.at(i), 2);
		}
		CharacterClick = true;
	}
	else {
		createMonsterNum = atoi(testText);
		//log("소환 : %d", createMonsterNum);
		Director::getInstance()->resume();
		b_CreateMonster = true;
		touchMove = true;

		createUpgrade();
		if (createPosSize == 0) {
			//소환 할 장소가 없다고 에러 창 띄우기
			log("소환 할 장소가 없습니다.");
		}
	}

}

void EarthMap::doMsgReceivedTool(Ref* obj) {
	char *inputStr = (char*)obj;
	char testText[20];
	sprintf(testText, "%s", inputStr);
	if (!strcmp(testText, "0")) {
		Director::getInstance()->resume();
		touchMove = true;

		//적 몬스터 타일 표시
		for (int i = 0; i < EmyMovePosition.size(); i++) {
			this->addChild(EmyMovePosition.at(i), 2);
		}
		//
		for (int i = 0; i < MovePosition.size(); i++) {
			addChild(MovePosition.at(i), 2);
		}
		CharacterClick = true;
	}
	else {
		ToolNum = atoi(testText);
		//log("도구 : %d", ToolNum);
		Director::getInstance()->resume();
		touchMove = true;

		if (ToolUseMonster) {
			monster_char[ToolUseMonster-1].hp = 50;
			//log("before monster_char[ToolUseMonster-1].hp = %d", monster_char[ToolUseMonster-1].hp);
			if (ToolNum == 1) {
				log("사과");
				ToolNum = 150;
			}
			else if (ToolNum == 2) {
				log("파인애플");
				ToolNum = 300;
			}
			else if (ToolNum == 3) {
				log("고기");
				ToolNum = 450;
			}
			monster_char[ToolUseMonster-1].hp += ToolNum;
			if (monster_char[ToolUseMonster-1].Fullhp < monster_char[ToolUseMonster-1].hp) {
				monster_char[ToolUseMonster-1].hp = monster_char[ToolUseMonster-1].Fullhp;
			}
			//log("after monster_char[ToolUseMonster-1].hp = %d", monster_char[ToolUseMonster-1].hp);
		}
	}

}

void EarthMap::createUpgrade() {

	for (int i = 0; i < MovePosition.size(); i++) {
		this->removeChild(MovePosition.at(i));
	}
	if (MovePosition.size()) {
		MovePosition.clear();
	}

	for (int i = 0; i < EmyMovePosition.size(); i++) {
		this->removeChild(EmyMovePosition.at(i));
	}
	if (EmyMovePosition.size()) {
		EmyMovePosition.clear();
	}

	VPos = Vec2(VPosX, VPosY);
	createPosSize = 0;
	createMonsterPos = ChecksPosition(VPos, createMonsterPos, 0, 1, 0);
	createPosSize = GrobalTempsize;
	//log("createPosSize = %d", createPosSize);
	//한칸
	for (int m = 0; m < createPosSize; m++) {
		Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
		Vec2 posit = FindCoordPosition(Vec2(createMonsterPos[m].x, createMonsterPos[m].y));
		//log("pos[%d] = %d", m, createMonsterPos[m].num);
		sp->setPosition(posit.x - 2, posit.y + 17);
		MovePosition.pushBack(sp);
	}
	//이동경로 sprite 띄우기
	for (int i = 0; i < MovePosition.size(); i++) {
		addChild(MovePosition.at(i), 2);
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
	//소환, 도구 다이얼로그 창 띄워져 있을 경우
	if (status) {
		return;
	}
	if (statusAttack) {
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
	if (x < winSize.width - 1006) {
		x = winSize.width - 1006;
	}
	else if (x > 1006) {
		x = 1006;
	}
	if (y < winSize.height - 767) {
		y = winSize.height - 767;
	}
	else if (y > 767) {
		y = 767;
	}
	BG->setPosition(Vec2(x, y));

	float tx = tmap->getPosition().x + (EndDragPosition.x - StartDragPosition.x);
	float ty = tmap->getPosition().y + (EndDragPosition.y - StartDragPosition.y);
	if (tx < -1006 - 66 + winSize.width - 1006) {
		tx = -1006 - 66 + winSize.width - 1006;
	}
	else if (tx > -66) {
		tx = -66;
	}
	if (ty < -767 - 32 + winSize.height - 767) {
		ty = -767 - 32 + winSize.height - 767;
	}
	else if (ty > -32) {
		ty = -32;
	}
	tmap->setPosition(Vec2(tx, ty));

	MovePositionX = tx;
	MovePositionY = ty;

	/*for (int i = 0; i < MovePosition.size(); i++) {
		float testx = MovePosition.at(i)->getPosition().x + (EndDragPosition.x - StartDragPosition.x);
		float testy = MovePosition.at(i)->getPosition().y + (EndDragPosition.y - StartDragPosition.y);
		if (testx < winSize.width - 1006.5) {
			testx = winSize.width - 1006.5;
		}
		else if (testx > 1006.5) {
			testx = 1006.5;
		}
		if (testy < 7.75 + winSize.height - 759.75) {
			testy = 7.75 + winSize.height - 759.75;
		}
		else if (testy > 767.5) {
			testy = 767.5;
		}
		MovePosition.at(i)->setPosition(Vec2(testx, testy));
	}
	for (int i = 0; i < EmyMovePosition.size(); i++) {
		float testx = EmyMovePosition.at(i)->getPosition().x + (EndDragPosition.x - StartDragPosition.x);
		float testy = EmyMovePosition.at(i)->getPosition().y + (EndDragPosition.y - StartDragPosition.y);
		if (testx < winSize.width - 1006.5) {
			testx = winSize.width - 1006.5;
		}
		else if (testx > 1006.5) {
			testx = 1006.5;
		}
		if (testy < 7.75 + winSize.height - 759.75) {
			testy = 7.75 + winSize.height - 759.75;
		}
		else if (testy > 767.5) {
			testy = 767.5;
		}
		EmyMovePosition.at(i)->setPosition(Vec2(testx, testy));
	}*/

	StartDragPosition = EndDragPosition;

	
}

void EarthMap::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;

	//일시정지
	bool bTouch1 = pause->getBoundingBox().containsPoint(touchPoint);
	if (bTouch1) {
		Scene* popWin;
		popWin = pauseScene::createScene();
		this->addChild(popWin, 2000, 2000);
	}
	
	//클릭타일좌표
	Vec2 m_pos = tileCoordForPosition(touchPoint);

	//아군소환할 경우
	if (b_CreateMonster) {
		for (int i = 0; i < createPosSize; i++) {
			if (m_pos == Vec2(createMonsterPos[i].x, createMonsterPos[i].y)) {
				//아군몬스터 소환 createMonsterNum
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
						//객체생성
						if (monsterSize)	monster_char = (Monster_num*)realloc(monster_char, sizeof(Monster_num) * (monsterSize + 1));
						else				monster_char = (Monster_num*)malloc(sizeof(Monster_num) * (monsterSize + 1));
						int	ID = sqlite3_column_int(statement, 0);
						int	Type = sqlite3_column_int(statement, 1);
						int	level = sqlite3_column_int(statement, 2);
						int	Item1 = sqlite3_column_int(statement, 3);
						int	Item2 = sqlite3_column_int(statement, 4);
						int	Item3 = sqlite3_column_int(statement, 5);
						int	Exp = sqlite3_column_int(statement, 6);

						if (createMonsterNum == ID) {
							monster_char[monsterSize].ID = ID;
							monster_char[monsterSize].Type = Type;
							monster_char[monsterSize].level = level;
							monster_char[monsterSize].Item1 = Item1;
							monster_char[monsterSize].Item2 = Item2;
							monster_char[monsterSize].Item3 = Item3;
							monster_char[monsterSize].exp = Exp;

							monster_char[monsterSize]._turn = false;
							monsterSize++;
							break;
						}
					}
				}

				sqlite3_finalize(statement);

				sqlite3_close(pDB);

				char str1[100];
				char str2[100];

				int num1 = m_pos.x;
				int num2 = m_pos.y;

				float xPosition;
				float yPosition;
				float xMovePosition;
				float yMovePosition;
				Vector<SpriteFrame*> animFrame;
				if (monster_char[monsterSize - 1].Type > 0 && monster_char[monsterSize - 1].Type < 10) {
					//log("대지속성");
					st = Sprite::createWithSpriteFrameName("EarthUpgrade1.png");
					sprintf(str1, "EarthUpgrade");
					for (int i = 1; i < 13; i++) {
						sprintf(str2, "%s%d.png", str1, i);
						SpriteFrame* frame = cache->getSpriteFrameByName(str2);
						animFrame.pushBack(frame);
					}
				}
				if (monster_char[monsterSize - 1].Type > 10 && monster_char[monsterSize - 1].Type < 20) {
					//log("불속성");
					st = Sprite::createWithSpriteFrameName("FireUpgrade1.png");
					sprintf(str1, "FireUpgrade");
					for (int i = 1; i < 13; i++) {
						sprintf(str2, "%s%d.png", str1, i);
						SpriteFrame* frame = cache->getSpriteFrameByName(str2);
						animFrame.pushBack(frame);
					}
				}
				if (monster_char[monsterSize - 1].Type > 20 && monster_char[monsterSize - 1].Type < 30) {
					//log("물속성");
					st = Sprite::createWithSpriteFrameName("WaterUpgrade1.png");
					sprintf(str1, "WaterUpgrade");
					for (int i = 1; i < 13; i++) {
						sprintf(str2, "%s%d.png", str1, i);
						SpriteFrame* frame = cache->getSpriteFrameByName(str2);
						animFrame.pushBack(frame);
					}
				}
				if (monster_char[monsterSize - 1].Type > 30 && monster_char[monsterSize - 1].Type < 40) {
					//log("바람속성");
					st = Sprite::createWithSpriteFrameName("WindUpgrade1.png");
					sprintf(str1, "WindUpgrade");
					for (int i = 1; i < 13; i++) {
						sprintf(str2, "%s%d.png", str1, i);
						SpriteFrame* frame = cache->getSpriteFrameByName(str2);
						animFrame.pushBack(frame);
					}
				}
				st->setScale(1.5);
				if (num2 % 2 == 0) {
					st->setPosition(64 * num1, 1551 - (37 + 48 * num2));
					xPosition = 64 * num1;
					yPosition = 1551 - (37 + 48 * num2);
					xMovePosition = 64 * num1;
					yMovePosition = 1551 - (37 + 48 * num2);
				}
				else {
					st->setPosition(32 + 64 * num1, 1551 - (37 + 48 * num2));
					xPosition = 32 + 64 * num1;
					yPosition = 1551 - (37 + 48 * num2);
					xMovePosition = 32 + 64 * num1;
					yMovePosition = 1551 - (37 + 48 * num2);
				}

				xMovePosition = xPosition - MovePositionDX;
				yMovePosition = yPosition - MovePositionDY;
				if (xMovePosition < xPosition - 733) {
					xMovePosition = xPosition - 733;
				}
				else if (xMovePosition > xPosition) {
					xMovePosition = xPosition;
				}
				if (yMovePosition < yPosition - 799.5) {
					yMovePosition = yPosition - 799.5;
				}
				else if (yMovePosition > yPosition) {
					yMovePosition = yPosition;
				}
				st->setPosition(Vec2(xMovePosition, yMovePosition));

				auto animation = Animation::createWithSpriteFrames(animFrame, 0.1f);
				auto animate = Animate::create(animation);
				auto cbSound = CallFunc::create(CC_CALLBACK_0(EarthMap::RemoveSprite, this));
				auto seq = Sequence::create(animate, cbSound, NULL);
				st->runAction(seq);
				addChild(st, 5);

				//땅질퍽이
				if (monster_char[monsterSize - 1].Type == 1) {
					monster_char[monsterSize - 1].atk = 150 + ((monster_char[monsterSize - 1].level - 1) * 15);
					monster_char[monsterSize - 1].def = 30 + ((monster_char[monsterSize - 1].level - 1) * 03);
					monster_char[monsterSize - 1].hp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].Fullhp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 14.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Earth1-1.png");
					sprintf(str1, "Earth1-");
				}
				else if (monster_char[monsterSize - 1].Type == 2) {
					monster_char[monsterSize - 1].atk = 200 + ((monster_char[monsterSize - 1].level - 1) * 20);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].Fullhp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 17;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Earth2-1.png");
					sprintf(str1, "Earth2-");
				}
				else if (monster_char[monsterSize - 1].Type == 3) {
					monster_char[monsterSize - 1].atk = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].def = 50 + ((monster_char[monsterSize - 1].level - 1) * 5);
					monster_char[monsterSize - 1].hp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].Fullhp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 25;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Earth3-1.png");
					sprintf(str1, "Earth3-");
				}
				//모닥픽
				else if (monster_char[monsterSize - 1].Type == 4) {
					monster_char[monsterSize - 1].atk = 100 + ((monster_char[monsterSize - 1].level - 1) * 10);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].Fullhp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 9;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Earth4-1.png");
					sprintf(str1, "Earth4-");
				}
				else if (monster_char[monsterSize - 1].Type == 5) {
					monster_char[monsterSize - 1].atk = 200 + ((monster_char[monsterSize - 1].level - 1) * 20);
					monster_char[monsterSize - 1].def = 50 + ((monster_char[monsterSize - 1].level - 1) * 5);
					monster_char[monsterSize - 1].hp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].Fullhp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 12.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Earth5-1.png");
					sprintf(str1, "Earth5-");
				}
				else if (monster_char[monsterSize - 1].Type == 6) {
					monster_char[monsterSize - 1].atk = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].def = 60 + ((monster_char[monsterSize - 1].level - 1) * 6);
					monster_char[monsterSize - 1].hp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].Fullhp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 20;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Earth6-1.png");
					sprintf(str1, "Earth6-");
				}
				//모래두지
				else if (monster_char[monsterSize - 1].Type == 7) {
					monster_char[monsterSize - 1].atk = 100 + ((monster_char[monsterSize - 1].level - 1) * 10);
					monster_char[monsterSize - 1].def = 20 + ((monster_char[monsterSize - 1].level - 1) * 2);
					monster_char[monsterSize - 1].hp = 200 + ((monster_char[monsterSize - 1].level - 1) * 20);
					monster_char[monsterSize - 1].Fullhp = 200 + ((monster_char[monsterSize - 1].level - 1) * 20);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 2;
					monster_char[monsterSize - 1].HPbarPosition = 19;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Earth7-1.png");
					sprintf(str1, "Earth7-");
				}
				else if (monster_char[monsterSize - 1].Type == 8) {
					monster_char[monsterSize - 1].atk = 150 + ((monster_char[monsterSize - 1].level - 1) * 15);
					monster_char[monsterSize - 1].def = 30 + ((monster_char[monsterSize - 1].level - 1) * 3);
					monster_char[monsterSize - 1].hp = 350 + ((monster_char[monsterSize - 1].level - 1) * 35);
					monster_char[monsterSize - 1].Fullhp = 350 + ((monster_char[monsterSize - 1].level - 1) * 35);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 2;
					monster_char[monsterSize - 1].HPbarPosition = 20;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Earth8-1.png");
					sprintf(str1, "Earth8-");
				}
				else if (monster_char[monsterSize - 1].Type == 9) {
					monster_char[monsterSize - 1].atk = 250 + ((monster_char[monsterSize - 1].level - 1) * 25);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 500 + ((monster_char[monsterSize - 1].level - 1) * 50);
					monster_char[monsterSize - 1].Fullhp = 500 + ((monster_char[monsterSize - 1].level - 1) * 50);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 2;
					monster_char[monsterSize - 1].HPbarPosition = 17;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Earth9-1.png");
					sprintf(str1, "Earth9-");
				}
				//파이뤼
				else if (monster_char[monsterSize - 1].Type == 11) {
					monster_char[monsterSize - 1].atk = 150 + ((monster_char[monsterSize - 1].level - 1) * 15);
					monster_char[monsterSize - 1].def = 30 + ((monster_char[monsterSize - 1].level - 1) * 3);
					monster_char[monsterSize - 1].hp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].Fullhp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 13.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Fire1-1.png");
					sprintf(str1, "Fire1-");
				}
				else if (monster_char[monsterSize - 1].Type == 12) {
					monster_char[monsterSize - 1].atk = 200 + ((monster_char[monsterSize - 1].level - 1) * 20);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].Fullhp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 21;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Fire2-1.png");
					sprintf(str1, "Fire2-");
				}
				else if (monster_char[monsterSize - 1].Type == 13) {
					monster_char[monsterSize - 1].atk = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].def = 50 + ((monster_char[monsterSize - 1].level - 1) * 5);
					monster_char[monsterSize - 1].hp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].Fullhp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 23.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Fire3-1.png");
					sprintf(str1, "Fire3-");
				}
				//팬템
				else if (monster_char[monsterSize - 1].Type == 14) {
					monster_char[monsterSize - 1].atk = 100 + ((monster_char[monsterSize - 1].level - 1) * 10);
					monster_char[monsterSize - 1].def = 30 + ((monster_char[monsterSize - 1].level - 1) * 3);
					monster_char[monsterSize - 1].hp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].Fullhp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 19;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Fire4-1.png");
					sprintf(str1, "Fire4-");
				}
				else if (monster_char[monsterSize - 1].Type == 15) {
					monster_char[monsterSize - 1].atk = 200 + ((monster_char[monsterSize - 1].level - 1) * 20);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].Fullhp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 23.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Fire5-1.png");
					sprintf(str1, "Fire5-");
				}
				else if (monster_char[monsterSize - 1].Type == 16) {
					monster_char[monsterSize - 1].atk = 350 + ((monster_char[monsterSize - 1].level - 1) * 35);
					monster_char[monsterSize - 1].def = 50 + ((monster_char[monsterSize - 1].level - 1) * 5);
					monster_char[monsterSize - 1].hp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].Fullhp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 23.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Fire6-1.png");
					sprintf(str1, "Fire6-");
				}
				//블랙매직숀
				else if (monster_char[monsterSize - 1].Type == 17) {
					monster_char[monsterSize - 1].atk = 100 + ((monster_char[monsterSize - 1].level - 1) * 10);
					monster_char[monsterSize - 1].def = 30 + ((monster_char[monsterSize - 1].level - 1) * 3);
					monster_char[monsterSize - 1].hp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].Fullhp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 2;
					monster_char[monsterSize - 1].HPbarPosition = 22;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Fire7-1.png");
					sprintf(str1, "Fire7-");
				}
				else if (monster_char[monsterSize - 1].Type == 18) {
					monster_char[monsterSize - 1].atk = 150 + ((monster_char[monsterSize - 1].level - 1) * 15);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].Fullhp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 2;
					monster_char[monsterSize - 1].HPbarPosition = 25.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Fire8-1.png");
					sprintf(str1, "Fire8-");
				}
				else if (monster_char[monsterSize - 1].Type == 19) {
					monster_char[monsterSize - 1].atk = 250 + ((monster_char[monsterSize - 1].level - 1) * 25);
					monster_char[monsterSize - 1].def = 50 + ((monster_char[monsterSize - 1].level - 1) * 5);
					monster_char[monsterSize - 1].hp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].Fullhp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 2;
					monster_char[monsterSize - 1].HPbarPosition = 21;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Fire9-1.png");
					sprintf(str1, "Fire9-");
				}
				//물질퍽이
				else if (monster_char[monsterSize - 1].Type == 21) {
					monster_char[monsterSize - 1].atk = 150 + ((monster_char[monsterSize - 1].level - 1) * 15);
					monster_char[monsterSize - 1].def = 30 + ((monster_char[monsterSize - 1].level - 1) * 3);
					monster_char[monsterSize - 1].hp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].Fullhp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 14.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Water1-1.png");
					sprintf(str1, "Water1-");
				}
				else if (monster_char[monsterSize - 1].Type == 22) {
					monster_char[monsterSize - 1].atk = 200 + ((monster_char[monsterSize - 1].level - 1) * 20);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].Fullhp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 13.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Water2-1.png");
					sprintf(str1, "Water2-");
				}
				else if (monster_char[monsterSize - 1].Type == 23) {
					monster_char[monsterSize - 1].atk = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].def = 50 + ((monster_char[monsterSize - 1].level - 1) * 5);
					monster_char[monsterSize - 1].hp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].Fullhp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 25;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Water3-1.png");
					sprintf(str1, "Water3-");
				}
				//꼬북이
				else if (monster_char[monsterSize - 1].Type == 24) {
					monster_char[monsterSize - 1].atk = 100 + ((monster_char[monsterSize - 1].level - 1) * 10);
					monster_char[monsterSize - 1].def = 30 + ((monster_char[monsterSize - 1].level - 1) * 3);
					monster_char[monsterSize - 1].hp = 350 + ((monster_char[monsterSize - 1].level - 1) * 35);
					monster_char[monsterSize - 1].Fullhp = 350 + ((monster_char[monsterSize - 1].level - 1) * 35);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 20;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Water4-1.png");
					sprintf(str1, "Water4-");
				}
				else if (monster_char[monsterSize - 1].Type == 25) {
					monster_char[monsterSize - 1].atk = 200 + ((monster_char[monsterSize - 1].level - 1) * 20);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 500 + ((monster_char[monsterSize - 1].level - 1) * 50);
					monster_char[monsterSize - 1].Fullhp = 500 + ((monster_char[monsterSize - 1].level - 1) * 50);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 22.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Water5-1.png");
					sprintf(str1, "Water5-");
				}
				else if (monster_char[monsterSize - 1].Type == 26) {
					monster_char[monsterSize - 1].atk = 350 + ((monster_char[monsterSize - 1].level - 1) * 35);
					monster_char[monsterSize - 1].def = 50 + ((monster_char[monsterSize - 1].level - 1) * 5);
					monster_char[monsterSize - 1].hp = 650 + ((monster_char[monsterSize - 1].level - 1) * 65);
					monster_char[monsterSize - 1].Fullhp = 650 + ((monster_char[monsterSize - 1].level - 1) * 65);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 25;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Water6-1.png");
					sprintf(str1, "Water6-");
				}
				//리아커
				else if (monster_char[monsterSize - 1].Type == 27) {
					monster_char[monsterSize - 1].atk = 100 + ((monster_char[monsterSize - 1].level - 1) * 10);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].Fullhp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 20;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Water7-1.png");
					sprintf(str1, "Water7-");
				}
				else if (monster_char[monsterSize - 1].Type == 28) {
					monster_char[monsterSize - 1].atk = 200 + ((monster_char[monsterSize - 1].level - 1) * 20);
					monster_char[monsterSize - 1].def = 50 + ((monster_char[monsterSize - 1].level - 1) * 5);
					monster_char[monsterSize - 1].hp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].Fullhp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 22.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Water8-1.png");
					sprintf(str1, "Water8-");
				}
				else if (monster_char[monsterSize - 1].Type == 29) {
					monster_char[monsterSize - 1].atk = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].def = 60 + ((monster_char[monsterSize - 1].level - 1) * 6);
					monster_char[monsterSize - 1].hp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].Fullhp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 28;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Water9-1.png");
					sprintf(str1, "Water9-");
				}
				//코이
				else if (monster_char[monsterSize - 1].Type == 31) {
					monster_char[monsterSize - 1].atk = 150 + ((monster_char[monsterSize - 1].level - 1) * 15);
					monster_char[monsterSize - 1].def = 30 + ((monster_char[monsterSize - 1].level - 1) * 3);
					monster_char[monsterSize - 1].hp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].Fullhp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 19;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Wind1-1.png");
					sprintf(str1, "Wind1-");
				}
				else if (monster_char[monsterSize - 1].Type == 32) {
					monster_char[monsterSize - 1].atk = 200 + ((monster_char[monsterSize - 1].level - 1) * 20);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].Fullhp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 18.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Wind2-1.png");
					sprintf(str1, "Wind2-");
				}
				else if (monster_char[monsterSize - 1].Type == 33) {
					monster_char[monsterSize - 1].atk = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].def = 50 + ((monster_char[monsterSize - 1].level - 1) * 5);
					monster_char[monsterSize - 1].hp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].Fullhp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 19.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Wind3-1.png");
					sprintf(str1, "Wind3-");
				}
				//피젼
				else if (monster_char[monsterSize - 1].Type == 34) {
					monster_char[monsterSize - 1].atk = 100 + ((monster_char[monsterSize - 1].level - 1) * 10);
					monster_char[monsterSize - 1].def = 30 + ((monster_char[monsterSize - 1].level - 1) * 3);
					monster_char[monsterSize - 1].hp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].Fullhp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 11.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Wind4-1.png");
					sprintf(str1, "Wind4-");
				}
				else if (monster_char[monsterSize - 1].Type == 35) {
					monster_char[monsterSize - 1].atk = 200 + ((monster_char[monsterSize - 1].level - 1) * 20);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].Fullhp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 17.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Wind5-1.png");
					sprintf(str1, "Wind5-");
				}
				else if (monster_char[monsterSize - 1].Type == 36) {
					monster_char[monsterSize - 1].atk = 350 + ((monster_char[monsterSize - 1].level - 1) * 35);
					monster_char[monsterSize - 1].def = 50 + ((monster_char[monsterSize - 1].level - 1) * 5);
					monster_char[monsterSize - 1].hp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].Fullhp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 1;
					monster_char[monsterSize - 1].HPbarPosition = 20;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Wind6-1.png");
					sprintf(str1, "Wind6-");
				}
				//코이
				else if (monster_char[monsterSize - 1].Type == 37) {
					monster_char[monsterSize - 1].atk = 100 + ((monster_char[monsterSize - 1].level - 1) * 10);
					monster_char[monsterSize - 1].def = 30 + ((monster_char[monsterSize - 1].level - 1) * 3);
					monster_char[monsterSize - 1].hp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].Fullhp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 2;
					monster_char[monsterSize - 1].HPbarPosition = 20;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Wind7-1.png");
					sprintf(str1, "Wind7-");
				}
				else if (monster_char[monsterSize - 1].Type == 38) {
					monster_char[monsterSize - 1].atk = 150 + ((monster_char[monsterSize - 1].level - 1) * 15);
					monster_char[monsterSize - 1].def = 40 + ((monster_char[monsterSize - 1].level - 1) * 4);
					monster_char[monsterSize - 1].hp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].Fullhp = 450 + ((monster_char[monsterSize - 1].level - 1) * 45);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 2;
					monster_char[monsterSize - 1].HPbarPosition = 17;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Wind8-1.png");
					sprintf(str1, "Wind8-");
				}
				else if (monster_char[monsterSize - 1].Type == 39) {
					monster_char[monsterSize - 1].atk = 250 + ((monster_char[monsterSize - 1].level - 1) * 25);
					monster_char[monsterSize - 1].def = 50 + ((monster_char[monsterSize - 1].level - 1) * 5);
					monster_char[monsterSize - 1].hp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].Fullhp = 600 + ((monster_char[monsterSize - 1].level - 1) * 60);
					monster_char[monsterSize - 1].move = 3;
					monster_char[monsterSize - 1].range = 2;
					monster_char[monsterSize - 1].HPbarPosition = 23.5;
					monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
					sprintf(str1, "Wind9-");
				}

				monster_char[monsterSize - 1].sprite->setScale(1.5);
				if (num2 % 2 == 0) {
					monster_char[monsterSize - 1].sprite->setPosition(64 * num1, 1551 - (37 + 48 * num2));
					monster_char[monsterSize - 1].xPosition = 64 * num1;
					monster_char[monsterSize - 1].yPosition = 1551 - (37 + 48 * num2);
					monster_char[monsterSize - 1].xMovePosition = 64 * num1;
					monster_char[monsterSize - 1].yMovePosition = 1551 - (37 + 48 * num2);
				}
				else {
					monster_char[monsterSize - 1].sprite->setPosition(32 + 64 * num1, 1551 - (37 + 48 * num2));
					monster_char[monsterSize - 1].xPosition = 32 + 64 * num1;
					monster_char[monsterSize - 1].yPosition = 1551 - (37 + 48 * num2);
					monster_char[monsterSize - 1].xMovePosition = 32 + 64 * num1;
					monster_char[monsterSize - 1].yMovePosition = 1551 - (37 + 48 * num2);
				}
				monster_char[monsterSize - 1].tx = num1;
				monster_char[monsterSize - 1].ty = num2;
				monster_char[monsterSize - 1].xMovePosition = monster_char[monsterSize - 1].xPosition - MovePositionDX;
				monster_char[monsterSize - 1].yMovePosition = monster_char[monsterSize - 1].yPosition - MovePositionDY;
				if (monster_char[monsterSize - 1].xMovePosition < monster_char[monsterSize - 1].xPosition - 733) {
					monster_char[monsterSize - 1].xMovePosition = monster_char[monsterSize - 1].xPosition - 733;
				}
				else if (monster_char[monsterSize - 1].xMovePosition > monster_char[monsterSize - 1].xPosition) {
					monster_char[monsterSize - 1].xMovePosition = monster_char[monsterSize - 1].xPosition;
				}
				if (monster_char[monsterSize - 1].yMovePosition < monster_char[monsterSize - 1].yPosition - 799.5) {
					monster_char[monsterSize - 1].yMovePosition = monster_char[monsterSize - 1].yPosition - 799.5;
				}
				else if (monster_char[monsterSize - 1].yMovePosition > monster_char[monsterSize - 1].yPosition) {
					monster_char[monsterSize - 1].yMovePosition = monster_char[monsterSize - 1].yPosition;
				}
				monster_char[monsterSize - 1].sprite->setPosition(Vec2(monster_char[monsterSize - 1].xMovePosition, monster_char[monsterSize - 1].yMovePosition));

				this->addChild(monster_char[monsterSize - 1].sprite, 3);
				Sprite* st = Sprite::createWithSpriteFrameName("HP_bar.png");
				st->setPosition(0, -5);
				st->setScaleX(monster_char[monsterSize - 1].HPbarPosition / 25 * 2);
				st->setAnchorPoint(Vec2(0, 0.5));
				monster_char[monsterSize - 1].sprite->addChild(st, 4);

				Sprite* hp = Sprite::createWithSpriteFrameName("Monster_HP.png");
				hp->setPosition(1, 0);
				hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
				hp->setAnchorPoint(Vec2(0, 0));
				st->addChild(hp, 4);

				char level[3];
				sprintf(level, "%d", monster_char[monsterSize - 1].level);
				auto pLabel3 = LabelAtlas::create(level, "Images/MonsterLevel.png", 7, 9, '0');
				pLabel3->setAnchorPoint(Vec2(0, 0));
				pLabel3->setPosition(Vec2(hp->getContentSize().width*(monster_char[monsterSize - 1].HPbarPosition / 25 * 2), -10));
				monster_char[monsterSize - 1].sprite->addChild(pLabel3);

				Sprite* End = Sprite::createWithSpriteFrameName("End.png");
				End->setAnchorPoint(Vec2(0, 0));
				End->setPosition(Vec2(0, 0));
				monster_char[monsterSize - 1].sprite->addChild(End);

				Vector<SpriteFrame*> animFrames;

				for (int i = 1; i < 5; i++) {
					sprintf(str2, "%s%d.png", str1, i);
					SpriteFrame* frame = cache->getSpriteFrameByName(str2);
					animFrames.pushBack(frame);
				}

				animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
				animate = Animate::create(animation);
				auto rep = RepeatForever::create(animate);
				monster_char[monsterSize - 1].sprite->runAction(rep);

				//FocusCharacter();
				b_CreateMonster = false;
				for (int i = 0; i < MovePosition.size(); i++) {
					this->removeChild(MovePosition.at(i));
				}
				MovePosition.clear();

				if (createPosSize != 0) {
					free(createMonsterPos);
					createPosSize = 0;
				}
			}
		}
		return;
	}

	//소환, 도구 다이얼로그 창 띄워져 있을 경우
	if (!touchMove) {
		return;
	}
	
	//myTouch(소환, 도구)
	if (status) {
		if (statuschar) {
			//소환
			bool bTouch2 = createMonster->getBoundingBox().containsPoint(touchPoint);
			if (bTouch2) {
				touchMove = false;
				Scene* popWin;
				popWin = CreateMonster::createScene();
				this->addChild(popWin, 2000, 2000);

				CharacterClick = false;
				status = false;
			}
		}
		//도구
		bool bTouch3 = Items->getBoundingBox().containsPoint(touchPoint);
		if (bTouch3) {
			touchMove = false;
			Scene* popWin;
			popWin = Toolbag::createScene();
			this->addChild(popWin, 2000, 2000);

			CharacterClick = false;
			status = false;
		}
		if (!status) {
			removeChild(createMonster);
			removeChild(Items);
		}

		for (int i = 0; i < monsterSize; i++) {
			Vec2 mon_pos = tileCoordForPosition(Vec2(monster_char[i].xMovePosition, monster_char[i].yMovePosition));
			//log("좌표2 %f, %f, %f, %f", mon_pos.x, mon_pos.y, ToolUsePosition.x, ToolUsePosition.y);
			if (mon_pos.x == ToolUsePosition.x && mon_pos.y == ToolUsePosition.y) {
				ToolUseMonster = i+1;
				break;
			}
		}
		return;
	}
	
	//공격가능 적 클릭(공격, 디스펠)
	if (statusAttack) {
		//공격
		bool bTouch2 = attack->getBoundingBox().containsPoint(touchPoint);
		if (bTouch2) {
			float bufDamage = 1.0;
			float bufDefense = 1.0;
			if (BufTileCheck(Vec2(monster_char[mons].tx, monster_char[mons].ty))) {
				bufDamage += 0.2;
			}
			if (BufTileCheck(Vec2(EmyMonster_char[ClickEmyMonster].tx, EmyMonster_char[ClickEmyMonster].ty))) {
				bufDefense += 0.2;
			}

			if (SynastryCheck(monster_char[mons].Type, EmyMonster_char[ClickEmyMonster].Type) == 1) {
				bufDamage += 0.2;
			}
			else if (SynastryCheck(monster_char[mons].Type, EmyMonster_char[ClickEmyMonster].Type) == 2) {
				bufDefense += 0.2;
			}
			//log("defore hp = %d", EmyMonster_char[ClickEmyMonster].hp);
			int damage = (monster_char[mons].atk * bufDamage) - (EmyMonster_char[ClickEmyMonster].def * bufDefense);
			//log("damage = %d, monster_char[mons].atk = %d, bufDamage = %f, EmyMonster_char[ClickEmyMonster].def = %d, bufDefense = %f",
				//damage, monster_char[mons].atk, bufDamage, EmyMonster_char[ClickEmyMonster].def, bufDefense);
			if (damage > 0) {
				EmyMonster_char[ClickEmyMonster].hp -= damage;
				EmyMonster_char[ClickEmyMonster].sprite->removeChildByTag(2);
				Sprite* hp = Sprite::createWithSpriteFrameName("EmyMonseter_HP.png");
				hp->setPosition(2, -5);
				hp->setScaleX((EmyMonster_char[ClickEmyMonster].HPbarPosition / 25 * 2) * EmyMonster_char[ClickEmyMonster].hp / EmyMonster_char[ClickEmyMonster].Fullhp);
				//hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
				hp->setAnchorPoint(Vec2(0, 0.5));
				EmyMonster_char[ClickEmyMonster].sprite->addChild(hp, 4, 2);

				if (EmyMonster_char[ClickEmyMonster].hp < 0) {
					EmyMonster_char[ClickEmyMonster].hp = 0;
					//적 몬스터 죽음 처리
					removeChild(EmyMonster_char[ClickEmyMonster].sprite);
					for (int k = ClickEmyMonster; k < EmyMonsterSize - 1; k++) {
						EmyMonster_char[k] = EmyMonster_char[k + 1];
					}
					EmyMonster_char = (Monster_num*)realloc(EmyMonster_char, sizeof(Monster_num) * (EmyMonsterSize - 1));
					EmyMonsterSize--;

					ExpCheck();
				}
			}
			statusAttack = false;
			//적 몬스터 타일 지우기
			for (int i = 0; i < EmyMovePosition.size(); i++) {
				this->removeChild(EmyMovePosition.at(i));
			}
			EmyMovePosition.clear();
			//
			for (int i = 0; i < MovePosition.size(); i++) {
				this->removeChild(MovePosition.at(i));
			}
			MovePosition.clear();
		}
		//디스펠
		bool bTouch3 = dispel->getBoundingBox().containsPoint(touchPoint);
		if (bTouch3) {
			int per = rand() % 100 + 1;
			float hp_per = ((float)EmyMonster_char[ClickEmyMonster].Fullhp - (float)EmyMonster_char[ClickEmyMonster].hp) / (float)EmyMonster_char[ClickEmyMonster].Fullhp * 100.0;
			//log("%d, %f", per, hp_per);
			if(per <= (int)hp_per){
				//GET!!!
				char str1[100];
				char str2[100];

				int num1 = EmyMonster_char[ClickEmyMonster].tx;
				int num2 = EmyMonster_char[ClickEmyMonster].ty;

				float xPosition;
				float yPosition;
				float xMovePosition;
				float yMovePosition;
				Vector<SpriteFrame*> animFrame;
				if (EmyMonster_char[ClickEmyMonster].Type > 0 && EmyMonster_char[ClickEmyMonster].Type < 10) {
					//log("대지속성");
					st = Sprite::createWithSpriteFrameName("EarthUpgrade1.png");
					sprintf(str1, "EarthUpgrade");
					for (int i = 1; i < 13; i++) {
						sprintf(str2, "%s%d.png", str1, i);
						SpriteFrame* frame = cache->getSpriteFrameByName(str2);
						animFrame.pushBack(frame);
					}
				}
				if (EmyMonster_char[ClickEmyMonster].Type > 10 && EmyMonster_char[ClickEmyMonster].Type < 20) {
					//log("불속성");
					st = Sprite::createWithSpriteFrameName("FireUpgrade1.png");
					sprintf(str1, "FireUpgrade");
					for (int i = 1; i < 13; i++) {
						sprintf(str2, "%s%d.png", str1, i);
						SpriteFrame* frame = cache->getSpriteFrameByName(str2);
						animFrame.pushBack(frame);
					}
				}
				if (EmyMonster_char[ClickEmyMonster].Type > 20 && EmyMonster_char[ClickEmyMonster].Type < 30) {
					//log("물속성");
					st = Sprite::createWithSpriteFrameName("WaterUpgrade1.png");
					sprintf(str1, "WaterUpgrade");
					for (int i = 1; i < 13; i++) {
						sprintf(str2, "%s%d.png", str1, i);
						SpriteFrame* frame = cache->getSpriteFrameByName(str2);
						animFrame.pushBack(frame);
					}
				}
				if (EmyMonster_char[ClickEmyMonster].Type > 30 && EmyMonster_char[ClickEmyMonster].Type < 40) {
					//log("바람속성");
					st = Sprite::createWithSpriteFrameName("WindUpgrade1.png");
					sprintf(str1, "WindUpgrade");
					for (int i = 1; i < 13; i++) {
						sprintf(str2, "%s%d.png", str1, i);
						SpriteFrame* frame = cache->getSpriteFrameByName(str2);
						animFrame.pushBack(frame);
					}
				}
				st->setScale(1.5);
				if (num2 % 2 == 0) {
					st->setPosition(64 * num1, 1551 - (37 + 48 * num2));
					xPosition = 64 * num1;
					yPosition = 1551 - (37 + 48 * num2);
					xMovePosition = 64 * num1;
					yMovePosition = 1551 - (37 + 48 * num2);
				}
				else {
					st->setPosition(32 + 64 * num1, 1551 - (37 + 48 * num2));
					xPosition = 32 + 64 * num1;
					yPosition = 1551 - (37 + 48 * num2);
					xMovePosition = 32 + 64 * num1;
					yMovePosition = 1551 - (37 + 48 * num2);
				}

				xMovePosition = xPosition - MovePositionDX;
				yMovePosition = yPosition - MovePositionDY;
				if (xMovePosition < xPosition - 733) {
					xMovePosition = xPosition - 733;
				}
				else if (xMovePosition > xPosition) {
					xMovePosition = xPosition;
				}
				if (yMovePosition < yPosition - 799.5) {
					yMovePosition = yPosition - 799.5;
				}
				else if (yMovePosition > yPosition) {
					yMovePosition = yPosition;
				}
				st->setPosition(Vec2(xMovePosition, yMovePosition));

				auto animation = Animation::createWithSpriteFrames(animFrame, 0.1f);
				auto animate = Animate::create(animation);
				auto cbSound = CallFunc::create(CC_CALLBACK_0(EarthMap::RemoveSprite, this));
				auto seq = Sequence::create(animate, cbSound, NULL);
				st->runAction(seq);
				addChild(st, 5);


				removeChild(EmyMonster_char[ClickEmyMonster].sprite);
				for (int k = ClickEmyMonster; k < EmyMonsterSize - 1; k++) {
					EmyMonster_char[k] = EmyMonster_char[k + 1];
				}
				EmyMonster_char = (Monster_num*)realloc(EmyMonster_char, sizeof(Monster_num) * (EmyMonsterSize - 1));
				EmyMonsterSize--;
			}
			ExpCheck();
			statusAttack = false;
			for (int i = 0; i < EmyMovePosition.size(); i++) {
				this->removeChild(EmyMovePosition.at(i));
			}
			EmyMovePosition.clear();
			for (int i = 0; i < MovePosition.size(); i++) {
				this->removeChild(MovePosition.at(i));
			}
			MovePosition.clear();
		}
		if (!statusAttack) {
			removeChild(attack);
			removeChild(dispel);

		}
		return;
	}
	
	//자기자신이 클릭상태일 경우
	if (CharacterClick) {
		Vec2 mon_pos = tileCoordForPosition(Vec2(monster_char[mons].xMovePosition, monster_char[mons].yMovePosition));
		ToolUsePosition = m_pos;
		//자기자신을 클릭시 (도구, 소환)
		if (m_pos == mon_pos) {
			if (monster_char[mons].Type == 0) {
				status = true;
				statuschar = true;
				//log("소환, 도구");
				//create 소환
				createMonster = Sprite::create("Images/Scene/createMonster.png");
				createMonster->setPosition(Vec2(monster_char[mons].xMovePosition, monster_char[mons].yMovePosition - 28));
				createMonster->setScale(2.0f);
				addChild(createMonster, 6);
				//create 도구
				Items = Sprite::create("Images/Scene/Items.png");
				Items->setPosition(Vec2(monster_char[mons].xMovePosition, monster_char[mons].yMovePosition + 28));
				Items->setScale(2.0f);
				addChild(Items, 6);
			}
			else {
				//log("도구");
				status = true;
				statuschar = false;
				//create 도구
				Items = Sprite::create("Images/Scene/Items1.png");
				Items->setPosition(Vec2(monster_char[mons].xMovePosition, monster_char[mons].yMovePosition));
				Items->setScale(2.0f);
				addChild(Items, 6);
			}
			VPosX = mon_pos.x;
			VPosY = mon_pos.y;

			for (int i = 0; i < EmyMovePosition.size(); i++) {
				this->removeChild(EmyMovePosition.at(i));
			}
			for (int i = 0; i < MovePosition.size(); i++) {
				this->removeChild(MovePosition.at(i));
			}
			return;
		}
		
		//공격 범위내 적군몬스터 클릭시 (공격, 디스펠)
		else if (checkEmyMonsterCoordinate(m_pos)) {
			//데미지 계산
			//주인공이 적군 몬스터를 공격, 디스펠 할 경우
			if (mons == 0) {
				//log("공격, 디스펠");
				statusAttack = true;
				//create 공격
				attack = Sprite::create("Images/Scene/Attack2.png");
				attack->setPosition(Vec2(EmyMonster_char[ClickEmyMonster].xMovePosition, EmyMonster_char[ClickEmyMonster].yMovePosition + 28));
				attack->setScale(2.0f);
				addChild(attack, 6);
				//create 디스펠
				dispel = Sprite::create("Images/Scene/DISPEL2.png");
				dispel->setPosition(Vec2(EmyMonster_char[ClickEmyMonster].xMovePosition, EmyMonster_char[ClickEmyMonster].yMovePosition - 28));
				dispel->setScale(2.0f);
				addChild(dispel, 6);
			}
			//아군 소환몬스터가 적군 몬스터 공격
			else {
				float bufDamage = 1.0;
				float bufDefense = 1.0;
				if (BufTileCheck(Vec2(monster_char[mons].tx, monster_char[mons].ty))) {
					bufDamage += 0.2;
				}
				if (BufTileCheck(Vec2(EmyMonster_char[ClickEmyMonster].tx, EmyMonster_char[ClickEmyMonster].ty))) {
					bufDefense += 0.2;
				}

				if (SynastryCheck(monster_char[mons].Type, EmyMonster_char[ClickEmyMonster].Type) == 1) {
					bufDamage += 0.2;
				}
				else if (SynastryCheck(monster_char[mons].Type, EmyMonster_char[ClickEmyMonster].Type) == 2) {
					bufDefense += 0.2;
				}
				//log("defore hp = %d", EmyMonster_char[ClickEmyMonster].hp);
				int damage = (monster_char[mons].atk * bufDamage) - (EmyMonster_char[ClickEmyMonster].def * bufDefense);
				//log("damage = %d, monster_char[mons].atk = %d, bufDamage = %f, EmyMonster_char[ClickEmyMonster].def = %d, bufDefense = %f",
				//damage, monster_char[mons].atk, bufDamage, EmyMonster_char[ClickEmyMonster].def, bufDefense);
				if (damage > 0) {
					EmyMonster_char[ClickEmyMonster].hp -= damage;
					EmyMonster_char[ClickEmyMonster].sprite->removeChildByTag(2);
					Sprite* hp = Sprite::createWithSpriteFrameName("EmyMonseter_HP.png");
					hp->setPosition(2, -5);
					hp->setScaleX((EmyMonster_char[ClickEmyMonster].HPbarPosition / 25 * 2) * EmyMonster_char[ClickEmyMonster].hp / EmyMonster_char[ClickEmyMonster].Fullhp);
					//hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
					hp->setAnchorPoint(Vec2(0, 0.5));
					EmyMonster_char[ClickEmyMonster].sprite->addChild(hp, 4, 2);

					if (EmyMonster_char[ClickEmyMonster].hp < 0) {
						EmyMonster_char[ClickEmyMonster].hp = 0;
						//적 몬스터 죽음 처리
						removeChild(EmyMonster_char[ClickEmyMonster].sprite);
						for (int k = ClickEmyMonster; k < EmyMonsterSize - 1; k++) {
							EmyMonster_char[k] = EmyMonster_char[k + 1];
						}
						EmyMonster_char = (Monster_num*)realloc(EmyMonster_char, sizeof(Monster_num) * (EmyMonsterSize - 1));
						EmyMonsterSize--;

						ExpCheck();
					}
				}
				statusAttack = false;
				//적 몬스터 타일 지우기
				for (int i = 0; i < EmyMovePosition.size(); i++) {
					this->removeChild(EmyMovePosition.at(i));
				}
				EmyMovePosition.clear();
				//
				for (int i = 0; i < MovePosition.size(); i++) {
					this->removeChild(MovePosition.at(i));
				}
				MovePosition.clear();
			}
			CharacterClick = false;
			return;
		}
		
		//아군몬스터 범위내 클릭시 (경로 이동)
		else if (checkcoordinate(m_pos)) {
			
			SpriteCoordinateChange(m_pos);

			//이동 시작

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
						//log("shortpass[%d] = %d, xy = %d, %d", k, shortpass[k].num, shortpass[k].x, shortpass[k].y);
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
						//log("shortpass[%d] = %d, front = %d, %d, xy = %d, %d", k, shortpass[k].num, shortpass[k].front_x, shortpass[k].front_y, shortpass[k].x, shortpass[k].y);
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
						//log("shortpass[%d] = %d, frontfront = %d, %d, front = %d, %d, xy = %d, %d", k, shortpass[k].num, shortpass[k].front_front_x, shortpass[k].front_front_y, shortpass[k].front_x, shortpass[k].front_y, shortpass[k].front_x, shortpass[k].front_y);
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
						//log("shortpass[%d] = %d, frontfrontfront = %d, %d, frontfront = %d, %d, front = %d, %d, xy = %d, %d", k, shortpass[k].num, shortpass[k].front_front_front_x, shortpass[k].front_front_front_y, shortpass[k].front_front_x, shortpass[k].front_front_y, shortpass[k].front_x, shortpass[k].front_y, shortpass[k].front_x, shortpass[k].front_y);
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
			
			//이동 끝

			//이동후 공격범위 내 적 몬스터가 있을 시 공격상태
			//공격가능 몬스터 타일표시
			DisplayEmyMonsterAttack(m_pos);
			CharacterClick = true;
		}
	}
	//아무런 상태가 아닐 경우
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

			//적 몬스터 타일 지우기
			for (int i = 0; i < EmyMovePosition.size(); i++) {
				this->removeChild(EmyMovePosition.at(i));
			}
			EmyMovePosition.clear();
			//
			for (int i = 0; i < MovePosition.size(); i++) {
				this->removeChild(MovePosition.at(i));
			}
			MovePosition.clear();

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
			pos = ChecksPosition(mon_pos, pos, posSize, monster_char[mons].move, 1);
			posSize = GrobalTempsize;
			//한칸
			for (int m = 0; m < posSize; m++) {
				Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
				Vec2 posit = FindCoordPosition(Vec2(pos[m].x, pos[m].y));
				//log("pos[%d] = %d", m, pos[m].num);
				//sp->setPosition(posit.x - 2, posit.y + 17);
				sp->setPosition(posit.x + 30 - monster_char[mons].xMovePosition, posit.y + 64 - monster_char[mons].yMovePosition);
				monster_char[mons].sprite->addChild(sp);
				MovePosition.pushBack(sp);
				//두칸
				if (pos[m].pos2Size) {
					for (int k = 0; k < pos[m].pos2Size; k++) {
						Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
						Vec2 posit2 = FindCoordPosition(Vec2(pos[m].pos2[k].x, pos[m].pos2[k].y));
						//log("pos[%d].pos2[%d] = %d", m, k, pos[m].pos2[k].num);
						//sp->setPosition(posit2.x - 2, posit2.y + 34);
						sp->setPosition(posit2.x + 30 - monster_char[mons].xMovePosition, posit2.y + 64 - monster_char[mons].yMovePosition);
						monster_char[mons].sprite->addChild(sp);
						MovePosition.pushBack(sp);
						//세칸
						if (pos[m].pos2[k].pos2Size) {
							for (int z = 0; z < pos[m].pos2[k].pos2Size; z++) {
								Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
								Vec2 posit2 = FindCoordPosition(Vec2(pos[m].pos2[k].pos2[z].x, pos[m].pos2[k].pos2[z].y));
								//log("pos[%d].pos2[%d].pos2[%d] = %d", m, k, z, pos[m].pos2[k].pos2[z].num);
								//sp->setPosition(posit2.x - 2, posit2.y + 34);
								sp->setPosition(posit2.x + 30 - monster_char[mons].xMovePosition, posit2.y + 64 - monster_char[mons].yMovePosition);
								monster_char[mons].sprite->addChild(sp);
								MovePosition.pushBack(sp);
								//네칸
								if (pos[m].pos2[k].pos2[z].pos2Size) {
									for (int i = 0; i < pos[m].pos2[k].pos2[z].pos2Size; i++) {
										Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
										Vec2 posit2 = FindCoordPosition(Vec2(pos[m].pos2[k].pos2[z].pos2[i].x, pos[m].pos2[k].pos2[z].pos2[i].y));
										//log("pos[%d].pos2[%d].pos2[%d].pos2[i] = %d", m, k, z, i, pos[m].pos2[k].pos2[z].pos2[i].num);
										//sp->setPosition(posit2.x - 2, posit2.y + 34);
										sp->setPosition(posit2.x + 30 - monster_char[mons].xMovePosition, posit2.y + 64 - monster_char[mons].yMovePosition);
										monster_char[mons].sprite->addChild(sp);
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
			/*for (int i = 0; i < MovePosition.size(); i++) {
				this->addChild(MovePosition.at(i), 2);
			}*/
			//적 표시
			for (int m = 0; m < EmyposSize; m++) {
				Emypos[m].PositionView = false;
				for (int k = 0; k < EmyMonsterSize; k++) {

					//공격범위 1이상 체크
					if (monster_char[mons].range > 0) {
						if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty == Emypos[m].y) {
							Emypos[m].PositionView = true;
							break;
						}
						if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty == Emypos[m].y) {
							Emypos[m].PositionView = true;
							break;
						}
						if (monster_char[mons].tx == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
							Emypos[m].PositionView = true;
							break;
						}
						if (monster_char[mons].tx == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
							Emypos[m].PositionView = true;
							break;
						}
						if (monster_char[mons].ty % 2 == 0) {
							if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
							if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
						}
						else {
							if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
							if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
						}
						//공격범위 2일때 체크
						if (monster_char[mons].range > 1) {
							if (monster_char[mons].tx == Emypos[m].x && monster_char[mons].ty - 2 == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
							if (monster_char[mons].tx == Emypos[m].x && monster_char[mons].ty + 2 == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
							if (monster_char[mons].tx + 2 == Emypos[m].x && monster_char[mons].ty == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
							if (monster_char[mons].tx - 2 == Emypos[m].x && monster_char[mons].ty == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
							if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty - 2 == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
							if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty + 2 == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
							if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty - 2 == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
							if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty + 2 == Emypos[m].y) {
								Emypos[m].PositionView = true;
								break;
							}
							if (monster_char[mons].ty % 2 == 0) {
								if (monster_char[mons].tx - 2 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
									Emypos[m].PositionView = true;
									break;
								}
								if (monster_char[mons].tx - 2 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
									Emypos[m].PositionView = true;
									break;
								}
								if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
									Emypos[m].PositionView = true;
									break;
								}
								if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
									Emypos[m].PositionView = true;
									break;
								}
							}
							else {
								if (monster_char[mons].tx + 2 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
									Emypos[m].PositionView = true;
									break;
								}
								if (monster_char[mons].tx + 2 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
									Emypos[m].PositionView = true;
									break;
								}
								if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
									Emypos[m].PositionView = true;
									break;
								}
								if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
									Emypos[m].PositionView = true;
									break;
								}
							}
						}
					}
					
				}
				
				if (Emypos[m].PositionView) {
					int type;
					for (int k = 0; k < EmyMonsterSize; k++) {
						if (EmyMonster_char[k].tx == Emypos[m].x && EmyMonster_char[k].ty == Emypos[m].y) {
							type = EmyMonster_char[k].Type;
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
							//sp->setPosition(posit.x - 2, posit.y + 34);
							sp->setPosition(posit.x + 25 - EmyMonster_char[k].xMovePosition, posit.y + 44 - EmyMonster_char[k].yMovePosition);
							EmyMonster_char[k].sprite->addChild(sp);
							EmyMovePosition.pushBack(sp);
							break;
						}
					}
					
				}
				
			}
			/*for (int i = 0; i < EmyMovePosition.size(); i++) {
				this->addChild(EmyMovePosition.at(i), 2);
			}*/
		}
	}
}

void EarthMap::DisplayEmyMonsterAttack(Vec2 posVec) {
	if (EmyposSize) {
		free(Emypos);
		EmyposSize = 0;
	}
	for (int k = 0; k < EmyMonsterSize; k++) {

		//공격범위 1이상 체크
		if (monster_char[mons].range > 0) {
			if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y == EmyMonster_char[k].ty) {
				if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
				else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
				EmyposSize++;
				Emypos[EmyposSize - 1].x = posVec.x - 1;
				Emypos[EmyposSize - 1].y = posVec.y;
				Emypos[EmyposSize - 1].PositionView = true;
				Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
			}
			if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y == EmyMonster_char[k].ty) {
				if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
				else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
				EmyposSize++;
				Emypos[EmyposSize - 1].x = posVec.x + 1;
				Emypos[EmyposSize - 1].y = posVec.y;
				Emypos[EmyposSize - 1].PositionView = true;
				Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
			}
			if (posVec.x == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
				if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
				else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
				EmyposSize++;
				Emypos[EmyposSize - 1].x = posVec.x;
				Emypos[EmyposSize - 1].y = posVec.y - 1;
				Emypos[EmyposSize - 1].PositionView = true;
				Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
			}
			if (posVec.x == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
				if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
				else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
				EmyposSize++;
				Emypos[EmyposSize - 1].x = posVec.x;
				Emypos[EmyposSize - 1].y = posVec.y + 1;
				Emypos[EmyposSize - 1].PositionView = true;
				Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
			}
			if (fmodf(posVec.y, 2) == 0) {
				if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x - 1;
					Emypos[EmyposSize - 1].y = posVec.y - 1;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
				if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x - 1;
					Emypos[EmyposSize - 1].y = posVec.y + 1;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
			}
			else {
				if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x + 1;
					Emypos[EmyposSize - 1].y = posVec.y + 1;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
				if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x + 1;
					Emypos[EmyposSize - 1].y = posVec.y - 1;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
			}
			//공격범위 2일때 체크
			if (monster_char[mons].range > 1) {
				if (posVec.x == EmyMonster_char[k].tx && posVec.y - 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x;
					Emypos[EmyposSize - 1].y = posVec.y - 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
				if (posVec.x == EmyMonster_char[k].tx && posVec.y + 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x;
					Emypos[EmyposSize - 1].y = posVec.y + 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
				if (posVec.x + 2 == EmyMonster_char[k].tx && posVec.y == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x + 2;
					Emypos[EmyposSize - 1].y = posVec.y;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
				if (posVec.x - 2 == EmyMonster_char[k].tx && posVec.y == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x - 2;
					Emypos[EmyposSize - 1].y = posVec.y;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
				if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y - 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x - 1;
					Emypos[EmyposSize - 1].y = posVec.y - 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
				if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y + 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x - 1;
					Emypos[EmyposSize - 1].y = posVec.y + 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
				if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y - 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x + 1;
					Emypos[EmyposSize - 1].y = posVec.y - 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
				if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y + 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].x = posVec.x + 1;
					Emypos[EmyposSize - 1].y = posVec.y + 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				}
				if (fmodf(posVec.y, 2) == 0) {
					if (posVec.x - 2 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].x = posVec.x - 2;
						Emypos[EmyposSize - 1].y = posVec.y - 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					}
					if (posVec.x - 2 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].x = posVec.x - 2;
						Emypos[EmyposSize - 1].y = posVec.y + 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					}
					if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].x = posVec.x + 1;
						Emypos[EmyposSize - 1].y = posVec.y - 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					}
					if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].x = posVec.x + 1;
						Emypos[EmyposSize - 1].y = posVec.y + 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					}
				}
				else {
					if (posVec.x + 2 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].x = posVec.x + 2;
						Emypos[EmyposSize - 1].y = posVec.y - 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					}
					if (posVec.x + 2 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].x = posVec.x + 2;
						Emypos[EmyposSize - 1].y = posVec.y + 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					}
					if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].x = posVec.x - 1;
						Emypos[EmyposSize - 1].y = posVec.y - 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					}
					if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].x = posVec.x - 1;
						Emypos[EmyposSize - 1].y = posVec.y + 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					}
				}
			}
		}
	}
	
	//적 표시
	for (int i = 0; i < EmyMovePosition.size(); i++) {
		this->removeChild(EmyMovePosition.at(i));
	}
	if (EmyMovePosition.size()) {
		EmyMovePosition.clear();
	}
	for (int m = 0; m < EmyposSize; m++) {
		
		if (Emypos[m].PositionView) {
			int type = Emypos[m].type;
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

	}
	//적 몬스터 타일 표시
	for (int i = 0; i < EmyMovePosition.size(); i++) {
		this->addChild(EmyMovePosition.at(i), 2);
	}

	//자기자신 타일 표시
	if (posSize) {
		free(pos);
		posSize = 0;
	}
	pos = (Position*)malloc(sizeof(Position) * (posSize + 1));
	//pos[posSize].num = 0;
	pos[posSize].x = monster_char[mons].tx;
	pos[posSize].y = monster_char[mons].ty;
	//pos[posSize].pos2Size = 0;
	posSize++;
	Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
	Vec2 posit = FindCoordPosition(Vec2(pos[posSize-1].x, pos[posSize-1].y));
	sp->setPosition(posit.x - 2, posit.y + 17);
	for (int i = 0; i < MovePosition.size(); i++) {
		this->removeChild(MovePosition.at(i));
	}
	if (MovePosition.size()) {
		MovePosition.clear();
	}
	MovePosition.pushBack(sp);
	for (int i = 0; i < MovePosition.size(); i++) {
		addChild(MovePosition.at(i), 2);
	}
}

void EarthMap::SpriteCoordinateChange(Vec2 m_pos) {
	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;
	Vec2 mon_pos = tileCoordForPosition(Vec2(monster_char[mons].xMovePosition, monster_char[mons].yMovePosition));
	//오른쪽 스프라이트
	if (fmodf(mon_pos.y, 2) == 0 && mon_pos.x == m_pos.x || mon_pos.x < m_pos.x) {
		if (monster_char[mons].Type == 0) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Person1-5.png"));
			sprintf(str1, "Person1-");
		}
		//땅질퍽이
		else if (monster_char[mons].Type == 1) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth1-5.png"));
			sprintf(str1, "Earth1-");
		}
		else if (monster_char[mons].Type == 2) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth2-5.png"));
			sprintf(str1, "Earth2-");
		}
		else if (monster_char[mons].Type == 3) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth3-5.png"));
			sprintf(str1, "Earth3-");
		}
		//모닥픽
		else if (monster_char[mons].Type == 4) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth4-5.png"));
			sprintf(str1, "Earth4-");
		}
		else if (monster_char[mons].Type == 5) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth5-5.png"));
			sprintf(str1, "Earth5-");
		}
		else if (monster_char[mons].Type == 6) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth6-5.png"));
			sprintf(str1, "Earth6-");
		}
		//모래두지
		else if (monster_char[mons].Type == 7) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth7-5.png"));
			sprintf(str1, "Earth7-");
		}
		else if (monster_char[mons].Type == 8) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth8-5.png"));
			sprintf(str1, "Earth8-");
		}
		else if (monster_char[mons].Type == 9) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth9-5.png"));
			sprintf(str1, "Earth9-");
		}
		//파이뤼
		else if (monster_char[mons].Type == 11) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire1-5.png"));
			sprintf(str1, "Fire1-");
		}
		else if (monster_char[mons].Type == 12) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire2-5.png"));
			sprintf(str1, "Fire2-");
		}
		else if (monster_char[mons].Type == 13) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire3-5.png"));
			sprintf(str1, "Fire3-");
		}
		//팬템
		else if (monster_char[mons].Type == 14) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire4-5.png"));
			sprintf(str1, "Fire4-");
		}
		else if (monster_char[mons].Type == 15) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire5-5.png"));
			sprintf(str1, "Fire5-");
		}
		else if (monster_char[mons].Type == 16) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire6-5.png"));
			sprintf(str1, "Fire6-");
		}
		//블랙매직숀
		else if (monster_char[mons].Type == 17) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire7-5.png"));
			sprintf(str1, "Fire7-");
		}
		else if (monster_char[mons].Type == 18) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire8-5.png"));
			sprintf(str1, "Fire8-");
		}
		else if (monster_char[mons].Type == 19) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire9-5.png"));
			sprintf(str1, "Fire9-");
		}
		//물질퍽이
		else if (monster_char[mons].Type == 21) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water1-5.png"));
			sprintf(str1, "Water1-");
		}
		else if (monster_char[mons].Type == 22) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water2-5.png"));
			sprintf(str1, "Water2-");
		}
		else if (monster_char[mons].Type == 23) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water3-5.png"));
			sprintf(str1, "Water3-");
		}
		//꼬북이
		else if (monster_char[mons].Type == 24) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water4-5.png"));
			sprintf(str1, "Water4-");
		}
		else if (monster_char[mons].Type == 25) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water5-5.png"));
			sprintf(str1, "Water5-");
		}
		else if (monster_char[mons].Type == 26) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water6-5.png"));
			sprintf(str1, "Water6-");
		}
		//리아커
		else if (monster_char[mons].Type == 27) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water7-5.png"));
			sprintf(str1, "Water7-");
		}
		else if (monster_char[mons].Type == 28) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water8-5.png"));
			sprintf(str1, "Water8-");
		}
		else if (monster_char[mons].Type == 29) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water9-5.png"));
			sprintf(str1, "Water9-");
		}
		//코이
		else if (monster_char[mons].Type == 31) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind1-5.png"));
			sprintf(str1, "Wind1-");
		}
		else if (monster_char[mons].Type == 32) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind2-5.png"));
			sprintf(str1, "Wind2-");
		}
		else if (monster_char[mons].Type == 33) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind3-5.png"));
			sprintf(str1, "Wind3-");
		}
		//피젼
		else if (monster_char[mons].Type == 34) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind4-5.png"));
			sprintf(str1, "Wind4-");
		}
		else if (monster_char[mons].Type == 35) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind5-5.png"));
			sprintf(str1, "Wind5-");
		}
		else if (monster_char[mons].Type == 36) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind6-5.png"));
			sprintf(str1, "Wind6-");
		}
		//코이
		else if (monster_char[mons].Type == 37) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind7-5.png"));
			sprintf(str1, "Wind7-");
		}
		else if (monster_char[mons].Type == 38) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind8-5.png"));
			sprintf(str1, "Wind8-");
		}
		else if (monster_char[mons].Type == 39) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind9-5.png"));
			sprintf(str1, "Wind9-");
		}

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
		if (monster_char[mons].Type == 0) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Person1-1.png"));
			sprintf(str1, "Person1-");
		}
		//땅질퍽이
		else if (monster_char[mons].Type == 1) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth1-1.png"));
			sprintf(str1, "Earth1-");
		}
		else if (monster_char[mons].Type == 2) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth2-1.png"));
			sprintf(str1, "Earth2-");
		}
		else if (monster_char[mons].Type == 3) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth3-1.png"));
			sprintf(str1, "Earth3-");
		}
		//모닥픽
		else if (monster_char[mons].Type == 4) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth4-1.png"));
			sprintf(str1, "Earth4-");
		}
		else if (monster_char[mons].Type == 5) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth5-1.png"));
			sprintf(str1, "Earth5-");
		}
		else if (monster_char[mons].Type == 6) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth6-1.png"));
			sprintf(str1, "Earth6-");
		}
		//모래두지
		else if (monster_char[mons].Type == 7) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth7-1.png"));
			sprintf(str1, "Earth7-");
		}
		else if (monster_char[mons].Type == 8) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth8-1.png"));
			sprintf(str1, "Earth8-");
		}
		else if (monster_char[mons].Type == 9) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth9-1.png"));
			sprintf(str1, "Earth9-");
		}
		//파이뤼
		else if (monster_char[mons].Type == 11) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire1-1.png"));
			sprintf(str1, "Fire1-");
		}
		else if (monster_char[mons].Type == 12) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire2-1.png"));
			sprintf(str1, "Fire2-");
		}
		else if (monster_char[mons].Type == 13) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire3-1.png"));
			sprintf(str1, "Fire3-");
		}
		//팬템
		else if (monster_char[mons].Type == 14) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire4-1.png"));
			sprintf(str1, "Fire4-");
		}
		else if (monster_char[mons].Type == 15) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire5-1.png"));
			sprintf(str1, "Fire5-");
		}
		else if (monster_char[mons].Type == 16) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire6-1.png"));
			sprintf(str1, "Fire6-");
		}
		//블랙매직숀
		else if (monster_char[mons].Type == 17) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire7-1.png"));
			sprintf(str1, "Fire7-");
		}
		else if (monster_char[mons].Type == 18) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire8-1.png"));
			sprintf(str1, "Fire8-");
		}
		else if (monster_char[mons].Type == 19) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire9-1.png"));
			sprintf(str1, "Fire9-");
		}
		//물질퍽이
		else if (monster_char[mons].Type == 21) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water1-1.png"));
			sprintf(str1, "Water1-");
		}
		else if (monster_char[mons].Type == 22) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water2-1.png"));
			sprintf(str1, "Water2-");
		}
		else if (monster_char[mons].Type == 23) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water3-1.png"));
			sprintf(str1, "Water3-");
		}
		//꼬북이
		else if (monster_char[mons].Type == 24) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water4-1.png"));
			sprintf(str1, "Water4-");
		}
		else if (monster_char[mons].Type == 25) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water5-1.png"));
			sprintf(str1, "Water5-");
		}
		else if (monster_char[mons].Type == 26) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water6-1.png"));
			sprintf(str1, "Water6-");
		}
		//리아커
		else if (monster_char[mons].Type == 27) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water7-1.png"));
			sprintf(str1, "Water7-");
		}
		else if (monster_char[mons].Type == 28) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water8-1.png"));
			sprintf(str1, "Water8-");
		}
		else if (monster_char[mons].Type == 29) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water9-1.png"));
			sprintf(str1, "Water9-");
		}
		//코이
		else if (monster_char[mons].Type == 31) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind1-1.png"));
			sprintf(str1, "Wind1-");
		}
		else if (monster_char[mons].Type == 32) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind2-1.png"));
			sprintf(str1, "Wind2-");
		}
		else if (monster_char[mons].Type == 33) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind3-1.png"));
			sprintf(str1, "Wind3-");
		}
		//피젼
		else if (monster_char[mons].Type == 34) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind4-1.png"));
			sprintf(str1, "Wind4-");
		}
		else if (monster_char[mons].Type == 35) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind5-1.png"));
			sprintf(str1, "Wind5-");
		}
		else if (monster_char[mons].Type == 36) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind6-1.png"));
			sprintf(str1, "Wind6-");
		}
		//코이
		else if (monster_char[mons].Type == 37) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind7-1.png"));
			sprintf(str1, "Wind7-");
		}
		else if (monster_char[mons].Type == 38) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind8-1.png"));
			sprintf(str1, "Wind8-");
		}
		else if (monster_char[mons].Type == 39) {
			monster_char[mons].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind9-1.png"));
			sprintf(str1, "Wind9-");
		}
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
}

void EarthMap::ExpCheck() {
	//레벨업 체크
	if (monster_char[mons].exp < MaxExp(monster_char[mons].Type, monster_char[mons].level)) {
		monster_char[mons].exp++;
		if (monster_char[mons].exp == MaxExp(monster_char[mons].Type, monster_char[mons].level)) {

			if (monster_char[mons].level < 10) {
				monster_char[mons].exp = 0;
				//log("monster_char[mons].level = %d, monster_char[mons].atk = %d", monster_char[mons].level, monster_char[mons].atk);
				monster_char[mons].level++;
				LevelUpCheck(&monster_char[mons]);
				//log("monster_char[mons].level = %d, monster_char[mons].atk = %d", monster_char[mons].level, monster_char[mons].atk);
			}
		}
	}
}

int EarthMap::MaxExp(int type, int level) {
	if (type == 0) {
		return level * 2;
	}
	else if (type == 1 || type == 4 || type == 7 || type == 11 || type == 14 || type == 17 || type == 21 || type == 24 || type == 27 || type == 31 || type == 34 || type == 37) {
		return level * 5;
	}
	else if (type == 2 || type == 5 || type == 8 || type == 12 || type == 15 || type == 18 || type == 22 || type == 25 || type == 28 || type == 32 || type == 35 || type == 38) {
		return level * 5;
	}
	else if (type == 3 || type == 6 || type == 9 || type == 13 || type == 16 || type == 19 || type == 23 || type == 26 || type == 29 || type == 33 || type == 36 || type == 39) {
		return level * 5;
	}
}

void EarthMap::LevelUpCheck(Monster_num *monster) {
	//주인공
	if (monster->Type == 0) {
		monster_char[0].atk = 200 + ((monster_char[0].level - 1) * 20);
		monster_char[0].def = 100 + ((monster_char[0].level - 1) * 10);
		monster_char[0].hp = 400 + ((monster_char[0].level - 1) * 40);
		monster_char[0].Fullhp = 400 + ((monster_char[0].level - 1) * 40);
		monster_char[0].move = 3;
		monster_char[0].range = 1;
		monster_char[0].HPbarPosition = 21.5;
	}
	//땅질퍽이
	else if (monster->Type == 1) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 14.5;
	}
	else if (monster->Type == 2) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 17;
	}
	else if (monster->Type == 3) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 25;
	}
	//모닥픽
	else if (monster->Type == 4) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 9;
	}
	else if (monster->Type == 5) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 12.5;
	}
	else if (monster->Type == 6) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 60 + ((monster->level - 1) * 6);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 20;
	}
	//모래두지
	else if (monster->Type == 7) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 20 + ((monster->level - 1) * 2);
		monster->hp = 200 + ((monster->level - 1) * 20);
		monster->Fullhp = 200 + ((monster->level - 1) * 20);
		monster->move = 3;
		monster->range = 2;
		monster->HPbarPosition = 19;
	}
	else if (monster->Type == 8) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 350 + ((monster->level - 1) * 35);
		monster->Fullhp = 350 + ((monster->level - 1) * 35);
		monster->move = 3;
		monster->range = 2;
		monster->HPbarPosition = 20;
	}
	else if (monster->Type == 9) {
		monster->atk = 250 + ((monster->level - 1) * 25);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 500 + ((monster->level - 1) * 50);
		monster->Fullhp = 500 + ((monster->level - 1) * 50);
		monster->move = 3;
		monster->range = 2;
		monster->HPbarPosition = 17;
	}
	//파이뤼
	else if (monster->Type == 11) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 13.5;
	}
	else if (monster->Type == 12) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 21;
	}
	else if (monster->Type == 13) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 23.5;
	}
	//팬템
	else if (monster->Type == 14) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 19;
	}
	else if (monster->Type == 15) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 23.5;
	}
	else if (monster->Type == 16) {
		monster->atk = 350 + ((monster->level - 1) * 35);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 23.5;
	}
	//블랙매직숀
	else if (monster->Type == 17) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 2;
		monster->HPbarPosition = 22;
	}
	else if (monster->Type == 18) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 2;
		monster->HPbarPosition = 25.5;
	}
	else if (monster->Type == 19) {
		monster->atk = 250 + ((monster->level - 1) * 25);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 2;
		monster->HPbarPosition = 21;
	}
	//물질퍽이
	else if (monster->Type == 21) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 30;
		monster->range = 1;
		monster->HPbarPosition = 14.5;
	}
	else if (monster->Type == 22) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 13.5;
	}
	else if (monster->Type == 23) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 25;
	}
	//꼬북이
	else if (monster->Type == 24) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 350 + ((monster->level - 1) * 35);
		monster->Fullhp = 350 + ((monster->level - 1) * 35);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 20;
	}
	else if (monster->Type == 25) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 500 + ((monster->level - 1) * 50);
		monster->Fullhp = 500 + ((monster->level - 1) * 50);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 22.5;
	}
	else if (monster->Type == 26) {
		monster->atk = 350 + ((monster->level - 1) * 35);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 650 + ((monster->level - 1) * 65);
		monster->Fullhp = 650 + ((monster->level - 1) * 65);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 25;
	}
	//리아커
	else if (monster->Type == 27) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 20;
	}
	else if (monster->Type == 28) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 22.5;
	}
	else if (monster->Type == 29) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 60 + ((monster->level - 1) * 6);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 28;
	}
	//코이
	else if (monster->Type == 31) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 19;
	}
	else if (monster->Type == 32) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 18.5;
	}
	else if (monster->Type == 33) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 19.5;
	}
	//피젼
	else if (monster->Type == 34) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 11.5;
	}
	else if (monster->Type == 35) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 17.5;
	}
	else if (monster->Type == 36) {
		monster->atk = 350 + ((monster->level - 1) * 35);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
		monster->HPbarPosition = 20;
	}
	//코이
	else if (monster->Type == 37) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 2;
		monster->HPbarPosition = 20;
	}
	else if (monster->Type == 38) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 40 + ((monster->level - 1) * 04);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 2;
		monster->HPbarPosition = 17;
	}
	else if (monster->Type == 39) {
		monster->atk = 250 + ((monster->level - 1) * 25);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 2;
		monster->HPbarPosition = 23.5;
	}
}

bool EarthMap::BufTileCheck(Vec2 vec) {
	Vec2 tileCoord = Vec2(vec.x, vec.y);
	int tileGid = metainfo->getTileGIDAt(tileCoord);
	if (tileGid) {
		Value properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull()) {
			std::string item1 = properties.asValueMap()["Items"].asString();
			if (item1 == "buf") {
				//log("buf");
				return true;
			}
		}
	}
	return false;
}

int EarthMap::SynastryCheck(int s1, int s2) {
	//대지
	if (s1 > 0 && s1 < 10) {
		//불
		if ((s2 > 10 && s2 < 20) || s2 == 0) {
			return 2;
		}
		//물
		else if (s2 > 20 && s2 < 30) {
			return 1;
		}
	}
	//불
	else if ((s1 > 10 && s1 < 20) || s1 == 0) {
		//대지
		if (s2 > 0 && s2 < 10) {
			return 1;
		}
		//바람
		else if (s2 > 30 && s2 < 40) {
			return 2;
		}
	}
	//물
	else if (s1 > 20 && s1 < 30) {
		//대지
		if (s2 > 0 && s2 < 10) {
			return 2;
		}
		//바람
		else if (s2 > 30 && s2 < 40) {
			return 1;
		}
	}
	//바람
	else if (s1 > 30 && s1 < 40) {
		//불
		if ((s2 > 10 && s2 < 20) || s2 == 0) {
			return 1;
		}
		//물
		else if (s2 > 20 && s2 < 30) {
			return 2;
		}
	}
	return 0;
}

void EarthMap::RemoveSprite() {
	this->removeChild(st);
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

bool EarthMap::checkEmyMonsterCoordinate(Vec2 click) {
	log("EmyposSize = %d", EmyposSize);
	for (int m = 0; m < EmyposSize; m++) {
		if(Emypos[m].PositionView){
			for (int i = 0; i < EmyMonsterSize; i++) {
				if (Emypos[m].x == EmyMonster_char[i].tx && Emypos[m].y == EmyMonster_char[i].ty) {
					if (EmyMonster_char[i].tx == click.x && EmyMonster_char[i].ty == click.y) {
						//log("emymonster click");
						ClickEmyMonster = i;
						return true;
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
	//tmap = TMXTiledMap::create("Images/Scene/EarthMapTest.tmx");
	//metainfo = tmap->getLayer("MetaInfo");
	int tileGid = metainfo->getTileGIDAt(tileCoord);
	if (tileGid) {
		Value properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull()) {
			std::string item1 = properties.asValueMap()["Items"].asString();
			if (item1 == "wall") {
				//log("wall....");
				return false;
			}
		}
	}
	return true;
}

EarthMap::Position* EarthMap::ChecksPosition(Vec2 charactor, Position *pos_temp, int tempSize, int Count, int move) {
	if (Count > 0) {
		//Vec2(charactor.x, charactor.y);
		if (move == 1) {
			if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
			else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
			pos_temp[tempSize].num = Count;
			pos_temp[tempSize].x = charactor.x;
			pos_temp[tempSize].y = charactor.y;
			pos_temp[tempSize].pos2Size = 0;
			tempSize++;
		}
		
		//Vec2(charactor.x, charactor.y - 1);
		if (ChecksPosition(charactor.x, charactor.y - 1)) {
			if (tempSize)	pos_temp = (Position*)realloc(pos_temp,	sizeof(Position) * (tempSize + 1));
			else			pos_temp = (Position*)malloc(			sizeof(Position) * (tempSize + 1));
			pos_temp[tempSize].num = Count;
			pos_temp[tempSize].x = charactor.x;
			pos_temp[tempSize].y = charactor.y - 1;
			pos_temp[tempSize].pos2Size = 0;
			pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count-1, 1);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = GrobalTempsize;
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
			pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = GrobalTempsize;
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
			pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = GrobalTempsize;
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
			pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = GrobalTempsize;
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
				pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1);
				if (Count != 1) {
					pos_temp[tempSize].pos2Size = GrobalTempsize;
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
				pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1);
				if (Count != 1) {
					pos_temp[tempSize].pos2Size = GrobalTempsize;
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
				pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1);
				if (Count != 1) {
					pos_temp[tempSize].pos2Size = GrobalTempsize;
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
				pos_temp[tempSize].pos2 = ChecksPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1);
				if (Count != 1) {
					pos_temp[tempSize].pos2Size = GrobalTempsize;
				}
				tempSize++;
			}
		}
	}
	GrobalTempsize = tempSize;
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

