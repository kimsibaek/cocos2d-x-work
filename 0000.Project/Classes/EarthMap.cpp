#include "EarthMap.h"
#include "pauseScene.h"
#include "TurnEndScene.h"
#include "CreateMonster.h"
#include "MainScene.h"
#include "sqlite3.h"
#include "stdafx.h"
#include <time.h>
#include "Toolbag.h"
#include "EndGame.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

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
	
	winSize = Director::getInstance()->getWinSize();

	cache = SpriteFrameCache::getInstance();

	SimpleAudioEngine::getInstance()->preloadEffect("snd/etc/click.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/etc/GameEnd2.wav");
	//대지공격 액션
	cache->addSpriteFramesWithFile("Plist/EarthAttackPlist/fx_f5_earthsphere.plist");
	cache->addSpriteFramesWithFile("Plist/EarthAttackPlist/fx_impactgreen.plist");
	cache->addSpriteFramesWithFile("Plist/EarthAttackPlist/fx_smoke.plist");
	cache->addSpriteFramesWithFile("Plist/EarthAttackPlist/fx_smoke2.plist");

	SimpleAudioEngine::getInstance()->preloadEffect("snd/Earth/fx_impactgreen.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Earth/fx_smoke.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Earth/fx_smoke2.wav");
	
	
	//불공격 액션
	cache->addSpriteFramesWithFile("Plist/FireAttackPlist/fx_blood_explosion.plist");
	cache->addSpriteFramesWithFile("Plist/FireAttackPlist/fx_explosionorangesmoke.plist");
	cache->addSpriteFramesWithFile("Plist/FireAttackPlist/fx_f2_eightgates_purpleflame.plist");
	cache->addSpriteFramesWithFile("Plist/FireAttackPlist/fx_f2_teleport.plist");
	cache->addSpriteFramesWithFile("Plist/FireAttackPlist/fx_f2_twinstrike.plist");
	cache->addSpriteFramesWithFile("Plist/FireAttackPlist/fx_f5_earthsphere_orange.plist");
	cache->addSpriteFramesWithFile("Plist/FireAttackPlist/fx_firetornado.plist");
	cache->addSpriteFramesWithFile("Plist/FireAttackPlist/fx_whiteexplosion.plist");

	SimpleAudioEngine::getInstance()->preloadEffect("snd/Fire/fx_blood_explosion.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Fire/fx_explosionorangesmoke.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Fire/fx_f2_eightgates_purpleflame.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Fire/fx_f2_teleport.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Fire/fx_f2_twinstrike.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Fire/fx_f5_earthsphere_orange.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Fire/fx_firetornado.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Fire/fx_whiteexplosion.wav");

	//물공격 액션
	cache->addSpriteFramesWithFile("Plist/WaterAttackPlist/fx_cleanse.plist");
	cache->addSpriteFramesWithFile("Plist/WaterAttackPlist/fx_distortion_hex_shield.plist");
	cache->addSpriteFramesWithFile("Plist/WaterAttackPlist/fx_f3_fountainofyouth.plist");
	cache->addSpriteFramesWithFile("Plist/WaterAttackPlist/fx_f6_cryogenesis.plist");
	cache->addSpriteFramesWithFile("Plist/WaterAttackPlist/fx_f6_spiritofthewild.plist");
	cache->addSpriteFramesWithFile("Plist/WaterAttackPlist/fx_frozen.plist");
	cache->addSpriteFramesWithFile("Plist/WaterAttackPlist/fx_teleportblueorb.plist");
	cache->addSpriteFramesWithFile("Plist/WaterAttackPlist/fx_teleportrecall2.plist");

	SimpleAudioEngine::getInstance()->preloadEffect("snd/Water/fx_cleanse.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Water/fx_distortion_hex_shield.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Water/fx_f6_cryogenesis.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Water/fx_f6_spiritofthewild.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Water/fx_teleportblueorb.wav");

	//바람공격 액션
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_bladestorm.plist");
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_blueplasma_vertical.plist");
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_bluewatersplash.plist");
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_clawslash.plist");
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_f1_casterprojectile.plist");
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_f1_circlelife.plist");
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_f1_decimate.plist");
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_f1_inmolation.plist");
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_f1_lasting_judgment.plist");
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_f1_lionheartblessing.plist");
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_f2_spiraltechnique02.plist");
	cache->addSpriteFramesWithFile("Plist/WindAttackPlist/fx_slashfrenzy.plist");

	SimpleAudioEngine::getInstance()->preloadEffect("snd/Wind/fx_bladestorm.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Wind/fx_blueplasma_vertical.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Wind/fx_bluewatersplash.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Wind/fx_clawslash.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Wind/fx_f1_casterprojectile.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Wind/fx_f1_circlelife.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Wind/fx_f1_decimate.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Wind/fx_f1_inmolation.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Wind/fx_f1_lionheartblessing.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Wind/fx_f2_spiraltechnique02.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("snd/Wind/fx_slashfrenzy.wav");


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
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Person1-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Earth1-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Earth2-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Earth3-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Earth4-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Earth5-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Earth6-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Earth7-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Earth8-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Earth9-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Fire1-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Fire2-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Fire3-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Fire4-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Fire5-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Fire6-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Fire7-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Fire8-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Fire9-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Water1-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Water2-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Water3-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Water4-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Water5-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Water6-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Water7-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Water8-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Water9-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Wind1-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Wind2-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Wind3-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Wind4-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Wind5-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Wind6-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Wind7-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Wind8-A.plist");
	cache->addSpriteFramesWithFile("Plist/ActionPlist/Wind9-A.plist");

	//this->setPosition(Vec2(0, 0));
	if (Mapdata == 1) {
		//earth map
		tmap = TMXTiledMap::create("Images/Scene/EarthMap.tmx");
		BG = Sprite::create("Images/Scene/EarthMap.png");
	}
	else if (Mapdata == 2) {
		//fire map
		tmap = TMXTiledMap::create("Images/Scene/FireMap.tmx");
		BG = Sprite::create("Images/Scene/FireMap.png");
	}
	else if (Mapdata == 3) {
		//water map
		tmap = TMXTiledMap::create("Images/Scene/WaterMap.tmx");
		BG = Sprite::create("Images/Scene/WaterMap.png");
	}
	else if (Mapdata == 4) {
		//wind map
		tmap = TMXTiledMap::create("Images/Scene/WindMap.tmx");
		BG = Sprite::create("Images/Scene/WindMap.png");
	}
	//tmap = TMXTiledMap::create("Images/Scene/EarthMap.tmx");
	tmap->setPosition(Vec2(-66, -32));
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap, 2, 11);

	MovePositionX = tmap->getPosition().x;
	MovePositionY = tmap->getPosition().y;
	//log("MovePositionX = %f, MovePositionY = %f", MovePositionX, MovePositionY);
	//BG = Sprite::create("Images/Scene/Earthmap.png");
	BG->setPosition(Vec2(1072, 795));
	tmap->addChild(BG, -1);
	

	auto pMenuItem1 = MenuItemImage::create("Images/Scene/TurnEnd.png", "Images/Scene/TurnEnd_click.png", CC_CALLBACK_1(EarthMap::doClick1, this));
	pMenuItem1->setPosition(Vec2(160, 650));
	pMenuItem1->setScale(1);
	pMenuItem1->setTag(1);
	auto pMenuItem2 = MenuItemImage::create("Images/Scene/pause2.png", "Images/Scene/pause2_click2.png", CC_CALLBACK_1(EarthMap::doClick1, this));
	pMenuItem2->setPosition(Vec2(1200, 660));
	pMenuItem2->setScale(1);
	pMenuItem2->setTag(2);
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	pMenu->setPosition(Vec2(0, 0));
	this->addChild(pMenu, 4);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(EarthMap::doMsgReceived), "TouchStatus", nullptr);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(EarthMap::doMsgReceivedTurnEnd), "TouchTurnEnd", nullptr);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(EarthMap::doMsgReceivedMonster), "TouchMonster", nullptr);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(EarthMap::doMsgReceivedTool), "TouchTool", nullptr);

	//DB불러오기
	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";
	//log("%s", dbfileName.c_str());
	
	

	//변수 초기화
	if (monsterSize) {
		free(monster_char);
		monsterSize = 0;
	}
	if (EmyMonsterSize) {
		free(EmyMonster_char);
		EmyMonsterSize = 0;
	}
	if (DeathMonsterListSize) {
		free(Death_Monster_List);
		DeathMonsterListSize = 0;
	}

	if (posSize) {
		free(pos);
	}
	
	if (EmyposSize) {
		free(Emypos);
	}

	if (EmyposAttackSize) {
		free(EmyposAttack);
	}
	if (shortpassSize) {
		free(shortpass);
	}
	if (createPosSize) {
		free(createMonsterPos);
	}
	if (VecPositionSize) {
		free(VecPosition);
	}

	posSize = 0;
	EmyposSize = 0;
	EmyposAttackSize = 0;
	shortpassSize = 0;
	createPosSize = 0;
	VecPositionSize = 0;

	MovePosition.clear();
	EmyMovePosition.clear();
	
	mons = 0;

	ReturnMove_tx = 0;
	ReturnMove_ty = 0;

	Moving_tx = 0;
	Moving_ty = 0;

	statuschar = true;

	createMonsterNum = 0;
	ToolNum = 0;
	movement = 0;

	ClickEmyMonster = 0;

	TouchTurnEnd = true;

	emynum = 0;
	monsterNum = 0;

	VPosX = 0;
	VPosY = 0;

	EndGame_Num = 0;

	GrobalTempsize = 0;

	MovePositionDX = 0;
	MovePositionDY = 0;
	createDatabase();
	onCreateCharacter();
	onCreateEmyCharacter();
	//주인공이 화면의 센터로
	FocusMonster(&monster_char[0]);

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
	ChageSchedule = false;
	ReturnState = false;
	Msgerror = true;
	Coin = 0;
	this->schedule(schedule_selector(EarthMap::doChange), 1.0f);
	return true;
}

void EarthMap::doClick1(Ref *pSender) {
	auto tItem = (MenuItem *)pSender;
	
	int i = tItem->getTag();
	if (i == 1) {
		//턴종료
		if (TouchTurnEnd) {
			m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/click.wav");
			Scene* popWin;
			popWin = TurnEndScene::createScene();
			this->addChild(popWin, 1000, 1000);
		}
	}
	else if (i == 2) {
		//일시정지
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/click.wav");
		Scene* popWin;
		popWin = pauseScene::createScene();
		this->addChild(popWin, 2000, 2000);
	}
}

void EarthMap::createDatabase()
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
		monster_char[0].hp = 1000 + ((monster_char[0].level - 1) * 100);
		monster_char[0].Fullhp = 1000 + ((monster_char[0].level - 1) * 100);
		monster_char[0].move = 3;
		monster_char[0].range = 1;
		monster_char[0].HPbarPosition = 43;
		monster_char[0]._turn = true;
	}

	int num1 = rand() % 14 + 1;
	int num2 = rand() % 14 + 1;

	while (!CheckPosition(num1, num2, monsterSize, monster_char, EmyMonsterSize, EmyMonster_char)) {
		num1 = rand() % 14 + 1;
		num2 = rand() % 14 + 1;
	}

	monster_char[0].tx = num1;
	monster_char[0].ty = num2;
	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;
	if (monster_char[0].Type == 0) {
			
		monster_char[0].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
	}

	monster_char[0].sprite->setScale(1);
	if (num2 % 2 == 0) {
		monster_char[0].sprite->setPosition(128 * num1 + 66, 1632 - (160 + 96 * num2) + 32);
	}
	else {
		monster_char[0].sprite->setPosition(62 + 128 * num1 + 66, 1632 - (160 + 96 * num2) + 32);
	}
	tmap->addChild(monster_char[0].sprite, 5, 0);

	Sprite* st = Sprite::createWithSpriteFrameName("HP_bar.png");
	st->setPosition(0, -5);
	st->setScaleX(monster_char[0].HPbarPosition / 25 * 2);
	st->setScaleY(2.0f);
	st->setAnchorPoint(Vec2(0, 0.5));
	monster_char[0].sprite->addChild(st, 4, 1);

	Sprite* hp = Sprite::createWithSpriteFrameName("Monster_HP.png");
	hp->setPosition(0, -5);
	hp->setScaleX(monster_char[0].HPbarPosition / 25 * 2);
	hp->setScaleY(2.0f);
	hp->setAnchorPoint(Vec2(0, 0.5));
	monster_char[0].sprite->addChild(hp, 4, 2);
	
	char level[3];
	sprintf(level, "%d", monster_char[0].level);
	auto pLabel3 = LabelAtlas::create(level, "Images/Scene/ML.png", 7, 9, '0');
	pLabel3->setAnchorPoint(Vec2(0, 0));
	pLabel3->setPosition(Vec2(hp->getContentSize().width*(monster_char[0].HPbarPosition / 25 * 2) + 5, -10));
	pLabel3->setScale(2.0f);
	monster_char[0].sprite->addChild(pLabel3, 4, 3);

	Sprite* End = Sprite::createWithSpriteFrameName("End.png");
	End->setAnchorPoint(Vec2(0, 0));
	End->setPosition(Vec2(0, 0));
	End->setScale(2.0f);

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
		int	Item1 = -1;
		int	Item2 = -1;
		int	Item3 = -1;

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

		while (!CheckPosition(num1, num2, monsterSize, monster_char, EmyMonsterSize, EmyMonster_char)) {
			num1 = rand() % 14 + 1;
			num2 = rand() % 14 + 1;
		}
		EmyMonster_char[i].tx = num1;
		EmyMonster_char[i].ty = num2;
		char str1[100];
		char str2[100];
		Vector<SpriteFrame*> animFrames;
		if (true) {
			//땅질퍽이
			if (EmyMonster_char[i].Type == 1) {
				EmyMonster_char[i].atk = 150 + ((EmyMonster_char[i].level - 1) * 15);
				EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
				EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
				EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
				EmyMonster_char[i].move = 3;
				EmyMonster_char[i].range = 1;
				EmyMonster_char[i].HPbarPosition = 30;
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
				EmyMonster_char[i].HPbarPosition = 34;
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
				EmyMonster_char[i].HPbarPosition = 57;
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
				EmyMonster_char[i].HPbarPosition = 23;
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
				EmyMonster_char[i].HPbarPosition = 27;
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
				EmyMonster_char[i].HPbarPosition = 40;
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
				EmyMonster_char[i].HPbarPosition = 38;
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
				EmyMonster_char[i].HPbarPosition = 56;
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
				EmyMonster_char[i].HPbarPosition = 42;
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
				EmyMonster_char[i].HPbarPosition = 29;
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
				EmyMonster_char[i].HPbarPosition = 50;
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
				EmyMonster_char[i].HPbarPosition = 56;
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
				EmyMonster_char[i].HPbarPosition = 39;
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
				EmyMonster_char[i].HPbarPosition = 52;
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
				EmyMonster_char[i].HPbarPosition = 49;
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
				EmyMonster_char[i].HPbarPosition = 48;
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
				EmyMonster_char[i].HPbarPosition = 54;
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
				EmyMonster_char[i].HPbarPosition = 42;
				EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire9-1.png");
				sprintf(str1, "Fire9-");
			}
			//물질퍽이
			else if (EmyMonster_char[i].Type == 21) {
				EmyMonster_char[i].atk = 150 + ((EmyMonster_char[i].level - 1) * 15);
				EmyMonster_char[i].def = 30 + ((EmyMonster_char[i].level - 1) * 3);
				EmyMonster_char[i].hp = 300 + ((EmyMonster_char[i].level - 1) * 30);
				EmyMonster_char[i].Fullhp = 300 + ((EmyMonster_char[i].level - 1) * 30);
				EmyMonster_char[i].move = 3;
				EmyMonster_char[i].range = 1;
				EmyMonster_char[i].HPbarPosition = 29;
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
				EmyMonster_char[i].HPbarPosition = 33;
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
				EmyMonster_char[i].HPbarPosition = 58;
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
				EmyMonster_char[i].HPbarPosition = 41;
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
				EmyMonster_char[i].HPbarPosition = 46;
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
				EmyMonster_char[i].HPbarPosition = 50;
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
				EmyMonster_char[i].HPbarPosition = 42;
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
				EmyMonster_char[i].HPbarPosition = 50;
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
				EmyMonster_char[i].HPbarPosition = 61;
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
				EmyMonster_char[i].HPbarPosition = 38;
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
				EmyMonster_char[i].HPbarPosition = 39;
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
				EmyMonster_char[i].HPbarPosition = 59;
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
				EmyMonster_char[i].HPbarPosition = 23;
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
				EmyMonster_char[i].HPbarPosition = 35;
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
				EmyMonster_char[i].HPbarPosition = 46;
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
				EmyMonster_char[i].HPbarPosition = 42;
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
				EmyMonster_char[i].HPbarPosition = 34;
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
				EmyMonster_char[i].HPbarPosition = 49;
				EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
				sprintf(str1, "Wind9-");
			}
		}
		
		EmyMonster_char[i]._turn = false;
		EmyMonster_char[i].sprite->setScale(1);
		if (num2 % 2 == 0) {
			EmyMonster_char[i].sprite->setPosition(128 * num1 + 66, 1632 - (160 + 96 * num2) + 32);
		}
		else {
			EmyMonster_char[i].sprite->setPosition(62 + 128 * num1 + 66, 1632 - (160 + 96 * num2) + 32);
		}
		int tag = i;
		tag += 100;
		tmap->addChild(EmyMonster_char[i].sprite, 3, tag);
		Sprite* st = Sprite::createWithSpriteFrameName("HP_bar.png");
		st->setPosition(0, -5);
		st->setScaleX(EmyMonster_char[i].HPbarPosition / 25 * 2);
		st->setScaleY(2.0f);
		st->setAnchorPoint(Vec2(0, 0.5));
		EmyMonster_char[i].sprite->addChild(st, 4, 1);

		Sprite* hp = Sprite::createWithSpriteFrameName("EmyMonseter_HP.png");
		hp->setPosition(0, -5);
		hp->setScaleX(EmyMonster_char[i].HPbarPosition / 25 * 2);
		hp->setScaleY(2.0f);
		hp->setAnchorPoint(Vec2(0, 0.5));
		EmyMonster_char[i].sprite->addChild(hp, 4, 2);

		char level[3];
		sprintf(level, "%d", EmyMonster_char[i].level);
		auto pLabel3 = LabelAtlas::create(level, "Images/Scene/EmyML.png", 7, 9, '0');
		pLabel3->setAnchorPoint(Vec2(0, 0));
		pLabel3->setScale(2.0f);
		pLabel3->setPosition(Vec2(st->getContentSize().width*(EmyMonster_char[i].HPbarPosition / 25 * 2) + 5, -10));
		EmyMonster_char[i].sprite->addChild(pLabel3, 4, 3);
		
		Sprite* End = Sprite::createWithSpriteFrameName("End.png");
		End->setAnchorPoint(Vec2(0, 0));
		End->setScale(2.0f);
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

void EarthMap::FocusMonster(Monster_num *monster) {
	winSize = Director::getInstance()->getWinSize();

	float dx = 0;
	float dy = 0;
	
	Vec2 posit = FindCoordPosition(Vec2(monster->tx, monster->ty));
	//attack->setPosition(Vec2(, ));
	log("MovePositionX = %f, MovePositionY = %f", MovePositionX, MovePositionY);
	dx = posit.x - tmap->getPosition().x  - (winSize.width / 2);
	dy = posit.y - tmap->getPosition().y  - 60 - (winSize.height / 2);

	log("dx %f, dy %f", dx, dy);

	if (dx > 703) {
		dx = 703;
	}
	if (dy > 785) {
		dy = 785;
	}

	MovePositionDX = dx;
	MovePositionDY = dy;
	if (dx < 0) {
		MovePositionDX = 0;
	}
	if (dy < 0) {
		MovePositionDY = 0;
	}

	float tx = tmap->getPosition().x - dx;
	float ty = tmap->getPosition().y - dy;

	if (tx < -1006 - 66 + winSize.width - 976) {
		tx = -1006 - 66 + winSize.width - 976;
	}
	else if (tx > -66) {
		tx = -66;
	}
	if (ty < -767 - 32 + winSize.height - 737) {
		ty = -767 - 32 + winSize.height - 737;
	}
	else if (ty > -32) {
		ty = -32;
	}
	//움직인 타일맵의 위치를 가지고 클릭좌표를 계산
	MovePositionX = tx;
	MovePositionY = ty;
	log("MovePositionX = %f, MovePositionY = %f", MovePositionX, MovePositionY);
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
		
		auto pScene = TransitionFade::create(1.0f, MainScene::createScene());
		Director::getInstance()->replaceScene(pScene);
	}
	
}

void EarthMap::doChange(float f) {
	if (ChageSchedule) {
		ChageSchedule = false;
		this->schedule(schedule_selector(EarthMap::EmyMoveAttack), 2.0f, EmyMonsterSize - 1, 0.1f);
	}
	else {
		//this->unschedule(schedule_selector(EarthMap::EmyMoveAttack));
	}
}

//엔드 버튼 메세지 받기
void EarthMap::doMsgReceivedTurnEnd(Ref* obj) {
	char *inputStr = (char*)obj;
	char testText[20];
	sprintf(testText, "%s", inputStr);
	if (!strcmp(testText, "0")) {
		Director::getInstance()->pause();
	}
	else if (!strcmp(testText, "1")) {
		Director::getInstance()->resume();
		//아군 몬스터 턴 End
		TouchTurnEnd = false;
		for (int i = 0; i < monsterSize; i++) {
			if (monster_char[i]._turn) {
				Sprite* End = Sprite::createWithSpriteFrameName("End.png");
				End->setAnchorPoint(Vec2(0, 0));
				End->setPosition(Vec2(0, 0));
				End->setScale(2.0f);
				monster_char[i]._turn = false;
				monster_char[i].sprite->addChild(End, 4, 4);
			}
		}
		//enemy turn 표시
		Sprite* EnemyTurnLabel = Sprite::create("Images/Scene/EnemyTurnLabel2.png");
		EnemyTurnLabel->setScale(2.0f);
		EnemyTurnLabel->setPosition(Vec2(1000, 50));
		this->addChild(EnemyTurnLabel, 10, 200);
		auto myAction1 = FadeOut::create(0.5f);
		auto myAction2 = FadeIn::create(0.5f);
		auto myAction3 = Sequence::create(myAction1, myAction2, nullptr);
		auto rep1 = RepeatForever::create(myAction3);
		EnemyTurnLabel->runAction(rep1);
		//적군 몬스터 턴
		for (int i = 0; i < EmyMonsterSize; i++) {
			EmyMonster_char[i]._turn = true;
			//log("%d : %d", i, EmyMonster_char[i].Type);
			EmyMonster_char[i].sprite->removeChildByTag(4);
		}
		emynum = 0;
		if (!EmyMonsterSize) {
			log("더이상 없음");
		}
		else {
			if (!ChageSchedule) {
				ChageSchedule = true;
			}
			

		}
	}
	else {
		Director::getInstance()->resume();
		
	}

}

void EarthMap::EmyMoveAttack(float f) {
	Vec2 mon_pos = Vec2(EmyMonster_char[emynum].tx, EmyMonster_char[emynum].ty);
	log("mon_pos[%d] = %f, %f", emynum, mon_pos.x, mon_pos.y);
	if (EmyMonster_char[emynum].move == 4) {
		movement = 0;
	}
	if (EmyMonster_char[emynum].move == 3) {
		movement = 1;
	}
	if (EmyMonster_char[emynum].move == 2) {
		movement = 2;
	}
	if (EmyMonster_char[emynum].move == 1) {
		movement = 0;
	}

	if (posSize) {
		free(pos);
		posSize = 0;
	}
	if (EmyposSize) {
		free(Emypos);
		EmyposSize = 0;
	}

	GrobalTempsize = 0;
	pos = CheckPosition(mon_pos, pos, posSize, EmyMonster_char[emynum].move + 1, 0, EmyMonsterSize, EmyMonster_char, monsterSize, monster_char);
	posSize = GrobalTempsize;
	log("posSize = %d, EmyposSize = %d", posSize, EmyposSize);
	if (EmyposSize) {
		//움직이지 않고 가까운 적 공격
		if (CheckOnePositionMonster(mon_pos)) {
			this->scheduleOnce(schedule_selector(EarthMap::EmyMove), 1.0f);
		}
		else {
			//적에게 다가 가기
			if (createPosSize) {
				free(createMonsterPos);
				createPosSize = 0;
			}
			bool move_t = false;
			for (int j = 0; j < EmyposSize; j++) {
				if (!move_t) {
					GrobalTempsize = 0;
					Vec2 EmyVec = Vec2(Emypos[j].x, Emypos[j].y);
					monsterNum = 0;
					for (int q = 0; q < monsterSize; q++) {
						if (monster_char[q].tx == Emypos[j].x && monster_char[q].ty == Emypos[j].y) {
							monsterNum = q;
							break;
						}
					}


					createMonsterPos = CheckPosition(EmyVec, createMonsterPos, createPosSize, 1, 0, monsterSize, monster_char, EmyMonsterSize, EmyMonster_char);
					createPosSize = GrobalTempsize;
					log("posSize = %d, createPosSize = %d", posSize, createPosSize);

					for (int k = 0; k < createPosSize; k++) {
						for (int m = 0; m < posSize; m++) {
							if (createMonsterPos[k].x == pos[m].x && createMonsterPos[k].y == pos[m].y) {
								//이동(이동할좌표, 이동가능한좌표, 이동가능한좌표개수, 움직일몬스터)
								log("1 createMonsterPos[%d] = %d, %d", k, createMonsterPos[k].x, createMonsterPos[k].y);
								Vec2 v_pos = Vec2(createMonsterPos[k].x, createMonsterPos[k].y);
								ShortistMove(v_pos, pos, posSize, &EmyMonster_char[emynum]);
								this->scheduleOnce(schedule_selector(EarthMap::EmyMove), 1.0f);
								move_t = true;
								break;
							}
							else if (pos[m].pos2Size) {
								for (int i = 0; i < pos[m].pos2Size; i++) {
									if (createMonsterPos[k].x == pos[m].pos2[i].x && createMonsterPos[k].y == pos[m].pos2[i].y) {
										log("2 createMonsterPos[%d] = %d, %d", k, createMonsterPos[k].x, createMonsterPos[k].y);
										Vec2 v_pos = Vec2(createMonsterPos[k].x, createMonsterPos[k].y);
										ShortistMove(v_pos, pos, posSize, &EmyMonster_char[emynum]);
										this->scheduleOnce(schedule_selector(EarthMap::EmyMove), 1.0f);
										move_t = true;
										break;
									}
									else if (pos[m].pos2[i].pos2Size) {
										for (int x = 0; x < pos[m].pos2[i].pos2Size; x++) {
											if (createMonsterPos[k].x == pos[m].pos2[i].pos2[x].x && createMonsterPos[k].y == pos[m].pos2[i].pos2[x].y) {
												log("3 createMonsterPos[%d] = %d, %d", k, createMonsterPos[k].x, createMonsterPos[k].y);
												Vec2 v_pos = Vec2(createMonsterPos[k].x, createMonsterPos[k].y);
												ShortistMove(v_pos, pos, posSize, &EmyMonster_char[emynum]);
												this->scheduleOnce(schedule_selector(EarthMap::EmyMove), 1.0f);
												move_t = true;
												break;
											}
											else if (pos[m].pos2[i].pos2[x].pos2Size) {
												for (int p = 0; p < pos[m].pos2[i].pos2[x].pos2Size; p++) {
													if (createMonsterPos[k].x == pos[m].pos2[i].pos2[x].pos2[p].x && createMonsterPos[k].y == pos[m].pos2[i].pos2[x].pos2[p].y) {
														log("4 createMonsterPos[%d] = %d, %d", k, createMonsterPos[k].x, createMonsterPos[k].y);
														Vec2 v_pos = Vec2(createMonsterPos[k].x, createMonsterPos[k].y);
														ShortistMove(v_pos, pos, posSize, &EmyMonster_char[emynum]);
														this->scheduleOnce(schedule_selector(EarthMap::EmyMove), 1.0f);
														move_t = true;
														break;
													}
												}
											}
											if (move_t) {
												break;
											}
										}
									}
									if (move_t) {
										break;
									}
								}
							}
							if (move_t) {
								break;
							}
						}
						if (move_t) {
							break;
						}
					}
					if (move_t) {
						break;
					}
				}
			}
		}
	}
	if (EmyposSize) {
		free(Emypos);
		EmyposSize = 0;
	}
	this->scheduleOnce(schedule_selector(EarthMap::deleytime), 1.5f);
	
	//FocusMonster(&EmyMonster_char[emynum]);
	
}

bool EarthMap::CheckOnePositionMonster(Vec2 mon_pos) {
	bool Check = false;
	int num = -1;
	for (int j = 0; j < EmyposSize; j++) {
		Vec2 EmyVec = Vec2(Emypos[j].x, Emypos[j].y);
		if (mon_pos.x - 1 == EmyVec.x && mon_pos.y == EmyVec.y) {
			num = j;
			Check = true;
		}
		if (mon_pos.x + 1 == EmyVec.x && mon_pos.y == EmyVec.y) {
			num = j;
			Check = true;
		}
		if (mon_pos.x == EmyVec.x && mon_pos.y - 1 == EmyVec.y) {
			num = j;
			Check = true;
		}
		if (mon_pos.x == EmyVec.x && mon_pos.y + 1 == EmyVec.y) {
			num = j;
			Check = true;
		}
		
		//짝수
		if (fmodf(mon_pos.y, 2) == 0) {
			if (mon_pos.x - 1 == EmyVec.x && mon_pos.y - 1 == EmyVec.y) {
				num = j;
				Check = true;
			}
			if (mon_pos.x - 1 == EmyVec.x && mon_pos.y + 1 == EmyVec.y) {
				num = j;
				Check = true;
			}
		}
		//홀수
		else {
			if (mon_pos.x + 1 == EmyVec.x && mon_pos.y + 1 == EmyVec.y) {
				num = j;
				Check = true;
			}
			if (mon_pos.x + 1 == EmyVec.x && mon_pos.y - 1 == EmyVec.y) {
				num = j;
				Check = true;
			}
		}
	}
	
	if (Check) {
		monsterNum = 0;
		for (int q = 0; q < monsterSize; q++) {
			if (monster_char[q].tx == Emypos[num].x && monster_char[q].ty == Emypos[num].y) {
				monsterNum = q;
				break;
			}
		}
		return true;
	}
	else {
		return false;
	}
	
}

void EarthMap::deleytime(float f) {
	Sprite* End = Sprite::createWithSpriteFrameName("End.png");
	End->setAnchorPoint(Vec2(0, 0));
	End->setPosition(Vec2(0, 0));
	End->setScale(2.0f);
	EmyMonster_char[emynum]._turn = false;
	EmyMonster_char[emynum].sprite->addChild(End, 4, 4);

	emynum++;
	if (emynum == EmyMonsterSize) {
		ChageSchedule = false;
		this->schedule(schedule_selector(EarthMap::EmyTurn));
	}
}

void EarthMap::EmyMove(float f) {
	log("emynum = %d", emynum);

	Attack(&EmyMonster_char[emynum], &monster_char[monsterNum]);
}

void EarthMap::EmyMonsterAttackAction() {

	EmyMonster_char[emynum].sprite->stopAllActions();
	EmyMonster_char[emynum].sprite->removeAllChildren();
	tmap->removeChild(EmyMonster_char[emynum].sprite, true);

	//L_R == true 왼쪽 false 오른쪽
	char str1[100];
	char str2[100];
	//Vector<SpriteFrame*> animFrames;
	char str3[100];
	char str4[100];
	Vector<SpriteFrame*> animFrames3;
	Sprite *sst = Sprite::create();
	Vector<SpriteFrame*> animFrames_Action;

	//땅질퍽이
	if (EmyMonster_char[emynum].Type == 1) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth1-A1.png");
		sprintf(str1, "Earth1-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_smoke.wav");
		sst = Sprite::createWithSpriteFrameName("fx_smokeground_000.png");
		sprintf(str3, "fx_smokeground_0");
		for (int i = 0; i <= 7; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 2) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth2-A1.png");
		sprintf(str1, "Earth2-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_smoke.wav");
		sst = Sprite::createWithSpriteFrameName("fx_explosiondarkplume_000.png");
		sprintf(str3, "fx_explosiondarkplume_0");
		for (int i = 0; i <= 8; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 3) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth3-A1.png");
		sprintf(str1, "Earth3-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_smoke.wav");
		sst = Sprite::createWithSpriteFrameName("fx_explosionwhitesmokemedium_000.png");
		sprintf(str3, "fx_explosionwhitesmokemedium_0");
		for (int i = 0; i <= 9; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//모닥픽
	else if (EmyMonster_char[emynum].Type == 4) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth4-A1.png");
		sprintf(str1, "Earth4-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_impactgreensmall_000.png");
		sprintf(str3, "fx_impactgreensmall_0");
		for (int i = 0; i <= 4; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 5) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth5-A1.png");
		sprintf(str1, "Earth5-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_impactgreenmedium_000.png");
		sprintf(str3, "fx_impactgreenmedium_0");
		for (int i = 0; i <= 5; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 6) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth6-A1.png");
		sprintf(str1, "Earth6-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_impactgreenbig_000.png");
		sprintf(str3, "fx_impactgreenbig_0");
		for (int i = 0; i <= 6; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//모래두지
	else if (EmyMonster_char[emynum].Type == 7) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth7-A1.png");
		sprintf(str1, "Earth7-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f5_earthsphere_000.png");
		sprintf(str3, "fx_f5_earthsphere_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 8) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth8-A1.png");
		sprintf(str1, "Earth8-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f5_earthsphere_000.png");
		sprintf(str3, "fx_f5_earthsphere_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 9) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth9-A1.png");
		sprintf(str1, "Earth9-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f5_earthsphere_000.png");
		sprintf(str3, "fx_f5_earthsphere_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//파이뤼
	else if (EmyMonster_char[emynum].Type == 11) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire1-A1.png");
		sprintf(str1, "Fire1-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_explosionorangesmoke.wav");
		sst = Sprite::createWithSpriteFrameName("fx_explosionorangesmoke_000.png");
		sprintf(str3, "fx_explosionorangesmoke_0");
		for (int i = 0; i <= 5; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 12) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire2-A1.png");
		sprintf(str1, "Fire2-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_whiteexplosion.wav");
		sst = Sprite::createWithSpriteFrameName("fx_whitehotmedium_000.png");
		sprintf(str3, "fx_whitehotmedium_0");
		for (int i = 0; i <= 8; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 13) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire3-A1.png");
		sprintf(str1, "Fire3-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_whiteexplosion.wav");
		sst = Sprite::createWithSpriteFrameName("fx_whitehotbig_000.png");
		sprintf(str3, "fx_whitehotbig_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//팬템
	else if (EmyMonster_char[emynum].Type == 14) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire4-A1.png");
		sprintf(str1, "Fire4-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_blood_explosion.wav");
		sst = Sprite::createWithSpriteFrameName("fx_bloodmedium_000.png");
		sprintf(str3, "fx_bloodmedium_0");
		for (int i = 0; i <= 9; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 15) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire5-A1.png");
		sprintf(str1, "Fire5-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_blood_explosion.wav");
		sst = Sprite::createWithSpriteFrameName("fx_bloodbig_000.png");
		sprintf(str3, "fx_bloodbig_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 16) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire6-A1.png");
		sprintf(str1, "Fire6-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_f2_eightgates_purpleflame.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f2_eightgates_purpleflame_000.png");
		sprintf(str3, "fx_f2_eightgates_purpleflame_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//블랙매직숀
	else if (EmyMonster_char[emynum].Type == 17) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire7-A1.png");
		sprintf(str1, "Fire7-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_f5_earthsphere_orange.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f5_earthsphere_orange_000.png");
		sprintf(str3, "fx_f5_earthsphere_orange_0");
		for (int i = 0; i <= 7; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 18) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire8-A1.png");
		sprintf(str1, "Fire8-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_f2_teleport.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f2_teleport_000.png");
		sprintf(str3, "fx_f2_teleport_0");
		for (int i = 0; i <= 7; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 19) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire9-A1.png");
		sprintf(str1, "Fire9-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_f2_twinstrike.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f2_twinstrike_000.png");
		sprintf(str3, "fx_f2_twinstrike_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//물질퍽이
	else if (EmyMonster_char[emynum].Type == 21) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water1-A1.png");
		sprintf(str1, "Water1-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_cleanse.wav");
		sst = Sprite::createWithSpriteFrameName("fx_cleanse_ripples_000.png");
		sprintf(str3, "fx_cleanse_ripples_0");
		for (int i = 0; i <= 6; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 22) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water2-A1.png");
		sprintf(str1, "Water2-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_f6_spiritofthewild.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f6_spiritofthewild_000.png");
		sprintf(str3, "fx_f6_spiritofthewild_0");
		for (int i = 0; i <= 8; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 23) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water3-A1.png");
		sprintf(str1, "Water3-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_f6_spiritofthewild.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f6_spiritofthewild_000.png");
		sprintf(str3, "fx_f6_spiritofthewild_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//꼬북이
	else if (EmyMonster_char[emynum].Type == 24) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water4-A1.png");
		sprintf(str1, "Water4-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_cleanse.wav");
		sst = Sprite::createWithSpriteFrameName("fx_cleanse_ripples_000.png");
		sprintf(str3, "fx_cleanse_ripples_0");
		for (int i = 0; i <= 6; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 25) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water5-A1.png");
		sprintf(str1, "Water5-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_teleportblueorb.wav");
		sst = Sprite::createWithSpriteFrameName("fx_teleportblueorb_000.png");
		sprintf(str3, "fx_teleportblueorb_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 26) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water6-A1.png");
		sprintf(str1, "Water6-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_distortion_hex_shield.wav");
		sst = Sprite::createWithSpriteFrameName("distortion_hex_shield_000.png");
		sprintf(str3, "distortion_hex_shield_0");
		for (int i = 0; i <= 9; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//리아커
	else if (EmyMonster_char[emynum].Type == 27) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water7-A1.png");
		sprintf(str1, "Water7-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_cleanse.wav");
		sst = Sprite::createWithSpriteFrameName("fx_cleanse_ripples_000.png");
		sprintf(str3, "fx_cleanse_ripples_0");
		for (int i = 0; i <= 6; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 28) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water8-A1.png");
		sprintf(str1, "Water8-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_f6_cryogenesis.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f6_cryogenesis_000.png");
		sprintf(str3, "fx_f6_cryogenesis_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 29) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water9-A1.png");
		sprintf(str1, "Water9-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_f3_fountainofyouth.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f3_fountainofyouth_000.png");
		sprintf(str3, "fx_f3_fountainofyouth_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//코이
	else if (EmyMonster_char[emynum].Type == 31) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind1-A1.png");
		sprintf(str1, "Wind1-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_f2_spiraltechnique02.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f2_spiraltechnique02_000.png");
		sprintf(str3, "fx_f2_spiraltechnique02_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 32) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind2-A1.png");
		sprintf(str1, "Wind2-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_blueplasma_vertical.wav");
		sst = Sprite::createWithSpriteFrameName("fx_blueplasma_vertical_000.png");
		sprintf(str3, "fx_blueplasma_vertical_0");
		for (int i = 0; i <= 7; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 33) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind3-A1.png");
		sprintf(str1, "Wind3-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_f1_decimate.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f1_decimate_000.png");
		sprintf(str3, "fx_f1_decimate_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//피젼
	else if (EmyMonster_char[emynum].Type == 34) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind4-A1.png");
		sprintf(str1, "Wind4-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_clawslash.wav");
		sst = Sprite::createWithSpriteFrameName("fx_clawslash_000.png");
		sprintf(str3, "fx_clawslash_0");
		for (int i = 0; i <= 4; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 35) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind5-A1.png");
		sprintf(str1, "Wind5-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_bluewatersplash.wav");
		sst = Sprite::createWithSpriteFrameName("fx_bluewatersplash_000.png");
		sprintf(str3, "fx_bluewatersplash_0");
		for (int i = 0; i <= 8; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 36) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind6-A1.png");
		sprintf(str1, "Wind6-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_f1_casterprojectile.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f1casterprojectile_000.png");
		sprintf(str3, "fx_f1casterprojectile_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//토게피
	else if (EmyMonster_char[emynum].Type == 37) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind7-A1.png");
		sprintf(str1, "Wind7-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_bladestorm.wav");
		sst = Sprite::createWithSpriteFrameName("fx_bladestorm_000.png");
		sprintf(str3, "fx_bladestorm_0");
		for (int i = 0; i <= 11; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 38) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind8-A1.png");
		sprintf(str1, "Wind8-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_f1_lionheartblessing.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f1_lionheartblessing_000.png");
		sprintf(str3, "fx_f1_lionheartblessing_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (EmyMonster_char[emynum].Type == 39) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind9-A1.png");
		sprintf(str1, "Wind9-A");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_f1_circlelife.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f1_circlelife_000.png");
		sprintf(str3, "fx_f1_circlelife_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}

	if (L_R) {
		for (int i = 1; i <= 3; i++) {
			sprintf(str2, "%s%d.png", str1, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str2);
			animFrames_Action.pushBack(frame);
		}
	}
	else {
		for (int i = 4; i <= 6; i++) {
			sprintf(str2, "%s%d.png", str1, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str2);
			animFrames_Action.pushBack(frame);
		}
	}

	//공격 사용 스킬 액션
	auto animation2 = Animation::createWithSpriteFrames(animFrames3, 0.02f);
	auto animate2 = Animate::create(animation2);
	sst->runAction(animate2);
	if (EmyMonster_char[emynum].Type == 22 || EmyMonster_char[emynum].Type == 23 || EmyMonster_char[emynum].Type == 28) {
		sst->setScale(0.5f);
	}
	else if(EmyMonster_char[emynum].Type == 16 || EmyMonster_char[emynum].Type == 17 || EmyMonster_char[emynum].Type == 19 || EmyMonster_char[emynum].Type == 26 || EmyMonster_char[emynum].Type == 38) {
		sst->setScale(1.0f);
	}
	else {
		sst->setScale(2.0f);
	}
	
	Vec2 Vector1 = FindCoordPosition(Vec2(monster_char[monsterNum].tx, monster_char[monsterNum].ty));
	sst->setPosition(Vec2(Vector1.x - MovePositionX, Vector1.y - 60 - MovePositionY));
	tmap->addChild(sst, 5, 500);

	auto animation0 = Animation::createWithSpriteFrames(animFrames_Action, 0.2f);
	auto animate0 = Animate::create(animation0);

	EmyMonster_char[emynum].sprite->runAction(animate0);
	Vec2 Vector = FindCoordPosition(Vec2(EmyMonster_char[emynum].tx, EmyMonster_char[emynum].ty));
	//posit.x - MovePositionX,		posit.y - 60 - MovePositionY
	EmyMonster_char[emynum].sprite->setPosition(Vec2(Vector.x - MovePositionX, Vector.y - 60 - MovePositionY));
	tmap->addChild(EmyMonster_char[emynum].sprite, 5, 100+emynum);
	
	//다시 걸어다니는 액션으로 교체
	this->scheduleOnce(schedule_selector(EarthMap::callbackrepeatforeverAmy), 0.3f);
}

void EarthMap::callbackrepeatforeverAmy(float delta) {
	log("callbackrepeatforeverAmy %d", EmyMonster_char[emynum].sprite->getTag());
	EmyMonster_char[emynum].sprite->stopAllActions();
	EmyMonster_char[emynum].sprite->removeAllChildren();
	tmap->removeChild(EmyMonster_char[emynum].sprite);
	//공격효과액션 삭제
	tmap->removeChildByTag(500);
	//L_R == true 왼쪽 false 오른쪽
	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;
	Vector<SpriteFrame*> animFrames_Action;

	if (EmyMonster_char[emynum].Type == 0) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
	}
	if (EmyMonster_char[emynum].Type == 1) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth1-1.png");
		sprintf(str1, "Earth1-");
	}
	else if (EmyMonster_char[emynum].Type == 2) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth2-1.png");
		sprintf(str1, "Earth2-");
	}
	else if (EmyMonster_char[emynum].Type == 3) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth3-1.png");
		sprintf(str1, "Earth3-");
	}
	//모닥픽
	else if (EmyMonster_char[emynum].Type == 4) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth4-1.png");
		sprintf(str1, "Earth4-");
	}
	else if (EmyMonster_char[emynum].Type == 5) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth5-1.png");
		sprintf(str1, "Earth5-");
	}
	else if (EmyMonster_char[emynum].Type == 6) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth6-1.png");
		sprintf(str1, "Earth6-");
	}
	//모래두지
	else if (EmyMonster_char[emynum].Type == 7) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth7-1.png");
		sprintf(str1, "Earth7-");
	}
	else if (EmyMonster_char[emynum].Type == 8) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth8-1.png");
		sprintf(str1, "Earth8-");
	}
	else if (EmyMonster_char[emynum].Type == 9) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Earth9-1.png");
		sprintf(str1, "Earth9-");
	}
	//파이뤼
	else if (EmyMonster_char[emynum].Type == 11) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire1-1.png");
		sprintf(str1, "Fire1-");
	}
	else if (EmyMonster_char[emynum].Type == 12) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire2-1.png");
		sprintf(str1, "Fire2-");
	}
	else if (EmyMonster_char[emynum].Type == 13) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire3-1.png");
		sprintf(str1, "Fire3-");
	}
	//팬템
	else if (EmyMonster_char[emynum].Type == 14) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire4-1.png");
		sprintf(str1, "Fire4-");
	}
	else if (EmyMonster_char[emynum].Type == 15) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire5-1.png");
		sprintf(str1, "Fire5-");
	}
	else if (EmyMonster_char[emynum].Type == 16) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire6-1.png");
		sprintf(str1, "Fire6-");
	}
	//블랙매직숀
	else if (EmyMonster_char[emynum].Type == 17) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire7-1.png");
		sprintf(str1, "Fire7-");
	}
	else if (EmyMonster_char[emynum].Type == 18) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire8-1.png");
		sprintf(str1, "Fire8-");
	}
	else if (EmyMonster_char[emynum].Type == 19) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Fire9-1.png");
		sprintf(str1, "Fire9-");
	}
	//물질퍽이
	else if (EmyMonster_char[emynum].Type == 21) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water1-1.png");
		sprintf(str1, "Water1-");
	}
	else if (EmyMonster_char[emynum].Type == 22) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water2-1.png");
		sprintf(str1, "Water2-");
	}
	else if (EmyMonster_char[emynum].Type == 23) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water3-1.png");
		sprintf(str1, "Water3-");
	}
	//꼬북이
	else if (EmyMonster_char[emynum].Type == 24) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water4-1.png");
		sprintf(str1, "Water4-");
	}
	else if (EmyMonster_char[emynum].Type == 25) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water5-1.png");
		sprintf(str1, "Water5-");
	}
	else if (EmyMonster_char[emynum].Type == 26) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water6-1.png");
		sprintf(str1, "Water6-");
	}
	//리아커
	else if (EmyMonster_char[emynum].Type == 27) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water7-1.png");
		sprintf(str1, "Water7-");
	}
	else if (EmyMonster_char[emynum].Type == 28) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water8-1.png");
		sprintf(str1, "Water8-");
	}
	else if (EmyMonster_char[emynum].Type == 29) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Water9-1.png");
		sprintf(str1, "Water9-");
	}
	//코이
	else if (EmyMonster_char[emynum].Type == 31) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind1-1.png");
		sprintf(str1, "Wind1-");
	}
	else if (EmyMonster_char[emynum].Type == 32) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind2-1.png");
		sprintf(str1, "Wind2-");
	}
	else if (EmyMonster_char[emynum].Type == 33) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind3-1.png");
		sprintf(str1, "Wind3-");
	}
	//피젼
	else if (EmyMonster_char[emynum].Type == 34) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind4-1.png");
		sprintf(str1, "Wind4-");
	}
	else if (EmyMonster_char[emynum].Type == 35) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind5-1.png");
		sprintf(str1, "Wind5-");
	}
	else if (EmyMonster_char[emynum].Type == 36) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind6-1.png");
		sprintf(str1, "Wind6-");
	}
	//코이
	else if (EmyMonster_char[emynum].Type == 37) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind7-1.png");
		sprintf(str1, "Wind7-");
	}
	else if (EmyMonster_char[emynum].Type == 38) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind8-1.png");
		sprintf(str1, "Wind8-");
	}
	else if (EmyMonster_char[emynum].Type == 39) {
		EmyMonster_char[emynum].sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
		sprintf(str1, "Wind9-");
	}

	if (L_R) {
		for (int i = 1; i <= 4; i++) {
			sprintf(str2, "%s%d.png", str1, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str2);
			animFrames.pushBack(frame);
		}
	}
	else {
		for (int i = 5; i <= 8; i++) {
			sprintf(str2, "%s%d.png", str1, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str2);
			animFrames.pushBack(frame);
		}
	}

	auto animation1 = Animation::createWithSpriteFrames(animFrames, 0.2f);
	auto animate1 = Animate::create(animation1);
	auto rep1 = RepeatForever::create(animate1);

	EmyMonster_char[emynum].sprite->runAction(rep1);
	Vec2 Vector = FindCoordPosition(Vec2(EmyMonster_char[emynum].tx, EmyMonster_char[emynum].ty));
	//posit.x - MovePositionX, posit.y - 60 - MovePositionY
	EmyMonster_char[emynum].sprite->setPosition(Vec2(Vector.x - MovePositionX, Vector.y - 60 - MovePositionY));
	tmap->addChild(EmyMonster_char[emynum].sprite, 5, 100 + emynum);

	Sprite* st = Sprite::createWithSpriteFrameName("HP_bar.png");
	st->setPosition(0, -5);
	st->setScaleX(EmyMonster_char[emynum].HPbarPosition / 25 * 2);
	st->setScaleY(2.0f);
	st->setAnchorPoint(Vec2(0, 0.5));
	EmyMonster_char[emynum].sprite->addChild(st, 4, 1);

	Sprite* hp = Sprite::createWithSpriteFrameName("EmyMonseter_HP.png");
	hp->setPosition(0, -5);
	hp->setScaleX((EmyMonster_char[emynum].HPbarPosition / 25 * 2) * EmyMonster_char[emynum].hp / EmyMonster_char[emynum].Fullhp);
	hp->setScaleY(2.0f);
	hp->setAnchorPoint(Vec2(0, 0.5));
	EmyMonster_char[emynum].sprite->addChild(hp, 4, 2);

	char level[3];
	sprintf(level, "%d", EmyMonster_char[emynum].level);
	auto pLabel3 = LabelAtlas::create(level, "Images/Scene/EmyML.png", 7, 9, '0');
	pLabel3->setAnchorPoint(Vec2(0, 0));
	pLabel3->setScale(2.0f);
	pLabel3->setPosition(Vec2(st->getContentSize().width*(EmyMonster_char[emynum].HPbarPosition / 25 * 2) + 5, -10));
	EmyMonster_char[emynum].sprite->addChild(pLabel3, 4, 3);

	//monster_char[monsterNum].hp -= attackdamage;
	//monster_char[monsterNum].sprite->removeChildByTag(2);
	//hp = Sprite::createWithSpriteFrameName("EmyMonseter_HP.png");
	//hp->setPosition(2, -5);
	//hp->setScaleX((monster_char[monsterNum].HPbarPosition / 25 * 2) * monster_char[monsterNum].hp / monster_char[monsterNum].Fullhp);
	////hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
	//hp->setAnchorPoint(Vec2(0, 0.5));
	//monster_char[monsterNum].sprite->addChild(hp, 4, 2);

	monster_char[monsterNum].hp -= attackdamage;
	monster_char[monsterNum].sprite->removeChildByTag(2);
	Sprite* hp1 = Sprite::createWithSpriteFrameName("Monster_HP.png");
	hp1->setPosition(2, -5);
	hp1->setScaleX((monster_char[monsterNum].HPbarPosition / 25 * 2) * monster_char[monsterNum].hp / monster_char[monsterNum].Fullhp);
	hp1->setScaleY(2);
	//hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
	hp1->setAnchorPoint(Vec2(0, 0.5));
	monster_char[monsterNum].sprite->addChild(hp1, 4, 2);
	log("after monster_char[monsterNum].hp = %d", monster_char[monsterNum].hp);
	if (monster_char[monsterNum].hp < 0) {
		monster_char[monsterNum].hp = 0;
		//적 몬스터 죽음 처리
		tmap->removeChild(monster_char[monsterNum].sprite);
		if (monster_char[monsterNum].Type == 0) {
			log("주인공 죽음");
			//주인공 죽음 화면 전환
			m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/GameEnd2.wav");
			this->unschedule(schedule_selector(EarthMap::EmyMoveAttack));
			this->unschedule(schedule_selector(EarthMap::doChange));
			
			EndGame(2);
			return;
		}
		else {
			int monster_num;
			for (int k = 0; k < monsterSize; k++) {
				if (monster_char[monsterNum].ID == monster_char[k].ID) {
					monster_num = k;
					break;
				}
			}

			if (DeathMonsterListSize)	Death_Monster_List = (Monster_num*)realloc(Death_Monster_List, sizeof(Monster_num) * (DeathMonsterListSize + 1));
			else						Death_Monster_List = (Monster_num*)malloc(sizeof(Monster_num) * (DeathMonsterListSize + 1));
			DeathMonsterListSize++;
			Death_Monster_List[DeathMonsterListSize - 1].ID = monster_char[monsterNum].ID;

			for (int k = monster_num; k < monsterSize - 1; k++) {
				monster_char[k] = monster_char[k + 1];
			}
			monster_char = (Monster_num*)realloc(monster_char, sizeof(Monster_num) * (monsterSize - 1));
			monsterSize--;
		}
	}
	log("callbackrepeatforeverAmy End %d", EmyMonster_char[emynum].sprite->getTag());
}

void EarthMap::Attack(Monster_num *monster, Monster_num *Emymonster) {
	float bufDamage = 1.0;
	float bufDefense = 1.0;
	if (BufTileCheck(Vec2(monster->tx, monster->ty))) {
		bufDamage += 0.2;
	}
	if (BufTileCheck(Vec2(Emymonster->tx, Emymonster->ty))) {
		bufDefense += 0.2;
	}

	if (SynastryCheck(monster->Type, Emymonster->Type) == 1) {
		bufDamage += 0.2;
	}
	else if (SynastryCheck(monster->Type, Emymonster->Type) == 2) {
		bufDefense += 0.2;
	}
	//log("defore hp = %d", Emymonster->hp);
	int defdamage = Emymonster->def;
	if (Emymonster->Item1 != -1) {
		if (Emymonster->Item1 == 3) {
			defdamage += 30;
		}
		else if (Emymonster->Item1 == 4) {
			defdamage += 60;
		}
		else if (Emymonster->Item1 == 5) {
			defdamage += 90;
		}
	}
	if (Emymonster->Item2 != -1) {
		if (Emymonster->Item2 == 3) {
			defdamage += 30;
		}
		else if (Emymonster->Item2 == 4) {
			defdamage += 60;
		}
		else if (Emymonster->Item2 == 5) {
			defdamage += 90;
		}
	}
	if (Emymonster->Item3 != -1) {
		if (Emymonster->Item3 == 3) {
			defdamage += 30;
		}
		else if (Emymonster->Item3 == 4) {
			defdamage += 60;
		}
		else if (Emymonster->Item3 == 5) {
			defdamage += 90;
		}
	}
	attackdamage = (monster->atk * bufDamage) - (defdamage * bufDefense);
	//log("type = %d", monster->Type);
	//log("attackdamage = %d, monster->atk = %d, bufDamage = %f, Emymonster->def = %d, bufDefense = %f",
	//	attackdamage, monster->atk, bufDamage, Emymonster->def, bufDefense);
	if (attackdamage > 0) {
		Vec2 vec1 = FindCoordPosition(Vec2(monster->tx, monster->ty));
		Vec2 vec2 = FindCoordPosition(Vec2(Emymonster->tx, Emymonster->ty));
		if (vec1.x < vec2.x)	L_R = false;
		else 					L_R = true;
		log("defore Emymonster->hp = %d", Emymonster->hp);
		EmyMonsterAttackAction();
	}
	else {
		//miss

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/sell.wav");
	}
}

//적군 턴이 끝날 경우 아군 end표시 삭제
void EarthMap::EmyTurn(float f) {
	this->unschedule(schedule_selector(EarthMap::EmyTurn));
	this->unschedule(schedule_selector(EarthMap::EmyMove));
	this->unschedule(schedule_selector(EarthMap::deleytime));
	for (int i = monsterSize - 1; i >= 0; i--) {
		monster_char[i]._turn = true;
		log("%d : %d", i, monster_char[i].Type);
		//monster_char[i].sprite->removeChildByTag(4);
	}
	monster_char[0].sprite->removeChildByTag(4);
	TouchTurnEnd = true;
	//EnemyTurn 삭제
	this->removeChildByTag(200);
	//MyTurn 표시
	m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/click.wav");
	Sprite* MyTurnLabel = Sprite::create("Images/Scene/MyTurnLabel.png");
	MyTurnLabel->setScale(4.0f);
	MyTurnLabel->setPosition(Vec2(640, 360));
	this->addChild(MyTurnLabel, 200, 201);
}

//몬스터 소환 메세지 받기
void EarthMap::doMsgReceivedMonster(Ref* obj) {
	char *inputStr = (char*)obj;
	char testText[20];
	sprintf(testText, "%s", inputStr);
	if (!strcmp(testText, "0")) {
		Director::getInstance()->resume();
		touchMove = true;
		CharacterClick = true;
	}
	else {
		createMonsterNum = atoi(testText);
		//log("소환 : %d", createMonsterNum);
		Director::getInstance()->resume();
		b_CreateMonster = true;
		touchMove = true;
		
		if (Msgerror) {
			createUpgrade();
		}
		
		if (createPosSize == 0) {
			//소환 할 장소가 없다고 에러 창 띄우기
			log("소환 할 장소가 없습니다.");
		}
	}

}

//도구사용 메세지 받기
void EarthMap::doMsgReceivedTool(Ref* obj) {
	char *inputStr = (char*)obj;
	char testText[20];
	sprintf(testText, "%s", inputStr);
	if (!strcmp(testText, "0")) {
		Director::getInstance()->resume();
		touchMove = true;

		
		CharacterClick = true;
	}
	else {
		ToolNum = atoi(testText);
		//log("도구 : %d", ToolNum);
		Director::getInstance()->resume();
		touchMove = true;

		if (ToolUseMonster) {
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
			monster_char[ToolUseMonster - 1].sprite->removeChildByTag(2);
			Sprite* hp = Sprite::createWithSpriteFrameName("Monster_HP.png");
			hp->setPosition(2, -5);
			hp->setScaleX((monster_char[ToolUseMonster - 1].HPbarPosition / 25 * 2) * monster_char[ToolUseMonster - 1].hp / monster_char[ToolUseMonster - 1].Fullhp);
			hp->setScaleY(2);
			//hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
			hp->setAnchorPoint(Vec2(0, 0.5));
			monster_char[ToolUseMonster - 1].sprite->addChild(hp, 4, 2);

			//log("after monster_char[ToolUseMonster-1].hp = %d", monster_char[ToolUseMonster-1].hp);
			
			//적 몬스터 타일 표시
			for (int i = 0; i < EmyMovePosition.size(); i++) {
				tmap->removeChild(EmyMovePosition.at(i), true);
			}
			//아군 몬스터 타일 표시
			for (int i = 0; i < MovePosition.size(); i++) {
				tmap->removeChild(MovePosition.at(i), true);
			}

			//데이터베이스 최신화
			int num = atoi(testText);
			UpdateItemDB(num);

			ReturnState = false;
			//턴종료
			if (!status) {
				Sprite* End = Sprite::createWithSpriteFrameName("End.png");
				End->setAnchorPoint(Vec2(0, 0));
				End->setPosition(Vec2(0, 0));
				End->setScale(2.0f);
				monster_char[mons]._turn = false;
				monster_char[mons].sprite->addChild(End, 4, 4);
				ReturnState = false;
			}
		}
	}

}

//몬스터 소환시 소환할 위치 표시
void EarthMap::createUpgrade() {

	for (int i = 0; i < MovePosition.size(); i++) {
		tmap->removeChild(MovePosition.at(i));
	}
	if (MovePosition.size()) {
		MovePosition.clear();
	}

	for (int i = 0; i < EmyMovePosition.size(); i++) {
		tmap->removeChild(EmyMovePosition.at(i));
	}
	if (EmyMovePosition.size()) {
		EmyMovePosition.clear();
	}

	VPos = Vec2(VPosX, VPosY);
	createPosSize = 0;
	createMonsterPos = CheckPosition(VPos, createMonsterPos, createPosSize, 1, 0, monsterSize, monster_char, EmyMonsterSize, EmyMonster_char);
	createPosSize = GrobalTempsize;
	
	//한칸
	for (int m = 0; m < createPosSize; m++) {
		Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
		Vec2 posit = FindCoordPosition(Vec2(createMonsterPos[m].x, createMonsterPos[m].y));
		sp->setPosition(posit.x - MovePositionX, posit.y - 60 - MovePositionY);
		tmap->addChild(sp);
		MovePosition.pushBack(sp);
	}
	Msgerror = false;
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
	this->removeAllChildren();
	this->removeAllChildrenWithCleanup(true);
	//변수 초기화
	if (monsterSize) {
		free(monster_char);
		monsterSize = 0;
	}
	if (EmyMonsterSize) {
		free(EmyMonster_char);
		EmyMonsterSize = 0;
	}

	if (DeathMonsterListSize) {
		free(Death_Monster_List);
		DeathMonsterListSize = 0;
	}

	if (MonsterListSize) {
		free(Monster_List);
		MonsterListSize = 0;
	}

	if (posSize) {
		free(pos);
	}

	if (EmyposSize) {
		free(Emypos);
	}

	if (EmyposAttackSize) {
		free(EmyposAttack);
	}
	if (shortpassSize) {
		free(shortpass);
	}
	if (createPosSize) {
		free(createMonsterPos);
	}
	if (VecPositionSize) {
		free(VecPosition);
	}

	if (ItemsListSize) {
		free(Items_List);
		ItemsListSize = 0;
	}

	posSize = 0;
	EmyposSize = 0;
	EmyposAttackSize = 0;
	shortpassSize = 0;
	createPosSize = 0;
	VecPositionSize = 0;

	MovePosition.clear();
	EmyMovePosition.clear();

	mons = 0;

	ReturnMove_tx = 0;
	ReturnMove_ty = 0;

	Moving_tx = 0;
	Moving_ty = 0;

	statuschar = true;

	createMonsterNum = 0;
	ToolNum = 0;
	movement = 0;

	ClickEmyMonster = 0;

	TouchTurnEnd = true;

	emynum = 0;
	monsterNum = 0;

	VPosX = 0;
	VPosY = 0;

	EndGame_Num = 0;

	GrobalTempsize = 0;

	MovePositionDX = 0;
	MovePositionDY = 0;

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
	ChageSchedule = false;
	ReturnState = false;
	Msgerror = true;
	Layer::onExit();
}

bool EarthMap::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (!touchMove) {
		return false;
	}
	this->removeChildByTag(10);
	auto touchPoint = touch->getLocation();
	StartDragPosition = touchPoint;
	//myTurn Label 삭제
	this->removeChildByTag(201);

	return true;
}

void EarthMap::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	//소환, 도구 다이얼로그 창 띄워져 있을 경우
	/*if (status) {
		return;
	}
	if (statusAttack) {
		return;
	}*/
	winSize = Director::getInstance()->getWinSize();

	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	EndDragPosition = touchPoint;

	MovePositionDX -= (EndDragPosition.x - StartDragPosition.x);
	if (MovePositionDX < 0 ) {
		MovePositionDX = 0;
	}
	else if (MovePositionDX > 703) {
		MovePositionDX = 703;
	}
	MovePositionDY -= (EndDragPosition.y - StartDragPosition.y);
	if (MovePositionDY < 0) {
		MovePositionDY = 0;
	}
	else if (MovePositionDY > 785) {
		MovePositionDY = 785;
	}

	float tx = tmap->getPosition().x + (EndDragPosition.x - StartDragPosition.x);
	float ty = tmap->getPosition().y + (EndDragPosition.y - StartDragPosition.y);
	if (tx < -1006 - 66 + winSize.width - 976) {
		tx = -1006 - 66 + winSize.width - 976;
	}
	else if (tx > -66) {
		tx = -66;
	}
	if (ty < -767 - 32 + winSize.height - 737) {
		ty = -767 - 32 + winSize.height - 737;
	}
	else if (ty > -32) {
		ty = -32;
	}
	tmap->setPosition(Vec2(tx, ty));

	MovePositionX = tx;
	MovePositionY = ty;

	//log("MovePositionX = %f, MovePositionY = %f", MovePositionX, MovePositionY);

	StartDragPosition = EndDragPosition;

	
}

void EarthMap::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;

	//클릭타일좌표
	Vec2 m_pos = tileCoordForPosition(touchPoint);

	//아군소환할 경우
	if (b_CreateMonster) {
		ReturnState = false;
		Msgerror = true;
		
		for (int i = 0; i < createPosSize; i++) {
			if (m_pos == Vec2(createMonsterPos[i].x, createMonsterPos[i].y)) {
				//아군몬스터 소환 createMonsterNum
				m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/create.wav");
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
					st->setPosition(128 * num1 + 66, 1632 - (160 + 96 * num2) + 32);
				}
				else {
					st->setPosition(62 + 128 * num1 + 66, 1632 - (160 + 96 * num2) + 32);
				}


				auto animation = Animation::createWithSpriteFrames(animFrame, 0.1f);
				auto animate = Animate::create(animation);
				auto cbSound = CallFunc::create(CC_CALLBACK_0(EarthMap::RemoveSprite, this));
				auto seq = Sequence::create(animate, cbSound, NULL);
				st->runAction(seq);
				tmap->addChild(st, 5);

				if (true) {
					//땅질퍽이
					if (monster_char[monsterSize - 1].Type == 1) {
						monster_char[monsterSize - 1].atk = 150 + ((monster_char[monsterSize - 1].level - 1) * 15);
						monster_char[monsterSize - 1].def = 30 + ((monster_char[monsterSize - 1].level - 1) * 03);
						monster_char[monsterSize - 1].hp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
						monster_char[monsterSize - 1].Fullhp = 300 + ((monster_char[monsterSize - 1].level - 1) * 30);
						monster_char[monsterSize - 1].move = 3;
						monster_char[monsterSize - 1].range = 1;
						monster_char[monsterSize - 1].HPbarPosition = 30;
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
						monster_char[monsterSize - 1].HPbarPosition = 34;
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
						monster_char[monsterSize - 1].HPbarPosition = 57;
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
						monster_char[monsterSize - 1].HPbarPosition = 23;
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
						monster_char[monsterSize - 1].HPbarPosition = 27;
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
						monster_char[monsterSize - 1].HPbarPosition = 40;
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
						monster_char[monsterSize - 1].HPbarPosition = 38;
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
						monster_char[monsterSize - 1].HPbarPosition = 56;
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
						monster_char[monsterSize - 1].HPbarPosition = 42;
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
						monster_char[monsterSize - 1].HPbarPosition = 29;
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
						monster_char[monsterSize - 1].HPbarPosition = 50;
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
						monster_char[monsterSize - 1].HPbarPosition = 56;
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
						monster_char[monsterSize - 1].HPbarPosition = 39;
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
						monster_char[monsterSize - 1].HPbarPosition = 52;
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
						monster_char[monsterSize - 1].HPbarPosition = 49;
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
						monster_char[monsterSize - 1].HPbarPosition = 48;
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
						monster_char[monsterSize - 1].HPbarPosition = 54;
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
						monster_char[monsterSize - 1].HPbarPosition = 42;
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
						monster_char[monsterSize - 1].HPbarPosition = 29;
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
						monster_char[monsterSize - 1].HPbarPosition = 33;
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
						monster_char[monsterSize - 1].HPbarPosition = 58;
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
						monster_char[monsterSize - 1].HPbarPosition = 41;
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
						monster_char[monsterSize - 1].HPbarPosition = 46;
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
						monster_char[monsterSize - 1].HPbarPosition = 50;
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
						monster_char[monsterSize - 1].HPbarPosition = 42;
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
						monster_char[monsterSize - 1].HPbarPosition = 50;
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
						monster_char[monsterSize - 1].HPbarPosition = 61;
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
						monster_char[monsterSize - 1].HPbarPosition = 38;
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
						monster_char[monsterSize - 1].HPbarPosition = 39;
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
						monster_char[monsterSize - 1].HPbarPosition = 59;
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
						monster_char[monsterSize - 1].HPbarPosition = 23;
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
						monster_char[monsterSize - 1].HPbarPosition = 35;
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
						monster_char[monsterSize - 1].HPbarPosition = 46;
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
						monster_char[monsterSize - 1].HPbarPosition = 42;
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
						monster_char[monsterSize - 1].HPbarPosition = 34;
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
						monster_char[monsterSize - 1].HPbarPosition = 49;
						monster_char[monsterSize - 1].sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
						sprintf(str1, "Wind9-");
					}
				}
				
				monster_char[monsterSize - 1]._turn = false;

				if (num2 % 2 == 0) {
					monster_char[monsterSize - 1].sprite->setPosition(128 * num1 + 66, 1632 - (160 + 96 * num2) + 32);
				}
				else {
					monster_char[monsterSize - 1].sprite->setPosition(62 + 128 * num1 + 66, 1632 - (160 + 96 * num2) + 32);
				}

				monster_char[monsterSize - 1].tx = num1;
				monster_char[monsterSize - 1].ty = num2;

				tmap->addChild(monster_char[monsterSize - 1].sprite, 3, monsterSize - 1);
				Sprite* st = Sprite::createWithSpriteFrameName("HP_bar.png");
				st->setPosition(0, -5);
				st->setScaleX(monster_char[monsterSize - 1].HPbarPosition / 25 * 2);
				st->setScaleY(2.0f);
				st->setAnchorPoint(Vec2(0, 0.5));
				monster_char[monsterSize - 1].sprite->addChild(st, 4, 1);

				Sprite* hp = Sprite::createWithSpriteFrameName("Monster_HP.png");
				hp->setPosition(0, -5);
				hp->setScaleX(monster_char[monsterSize - 1].HPbarPosition / 25 * 2);
				hp->setScaleY(2.0f);
				hp->setAnchorPoint(Vec2(0, 0.5));
				monster_char[monsterSize - 1].sprite->addChild(hp, 4, 2);

				char level[3];
				sprintf(level, "%d", monster_char[monsterSize - 1].level);
				auto pLabel3 = LabelAtlas::create(level, "Images/Scene/ML.png", 7, 9, '0');
				pLabel3->setAnchorPoint(Vec2(0, 0));
				pLabel3->setScale(2.0f);
				pLabel3->setPosition(Vec2(hp->getContentSize().width*(monster_char[monsterSize - 1].HPbarPosition / 25 * 2) + 5, -10));
				monster_char[monsterSize - 1].sprite->addChild(pLabel3, 4, 3);

				Sprite* End = Sprite::createWithSpriteFrameName("End.png");
				End->setAnchorPoint(Vec2(0, 0));
				End->setPosition(Vec2(0, 0));
				End->setScale(2.0f);
				monster_char[monsterSize - 1].sprite->addChild(End, 4, 4);

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
					tmap->removeChild(MovePosition.at(i));
				}
				MovePosition.clear();

				if (createPosSize != 0) {
					free(createMonsterPos);
					createPosSize = 0;
				}

				//주인공 턴종료
				End = Sprite::createWithSpriteFrameName("End.png");
				End->setAnchorPoint(Vec2(0, 0));
				End->setPosition(Vec2(0, 0));
				End->setScale(2.0f);
				monster_char[0]._turn = false;
				monster_char[0].sprite->addChild(End, 4, 4);

				//턴종료
				if (!status) {
					Sprite* End = Sprite::createWithSpriteFrameName("End.png");
					End->setAnchorPoint(Vec2(0, 0));
					End->setPosition(Vec2(0, 0));
					End->setScale(2.0f);
					monster_char[mons]._turn = false;
					monster_char[mons].sprite->addChild(End, 4, 4);
					ReturnState = false;
				}
			}
		}
		return;
	}

	//소환, 도구 다이얼로그 창 띄워져 있을 경우
	if (!touchMove) {
		return;
	}
	
	//myTouch(대기, 소환, 도구, 취소)
	if (status) {
		//대기
		touchPoint.x = touchPoint.x - MovePositionX;
		touchPoint.y = touchPoint.y - MovePositionY;
		bool bTouch1 = EndButton->getBoundingBox().containsPoint(touchPoint);
		if (bTouch1) {
			CharacterClick = false;
			status = false;

			for (int i = 0; i < EmyMovePosition.size(); i++) {
				tmap->removeChild(EmyMovePosition.at(i));
			}
			EmyMovePosition.clear();
			for (int i = 0; i < MovePosition.size(); i++) {
				tmap->removeChild(MovePosition.at(i));
			}
			MovePosition.clear();

			//턴종료
			if (!status) {
				Sprite* End = Sprite::createWithSpriteFrameName("End.png");
				End->setAnchorPoint(Vec2(0, 0));
				End->setPosition(Vec2(0, 0));
				End->setScale(2.0f);
				monster_char[mons]._turn = false;
				monster_char[mons].sprite->addChild(End, 4, 4);
				ReturnState = false;
			}
		}
		if (statuschar) {
			//소환
			bool bTouch2 = createMonster->getBoundingBox().containsPoint(touchPoint);
			if (bTouch2) {
				//소환위치 체크
				if (!CreateMonsterPositionCheck()) {
					return;
				}
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
		
		
		//취소
		bool bTouch4 = cancel->getBoundingBox().containsPoint(touchPoint);
		if (bTouch4) {
			status = false;
			CharacterClick = false;
			for (int i = 0; i < EmyMovePosition.size(); i++) {
				tmap->removeChild(EmyMovePosition.at(i));
			}
			EmyMovePosition.clear();
			for (int i = 0; i < MovePosition.size(); i++) {
				tmap->removeChild(MovePosition.at(i));
			}
			MovePosition.clear();
			//return move 저장
			if (ReturnState) {
				monster_char[mons].tx = ReturnMove_tx;
				monster_char[mons].ty = ReturnMove_ty;
				ReturnState = false;
			}
			Vec2 posit = FindCoordPosition(Vec2(monster_char[mons].tx, monster_char[mons].ty));
			monster_char[mons].sprite->setPosition(Vec2(posit.x - MovePositionX, posit.y - 60 - MovePositionY));
		}
		
		if (!status) {
			tmap->removeChild(EndButton);
			tmap->removeChild(createMonster);
			tmap->removeChild(Items);
			tmap->removeChild(cancel);
		}
		return;
	}
	
	//공격가능 적 클릭(공격, 디스펠, 취소)
	if (statusAttack) {
		//공격
		touchPoint.x = touchPoint.x - MovePositionX;
		touchPoint.y = touchPoint.y - MovePositionY;
		bool bTouch2 = attack->getBoundingBox().containsPoint(touchPoint);
		//log("minx = %f, maxx = %f, minx = %f, miny = %f", attack->getBoundingBox().getMinX(), attack->getBoundingBox().getMaxX(), attack->getBoundingBox().getMinY(), attack->getBoundingBox().getMaxY());
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
			int atkdamage = monster_char[mons].atk;
			if (monster_char[mons].Item1 != -1) {
				if (monster_char[mons].Item1 == 0) {
					atkdamage += 30;
				}
				else if (monster_char[mons].Item1 == 1) {
					atkdamage += 60;
				}
				else if (monster_char[mons].Item1 == 2) {
					atkdamage += 90;
				}
			}
			if (monster_char[mons].Item2 != -1) {
				if (monster_char[mons].Item2 == 0) {
					atkdamage += 30;
				}
				else if (monster_char[mons].Item2 == 1) {
					atkdamage += 60;
				}
				else if (monster_char[mons].Item2 == 2) {
					atkdamage += 90;
				}
			}
			if (monster_char[mons].Item3 != -1) {
				if (monster_char[mons].Item3 == 0) {
					atkdamage += 30;
				}
				else if (monster_char[mons].Item3 == 1) {
					atkdamage += 60;
				}
				else if (monster_char[mons].Item3 == 2) {
					atkdamage += 90;
				}
			}
			attackdamage = (atkdamage * bufDamage) - (EmyMonster_char[ClickEmyMonster].def * bufDefense);
			//log("damage = %d, monster_char[mons].atk = %d, bufDamage = %f, EmyMonster_char[ClickEmyMonster].def = %d, bufDefense = %f",
				//damage, monster_char[mons].atk, bufDamage, EmyMonster_char[ClickEmyMonster].def, bufDefense);
			if (attackdamage > 0) {
				//공격액션
				Vec2 vec1 = FindCoordPosition(Vec2(monster_char[mons].tx, monster_char[mons].ty));
				Vec2 vec2 = FindCoordPosition(Vec2(EmyMonster_char[ClickEmyMonster].tx, EmyMonster_char[ClickEmyMonster].ty));
				if (vec1.x < vec2.x)	L_R = false;
				else 					L_R = true;
				AttackAction();

				
			}
			statusAttack = false;
			//적 몬스터 타일 지우기
			for (int i = 0; i < EmyMovePosition.size(); i++) {
				tmap->removeChild(EmyMovePosition.at(i));
			}
			EmyMovePosition.clear();
			//
			for (int i = 0; i < MovePosition.size(); i++) {
				tmap->removeChild(MovePosition.at(i));
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
				m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/create.wav");
				char str1[100];
				char str2[100];

				int num1 = EmyMonster_char[ClickEmyMonster].tx;
				int num2 = EmyMonster_char[ClickEmyMonster].ty;

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
					st->setPosition(128 * num1 + 66, 1632 - (160 + 96 * num2) + 32);
				}
				else {
					st->setPosition(62 + 128 * num1 + 66, 1632 - (160 + 96 * num2) + 32);
				}

				auto animation = Animation::createWithSpriteFrames(animFrame, 0.1f);
				auto animate = Animate::create(animation);
				auto cbSound = CallFunc::create(CC_CALLBACK_0(EarthMap::RemoveSprite, this));
				auto seq = Sequence::create(animate, cbSound, NULL);
				st->runAction(seq);
				tmap->addChild(st, 5);

				//잡은몬스터 저장
				DistelMonsterSave(&EmyMonster_char[ClickEmyMonster]);

				tmap->removeChild(EmyMonster_char[ClickEmyMonster].sprite);
				for (int k = ClickEmyMonster; k < EmyMonsterSize - 1; k++) {
					EmyMonster_char[k] = EmyMonster_char[k + 1];
				}
				EmyMonster_char = (Monster_num*)realloc(EmyMonster_char, sizeof(Monster_num) * (EmyMonsterSize - 1));
				EmyMonsterSize--;

				ExpCheck();

				if (!EmyMonsterSize) {
					log("적군 몬스터 전멸");
					//적군 몬스터 전멸
					m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/GameEnd.wav");
					EndGame(1);
					return;
				}
			}
			else {
				//fall
				m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/sell.wav");
			}
			statusAttack = false;
			for (int i = 0; i < EmyMovePosition.size(); i++) {
				tmap->removeChild(EmyMovePosition.at(i));
			}
			EmyMovePosition.clear();
			for (int i = 0; i < MovePosition.size(); i++) {
				tmap->removeChild(MovePosition.at(i));
			}
			MovePosition.clear();


			//턴종료
			if (!statusAttack) {
				Sprite* End = Sprite::createWithSpriteFrameName("End.png");
				End->setAnchorPoint(Vec2(0, 0));
				End->setPosition(Vec2(0, 0));
				End->setScale(2.0f);
				monster_char[mons]._turn = false;
				monster_char[mons].sprite->addChild(End, 4, 4);
			}
		}

		

		bool bTouch4 = cancel->getBoundingBox().containsPoint(touchPoint);
		if (bTouch4) {
			statusAttack = false;
			CharacterClick = true;
		}


		if (!statusAttack) {
			tmap->removeChild(attack);
			tmap->removeChild(dispel);
			tmap->removeChild(cancel);

		}
		return;
	}
	
	//자기자신이 클릭상태일 경우
	if (CharacterClick) {
		Vec2 mon_pos = Vec2(monster_char[mons].tx, monster_char[mons].ty);
		ToolUseMonster = mons + 1;
		//자기자신을 클릭시 (도구, 소환, 취소)
		if (m_pos == mon_pos) {
			if (monster_char[mons].Type == 0) {
				status = true;
				statuschar = true;
				//log("소환, 도구");
				//대기
				EndButton = Sprite::create("Images/Scene/endbutton.png");
				Vec2 posit = FindCoordPosition(Vec2(monster_char[mons].tx, monster_char[mons].ty));
				EndButton->setPosition(Vec2(posit.x - MovePositionX, posit.y - 60 - MovePositionY + 75));
				EndButton->setScale(2.0f);
				tmap->addChild(EndButton, 6);
				//create 도구
				Items = Sprite::create("Images/Scene/Itemsbutton.png");
				Items->setPosition(Vec2(posit.x - MovePositionX, posit.y - 60 - MovePositionY + 25));
				Items->setScale(2.0f);
				tmap->addChild(Items, 6);
				//create 소환
				createMonster = Sprite::create("Images/Scene/createMonsterbutton.png");
				createMonster->setPosition(Vec2(posit.x - MovePositionX, posit.y - 60 - MovePositionY - 23));
				createMonster->setScale(2.0f);
				tmap->addChild(createMonster, 6);
				//create 취소
				cancel = Sprite::create("Images/Scene/cancelbutton.png");
				cancel->setPosition(Vec2(posit.x - MovePositionX, posit.y - 60 - MovePositionY - 73));
				cancel->setScale(2.0f);
				tmap->addChild(cancel, 6);

			}
			else {

				//log("도구");
				status = true;
				statuschar = false;
				//대기
				EndButton = Sprite::create("Images/Scene/endbutton.png");
				Vec2 posit = FindCoordPosition(Vec2(monster_char[mons].tx, monster_char[mons].ty));
				EndButton->setPosition(Vec2(posit.x - MovePositionX, posit.y - 60 - MovePositionY + 50));
				EndButton->setScale(2.0f);
				tmap->addChild(EndButton, 6);
				//create 도구
				Items = Sprite::create("Images/Scene/Itemsbutton.png");
				Items->setPosition(Vec2(posit.x - MovePositionX, posit.y - 60 - MovePositionY));
				Items->setScale(2.0f);
				tmap->addChild(Items, 6);
				//create 취소
				cancel = Sprite::create("Images/Scene/cancelbutton.png");
				cancel->setPosition(Vec2(posit.x - MovePositionX, posit.y - 60 - MovePositionY - 50));
				cancel->setScale(2.0f);
				tmap->addChild(cancel, 6);
			}
			VPosX = mon_pos.x;
			VPosY = mon_pos.y;

			return;
		}
		
		//공격 범위내 적군몬스터 클릭시 (공격, 디스펠)
		else if (checkEmyMonsterCoordinate(m_pos, EmyMonster_char, EmyMonsterSize)) {
			//데미지 계산

			//주인공이 적군 몬스터를 공격, 디스펠 할 경우
			if (mons == 0) {
				//log("공격, 디스펠");
				statusAttack = true;
				//create 공격
				attack = Sprite::create("Images/Scene/attackbutton.png");
				Vec2 posit = FindCoordPosition(Vec2(EmyMonster_char[ClickEmyMonster].tx, EmyMonster_char[ClickEmyMonster].ty));
				attack->setPosition(Vec2(posit.x - MovePositionX, posit.y - 60 - MovePositionY + 26));
				attack->setScale(2.0f);
				tmap->addChild(attack, 6);
				//create 디스펠
				dispel = Sprite::create("Images/Scene/dispelButton.png");
				dispel->setPosition(Vec2(posit.x - MovePositionX, posit.y - 60 - MovePositionY - 26));
				dispel->setScale(2.0f);
				tmap->addChild(dispel, 6);
				//create 취소
				cancel = Sprite::create("Images/Scene/cancelbutton.png");
				cancel->setPosition(Vec2(posit.x - MovePositionX, posit.y - 60 - MovePositionY - 76));
				cancel->setScale(2.0f);
				tmap->addChild(cancel, 6);
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
				int atkdamage = monster_char[mons].atk;
				if (monster_char[mons].Item1 != -1) {
					if (monster_char[mons].Item1 == 0) {
						atkdamage += 30;
					}
					else if (monster_char[mons].Item1 == 1) {
						atkdamage += 60;
					}
					else if (monster_char[mons].Item1 == 2) {
						atkdamage += 90;
					}
				}
				if (monster_char[mons].Item2 != -1) {
					if (monster_char[mons].Item2 == 0) {
						atkdamage += 30;
					}
					else if (monster_char[mons].Item2 == 1) {
						atkdamage += 60;
					}
					else if (monster_char[mons].Item2 == 2) {
						atkdamage += 90;
					}
				}
				if (monster_char[mons].Item3 != -1) {
					if (monster_char[mons].Item3 == 0) {
						atkdamage += 30;
					}
					else if (monster_char[mons].Item3 == 1) {
						atkdamage += 60;
					}
					else if (monster_char[mons].Item3 == 2) {
						atkdamage += 90;
					}
				}
				attackdamage = (atkdamage * bufDamage) - (EmyMonster_char[ClickEmyMonster].def * bufDefense);
				//log("damage = %d, monster_char[mons].atk = %d, bufDamage = %f, EmyMonster_char[ClickEmyMonster].def = %d, bufDefense = %f",
				//damage, monster_char[mons].atk, bufDamage, EmyMonster_char[ClickEmyMonster].def, bufDefense);
				if (attackdamage > 0) {
					Vec2 vec1 = FindCoordPosition(Vec2(monster_char[mons].tx, monster_char[mons].ty));
					Vec2 vec2 = FindCoordPosition(Vec2(EmyMonster_char[ClickEmyMonster].tx, EmyMonster_char[ClickEmyMonster].ty));
					if (vec1.x < vec2.x)	L_R = false;
					else 					L_R = true;
					AttackAction();

					//EmyMonster_char[ClickEmyMonster].hp -= damage;
					//EmyMonster_char[ClickEmyMonster].sprite->removeChildByTag(2);
					//Sprite* hp = Sprite::createWithSpriteFrameName("EmyMonseter_HP.png");
					//hp->setPosition(2, -5);
					//hp->setScaleX((EmyMonster_char[ClickEmyMonster].HPbarPosition / 25 * 2) * EmyMonster_char[ClickEmyMonster].hp / EmyMonster_char[ClickEmyMonster].Fullhp);
					////hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
					//hp->setAnchorPoint(Vec2(0, 0.5));
					//EmyMonster_char[ClickEmyMonster].sprite->addChild(hp, 4, 2);

					//if (EmyMonster_char[ClickEmyMonster].hp < 0) {
					//	EmyMonster_char[ClickEmyMonster].hp = 0;
					//	//적 몬스터 죽음 처리
					//	tmap->removeChild(EmyMonster_char[ClickEmyMonster].sprite);
					//	for (int k = ClickEmyMonster; k < EmyMonsterSize - 1; k++) {
					//		EmyMonster_char[k] = EmyMonster_char[k + 1];
					//	}
					//	EmyMonster_char = (Monster_num*)realloc(EmyMonster_char, sizeof(Monster_num) * (EmyMonsterSize - 1));
					//	EmyMonsterSize--;

					//	ExpCheck();

					//	Coin += 2;

					//	if (!EmyMonsterSize) {
					//		log("적군 몬스터 전멸");
					//		//적군 몬스터 전멸
					//		EndGame(1);
					//		return;
					//	}
					//}
				}
				statusAttack = false;
				//적 몬스터 타일 지우기
				for (int i = 0; i < EmyMovePosition.size(); i++) {
					tmap->removeChild(EmyMovePosition.at(i));
				}
				EmyMovePosition.clear();
				//
				for (int i = 0; i < MovePosition.size(); i++) {
					tmap->removeChild(MovePosition.at(i));
				}
				MovePosition.clear();

				//턴종료
				if (!statusAttack) {
					Sprite* End = Sprite::createWithSpriteFrameName("End.png");
					End->setAnchorPoint(Vec2(0, 0));
					End->setPosition(Vec2(0, 0));
					End->setScale(2.0f);
					monster_char[mons]._turn = false;
					monster_char[mons].sprite->addChild(End, 4, 4);
				}
			}
			CharacterClick = false;
			return;
		}
		
		//아군몬스터 범위내 클릭시 (경로 이동)
		else if (checkcoordinate(m_pos)) {
			
			//return move 저장
			ReturnState = true;
			ReturnMove_tx = monster_char[mons].tx;
			ReturnMove_ty = monster_char[mons].ty;

			SpriteCoordinateChange(m_pos, monster_char, mons);

			//이동 시작

			ShortistMove(m_pos, pos, posSize, &monster_char[mons]);

			//moving position 저장
			Moving_tx = monster_char[mons].tx;
			Moving_ty = monster_char[mons].ty;
			//이동 끝
			
			for (int i = 0; i < MovePosition.size(); i++) {
				tmap->removeChild(MovePosition.at(i), true);
			}

			//이동후 공격범위 내 적 몬스터가 있을 시 공격상태
			//공격가능 몬스터 타일표시
			DisplayEmyMonsterAttack(m_pos);
			CharacterClick = true;
		}
	}

	//아무런 상태가 아닐 경우
	else {
		//아군몬스터 선택시
		ReturnState = false;
		mons = -1;
		for (int m = 0; m < monsterSize; m++) {
			if (monster_char[m].tx == m_pos.x && monster_char[m].ty == m_pos.y) {
				if (monster_char[m]._turn) {
					mons = m;
					break;
				}
			}
		}
		if (mons == -1) {
			log("error::선택된 몬스터가 없습니다.");
			return;
		}
		else {
			log("mons = %d", mons);
		}
		Vec2 mon_pos = Vec2(monster_char[mons].tx, monster_char[mons].ty);
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
				tmap->removeChild(EmyMovePosition.at(i));
			}
			EmyMovePosition.clear();
			//
			for (int i = 0; i < MovePosition.size(); i++) {
				tmap->removeChild(MovePosition.at(i), true);
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
			pos = CheckPosition(mon_pos, pos, posSize, monster_char[mons].move, 1, monsterSize, monster_char, EmyMonsterSize, EmyMonster_char);
			posSize = GrobalTempsize;

			if (VecPositionSize) {
				free(VecPosition);
				VecPositionSize = 0;
			}
			//한칸
			for (int m = 0; m < posSize; m++) {
				Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
				if (MoveTileCheck(Vec2(pos[m].x, pos[m].y))) {
					Vec2 posit = FindCoordPosition(Vec2(pos[m].x, pos[m].y));
					sp->setPosition(posit.x - MovePositionX, posit.y - 60 - MovePositionY);
					tmap->addChild(sp);
					MovePosition.pushBack(sp);
				}
				//두칸
				if (pos[m].pos2Size) {
					for (int k = 0; k < pos[m].pos2Size; k++) {
						Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
						if (MoveTileCheck(Vec2(pos[m].pos2[k].x, pos[m].pos2[k].y))) {
							Vec2 posit2 = FindCoordPosition(Vec2(pos[m].pos2[k].x, pos[m].pos2[k].y));
							//log("pos[%d].pos2[%d] = %d", m, k, pos[m].pos2[k].num);
							sp->setPosition(posit2.x - MovePositionX, posit2.y - 60 - MovePositionY);
							tmap->addChild(sp);
							MovePosition.pushBack(sp);
						}
						
						//세칸
						if (pos[m].pos2[k].pos2Size) {
							for (int z = 0; z < pos[m].pos2[k].pos2Size; z++) {
								Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
								if (MoveTileCheck(Vec2(pos[m].pos2[k].pos2[z].x, pos[m].pos2[k].pos2[z].y))) {
									Vec2 posit2 = FindCoordPosition(Vec2(pos[m].pos2[k].pos2[z].x, pos[m].pos2[k].pos2[z].y));
									//log("pos[%d].pos2[%d].pos2[%d] = %d", m, k, z, pos[m].pos2[k].pos2[z].num);
									sp->setPosition(posit2.x - MovePositionX, posit2.y - 60 - MovePositionY);
									tmap->addChild(sp);
									MovePosition.pushBack(sp);
								}
								
								//네칸
								if (pos[m].pos2[k].pos2[z].pos2Size) {
									for (int i = 0; i < pos[m].pos2[k].pos2[z].pos2Size; i++) {
										Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
										if (MoveTileCheck(Vec2(pos[m].pos2[k].pos2[z].pos2[i].x, pos[m].pos2[k].pos2[z].pos2[i].y))) {
											Vec2 posit2 = FindCoordPosition(Vec2(pos[m].pos2[k].pos2[z].pos2[i].x, pos[m].pos2[k].pos2[z].pos2[i].y));
											//log("pos[%d].pos2[%d].pos2[%d].pos2[i] = %d", m, k, z, i, pos[m].pos2[k].pos2[z].pos2[i].num);
											sp->setPosition(posit2.x - MovePositionX, posit2.y - 60 - MovePositionY);
											tmap->addChild(sp);
											MovePosition.pushBack(sp);
										}
									}
								}
							}
						}
					}
				}
				
			}
			//클릭상태표시
			CharacterClick = true;
			
			//적 표시
			for (int m = 0; m < EmyposSize; m++) {
				Emypos[m].PositionView = false;
				//공격범위 1이상 체크
				if (monster_char[mons].range > 0) {
					if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty == Emypos[m].y) {
						Emypos[m].PositionView = true;
					}
					if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty == Emypos[m].y) {
						Emypos[m].PositionView = true;
					}
					if (monster_char[mons].tx == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
						Emypos[m].PositionView = true;
					}
					if (monster_char[mons].tx == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
						Emypos[m].PositionView = true;
					}
					if (monster_char[mons].ty % 2 == 0) {
						if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
						if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
					}
					else {
						if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
						if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
					}
					//공격범위 2일때 체크
					if (monster_char[mons].range > 1) {
						if (monster_char[mons].tx == Emypos[m].x && monster_char[mons].ty - 2 == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
						if (monster_char[mons].tx == Emypos[m].x && monster_char[mons].ty + 2 == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
						if (monster_char[mons].tx + 2 == Emypos[m].x && monster_char[mons].ty == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
						if (monster_char[mons].tx - 2 == Emypos[m].x && monster_char[mons].ty == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
						if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty - 2 == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
						if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty + 2 == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
						if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty - 2 == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
						if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty + 2 == Emypos[m].y) {
							Emypos[m].PositionView = true;
						}
						if (monster_char[mons].ty % 2 == 0) {
							if (monster_char[mons].tx - 2 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
							}
							if (monster_char[mons].tx - 2 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
							}
							if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
							}
							if (monster_char[mons].tx + 1 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
							}
						}
						else {
							if (monster_char[mons].tx + 2 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
							}
							if (monster_char[mons].tx + 2 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
							}
							if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty - 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
							}
							if (monster_char[mons].tx - 1 == Emypos[m].x && monster_char[mons].ty + 1 == Emypos[m].y) {
								Emypos[m].PositionView = true;
							}
						}
					}
				}
				
				if (Emypos[m].PositionView) {
					int type;
					type = EmyMonster_char[Emypos[m].num].Type;
					
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
					sp->setPosition(posit.x - MovePositionX, posit.y - 60 - MovePositionY);
					tmap->addChild(sp);
					EmyMovePosition.pushBack(sp);
				}
				
			}
			/*for (int i = 0; i < EmyMovePosition.size(); i++) {
				this->addChild(EmyMovePosition.at(i), 2);
			}*/
		}
	}
}

void EarthMap::AttackAction() {
	attackMonster = mons;
	log("%d", monster_char[attackMonster].sprite->getTag());
	monster_char[attackMonster].sprite->stopAllActions();
	monster_char[attackMonster].sprite->removeAllChildren();
	tmap->removeChild(monster_char[attackMonster].sprite, true);
	//L_R == true 왼쪽 false 오른쪽
	char str1[100];
	char str2[100];
	//Vector<SpriteFrame*> animFrames;
	char str3[100];
	char str4[100];
	Vector<SpriteFrame*> animFrames3;
	Sprite *sst = Sprite::create();
	Vector<SpriteFrame*> animFrames_Action;
	
	if (monster_char[attackMonster].Type == 0) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Person1-A1.png");
		sprintf(str1, "Person1-A");
		
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_firetornado.wav");
		sst = Sprite::createWithSpriteFrameName("fx_firetornado_000.png");
		sprintf(str3, "fx_firetornado_0");
		for (int i = 0; i <= 12; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//땅질퍽이
	if (monster_char[attackMonster].Type == 1) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth1-A1.png");
		sprintf(str1, "Earth1-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_smoke.wav");
		sst = Sprite::createWithSpriteFrameName("fx_smokeground_000.png");
		sprintf(str3, "fx_smokeground_0");
		for (int i = 0; i <= 7; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 2) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth2-A1.png");
		sprintf(str1, "Earth2-A");
		
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_smoke.wav");
		sst = Sprite::createWithSpriteFrameName("fx_explosiondarkplume_000.png");
		sprintf(str3, "fx_explosiondarkplume_0");
		for (int i = 0; i <= 8; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 3) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth3-A1.png");
		sprintf(str1, "Earth3-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_smoke.wav");
		sst = Sprite::createWithSpriteFrameName("fx_explosionwhitesmokemedium_000.png");
		sprintf(str3, "fx_explosionwhitesmokemedium_0");
		for (int i = 0; i <= 9; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//모닥픽
	else if (monster_char[attackMonster].Type == 4) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth4-A1.png");
		sprintf(str1, "Earth4-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_impactgreensmall_000.png");
		sprintf(str3, "fx_impactgreensmall_0");
		for (int i = 0; i <= 4; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 5) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth5-A1.png");
		sprintf(str1, "Earth5-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_impactgreenmedium_000.png");
		sprintf(str3, "fx_impactgreenmedium_0");
		for (int i = 0; i <= 5; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 6) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth6-A1.png");
		sprintf(str1, "Earth6-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_impactgreenbig_000.png");
		sprintf(str3, "fx_impactgreenbig_0");
		for (int i = 0; i <= 6; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//모래두지
	else if (monster_char[attackMonster].Type == 7) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth7-A1.png");
		sprintf(str1, "Earth7-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f5_earthsphere_000.png");
		sprintf(str3, "fx_f5_earthsphere_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 8) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth8-A1.png");
		sprintf(str1, "Earth8-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f5_earthsphere_000.png");
		sprintf(str3, "fx_f5_earthsphere_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 9) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth9-A1.png");
		sprintf(str1, "Earth9-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Earth/fx_impactgreen.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f5_earthsphere_000.png");
		sprintf(str3, "fx_f5_earthsphere_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//파이뤼
	else if (monster_char[attackMonster].Type == 11) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire1-A1.png");
		sprintf(str1, "Fire1-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_explosionorangesmoke.wav");
		sst = Sprite::createWithSpriteFrameName("fx_explosionorangesmoke_000.png");
		sprintf(str3, "fx_explosionorangesmoke_0");
		for (int i = 0; i <= 5; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 12) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire2-A1.png");
		sprintf(str1, "Fire2-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_whiteexplosion.wav");
		sst = Sprite::createWithSpriteFrameName("fx_whitehotmedium_000.png");
		sprintf(str3, "fx_whitehotmedium_0");
		for (int i = 0; i <= 8; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 13) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire3-A1.png");
		sprintf(str1, "Fire3-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_whiteexplosion.wav");
		sst = Sprite::createWithSpriteFrameName("fx_whitehotbig_000.png");
		sprintf(str3, "fx_whitehotbig_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//팬템
	else if (monster_char[attackMonster].Type == 14) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire4-A1.png");
		sprintf(str1, "Fire4-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_blood_explosion.wav");
		sst = Sprite::createWithSpriteFrameName("fx_bloodmedium_000.png");
		sprintf(str3, "fx_bloodmedium_0");
		for (int i = 0; i <= 9; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 15) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire5-A1.png");
		sprintf(str1, "Fire5-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_blood_explosion.wav");
		sst = Sprite::createWithSpriteFrameName("fx_bloodbig_000.png");
		sprintf(str3, "fx_bloodbig_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 16) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire6-A1.png");
		sprintf(str1, "Fire6-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_f2_eightgates_purpleflame.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f2_eightgates_purpleflame_000.png");
		sprintf(str3, "fx_f2_eightgates_purpleflame_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//블랙매직숀
	else if (monster_char[attackMonster].Type == 17) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire7-A1.png");
		sprintf(str1, "Fire7-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_f5_earthsphere_orange.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f5_earthsphere_orange_000.png");
		sprintf(str3, "fx_f5_earthsphere_orange_0");
		for (int i = 0; i <= 7; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 18) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire8-A1.png");
		sprintf(str1, "Fire8-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_f2_teleport.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f2_teleport_000.png");
		sprintf(str3, "fx_f2_teleport_0");
		for (int i = 0; i <= 7; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 19) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire9-A1.png");
		sprintf(str1, "Fire9-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Fire/fx_f2_twinstrike.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f2_twinstrike_000.png");
		sprintf(str3, "fx_f2_twinstrike_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//물질퍽이
	else if (monster_char[attackMonster].Type == 21) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water1-A1.png");
		sprintf(str1, "Water1-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_cleanse.wav");
		sst = Sprite::createWithSpriteFrameName("fx_cleanse_ripples_000.png");
		sprintf(str3, "fx_cleanse_ripples_0");
		for (int i = 0; i <= 6; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 22) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water2-A1.png");
		sprintf(str1, "Water2-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_f6_spiritofthewild.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f6_spiritofthewild_000.png");
		sprintf(str3, "fx_f6_spiritofthewild_0");
		for (int i = 0; i <= 8; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 23) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water3-A1.png");
		sprintf(str1, "Water3-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_f6_spiritofthewild.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f6_spiritofthewild_000.png");
		sprintf(str3, "fx_f6_spiritofthewild_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//꼬북이
	else if (monster_char[attackMonster].Type == 24) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water4-A1.png");
		sprintf(str1, "Water4-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_cleanse.wav");
		sst = Sprite::createWithSpriteFrameName("fx_cleanse_ripples_000.png");
		sprintf(str3, "fx_cleanse_ripples_0");
		for (int i = 0; i <= 6; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 25) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water5-A1.png");
		sprintf(str1, "Water5-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_teleportblueorb.wav");
		sst = Sprite::createWithSpriteFrameName("fx_teleportblueorb_000.png");
		sprintf(str3, "fx_teleportblueorb_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 26) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water6-A1.png");
		sprintf(str1, "Water6-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_distortion_hex_shield.wav");
		sst = Sprite::createWithSpriteFrameName("distortion_hex_shield_000.png");
		sprintf(str3, "distortion_hex_shield_0");
		for (int i = 0; i <= 9; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//리아커
	else if (monster_char[attackMonster].Type == 27) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water7-A1.png");
		sprintf(str1, "Water7-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_cleanse.wav");
		sst = Sprite::createWithSpriteFrameName("fx_cleanse_ripples_000.png");
		sprintf(str3, "fx_cleanse_ripples_0");
		for (int i = 0; i <= 6; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 28) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water8-A1.png");
		sprintf(str1, "Water8-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_f6_cryogenesis.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f6_cryogenesis_000.png");
		sprintf(str3, "fx_f6_cryogenesis_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 29) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water9-A1.png");
		sprintf(str1, "Water9-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Water/fx_f3_fountainofyouth.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f3_fountainofyouth_000.png");
		sprintf(str3, "fx_f3_fountainofyouth_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//코이
	else if (monster_char[attackMonster].Type == 31) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind1-A1.png");
		sprintf(str1, "Wind1-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_f2_spiraltechnique02.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f2_spiraltechnique02_000.png");
		sprintf(str3, "fx_f2_spiraltechnique02_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 32) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind2-A1.png");
		sprintf(str1, "Wind2-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_blueplasma_vertical.wav");
		sst = Sprite::createWithSpriteFrameName("fx_blueplasma_vertical_000.png");
		sprintf(str3, "fx_blueplasma_vertical_0");
		for (int i = 0; i <= 7; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 33) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind3-A1.png");
		sprintf(str1, "Wind3-A");
		
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_f1_decimate.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f1_decimate_000.png");
		sprintf(str3, "fx_f1_decimate_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//피젼
	else if (monster_char[attackMonster].Type == 34) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind4-A1.png");
		sprintf(str1, "Wind4-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_clawslash.wav");
		sst = Sprite::createWithSpriteFrameName("fx_clawslash_000.png");
		sprintf(str3, "fx_clawslash_0");
		for (int i = 0; i <= 4; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 35) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind5-A1.png");
		sprintf(str1, "Wind5-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_bluewatersplash.wav");
		sst = Sprite::createWithSpriteFrameName("fx_bluewatersplash_000.png");
		sprintf(str3, "fx_bluewatersplash_0");
		for (int i = 0; i <= 8; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 36) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind6-A1.png");
		sprintf(str1, "Wind6-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_f1_casterprojectile.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f1casterprojectile_000.png");
		sprintf(str3, "fx_f1casterprojectile_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	//토게피
	else if (monster_char[attackMonster].Type == 37) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind7-A1.png");
		sprintf(str1, "Wind7-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_bladestorm.wav");
		sst = Sprite::createWithSpriteFrameName("fx_bladestorm_000.png");
		sprintf(str3, "fx_bladestorm_0");
		for (int i = 0; i <= 11; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 38) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind8-A1.png");
		sprintf(str1, "Wind8-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_f1_lionheartblessing.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f1_lionheartblessing_000.png");
		sprintf(str3, "fx_f1_lionheartblessing_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	else if (monster_char[attackMonster].Type == 39) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind9-A1.png");
		sprintf(str1, "Wind9-A");

		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/Wind/fx_f1_circlelife.wav");
		sst = Sprite::createWithSpriteFrameName("fx_f1_circlelife_000.png");
		sprintf(str3, "fx_f1_circlelife_0");
		for (int i = 0; i <= 13; i++) {
			sprintf(str4, "%s%02d.png", str3, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str4);
			animFrames3.pushBack(frame);
		}
	}
	
	if(L_R) {
		if (mons == 0) {
			for (int i = 1; i <= 4; i++) {
				sprintf(str2, "%s%d.png", str1, i);
				SpriteFrame* frame = cache->getSpriteFrameByName(str2);
				animFrames_Action.pushBack(frame);
			}
		}
		else {
			for (int i = 1; i <= 3; i++) {
				sprintf(str2, "%s%d.png", str1, i);
				SpriteFrame* frame = cache->getSpriteFrameByName(str2);
				animFrames_Action.pushBack(frame);
			}
		}

		
	}
	else {
		if (mons == 0) {
			for (int i = 5; i <= 8; i++) {
				sprintf(str2, "%s%d.png", str1, i);
				SpriteFrame* frame = cache->getSpriteFrameByName(str2);
				animFrames_Action.pushBack(frame);
			}
		}
		else {
			for (int i = 4; i <= 6; i++) {
				sprintf(str2, "%s%d.png", str1, i);
				SpriteFrame* frame = cache->getSpriteFrameByName(str2);
				animFrames_Action.pushBack(frame);
			}
		}
		
	}
	
	//공격 사용 스킬 액션
	auto animation2 = Animation::createWithSpriteFrames(animFrames3, 0.1f);
	auto animate2 = Animate::create(animation2);
	sst->runAction(animate2);
	if (monster_char[attackMonster].Type == 22 || monster_char[attackMonster].Type == 23 || monster_char[attackMonster].Type == 28) {
		sst->setScale(0.5f);
	}
	else if (monster_char[attackMonster].Type == 16 || monster_char[attackMonster].Type == 17 || monster_char[attackMonster].Type == 19 || monster_char[attackMonster].Type == 26 || monster_char[attackMonster].Type == 38) {
		sst->setScale(1.0f);
	}
	else {
		sst->setScale(2.0f);
	}
	Vec2 Vector1 = FindCoordPosition(Vec2(EmyMonster_char[ClickEmyMonster].tx, EmyMonster_char[ClickEmyMonster].ty));
	sst->setPosition(Vec2(Vector1.x - MovePositionX, Vector1.y - 60 - MovePositionY));
	tmap->addChild(sst, 5, 500);



	auto animation0 = Animation::createWithSpriteFrames(animFrames_Action, 0.2f);
	auto animate0 = Animate::create(animation0);
	
	monster_char[attackMonster].sprite->runAction(animate0);
	Vec2 Vector = FindCoordPosition(Vec2(monster_char[attackMonster].tx, monster_char[attackMonster].ty));
		//posit.x - MovePositionX,		posit.y - 60 - MovePositionY
	monster_char[attackMonster].sprite->setPosition(Vec2(Vector.x - MovePositionX, Vector.y - 60 - MovePositionY));
	tmap->addChild(monster_char[attackMonster].sprite, 5, mons);

	//다시 걸어다니는 액션으로 교체
	this->scheduleOnce(schedule_selector(EarthMap::callbackrepeatforever), 1.4f);
	
}

void EarthMap::callbackrepeatforever(float delta) {
	//log("%d", monster_char[attackMonster].sprite->getTag());
	monster_char[attackMonster].sprite->stopAllActions();
	monster_char[attackMonster].sprite->removeAllChildren();
	tmap->removeChild(monster_char[attackMonster].sprite, true);
	//공격효과액션 삭제
	tmap->removeChildByTag(500);
	//L_R == true 왼쪽 false 오른쪽
	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;
	Vector<SpriteFrame*> animFrames_Action;
	if (monster_char[attackMonster].Type == 0) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
	}
	if (monster_char[attackMonster].Type == 1) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth1-1.png");
		sprintf(str1, "Earth1-");
	}
	else if (monster_char[attackMonster].Type == 2) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth2-1.png");
		sprintf(str1, "Earth2-");
	}
	else if (monster_char[attackMonster].Type == 3) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth3-1.png");
		sprintf(str1, "Earth3-");
	}
	//모닥픽
	else if (monster_char[attackMonster].Type == 4) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth4-1.png");
		sprintf(str1, "Earth4-");
	}
	else if (monster_char[attackMonster].Type == 5) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth5-1.png");
		sprintf(str1, "Earth5-");
	}
	else if (monster_char[attackMonster].Type == 6) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth6-1.png");
		sprintf(str1, "Earth6-");
	}
	//모래두지
	else if (monster_char[attackMonster].Type == 7) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth7-1.png");
		sprintf(str1, "Earth7-");
	}
	else if (monster_char[attackMonster].Type == 8) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth8-1.png");
		sprintf(str1, "Earth8-");
	}
	else if (monster_char[attackMonster].Type == 9) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Earth9-1.png");
		sprintf(str1, "Earth9-");
	}
	//파이뤼
	else if (monster_char[attackMonster].Type == 11) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire1-1.png");
		sprintf(str1, "Fire1-");
	}
	else if (monster_char[attackMonster].Type == 12) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire2-1.png");
		sprintf(str1, "Fire2-");
	}
	else if (monster_char[attackMonster].Type == 13) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire3-1.png");
		sprintf(str1, "Fire3-");
	}
	//팬템
	else if (monster_char[attackMonster].Type == 14) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire4-1.png");
		sprintf(str1, "Fire4-");
	}
	else if (monster_char[attackMonster].Type == 15) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire5-1.png");
		sprintf(str1, "Fire5-");
	}
	else if (monster_char[attackMonster].Type == 16) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire6-1.png");
		sprintf(str1, "Fire6-");
	}
	//블랙매직숀
	else if (monster_char[attackMonster].Type == 17) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire7-1.png");
		sprintf(str1, "Fire7-");
	}
	else if (monster_char[attackMonster].Type == 18) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire8-1.png");
		sprintf(str1, "Fire8-");
	}
	else if (monster_char[attackMonster].Type == 19) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Fire9-1.png");
		sprintf(str1, "Fire9-");
	}
	//물질퍽이
	else if (monster_char[attackMonster].Type == 21) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water1-1.png");
		sprintf(str1, "Water1-");
	}
	else if (monster_char[attackMonster].Type == 22) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water2-1.png");
		sprintf(str1, "Water2-");
	}
	else if (monster_char[attackMonster].Type == 23) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water3-1.png");
		sprintf(str1, "Water3-");
	}
	//꼬북이
	else if (monster_char[attackMonster].Type == 24) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water4-1.png");
		sprintf(str1, "Water4-");
	}
	else if (monster_char[attackMonster].Type == 25) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water5-1.png");
		sprintf(str1, "Water5-");
	}
	else if (monster_char[attackMonster].Type == 26) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water6-1.png");
		sprintf(str1, "Water6-");
	}
	//리아커
	else if (monster_char[attackMonster].Type == 27) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water7-1.png");
		sprintf(str1, "Water7-");
	}
	else if (monster_char[attackMonster].Type == 28) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water8-1.png");
		sprintf(str1, "Water8-");
	}
	else if (monster_char[attackMonster].Type == 29) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Water9-1.png");
		sprintf(str1, "Water9-");
	}
	//코이
	else if (monster_char[attackMonster].Type == 31) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind1-1.png");
		sprintf(str1, "Wind1-");
	}
	else if (monster_char[attackMonster].Type == 32) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind2-1.png");
		sprintf(str1, "Wind2-");
	}
	else if (monster_char[attackMonster].Type == 33) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind3-1.png");
		sprintf(str1, "Wind3-");
	}
	//피젼
	else if (monster_char[attackMonster].Type == 34) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind4-1.png");
		sprintf(str1, "Wind4-");
	}
	else if (monster_char[attackMonster].Type == 35) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind5-1.png");
		sprintf(str1, "Wind5-");
	}
	else if (monster_char[attackMonster].Type == 36) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind6-1.png");
		sprintf(str1, "Wind6-");
	}
	//코이
	else if (monster_char[attackMonster].Type == 37) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind7-1.png");
		sprintf(str1, "Wind7-");
	}
	else if (monster_char[attackMonster].Type == 38) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind8-1.png");
		sprintf(str1, "Wind8-");
	}
	else if (monster_char[attackMonster].Type == 39) {
		monster_char[attackMonster].sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
		sprintf(str1, "Wind9-");
	}

	if (L_R) {
		for (int i = 1; i <= 4; i++) {
			sprintf(str2, "%s%d.png", str1, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str2);
			animFrames.pushBack(frame);
		}
	}
	else {
		for (int i = 5; i <= 8; i++) {
			sprintf(str2, "%s%d.png", str1, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str2);
			animFrames.pushBack(frame);
		}
	}

	auto animation1 = Animation::createWithSpriteFrames(animFrames, 0.2f);
	auto animate1 = Animate::create(animation1);
	auto rep1 = RepeatForever::create(animate1);

	monster_char[attackMonster].sprite->runAction(rep1);
	Vec2 Vector = FindCoordPosition(Vec2(monster_char[attackMonster].tx, monster_char[attackMonster].ty));
	//posit.x - MovePositionX, posit.y - 60 - MovePositionY
	monster_char[attackMonster].sprite->setPosition(Vec2(Vector.x - MovePositionX, Vector.y - 60 - MovePositionY));
	tmap->addChild(monster_char[attackMonster].sprite, 5, mons);

	Sprite* st = Sprite::createWithSpriteFrameName("HP_bar.png");
	st->setPosition(0, -5);
	st->setScaleX(monster_char[attackMonster].HPbarPosition / 25 * 2);
	st->setScaleY(2.0f);
	st->setAnchorPoint(Vec2(0, 0.5));
	monster_char[attackMonster].sprite->addChild(st, 4, 1);

	Sprite* hp = Sprite::createWithSpriteFrameName("Monster_HP.png");
	hp->setPosition(0, -5);
	hp->setScaleX((monster_char[attackMonster].HPbarPosition / 25 * 2) * monster_char[attackMonster].hp / monster_char[attackMonster].Fullhp);
	hp->setScaleY(2.0f);
	hp->setAnchorPoint(Vec2(0, 0.5));
	monster_char[attackMonster].sprite->addChild(hp, 4, 2);

	char level[3];
	sprintf(level, "%d", monster_char[attackMonster].level);
	auto pLabel3 = LabelAtlas::create(level, "Images/Scene/ML.png", 7, 9, '0');
	pLabel3->setAnchorPoint(Vec2(0, 0));
	pLabel3->setScale(2.0f);
	pLabel3->setPosition(Vec2(st->getContentSize().width*(monster_char[attackMonster].HPbarPosition / 25 * 2) + 5, -10));
	monster_char[attackMonster].sprite->addChild(pLabel3, 4, 3);

	EmyMonster_char[ClickEmyMonster].hp -= attackdamage;
	EmyMonster_char[ClickEmyMonster].sprite->removeChildByTag(2);
	hp = Sprite::createWithSpriteFrameName("EmyMonseter_HP.png");
	hp->setPosition(2, -5);
	hp->setScaleX((EmyMonster_char[ClickEmyMonster].HPbarPosition / 25 * 2) * EmyMonster_char[ClickEmyMonster].hp / EmyMonster_char[ClickEmyMonster].Fullhp);
	//hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
	hp->setAnchorPoint(Vec2(0, 0.5));
	EmyMonster_char[ClickEmyMonster].sprite->addChild(hp, 4, 2);

	if (EmyMonster_char[ClickEmyMonster].hp < 0) {
		EmyMonster_char[ClickEmyMonster].hp = 0;
		//적 몬스터 죽음 처리
		tmap->removeChild(EmyMonster_char[ClickEmyMonster].sprite);
		for (int k = ClickEmyMonster; k < EmyMonsterSize - 1; k++) {
			EmyMonster_char[k] = EmyMonster_char[k + 1];
		}
		EmyMonster_char = (Monster_num*)realloc(EmyMonster_char, sizeof(Monster_num) * (EmyMonsterSize - 1));
		EmyMonsterSize--;
		Coin += 2;
		ExpCheck();
		if (!EmyMonsterSize) {
			log("적군 몬스터 전멸");
			//적군 몬스터 전멸
			m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("snd/etc/GameEnd.wav");
			EndGame(1);
			return;
		}
	}
	//턴종료
	if (!statusAttack) {
		Sprite* End = Sprite::createWithSpriteFrameName("End.png");
		End->setAnchorPoint(Vec2(0, 0));
		End->setPosition(Vec2(0, 0));
		End->setScale(2.0f);
		monster_char[attackMonster]._turn = false;
		monster_char[attackMonster].sprite->addChild(End, 4, 4);
	}
}

void EarthMap::MonsterAdd(int num, Sprite *st) {

	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;
	if (Monster_List[num].Type == 0) {
		Monster_List[num].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
	}
	//땅질퍽이
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
	Monster_List[num].sprite->setPosition(Vec2(st->getContentSize().width / 2, st->getContentSize().height / 2));

	st->addChild(Monster_List[num].sprite, 3);


	char level[3];
	sprintf(level, "%d", Monster_List[num].level);
	auto pLabel3 = LabelAtlas::create(level, "Images/Scene/ML.png", 7, 9, '0');
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

bool EarthMap::CreateMonsterPositionCheck() {
	if (createPosSize) {
		free(createMonsterPos);
	}
	VPos = Vec2(VPosX, VPosY);
	createPosSize = 0;
	createMonsterPos = CheckPosition(VPos, createMonsterPos, createPosSize, 1, 0, monsterSize, monster_char, EmyMonsterSize, EmyMonster_char);
	createPosSize = GrobalTempsize;

	if (!createPosSize) {
		//소환할 위치가 없습니다.
		log("소환할 위치가 없습니다.");
		MenuItemFont::setFontSize(24);
		Sprite *BG_tex = Sprite::create("Images/Scene/TexScene2.png");
		BG_tex->setAnchorPoint(Vec2(0.5, 0.5));
		BG_tex->setScale(2.0f);
		BG_tex->setPosition(Vec2((winSize.width) / 2, (winSize.height) / 2));
		this->addChild(BG_tex, 10, 10);

		auto pMenuItem = MenuItemFont::create("소환할 위치가 없습니다.");
		pMenuItem->setColor(Color3B(255, 255, 255));
		pMenuItem->setPosition(Vec2(200, 80));
		BG_tex->addChild(pMenuItem, 11, 11);
		return false;
	}
	
	return true;
}

void EarthMap::DistelMonsterSave(Monster_num *monster) {

	if (DistelMonsterListSize)	Distel_Monster_List = (Monster_num*)realloc(Distel_Monster_List, sizeof(Monster_num) * (DistelMonsterListSize + 1));
	else						Distel_Monster_List = (Monster_num*)malloc(						 sizeof(Monster_num) * (DistelMonsterListSize + 1));
	DistelMonsterListSize++;

	Distel_Monster_List[DistelMonsterListSize - 1].Type = monster->Type;
	Distel_Monster_List[DistelMonsterListSize - 1].level = monster->level;
	Distel_Monster_List[DistelMonsterListSize - 1].Item1 = monster->Item1;
	Distel_Monster_List[DistelMonsterListSize - 1].Item2 = monster->Item2;
	Distel_Monster_List[DistelMonsterListSize - 1].Item3 = monster->Item3;
	
}

//이동범위 내 이동액션 (이동할좌표, 이동가능한좌표, 이동가능한좌표개수, 움직일몬스터)
void EarthMap::ShortistMove(Vec2 v_pos, Position *temppos, int tempposSize, Monster_num *monster) {
	//초기화
	if (shortpassSize) {
		free(shortpass);
		shortpassSize = 0;
	}
	//이동 가능 경로 저장
	for (int m = 0; m < tempposSize; m++) {
		if (temppos[m].x == v_pos.x && temppos[m].y == v_pos.y) {
			if (shortpassSize)	shortpass = (Position*)realloc(shortpass, sizeof(Position) * (shortpassSize + 1));
			else				shortpass = (Position*)malloc(sizeof(Position) * (shortpassSize + 1));
			shortpass[shortpassSize].num = temppos[m].num;
			shortpass[shortpassSize].x = temppos[m].x;
			shortpass[shortpassSize].y = temppos[m].y;
			shortpassSize++;
		}
		if (temppos[m].pos2Size) {
			for (int k = 0; k < temppos[m].pos2Size; k++) {
				if (temppos[m].pos2[k].x == v_pos.x && temppos[m].pos2[k].y == v_pos.y) {
					if (shortpassSize)	shortpass = (Position*)realloc(shortpass, sizeof(Position) * (shortpassSize + 1));
					else				shortpass = (Position*)malloc(sizeof(Position) * (shortpassSize + 1));
					shortpass[shortpassSize].num = temppos[m].pos2[k].num;
					shortpass[shortpassSize].front_x = temppos[m].x;
					shortpass[shortpassSize].front_y = temppos[m].y;
					shortpass[shortpassSize].x = temppos[m].pos2[k].x;
					shortpass[shortpassSize].y = temppos[m].pos2[k].y;
					shortpassSize++;
				}
				if (temppos[m].pos2[k].pos2Size) {
					for (int z = 0; z < temppos[m].pos2[k].pos2Size; z++) {
						if (temppos[m].pos2[k].pos2[z].x == v_pos.x && temppos[m].pos2[k].pos2[z].y == v_pos.y) {
							if (shortpassSize)	shortpass = (Position*)realloc(shortpass, sizeof(Position) * (shortpassSize + 1));
							else				shortpass = (Position*)malloc(sizeof(Position) * (shortpassSize + 1));
							shortpass[shortpassSize].num = temppos[m].pos2[k].pos2[z].num;
							shortpass[shortpassSize].front_front_x = temppos[m].x;
							shortpass[shortpassSize].front_front_y = temppos[m].y;
							shortpass[shortpassSize].front_x = temppos[m].pos2[k].x;
							shortpass[shortpassSize].front_y = temppos[m].pos2[k].y;
							shortpass[shortpassSize].x = temppos[m].pos2[k].pos2[z].x;
							shortpass[shortpassSize].y = temppos[m].pos2[k].pos2[z].y;
							shortpassSize++;
						}
						if (temppos[m].pos2[k].pos2[z].pos2Size) {
							for (int i = 0; i < temppos[m].pos2[k].pos2[z].pos2Size; i++) {
								if (temppos[m].pos2[k].pos2[z].pos2[i].x == v_pos.x && temppos[m].pos2[k].pos2[z].pos2[i].y == v_pos.y) {
									if (shortpassSize)	shortpass = (Position*)realloc(shortpass, sizeof(Position) * (shortpassSize + 1));
									else				shortpass = (Position*)malloc(sizeof(Position) * (shortpassSize + 1));
									shortpass[shortpassSize].num = temppos[m].pos2[k].pos2[z].pos2[i].num;
									shortpass[shortpassSize].front_front_front_x = temppos[m].x;
									shortpass[shortpassSize].front_front_front_y = temppos[m].y;
									shortpass[shortpassSize].front_front_x = temppos[m].pos2[k].x;
									shortpass[shortpassSize].front_front_y = temppos[m].pos2[k].y;
									shortpass[shortpassSize].front_x = temppos[m].pos2[k].pos2[z].x;
									shortpass[shortpassSize].front_y = temppos[m].pos2[k].pos2[z].y;
									shortpass[shortpassSize].x = temppos[m].pos2[k].pos2[z].pos2[i].x;
									shortpass[shortpassSize].y = temppos[m].pos2[k].pos2[z].pos2[i].y;
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
				log("shortpass[1].x = %d, shortpass[1].y = %d", shortpass[k].x, shortpass[k].y);
				Vec2 vec = FindCoordPosition(Vec2(shortpass[k].x, shortpass[k].y));
				auto animate = MoveTo::create(0.25, Vec2(vec.x - MovePositionX, vec.y - 60 - MovePositionY));
				monster->sprite->runAction(animate);
				pass = true;
				//이동 좌표 저장
				monster->tx = shortpass[k].x;
				monster->ty = shortpass[k].y;
				
				break;
			}
		}
	}
	if (!pass) {
		for (int k = 0; k < shortpassSize; k++) {
			if (shortpass[k].num + movement == 3) {
				log("shortpass[2].x = %d, shortpass[2].y = %d", shortpass[k].front_x, shortpass[k].front_y);
				Vec2 vec = FindCoordPosition(Vec2(shortpass[k].front_x, shortpass[k].front_y));
				auto animate = MoveTo::create(0.25, Vec2(vec.x - MovePositionX, vec.y - 60 - MovePositionY));

				monster->tx = shortpass[k].front_x;
				monster->ty = shortpass[k].front_y;

				log("shortpass[2].x = %d, shortpass[2].y = %d", shortpass[k].x, shortpass[k].y);
				Vec2 vec1 = FindCoordPosition(Vec2(shortpass[k].x, shortpass[k].y));
				auto animate1 = MoveTo::create(0.25, Vec2(vec1.x - MovePositionX, vec1.y - 60 - MovePositionY));

				monster->tx = shortpass[k].x;
				monster->ty = shortpass[k].y;
				
				auto myAction = Sequence::create(animate, animate1, nullptr);
				monster->sprite->runAction(myAction);
				pass = true;
				break;
			}
		}
	}
	if (!pass) {
		for (int k = 0; k < shortpassSize; k++) {
			if (shortpass[k].num + movement == 2) {
				log("shortpass[3].x = %d, shortpass[3].y = %d", shortpass[k].front_front_x, shortpass[k].front_front_y);
				Vec2 vec = FindCoordPosition(Vec2(shortpass[k].front_front_x, shortpass[k].front_front_y));
				auto animate = MoveTo::create(0.25, Vec2(vec.x - MovePositionX, vec.y - 60 - MovePositionY));

				monster->tx = shortpass[k].front_front_x;
				monster->ty = shortpass[k].front_front_y;

				log("shortpass[3].x = %d, shortpass[3].y = %d", shortpass[k].front_x, shortpass[k].front_y);
				Vec2 vec1 = FindCoordPosition(Vec2(shortpass[k].front_x, shortpass[k].front_y));
				auto animate1 = MoveTo::create(0.25, Vec2(vec1.x - MovePositionX, vec1.y - 60 - MovePositionY));

				monster->tx = shortpass[k].front_x;
				monster->ty = shortpass[k].front_y;

				log("shortpass[3].x = %d, shortpass[3].y = %d", shortpass[k].x, shortpass[k].y);
				Vec2 vec2 = FindCoordPosition(Vec2(shortpass[k].x, shortpass[k].y));
				auto animate2 = MoveTo::create(0.25, Vec2(vec2.x - MovePositionX, vec2.y - 60 - MovePositionY));

				monster->tx = shortpass[k].x;
				monster->ty = shortpass[k].y;
				
				auto myAction = Sequence::create(animate, animate1, animate2, nullptr);
				monster->sprite->runAction(myAction);
				pass = true;
				break;
			}
		}
	}
	if (!pass) {
		for (int k = 0; k < shortpassSize; k++) {
			if (shortpass[k].num + movement == 1) {
				log("shortpass[4].x = %d, shortpass[4].y = %d", shortpass[k].front_front_front_x, shortpass[k].front_front_front_y);
				Vec2 vec_1 = FindCoordPosition(Vec2(shortpass[k].front_front_front_x, shortpass[k].front_front_front_y));
				auto animate_1 = MoveTo::create(0.25, Vec2(vec_1.x - MovePositionX, vec_1.y - 60 - MovePositionY));

				monster->tx = shortpass[k].front_front_front_x;
				monster->ty = shortpass[k].front_front_front_y;

				log("shortpass[4].x = %d, shortpass[4].y = %d", shortpass[k].front_front_x, shortpass[k].front_front_y);
				Vec2 vec = FindCoordPosition(Vec2(shortpass[k].front_front_x, shortpass[k].front_front_y));
				auto animate = MoveTo::create(0.25, Vec2(vec.x - MovePositionX, vec.y - 60 - MovePositionY));

				monster->tx = shortpass[k].front_front_x;
				monster->ty = shortpass[k].front_front_y;

				log("shortpass[4].x = %d, shortpass[4].y = %d", shortpass[k].front_x, shortpass[k].front_y);
				Vec2 vec1 = FindCoordPosition(Vec2(shortpass[k].front_x, shortpass[k].front_y));
				auto animate1 = MoveTo::create(0.25, Vec2(vec1.x - MovePositionX, vec1.y - 60 - MovePositionY));

				monster->tx = shortpass[k].front_x;
				monster->ty = shortpass[k].front_y;

				log("shortpass[4].x = %d, shortpass[4].y = %d", shortpass[k].x, shortpass[k].y);
				Vec2 vec2 = FindCoordPosition(Vec2(shortpass[k].x, shortpass[k].y));
				auto animate2 = MoveTo::create(0.25, Vec2(vec2.x - MovePositionX, vec2.y - 60 - MovePositionY));

				monster->tx = shortpass[k].x;
				monster->ty = shortpass[k].y;
				
				auto myAction = Sequence::create(animate_1, animate, animate1, animate2, nullptr);
				monster->sprite->runAction(myAction);
				pass = true;
				break;
			}
		}
	}
}

//이동타일 중복체크
bool EarthMap::MoveTileCheck(Vec2 vec) {
	if (VecPositionSize == 0) {
		VecPosition = (Position*)malloc(sizeof(Position) * (VecPositionSize + 1));
		VecPositionSize++;
		VecPosition[VecPositionSize - 1].x = vec.x;
		VecPosition[VecPositionSize - 1].y = vec.y;
		return true;
	}
	for (int i = 0; i < VecPositionSize; i++) {
		if (VecPosition[i].x == vec.x && VecPosition[i].y == vec.y) {
			return false;
		}
		else if (i == VecPositionSize -1) {
			VecPosition = (Position*)realloc(VecPosition, sizeof(Position) * (VecPositionSize + 1));
			VecPositionSize++;
			VecPosition[VecPositionSize - 1].x = vec.x;
			VecPosition[VecPositionSize - 1].y = vec.y;
			return true;
		}
	}
}

//공격범위에 따른 적몬스터 타일 표시, 자기자신 타일 표시
void EarthMap::DisplayEmyMonsterAttack(Vec2 posVec) {
	if (EmyposSize) {
		free(Emypos);
		EmyposSize = 0;
	}
	
	for (int i = 0; i < EmyMovePosition.size(); i++) {
		tmap->removeChild(EmyMovePosition.at(i));
	}
	if (EmyMovePosition.size()) {
		EmyMovePosition.clear();
	}

	for (int k = 0; k < EmyMonsterSize; k++) {

		//공격범위 1이상 체크
		if (monster_char[mons].range > 0) {
			if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y == EmyMonster_char[k].ty) {
				if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
				else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
				EmyposSize++;
				Emypos[EmyposSize - 1].num = k;
				Emypos[EmyposSize - 1].x = posVec.x - 1;
				Emypos[EmyposSize - 1].y = posVec.y;
				Emypos[EmyposSize - 1].PositionView = true;
				Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				Emypos[EmyposSize - 1].tempsize = k;
			}
			if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y == EmyMonster_char[k].ty) {
				if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
				else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
				EmyposSize++;
				Emypos[EmyposSize - 1].num = k;
				Emypos[EmyposSize - 1].x = posVec.x + 1;
				Emypos[EmyposSize - 1].y = posVec.y;
				Emypos[EmyposSize - 1].PositionView = true;
				Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				Emypos[EmyposSize - 1].tempsize = k;
			}
			if (posVec.x == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
				if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
				else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
				EmyposSize++;
				Emypos[EmyposSize - 1].num = k;
				Emypos[EmyposSize - 1].x = posVec.x;
				Emypos[EmyposSize - 1].y = posVec.y - 1;
				Emypos[EmyposSize - 1].PositionView = true;
				Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				Emypos[EmyposSize - 1].tempsize = k;
			}
			if (posVec.x == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
				if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
				else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
				EmyposSize++;
				Emypos[EmyposSize - 1].num = k;
				Emypos[EmyposSize - 1].x = posVec.x;
				Emypos[EmyposSize - 1].y = posVec.y + 1;
				Emypos[EmyposSize - 1].PositionView = true;
				Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
				Emypos[EmyposSize - 1].tempsize = k;
			}
			if (fmodf(posVec.y, 2) == 0) {
				if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x - 1;
					Emypos[EmyposSize - 1].y = posVec.y - 1;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
				if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x - 1;
					Emypos[EmyposSize - 1].y = posVec.y + 1;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
			}
			else {
				if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x + 1;
					Emypos[EmyposSize - 1].y = posVec.y + 1;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
				if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x + 1;
					Emypos[EmyposSize - 1].y = posVec.y - 1;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
			}
			//공격범위 2일때 체크
			if (monster_char[mons].range > 1) {
				if (posVec.x == EmyMonster_char[k].tx && posVec.y - 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x;
					Emypos[EmyposSize - 1].y = posVec.y - 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
				if (posVec.x == EmyMonster_char[k].tx && posVec.y + 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x;
					Emypos[EmyposSize - 1].y = posVec.y + 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
				if (posVec.x + 2 == EmyMonster_char[k].tx && posVec.y == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x + 2;
					Emypos[EmyposSize - 1].y = posVec.y;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
				if (posVec.x - 2 == EmyMonster_char[k].tx && posVec.y == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x - 2;
					Emypos[EmyposSize - 1].y = posVec.y;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
				if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y - 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x - 1;
					Emypos[EmyposSize - 1].y = posVec.y - 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
				if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y + 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x - 1;
					Emypos[EmyposSize - 1].y = posVec.y + 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
				if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y - 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x + 1;
					Emypos[EmyposSize - 1].y = posVec.y - 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
				if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y + 2 == EmyMonster_char[k].ty) {
					if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
					else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
					EmyposSize++;
					Emypos[EmyposSize - 1].num = k;
					Emypos[EmyposSize - 1].x = posVec.x + 1;
					Emypos[EmyposSize - 1].y = posVec.y + 2;
					Emypos[EmyposSize - 1].PositionView = true;
					Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
					Emypos[EmyposSize - 1].tempsize = k;
				}
				if (fmodf(posVec.y, 2) == 0) {
					if (posVec.x - 2 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].num = k;
						Emypos[EmyposSize - 1].x = posVec.x - 2;
						Emypos[EmyposSize - 1].y = posVec.y - 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
						Emypos[EmyposSize - 1].tempsize = k;
					}
					if (posVec.x - 2 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].num = k;
						Emypos[EmyposSize - 1].x = posVec.x - 2;
						Emypos[EmyposSize - 1].y = posVec.y + 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
						Emypos[EmyposSize - 1].tempsize = k;
					}
					if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].num = k;
						Emypos[EmyposSize - 1].x = posVec.x + 1;
						Emypos[EmyposSize - 1].y = posVec.y - 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
						Emypos[EmyposSize - 1].tempsize = k;
					}
					if (posVec.x + 1 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].num = k;
						Emypos[EmyposSize - 1].x = posVec.x + 1;
						Emypos[EmyposSize - 1].y = posVec.y + 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
						Emypos[EmyposSize - 1].tempsize = k;
					}
				}
				else {
					if (posVec.x + 2 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].num = k;
						Emypos[EmyposSize - 1].x = posVec.x + 2;
						Emypos[EmyposSize - 1].y = posVec.y - 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
						Emypos[EmyposSize - 1].tempsize = k;
					}
					if (posVec.x + 2 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].num = k;
						Emypos[EmyposSize - 1].x = posVec.x + 2;
						Emypos[EmyposSize - 1].y = posVec.y + 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
						Emypos[EmyposSize - 1].tempsize = k;
					}
					if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y - 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].num = k;
						Emypos[EmyposSize - 1].x = posVec.x - 1;
						Emypos[EmyposSize - 1].y = posVec.y - 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
						Emypos[EmyposSize - 1].tempsize = k;
					}
					if (posVec.x - 1 == EmyMonster_char[k].tx && posVec.y + 1 == EmyMonster_char[k].ty) {
						if (EmyposSize)	Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						else			Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
						EmyposSize++;
						Emypos[EmyposSize - 1].num = k;
						Emypos[EmyposSize - 1].x = posVec.x - 1;
						Emypos[EmyposSize - 1].y = posVec.y + 1;
						Emypos[EmyposSize - 1].PositionView = true;
						Emypos[EmyposSize - 1].type = EmyMonster_char[k].Type;
						Emypos[EmyposSize - 1].tempsize = k;
					}
				}
			}
		}
	}
	
	//적 표시
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
			//적 몬스터 타일 표시
			Vec2 posit = FindCoordPosition(Vec2(Emypos[m].x, Emypos[m].y));
			sp->setPosition(posit.x - MovePositionX, posit.y - 60 - MovePositionY);
			tmap->addChild(sp);
			EmyMovePosition.pushBack(sp);
		}

	}
	
	

	//자기자신 타일 표시
	if (posSize) {
		free(pos);
		posSize = 0;
	}
	for (int i = 0; i < MovePosition.size(); i++) {
		tmap->removeChild(MovePosition.at(i));
	}
	if (MovePosition.size()) {
		MovePosition.clear();
	}
	pos = (Position*)malloc(sizeof(Position) * (posSize + 1));
	//pos[posSize].num = 0;
	pos[posSize].x = monster_char[mons].tx;
	pos[posSize].y = monster_char[mons].ty;
	//pos[posSize].pos2Size = 0;
	posSize++;
	Sprite* sp = Sprite::createWithSpriteFrameName("HexInfo4.png");
	Vec2 posit = FindCoordPosition(Vec2(pos[posSize-1].x, pos[posSize-1].y));
	sp->setPosition(posit.x - MovePositionX, posit.y - 60 - MovePositionY);
	tmap->addChild(sp);
	MovePosition.pushBack(sp);
}

//이동에 따른 sprite 교체
void EarthMap::SpriteCoordinateChange(Vec2 m_pos, Monster_num *monster, int mon_num) {
	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;
	Vec2 mon_pos = Vec2(monster[mon_num].tx, monster[mon_num].ty);
	//오른쪽 스프라이트
	if (fmodf(mon_pos.y, 2) == 0 && mon_pos.x == m_pos.x || mon_pos.x < m_pos.x) {
		if (monster[mon_num].Type == 0) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Person1-5.png"));
			sprintf(str1, "Person1-");
		}
		//땅질퍽이
		else if (monster[mon_num].Type == 1) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth1-5.png"));
			sprintf(str1, "Earth1-");
		}
		else if (monster[mon_num].Type == 2) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth2-5.png"));
			sprintf(str1, "Earth2-");
		}
		else if (monster[mon_num].Type == 3) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth3-5.png"));
			sprintf(str1, "Earth3-");
		}
		//모닥픽
		else if (monster[mon_num].Type == 4) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth4-5.png"));
			sprintf(str1, "Earth4-");
		}
		else if (monster[mon_num].Type == 5) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth5-5.png"));
			sprintf(str1, "Earth5-");
		}
		else if (monster[mon_num].Type == 6) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth6-5.png"));
			sprintf(str1, "Earth6-");
		}
		//모래두지
		else if (monster[mon_num].Type == 7) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth7-5.png"));
			sprintf(str1, "Earth7-");
		}
		else if (monster[mon_num].Type == 8) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth8-5.png"));
			sprintf(str1, "Earth8-");
		}
		else if (monster[mon_num].Type == 9) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth9-5.png"));
			sprintf(str1, "Earth9-");
		}
		//파이뤼
		else if (monster[mon_num].Type == 11) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire1-5.png"));
			sprintf(str1, "Fire1-");
		}
		else if (monster[mon_num].Type == 12) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire2-5.png"));
			sprintf(str1, "Fire2-");
		}
		else if (monster[mon_num].Type == 13) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire3-5.png"));
			sprintf(str1, "Fire3-");
		}
		//팬템
		else if (monster[mon_num].Type == 14) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire4-5.png"));
			sprintf(str1, "Fire4-");
		}
		else if (monster[mon_num].Type == 15) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire5-5.png"));
			sprintf(str1, "Fire5-");
		}
		else if (monster[mon_num].Type == 16) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire6-5.png"));
			sprintf(str1, "Fire6-");
		}
		//블랙매직숀
		else if (monster[mon_num].Type == 17) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire7-5.png"));
			sprintf(str1, "Fire7-");
		}
		else if (monster[mon_num].Type == 18) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire8-5.png"));
			sprintf(str1, "Fire8-");
		}
		else if (monster[mon_num].Type == 19) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire9-5.png"));
			sprintf(str1, "Fire9-");
		}
		//물질퍽이
		else if (monster[mon_num].Type == 21) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water1-5.png"));
			sprintf(str1, "Water1-");
		}
		else if (monster[mon_num].Type == 22) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water2-5.png"));
			sprintf(str1, "Water2-");
		}
		else if (monster[mon_num].Type == 23) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water3-5.png"));
			sprintf(str1, "Water3-");
		}
		//꼬북이
		else if (monster[mon_num].Type == 24) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water4-5.png"));
			sprintf(str1, "Water4-");
		}
		else if (monster[mon_num].Type == 25) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water5-5.png"));
			sprintf(str1, "Water5-");
		}
		else if (monster[mon_num].Type == 26) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water6-5.png"));
			sprintf(str1, "Water6-");
		}
		//리아커
		else if (monster[mon_num].Type == 27) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water7-5.png"));
			sprintf(str1, "Water7-");
		}
		else if (monster[mon_num].Type == 28) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water8-5.png"));
			sprintf(str1, "Water8-");
		}
		else if (monster[mon_num].Type == 29) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water9-5.png"));
			sprintf(str1, "Water9-");
		}
		//코이
		else if (monster[mon_num].Type == 31) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind1-5.png"));
			sprintf(str1, "Wind1-");
		}
		else if (monster[mon_num].Type == 32) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind2-5.png"));
			sprintf(str1, "Wind2-");
		}
		else if (monster[mon_num].Type == 33) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind3-5.png"));
			sprintf(str1, "Wind3-");
		}
		//피젼
		else if (monster[mon_num].Type == 34) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind4-5.png"));
			sprintf(str1, "Wind4-");
		}
		else if (monster[mon_num].Type == 35) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind5-5.png"));
			sprintf(str1, "Wind5-");
		}
		else if (monster[mon_num].Type == 36) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind6-5.png"));
			sprintf(str1, "Wind6-");
		}
		//코이
		else if (monster[mon_num].Type == 37) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind7-5.png"));
			sprintf(str1, "Wind7-");
		}
		else if (monster[mon_num].Type == 38) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind8-5.png"));
			sprintf(str1, "Wind8-");
		}
		else if (monster[mon_num].Type == 39) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind9-5.png"));
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
		monster[mon_num].sprite->stopAllActions();
		monster[mon_num].sprite->runAction(rep);
	}
	//왼쪽 스프라이트
	else {
		if (monster[mon_num].Type == 0) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Person1-1.png"));
			sprintf(str1, "Person1-");
		}
		//땅질퍽이
		else if (monster[mon_num].Type == 1) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth1-1.png"));
			sprintf(str1, "Earth1-");
		}
		else if (monster[mon_num].Type == 2) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth2-1.png"));
			sprintf(str1, "Earth2-");
		}
		else if (monster[mon_num].Type == 3) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth3-1.png"));
			sprintf(str1, "Earth3-");
		}
		//모닥픽
		else if (monster[mon_num].Type == 4) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth4-1.png"));
			sprintf(str1, "Earth4-");
		}
		else if (monster[mon_num].Type == 5) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth5-1.png"));
			sprintf(str1, "Earth5-");
		}
		else if (monster[mon_num].Type == 6) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth6-1.png"));
			sprintf(str1, "Earth6-");
		}
		//모래두지
		else if (monster[mon_num].Type == 7) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth7-1.png"));
			sprintf(str1, "Earth7-");
		}
		else if (monster[mon_num].Type == 8) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth8-1.png"));
			sprintf(str1, "Earth8-");
		}
		else if (monster[mon_num].Type == 9) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Earth9-1.png"));
			sprintf(str1, "Earth9-");
		}
		//파이뤼
		else if (monster[mon_num].Type == 11) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire1-1.png"));
			sprintf(str1, "Fire1-");
		}
		else if (monster[mon_num].Type == 12) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire2-1.png"));
			sprintf(str1, "Fire2-");
		}
		else if (monster[mon_num].Type == 13) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire3-1.png"));
			sprintf(str1, "Fire3-");
		}
		//팬템
		else if (monster[mon_num].Type == 14) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire4-1.png"));
			sprintf(str1, "Fire4-");
		}
		else if (monster[mon_num].Type == 15) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire5-1.png"));
			sprintf(str1, "Fire5-");
		}
		else if (monster[mon_num].Type == 16) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire6-1.png"));
			sprintf(str1, "Fire6-");
		}
		//블랙매직숀
		else if (monster[mon_num].Type == 17) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire7-1.png"));
			sprintf(str1, "Fire7-");
		}
		else if (monster[mon_num].Type == 18) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire8-1.png"));
			sprintf(str1, "Fire8-");
		}
		else if (monster[mon_num].Type == 19) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire9-1.png"));
			sprintf(str1, "Fire9-");
		}
		//물질퍽이
		else if (monster[mon_num].Type == 21) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water1-1.png"));
			sprintf(str1, "Water1-");
		}
		else if (monster[mon_num].Type == 22) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water2-1.png"));
			sprintf(str1, "Water2-");
		}
		else if (monster[mon_num].Type == 23) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water3-1.png"));
			sprintf(str1, "Water3-");
		}
		//꼬북이
		else if (monster[mon_num].Type == 24) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water4-1.png"));
			sprintf(str1, "Water4-");
		}
		else if (monster[mon_num].Type == 25) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water5-1.png"));
			sprintf(str1, "Water5-");
		}
		else if (monster[mon_num].Type == 26) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water6-1.png"));
			sprintf(str1, "Water6-");
		}
		//리아커
		else if (monster[mon_num].Type == 27) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water7-1.png"));
			sprintf(str1, "Water7-");
		}
		else if (monster[mon_num].Type == 28) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water8-1.png"));
			sprintf(str1, "Water8-");
		}
		else if (monster[mon_num].Type == 29) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Water9-1.png"));
			sprintf(str1, "Water9-");
		}
		//코이
		else if (monster[mon_num].Type == 31) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind1-1.png"));
			sprintf(str1, "Wind1-");
		}
		else if (monster[mon_num].Type == 32) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind2-1.png"));
			sprintf(str1, "Wind2-");
		}
		else if (monster[mon_num].Type == 33) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind3-1.png"));
			sprintf(str1, "Wind3-");
		}
		//피젼
		else if (monster[mon_num].Type == 34) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind4-1.png"));
			sprintf(str1, "Wind4-");
		}
		else if (monster[mon_num].Type == 35) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind5-1.png"));
			sprintf(str1, "Wind5-");
		}
		else if (monster[mon_num].Type == 36) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind6-1.png"));
			sprintf(str1, "Wind6-");
		}
		//코이
		else if (monster[mon_num].Type == 37) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind7-1.png"));
			sprintf(str1, "Wind7-");
		}
		else if (monster[mon_num].Type == 38) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind8-1.png"));
			sprintf(str1, "Wind8-");
		}
		else if (monster[mon_num].Type == 39) {
			monster[mon_num].sprite->setTexture(Director::getInstance()->getTextureCache()->addImage("Wind9-1.png"));
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
		monster[mon_num].sprite->stopAllActions();
		monster[mon_num].sprite->runAction(rep);
	}
}

//monster_char[mons] 공격또는 디스펠 후 max 경험치가 넘어가는지 확인후 레벨업
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
				monster_char[mons].sprite->removeAllChildren();

				Sprite* st = Sprite::createWithSpriteFrameName("HP_bar.png");
				st->setPosition(0, -5);
				st->setScaleX(monster_char[mons].HPbarPosition / 25 * 2);
				st->setScaleY(2.0f);
				st->setAnchorPoint(Vec2(0, 0.5));
				monster_char[mons].sprite->addChild(st, 4, 1);

				Sprite* hp = Sprite::createWithSpriteFrameName("Monster_HP.png");
				hp->setPosition(0, -5);
				hp->setScaleX(monster_char[mons].HPbarPosition / 25 * 2);
				hp->setScaleY(2.0f);
				//hp->setContentSize(Size(st->getContentSize().width, st->getContentSize().height));
				hp->setAnchorPoint(Vec2(0, 0.5));
				monster_char[mons].sprite->addChild(hp, 4, 2);

				char level[3];
				sprintf(level, "%d", monster_char[mons].level);
				auto pLabel3 = LabelAtlas::create(level, "Images/Scene/ML.png", 7, 9, '0');
				pLabel3->setAnchorPoint(Vec2(0, 0));
				pLabel3->setPosition(Vec2(hp->getContentSize().width*(monster_char[mons].HPbarPosition / 25 * 2) + 5, -10));
				pLabel3->setScale(2.0f);
				monster_char[mons].sprite->addChild(pLabel3, 4, 3);
				//log("monster_char[mons].level = %d, monster_char[mons].atk = %d", monster_char[mons].level, monster_char[mons].atk);
			}
		}
	}
}

//경험치 최대치 return
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

//Level 업시 능력치 상승
void EarthMap::LevelUpCheck(Monster_num *monster) {
	//주인공
	if (monster->Type == 0) {
		monster_char[0].atk = 200 + ((monster_char[0].level - 1) * 20);
		monster_char[0].def = 100 + ((monster_char[0].level - 1) * 10);
		monster_char[0].hp = 1000 + ((monster_char[0].level - 1) * 100);
		monster_char[0].Fullhp = 1000 + ((monster_char[0].level - 1) * 100);
		monster_char[0].move = 3;
		monster_char[0].range = 1;
	}
	//땅질퍽이
	else if (monster->Type == 1) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 2) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 3) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
	}
	//모닥픽
	else if (monster->Type == 4) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 5) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 6) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 60 + ((monster->level - 1) * 6);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
	}
	//모래두지
	else if (monster->Type == 7) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 20 + ((monster->level - 1) * 2);
		monster->hp = 200 + ((monster->level - 1) * 20);
		monster->Fullhp = 200 + ((monster->level - 1) * 20);
		monster->move = 3;
		monster->range = 2;
	}
	else if (monster->Type == 8) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 350 + ((monster->level - 1) * 35);
		monster->Fullhp = 350 + ((monster->level - 1) * 35);
		monster->move = 3;
		monster->range = 2;
	}
	else if (monster->Type == 9) {
		monster->atk = 250 + ((monster->level - 1) * 25);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 500 + ((monster->level - 1) * 50);
		monster->Fullhp = 500 + ((monster->level - 1) * 50);
		monster->move = 3;
		monster->range = 2;
	}
	//파이뤼
	else if (monster->Type == 11) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 12) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 13) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
	}
	//팬템
	else if (monster->Type == 14) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 15) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 16) {
		monster->atk = 350 + ((monster->level - 1) * 35);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
	}
	//블랙매직숀
	else if (monster->Type == 17) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 2;
	}
	else if (monster->Type == 18) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 2;
	}
	else if (monster->Type == 19) {
		monster->atk = 250 + ((monster->level - 1) * 25);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 2;
	}
	//물질퍽이
	else if (monster->Type == 21) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 22) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 23) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
	}
	//꼬북이
	else if (monster->Type == 24) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 350 + ((monster->level - 1) * 35);
		monster->Fullhp = 350 + ((monster->level - 1) * 35);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 25) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 500 + ((monster->level - 1) * 50);
		monster->Fullhp = 500 + ((monster->level - 1) * 50);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 26) {
		monster->atk = 350 + ((monster->level - 1) * 35);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 650 + ((monster->level - 1) * 65);
		monster->Fullhp = 650 + ((monster->level - 1) * 65);
		monster->move = 3;
		monster->range = 1;
	}
	//리아커
	else if (monster->Type == 27) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 28) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 29) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 60 + ((monster->level - 1) * 6);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
	}
	//코이
	else if (monster->Type == 31) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 32) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 33) {
		monster->atk = 300 + ((monster->level - 1) * 30);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
	}
	//피젼
	else if (monster->Type == 34) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 35) {
		monster->atk = 200 + ((monster->level - 1) * 20);
		monster->def = 40 + ((monster->level - 1) * 4);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 1;
	}
	else if (monster->Type == 36) {
		monster->atk = 350 + ((monster->level - 1) * 35);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 1;
	}
	//코이
	else if (monster->Type == 37) {
		monster->atk = 100 + ((monster->level - 1) * 10);
		monster->def = 30 + ((monster->level - 1) * 3);
		monster->hp = 300 + ((monster->level - 1) * 30);
		monster->Fullhp = 300 + ((monster->level - 1) * 30);
		monster->move = 3;
		monster->range = 2;
	}
	else if (monster->Type == 38) {
		monster->atk = 150 + ((monster->level - 1) * 15);
		monster->def = 40 + ((monster->level - 1) * 04);
		monster->hp = 450 + ((monster->level - 1) * 45);
		monster->Fullhp = 450 + ((monster->level - 1) * 45);
		monster->move = 3;
		monster->range = 2;
	}
	else if (monster->Type == 39) {
		monster->atk = 250 + ((monster->level - 1) * 25);
		monster->def = 50 + ((monster->level - 1) * 5);
		monster->hp = 600 + ((monster->level - 1) * 60);
		monster->Fullhp = 600 + ((monster->level - 1) * 60);
		monster->move = 3;
		monster->range = 2;
	}
}

//버프타일위에 있는지 확인
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

//상성체크 return = 2 -> s2, return = 1 -> s1, return = 0 -> 동급
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

//애니메이션이 끝나면 Sprite 삭제 (ex 진화)
void EarthMap::RemoveSprite() {
	tmap->removeChild(st);
}

//이동범위내 클릭했는지 확인
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

//클릭한 위치에 적몬스터가 있는지 확인
bool EarthMap::checkEmyMonsterCoordinate(Vec2 click, Monster_num *EmyMon, int EmyMonSize) {
	//log("EmyposSize = %d", EmyposSize);
	for (int m = 0; m < EmyposSize; m++) {
		if (Emypos[m].PositionView) {
			for (int i = 0; i < EmyMonSize; i++) {
				if (Emypos[m].x == EmyMon[i].tx && Emypos[m].y == EmyMon[i].ty) {
					if (EmyMon[i].tx == click.x && EmyMon[i].ty == click.y) {
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

//타일맵좌표에서 화면좌표
Vec2 EarthMap::FindCoordPosition(Vec2 pos) {
	float x;
	float y;
	y = 92 + ((15 - pos.y) * 96);
	if (fmodf(pos.x, 2) == 0) {
		if (fmodf(pos.y, 2) == 0) {
			
			x = pos.x * 128;
		}
		else {
			x = pos.x * 128 + 64;
		}
	}
	else {
		if (fmodf(pos.y, 2) == 0) {
			x = pos.x * 128; 
		}
		else {
			x = pos.x * 128 + 64;
		}
	}
	
	//log("x = %f, MovePositionDX = %f, y = %f, MovePositionDY = %f", x, MovePositionDX, y, MovePositionDY);
	return Vec2(x - MovePositionDX, y - MovePositionDY);
	//pos.x;
	//MovePositionX;
	//MovePositionY;
}

//주변의 장애물 체크, 적몬스터 저장
bool EarthMap::CheckPosition(int num1, int num2, int monSize, Monster_num *monster, int EmyMonSize, Monster_num *EmyMonster) {
	//Vec2 pos; 
	if (num2 % 2 == 0) {
		if (num1 > 15 || num1 < 1) {
			return false;
		}
	}
	else {
		if (num1 > 14 || num1 < 1) {
			return false;
		}
	}

	if (num2 > 14 || num2 < 1) {
		return false;
	}

	for (int i = 0; i < monSize; i++) {
		if (monster[i].tx == num1 && monster[i].ty == num2) {
			return false;
		}
	}

	for (int i = 0; i < EmyMonSize; i++) {
		if (EmyMonster[i].tx == num1 && EmyMonster[i].ty == num2) {
			if (EmyposSize) {
				for (int m = 0; m < EmyposSize; m++) {
					if (Emypos[m].x == num1 && Emypos[m].y == num2) {
						//중복체크
						return false;
					}
					else if (m == EmyposSize - 1) {
						Emypos = (Position*)realloc(Emypos, sizeof(Position) * (EmyposSize + 1));
						Emypos[EmyposSize].num = i;
						Emypos[EmyposSize].x = num1;
						Emypos[EmyposSize].y = num2;
						EmyposSize++;
						return false;
					}
				}
			}
			else {
				EmyposSize = 0;
				Emypos = (Position*)malloc(sizeof(Position) * (EmyposSize + 1));
				Emypos[EmyposSize].num = i;
				Emypos[EmyposSize].x = num1;
				Emypos[EmyposSize].y = num2;
				EmyposSize++;
				return false;
			}
		}
	}
	Vec2 tileCoord = Vec2(num1, num2);
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

//이동경로 저장 (이동할 위치
EarthMap::Position* EarthMap::CheckPosition(Vec2 charactor, Position *pos_temp, int tempSize, int Count, int move, int monSize, Monster_num *monster, int EmyMonSize, Monster_num *EmyMonster) {
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
		if (CheckPosition(charactor.x, charactor.y - 1, monSize, monster, EmyMonSize, EmyMonster)) {
			if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
			else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
			pos_temp[tempSize].num = Count;
			pos_temp[tempSize].x = charactor.x;
			pos_temp[tempSize].y = charactor.y - 1;
			pos_temp[tempSize].pos2Size = 0;
			pos_temp[tempSize].pos2 = CheckPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1, monSize, monster, EmyMonSize, EmyMonster);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = GrobalTempsize;
			}
			tempSize++;
		}
		//Vec2(charactor.x, charactor.y + 1);
		if (CheckPosition(charactor.x, charactor.y + 1, monSize, monster, EmyMonSize, EmyMonster)) {
			if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
			else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
			pos_temp[tempSize].num = Count;
			pos_temp[tempSize].x = charactor.x;
			pos_temp[tempSize].y = charactor.y + 1;
			pos_temp[tempSize].pos2Size = 0;
			pos_temp[tempSize].pos2 = CheckPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1, monSize, monster, EmyMonSize, EmyMonster);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = GrobalTempsize;
			}
			tempSize++;
		}
		//Vec2(charactor.x - 1, charactor.y);
		if (CheckPosition(charactor.x - 1, charactor.y, monSize, monster, EmyMonSize, EmyMonster)) {
			if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
			else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
			pos_temp[tempSize].num = Count;
			pos_temp[tempSize].x = charactor.x - 1;
			pos_temp[tempSize].y = charactor.y;
			pos_temp[tempSize].pos2Size = 0;
			pos_temp[tempSize].pos2 = CheckPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1, monSize, monster, EmyMonSize, EmyMonster);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = GrobalTempsize;
			}
			tempSize++;
		}
		//Vec2(charactor.x + 1, charactor.y);
		if (CheckPosition(charactor.x + 1, charactor.y, monSize, monster, EmyMonSize, EmyMonster)) {
			if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
			else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
			pos_temp[tempSize].num = Count;
			pos_temp[tempSize].x = charactor.x + 1;
			pos_temp[tempSize].y = charactor.y;
			pos_temp[tempSize].pos2Size = 0;
			pos_temp[tempSize].pos2 = CheckPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1, monSize, monster, EmyMonSize, EmyMonster);
			if (Count != 1) {
				pos_temp[tempSize].pos2Size = GrobalTempsize;
			}
			tempSize++;
		}
		if (fmodf(charactor.y, 2) == 0) {
			//Vec2(charactor.x - 1, charactor.y - 1);
			if (CheckPosition(charactor.x - 1, charactor.y - 1, monSize, monster, EmyMonSize, EmyMonster)) {
				if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
				else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
				pos_temp[tempSize].num = Count;
				pos_temp[tempSize].x = charactor.x - 1;
				pos_temp[tempSize].y = charactor.y - 1;
				pos_temp[tempSize].pos2Size = 0;
				pos_temp[tempSize].pos2 = CheckPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1, monSize, monster, EmyMonSize, EmyMonster);
				if (Count != 1) {
					pos_temp[tempSize].pos2Size = GrobalTempsize;
				}
				tempSize++;
			}
			//Vec2(charactor.x - 1, charactor.y + 1);
			if (CheckPosition(charactor.x - 1, charactor.y + 1, monSize, monster, EmyMonSize, EmyMonster)) {
				if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
				else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
				pos_temp[tempSize].num = Count;
				pos_temp[tempSize].x = charactor.x - 1;
				pos_temp[tempSize].y = charactor.y + 1;
				pos_temp[tempSize].pos2Size = 0;
				pos_temp[tempSize].pos2 = CheckPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1, monSize, monster, EmyMonSize, EmyMonster);
				if (Count != 1) {
					pos_temp[tempSize].pos2Size = GrobalTempsize;
				}
				tempSize++;
			}
		}
		else {
			//Vec2(charactor.x + 1, charactor.y + 1);
			if (CheckPosition(charactor.x + 1, charactor.y + 1, monSize, monster, EmyMonSize, EmyMonster)) {
				if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
				else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
				pos_temp[tempSize].num = Count;
				pos_temp[tempSize].x = charactor.x + 1;
				pos_temp[tempSize].y = charactor.y + 1;
				pos_temp[tempSize].pos2Size = 0;
				pos_temp[tempSize].pos2 = CheckPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1, monSize, monster, EmyMonSize, EmyMonster);
				if (Count != 1) {
					pos_temp[tempSize].pos2Size = GrobalTempsize;
				}
				tempSize++;
			}
			//Vec2(charactor.x + 1, charactor.y - 1);
			if (CheckPosition(charactor.x + 1, charactor.y - 1, monSize, monster, EmyMonSize, EmyMonster)) {
				if (tempSize)	pos_temp = (Position*)realloc(pos_temp, sizeof(Position) * (tempSize + 1));
				else			pos_temp = (Position*)malloc(sizeof(Position) * (tempSize + 1));
				pos_temp[tempSize].num = Count;
				pos_temp[tempSize].x = charactor.x + 1;
				pos_temp[tempSize].y = charactor.y - 1;
				pos_temp[tempSize].pos2Size = 0;
				pos_temp[tempSize].pos2 = CheckPosition(Vec2(pos_temp[tempSize].x, pos_temp[tempSize].y), pos_temp[tempSize].pos2, pos_temp[tempSize].pos2Size, Count - 1, 1, monSize, monster, EmyMonSize, EmyMonster);
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

//화면좌표에서 타일맵좌표
Vec2 EarthMap::tileCoordForPosition(cocos2d::Vec2 position) {
	position.x = position.x - MovePositionX;
	position.y = (1534 + MovePositionY) - position.y;
	//log("position.x = %f, position.y = %f", position.x, position.y);
	int x = position.x / 128;
	float rx = fmodf(position.x, 128);
	//log("x = %d, rx = %f", x, rx);

	int nx = position.x / 64;

	int ny = (position.y) / 96;
	float ry = fmodf((position.y), 96);
	//log("ny = %d, ry = %f", ny, ry);

	Vec2 p1, p2;
	//직선의 방정식 활용
	if (64 < ry) {
		if (ny % 2 == 0) {		//ny 가 짝수일 때
			if (nx % 2 == 0) {	//nx 가 짝수일 때
				p1 = Vec2(64 * nx + 64, 96 * (ny + 1));
				p2 = Vec2(64 * (nx + 1) - 64, 96 * ny + 64);
			}
			else {				//nx 가 홀수일 때
				p1 = Vec2(64 * nx + 64, 96 * ny + 64);
				p2 = Vec2(64 * (nx + 1) - 64, 96 * (ny + 1));
			}
		}
		else {					//ny 가 홀수일 때
			if (nx % 2 == 0) {	//nx 가 짝수일 때
				p1 = Vec2(64 * nx + 64, 96 * ny + 64);
				p2 = Vec2(64 * (nx + 1) - 64, 96 * (ny + 1));
			}
			else {				//nx 가 홀수일 때
				p1 = Vec2(64 * nx + 64, 96 * (ny + 1));
				p2 = Vec2(64 * (nx + 1) - 64, 96 * ny + 64);
			}
		}
		//log("p1 = (%f, %f), p2 = (%f, %f)", p1.x, p1.y, p2.x, p2.y);

		//직선의 방정식
		float tempy = (p2.y - p1.y) / (p2.x - p1.x) * (position.x - p1.x) + p1.y;
		//log("tempy = %f, position.y = %f", tempy, position.y);
		if (tempy < position.y) {
		//	log("plus 1");
			ny++;
		}
		else {
		//	log("minus 1");
		}
	}
	if (ny % 2 == 1) {
		x = (position.x - 64) / 128;
	}
	//log("x = %d, ny = %d", x, ny);
	return Vec2(x, ny);
}

void EarthMap::EndGame(int num) {
	if (num == 1) {
		UpdateMonsterDB();
	}
	
	EndGame_Num = num;
	
	Scene* popWin;
	popWin = EndGame::createScene();
	this->addChild(popWin, 3000, 3000);
}

void EarthMap::UpdateMonsterDB() {
	sqlite3* pDB = nullptr;
	char* errMsg = nullptr;
	int result;

	//select Coin
	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d   Msg:%s", result, errMsg);
	}
	int before_Coin = 0;
	// select data
	std::string sqlStr;
	sqlStr = "select _Id, Coin from Player";

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		std::string str1 = "";
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			int ID = sqlite3_column_int(statement, 0);
			before_Coin = sqlite3_column_int(statement, 1);
		}

		//lblStatus->setString(str1);
	}
	sqlite3_finalize(statement);

	sqlite3_close(pDB);



	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d  Msg:%s", result, errMsg);
	}

	char sqlstr[200];

	for (int i = 0; i < monsterSize; i++) {
		//Monster table
		int ID = monster_char[i].ID;
		int type = monster_char[i].Type;
		int level = monster_char[i].level;
		int Item1 = monster_char[i].Item1;
		int Item2 = monster_char[i].Item2;
		int Item3 = monster_char[i].Item3;
		int Exp = monster_char[i].exp;
		sprintf(sqlstr, "update Monster set Type = %d, level = %d, Item1 = %d, Item2 = %d, Item3 = %d, Exp = %d  where Monster_Id = %d", type, level, Item1, Item2, Item3, Exp, ID);
		//log(sqlstr);
		sqlStr = sqlstr;
		result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);


		if (result != SQLITE_OK)
		{
			log("update Error : Code:%d  Msg:%s", result, errMsg);
		}
	}

	//update Coin
	sprintf(sqlstr, "update Player set Coin = %d where _Id = 1", before_Coin + Coin);
	//log(sqlstr);
	sqlStr = sqlstr;
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	if (result != SQLITE_OK)
	{
		log("update Error : Code:%d  Msg:%s", result, errMsg);
	}

	sqlite3_close(pDB);
}

void EarthMap::UpdateItemDB(int num) {
	sqlite3* pDB = nullptr;
	char* errMsg = nullptr;
	int result;


	//select Items
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

	int DeleteItem = 0;
	for (int i = 0; i < ItemsListSize; i++) {
		if (Items_List[i]._ID == num + 5) {
			DeleteItem = Items_List[i].Num;
		}
	}

	//update Items
	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		log("Open Error : Code:%d  Msg:%s", result, errMsg);
	}

	char sqlstr[200];

	sprintf(sqlstr, "update Items set Num = %d  where _ID = %d", DeleteItem - 1, num + 5);
	//log(sqlstr);
	sqlStr = sqlstr;
	result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);


	if (result != SQLITE_OK)
	{
		log("update Error : Code:%d  Msg:%s", result, errMsg);
	}
	
	sqlite3_close(pDB);

	if (ItemsListSize) {
		free(Items_List);
		ItemsListSize = 0;
	}
}