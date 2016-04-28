#include "EarthMap.h"
#include "pauseScene.h"
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

	BG = Sprite::create("Images/Scene/EarthMap.png");
	BG->setPosition(Vec2(1006.5, 767.5));
	this->addChild(BG, 1);

	this->setPosition(Vec2(0, 0));

	tmap = TMXTiledMap::create("Images/Scene/EarthMapTest.tmx");
	tmap->setPosition(Vec2(-33, -16));
	metainfo = tmap->getLayer("MetaInfo");
	//metainfo->setVisible(false);
	this->addChild(tmap, 2, 11);

	MovePositionX = 0;
	MovePositionY = 0;
	//pause
	pause = Sprite::create("Images/Scene/pause.png");
	pause->setPosition(Vec2(1230, 670));
	pause->setScale(0.4);
	this->addChild(pause, 3);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(EarthMap::doMsgReceived), "TouchStatus", nullptr);

	//DB불러오기
	dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
	log("%s", dbfileName.c_str());
	//dbfileName = "C:\\cocos2d-x-work\\0000.Project\\SpiritualSoul\\Resources\\";
	//dbfileName = "C:\\cocos2d-x-work\\SpiritualSoul\\Resources\\";
	//log("%s", dbfileName.c_str());
	dbfileName = dbfileName + "SpiritualSoul.sqlite";
	log("%s", dbfileName.c_str());
	
	onCreateCharacter();
	onCreateEmyCharacter();
	//onMapCharacter();
	return true;
}

void EarthMap::onMapCharacter() {
	for (int i = 1; i < 31; i++) {
		for (int m = 1; m < 31; m++) {
			auto cache = SpriteFrameCache::getInstance();
			char str1[100];
			char str2[100];
			Vector<SpriteFrame*> animFrames;
			Sprite* sprite;
			cache->addSpriteFramesWithFile("Plist/Person.plist");
			sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
			sprintf(str1, "Person1-");
			sprite->setScale(1.5);
			if (m%2 == 0) {
				sprite->setPosition(32 + 64 * i, 1551 - (65 + 48 * m)); 
				
			}
			else {
				sprite->setPosition( 64 * i, 1551 - (65 + 48 * m));
			}
			//log("%d, %d, %f, %f", i, m, sprite->getPosition().x, sprite->getPosition().y);
			this->addChild(sprite, 3);
			TestPosition.pushBack(sprite);
			for (int i = 1; i < 5; i++) {
				sprintf(str2, "%s%d.png", str1, i);
				SpriteFrame* frame = cache->getSpriteFrameByName(str2);
				animFrames.pushBack(frame);
			}

			auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
			auto animate = Animate::create(animation);
			auto rep = RepeatForever::create(animate);
			sprite->runAction(rep);
		}
	}
}

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
	sqlStr = "select Monster_Id, Type, level, Item1, Item2, Item3 from Monster";

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

			//log("ID = %d, Type = %d, level = %d, Item1 = %d, Item2 = %d, Item3 = %d", ID, Type, level, Item1, Item2, Item3);
			
			monster_char[monsterSize].ID = ID;
			monster_char[monsterSize].Type = Type;
			monster_char[monsterSize].level = level;
			monster_char[monsterSize].Item1 = Item1;
			monster_char[monsterSize].Item2 = Item2;
			monster_char[monsterSize].Item3 = Item3;
			//log("ID = %d, Type = %d, level = %d, Item1 = %d, Item2 = %d, Item3 = %d", monster_char[monsterSize].ID, monster_char[monsterSize].Type, monster_char[monsterSize].level, monster_char[monsterSize].Item1, monster_char[monsterSize].Item2, monster_char[monsterSize].Item3);
			monsterSize++;
		}
	}
	sqlite3_finalize(statement);

	sqlite3_close(pDB);
	
	for (int i = 0; i < monsterSize; i++) {
		int num1 = rand() % 30 + 1;
		int num2 = rand() % 30 + 1;

		while (!ChecksPosition(num1, num2)) {
			num1 = rand() % 30 + 1;
			num2 = rand() % 30 + 1;
		}

		char str1[100];
		char str2[100];
		Vector<SpriteFrame*> animFrames;
		//log("monster_char[i].Type : %d", monster_char[i].Type);
		if (monster_char[i].Type == 0) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
			sprintf(str1, "Person1-");
		}
		/*else if (monster_char[i].Type == 1) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth1-1.png");
			sprintf(str1, "Earth1-");
		}
		else if (monster_char[i].Type == 2) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth2-1.png");
			sprintf(str1, "Earth2-");
		}
		else if (monster_char[i].Type == 3) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth3-1.png");
			sprintf(str1, "Earth3-");
		}
		else if (monster_char[i].Type == 4) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth4-1.png");
			sprintf(str1, "Earth4-");
		}
		else if (monster_char[i].Type == 5) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth5-1.png");
			sprintf(str1, "Earth5-");
		}
		else if (monster_char[i].Type == 6) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth6-1.png");
			sprintf(str1, "Earth6-");
		}
		else if (monster_char[i].Type == 7) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth7-1.png");
			sprintf(str1, "Earth7-");
		}
		else if (monster_char[i].Type == 8) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth8-1.png");
			sprintf(str1, "Earth8-");
		}
		else if (monster_char[i].Type == 9) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth9-1.png");
			sprintf(str1, "Earth9-");
		}
		else if (monster_char[i].Type == 10) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
			sprintf(str1, "Person1-");
		}
		else if (monster_char[i].Type == 11) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire1-1.png");
			sprintf(str1, "Fire1-");
		}
		else if (monster_char[i].Type == 12) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire2-1.png");
			sprintf(str1, "Fire2-");
		}
		else if (monster_char[i].Type == 13) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire3-1.png");
			sprintf(str1, "Fire3-");
		}
		else if (monster_char[i].Type == 14) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire4-1.png");
			sprintf(str1, "Fire4-");
		}
		else if (monster_char[i].Type == 15) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire5-1.png");
			sprintf(str1, "Fire5-");
		}
		else if (monster_char[i].Type == 16) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire6-1.png");
			sprintf(str1, "Fire6-");
		}
		else if (monster_char[i].Type == 17) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire7-1.png");
			sprintf(str1, "Fire7-");
		}
		else if (monster_char[i].Type == 18) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire8-1.png");
			sprintf(str1, "Fire8-");
		}
		else if (monster_char[i].Type == 19) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire9-1.png");
			sprintf(str1, "Fire9-");
		}
		else if (monster_char[i].Type == 20) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
			sprintf(str1, "Person1-");
		}
		else if (monster_char[i].Type == 21) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Water1-1.png");
			sprintf(str1, "Water1-");
		}
		else if (monster_char[i].Type == 22) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Water2-1.png");
			sprintf(str1, "Water2-");
		}
		else if (monster_char[i].Type == 23) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Water3-1.png");
			sprintf(str1, "Water3-");
		}
		else if (monster_char[i].Type == 24) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Water4-1.png");
			sprintf(str1, "Water4-");
		}
		else if (monster_char[i].Type == 25) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Water5-1.png");
			sprintf(str1, "Water5-");
		}
		else if (monster_char[i].Type == 26) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Water6-1.png");
			sprintf(str1, "Water6-");
		}
		else if (monster_char[i].Type == 27) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Water7-1.png");
			sprintf(str1, "Water7-");
		}
		else if (monster_char[i].Type == 28) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Water8-1.png");
			sprintf(str1, "Water8-");
		}
		else if (monster_char[i].Type == 29) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Water9-1.png");
			sprintf(str1, "Water9-");
		}
		else if (monster_char[i].Type == 30) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
			sprintf(str1, "Person1-");
		}
		else if (monster_char[i].Type == 31) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind1-1.png");
			sprintf(str1, "Wind1-");
		}
		else if (monster_char[i].Type == 32) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind2-1.png");
			sprintf(str1, "Wind2-");
		}
		else if (monster_char[i].Type == 33) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind3-1.png");
			sprintf(str1, "Wind3-");
		}
		else if (monster_char[i].Type == 34) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind4-1.png");
			sprintf(str1, "Wind4-");
		}
		else if (monster_char[i].Type == 35) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind5-1.png");
			sprintf(str1, "Wind5-");
		}
		else if (monster_char[i].Type == 36) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind6-1.png");
			sprintf(str1, "Wind6-");
		}
		else if (monster_char[i].Type == 37) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind7-1.png");
			sprintf(str1, "Wind7-");
		}
		else if (monster_char[i].Type == 38) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind8-1.png");
			sprintf(str1, "Wind8-");
		}
		else if (monster_char[i].Type == 39) {
			
			monster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
			sprintf(str1, "Wind9-");
		}
*/
		monster_char[i].sprite->setScale(1.5);
		if (num2 % 2 == 0) {
			monster_char[i].sprite->setPosition(32 + 64 * num1, 1551 - (75 + 48 * num2));
			monster_char[i].xPosition = 32 + 64 * num1;
			monster_char[i].yPosition = 1551 - (75 + 48 * num2);
			monster_char[i].xMovePosition = 32 + 64 * num1;
			monster_char[i].yMovePosition = 1551 - (75 + 48 * num2);
		}
		else {
			monster_char[i].sprite->setPosition(64 * num1, 1551 - (75 + 48 * num2));
			monster_char[i].xPosition = 64 * num1;
			monster_char[i].yPosition = 1551 - (75 + 48 * num2);
			monster_char[i].xMovePosition = 64 * num1;
			monster_char[i].yMovePosition = 1551 - (75 + 48 * num2);
		}
		log("monster_char[i] = %f, %f", monster_char[i].xPosition, monster_char[i].yPosition);
		this->addChild(monster_char[i].sprite, 3);

		for (int i = 1; i < 5; i++) {
			sprintf(str2, "%s%d.png", str1, i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str2);
			animFrames.pushBack(frame);
		}

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		monster_char[i].sprite->runAction(rep);
	}
	
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
			num = rand() % 40 + 1;
		}
		
		if (EmyMonsterSize)	EmyMonster_char = (Monster_num*)realloc(EmyMonster_char, sizeof(Monster_num) * (EmyMonsterSize + 1));
		else				EmyMonster_char = (Monster_num*)malloc(sizeof(Monster_num) * (EmyMonsterSize + 1));
		int	ID = i;
		int	Type = num;
		int	level = 1;
		int	Item1 = 0;
		int	Item2 = 0;
		int	Item3 = 0;

		//log("ID = %d, Type = %d, level = %d, Item1 = %d, Item2 = %d, Item3 = %d", ID, Type, level, Item1, Item2, Item3);

		EmyMonster_char[EmyMonsterSize].ID = ID;
		EmyMonster_char[EmyMonsterSize].Type = Type;
		EmyMonster_char[EmyMonsterSize].level = level;
		EmyMonster_char[EmyMonsterSize].Item1 = Item1;
		EmyMonster_char[EmyMonsterSize].Item2 = Item2;
		EmyMonster_char[EmyMonsterSize].Item3 = Item3;
		//log("ID = %d, Type = %d, level = %d, Item1 = %d, Item2 = %d, Item3 = %d", monster_char[monsterSize].ID, monster_char[monsterSize].Type, monster_char[monsterSize].level, monster_char[monsterSize].Item1, monster_char[monsterSize].Item2, monster_char[monsterSize].Item3);
		EmyMonsterSize++;
	}

	for (int i = 0; i < EmyMonsterSize; i++) {
		int num1 = rand() % 30 + 1;
		int num2 = rand() % 30 + 1;

		while (!ChecksPosition(num1, num2)) {
			num1 = rand() % 30 + 1;
			num2 = rand() % 30 + 1;
		}

		char str1[100];
		char str2[100];
		Vector<SpriteFrame*> animFrames;
		log("monster_char[i].Type : %d", EmyMonster_char[i].Type);
		if (EmyMonster_char[i].Type == 0) {

			EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
			sprintf(str1, "Person1-");
		}
		else if (EmyMonster_char[i].Type == 1) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth1-1.png");
		sprintf(str1, "Earth1-");
		}
		else if (EmyMonster_char[i].Type == 2) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth2-1.png");
		sprintf(str1, "Earth2-");
		}
		else if (EmyMonster_char[i].Type == 3) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth3-1.png");
		sprintf(str1, "Earth3-");
		}
		else if (EmyMonster_char[i].Type == 4) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth4-1.png");
		sprintf(str1, "Earth4-");
		}
		else if (EmyMonster_char[i].Type == 5) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth5-1.png");
		sprintf(str1, "Earth5-");
		}
		else if (EmyMonster_char[i].Type == 6) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth6-1.png");
		sprintf(str1, "Earth6-");
		}
		else if (EmyMonster_char[i].Type == 7) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth7-1.png");
		sprintf(str1, "Earth7-");
		}
		else if (EmyMonster_char[i].Type == 8) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth8-1.png");
		sprintf(str1, "Earth8-");
		}
		else if (EmyMonster_char[i].Type == 9) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Earth9-1.png");
		sprintf(str1, "Earth9-");
		}
		else if (EmyMonster_char[i].Type == 10) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
		}
		else if (EmyMonster_char[i].Type == 11) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire1-1.png");
		sprintf(str1, "Fire1-");
		}
		else if (EmyMonster_char[i].Type == 12) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire2-1.png");
		sprintf(str1, "Fire2-");
		}
		else if (EmyMonster_char[i].Type == 13) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire3-1.png");
		sprintf(str1, "Fire3-");
		}
		else if (EmyMonster_char[i].Type == 14) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire4-1.png");
		sprintf(str1, "Fire4-");
		}
		else if (EmyMonster_char[i].Type == 15) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire5-1.png");
		sprintf(str1, "Fire5-");
		}
		else if (EmyMonster_char[i].Type == 16) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire6-1.png");
		sprintf(str1, "Fire6-");
		}
		else if (EmyMonster_char[i].Type == 17) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire7-1.png");
		sprintf(str1, "Fire7-");
		}
		else if (EmyMonster_char[i].Type == 18) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire8-1.png");
		sprintf(str1, "Fire8-");
		}
		else if (EmyMonster_char[i].Type == 19) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Fire9-1.png");
		sprintf(str1, "Fire9-");
		}
		else if (EmyMonster_char[i].Type == 20) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
		}
		else if (EmyMonster_char[i].Type == 21) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water1-1.png");
		sprintf(str1, "Water1-");
		}
		else if (EmyMonster_char[i].Type == 22) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water2-1.png");
		sprintf(str1, "Water2-");
		}
		else if (EmyMonster_char[i].Type == 23) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water3-1.png");
		sprintf(str1, "Water3-");
		}
		else if (EmyMonster_char[i].Type == 24) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water4-1.png");
		sprintf(str1, "Water4-");
		}
		else if (EmyMonster_char[i].Type == 25) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water5-1.png");
		sprintf(str1, "Water5-");
		}
		else if (EmyMonster_char[i].Type == 26) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water6-1.png");
		sprintf(str1, "Water6-");
		}
		else if (EmyMonster_char[i].Type == 27) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water7-1.png");
		sprintf(str1, "Water7-");
		}
		else if (EmyMonster_char[i].Type == 28) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water8-1.png");
		sprintf(str1, "Water8-");
		}
		else if (EmyMonster_char[i].Type == 29) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Water9-1.png");
		sprintf(str1, "Water9-");
		}
		else if (EmyMonster_char[i].Type == 30) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
		}
		else if (EmyMonster_char[i].Type == 31) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind1-1.png");
		sprintf(str1, "Wind1-");
		}
		else if (EmyMonster_char[i].Type == 32) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind2-1.png");
		sprintf(str1, "Wind2-");
		}
		else if (EmyMonster_char[i].Type == 33) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind3-1.png");
		sprintf(str1, "Wind3-");
		}
		else if (EmyMonster_char[i].Type == 34) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind4-1.png");
		sprintf(str1, "Wind4-");
		}
		else if (EmyMonster_char[i].Type == 35) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind5-1.png");
		sprintf(str1, "Wind5-");
		}
		else if (EmyMonster_char[i].Type == 36) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind6-1.png");
		sprintf(str1, "Wind6-");
		}
		else if (EmyMonster_char[i].Type == 37) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind7-1.png");
		sprintf(str1, "Wind7-");
		}
		else if (EmyMonster_char[i].Type == 38) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind8-1.png");
		sprintf(str1, "Wind8-");
		}
		else if (EmyMonster_char[i].Type == 39) {

		EmyMonster_char[i].sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
		sprintf(str1, "Wind9-");
		}
		
		EmyMonster_char[i].sprite->setScale(1.5);
		if (num2 % 2 == 0) {
			EmyMonster_char[i].sprite->setPosition(32 + 64 * num1, 1551 - (75 + 48 * num2));
			EmyMonster_char[i].xPosition = 32 + 64 * num1;
			EmyMonster_char[i].yPosition = 1551 - (75 + 48 * num2);
			EmyMonster_char[i].xMovePosition = 32 + 64 * num1;
			EmyMonster_char[i].yMovePosition = 1551 - (75 + 48 * num2);
		}
		else {
			EmyMonster_char[i].sprite->setPosition(64 * num1, 1551 - (75 + 48 * num2));
			EmyMonster_char[i].xPosition = 64 * num1;
			EmyMonster_char[i].yPosition = 1551 - (75 + 48 * num2);
			EmyMonster_char[i].xMovePosition = 64 * num1;
			EmyMonster_char[i].yMovePosition = 1551 - (75 + 48 * num2);
		}
		log("EmyMonster_char[i] = %f, %f", EmyMonster_char[i].xPosition, EmyMonster_char[i].yPosition);
		this->addChild(EmyMonster_char[i].sprite, 3);

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

bool EarthMap::ChecksPosition(int num1, int num2) {
	//Vec2 pos; 
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

void EarthMap::doMsgReceived(Ref* obj) {
	char *inputStr = (char*)obj;
	char testText[20];
	sprintf(testText, "%s", inputStr);
	log("%s", testText);
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

void EarthMap::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(EarthMap::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(EarthMap::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(EarthMap::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void EarthMap::onExit() {
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}

bool EarthMap::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	StartDragPosition = touchPoint;

	bool bTouch = pause->getBoundingBox().containsPoint(touchPoint);
	if (bTouch) {
		log("Sprite clicked...");
		//Director::getInstance()->pause();
		Scene* popWin;
		popWin = pauseScene::createScene();
		this->addChild(popWin, 2000, 2000);
	}
	return true;
}

void EarthMap::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	winSize = Director::getInstance()->getWinSize();

	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	EndDragPosition = touchPoint;

	for (int i = 0; i < monsterSize; i++) {
		//log("move %f, %f", monster_char[i].xMovePosition, monster_char[i].yMovePosition);
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
		//log("move %f, %f", EmyMonster_char[i].xMovePosition, EmyMonster_char[i].yMovePosition);
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
	//log("BG = %f, %f", x, y);
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
	//log("tmap = %f, %f", tx, ty);
	tmap->setPosition(Vec2(tx, ty));

	MovePositionX = tx;
	MovePositionY = ty;

	StartDragPosition = EndDragPosition;
}

void EarthMap::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);
	Vec2 test = tileCoordForPosition(touchPoint);
	log("%f, %f", test.x, test.y);
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

