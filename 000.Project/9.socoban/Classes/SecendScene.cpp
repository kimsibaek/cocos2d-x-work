#include "SecendScene.h"
#include "ThirdScene.h"
USING_NS_CC;

Scene* SecendScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SecendScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SecendScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	////////////////////
	TagNum = 0;
	TagNum2 = 0;
	AfterCheck = false;
	IceMove = false;
	PenguinMove = false;
	winSize = Director::getInstance()->getWinSize();
	tmap = TMXTiledMap::create("Images/TileMapSocoban2.tmx");
	background = tmap->getLayer("Background");
	IceTile = tmap->getLayer("IceTile");
	FinishPoint = tmap->getLayer("FinishPoint");
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap);
	auto objects = tmap->getObjectGroup("Objects");
	ValueMap spawnPoint = objects->getObject("SpawnPoint");
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();
	PenguinPosition = Vec2(x, y);
	this->createPenguin(PenguinPosition);

	//버튼
	auto Right_button = MenuItemImage::create("Images/arrow1off.png", "Images/arrow1on.png", CC_CALLBACK_1(SecendScene::Right_button_Action, this));
	auto pMenu = Menu::create(Right_button, nullptr);
	pMenu->setPosition(430, 70);
	this->addChild(pMenu);

	auto Left_button = MenuItemImage::create("Images/arrow3off.png", "Images/arrow3on.png", CC_CALLBACK_1(SecendScene::Left_button_Action, this));
	auto pMenu1 = Menu::create(Left_button, nullptr);
	pMenu1->setPosition(350, 70);
	this->addChild(pMenu1);

	auto Up_button = MenuItemImage::create("Images/arrow4off.png", "Images/arrow4on.png", CC_CALLBACK_1(SecendScene::Up_button_Action, this));
	auto pMenu2 = Menu::create(Up_button, nullptr);
	pMenu2->setPosition(390, 110);
	this->addChild(pMenu2);

	auto Down_button = MenuItemImage::create("Images/arrow2off.png", "Images/arrow2on.png", CC_CALLBACK_1(SecendScene::Down_button_Action, this));
	auto pMenu3 = Menu::create(Down_button, nullptr);
	pMenu3->setPosition(390, 30);
	this->addChild(pMenu3);

	auto Back_button = MenuItemImage::create("Images/back_off.png", "Images/back_on.png", CC_CALLBACK_1(SecendScene::Back_button_Action, this));
	auto pMenu4 = Menu::create(Back_button, nullptr);
	pMenu4->setPosition(120, 50);
	this->addChild(pMenu4);

	auto Retset_button = MenuItemImage::create("Images/restart_off.png", "Images/restart_on.png", CC_CALLBACK_1(SecendScene::Retset_button_Action, this));
	auto pMenu5 = Menu::create(Retset_button, nullptr);
	pMenu5->setPosition(60, 50);
	this->addChild(pMenu5);

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 24; j++) {
			Vec2 tileCoord = this->tileCoordForPosition(Vec2(j * 20 + 10, i * 20 + 10));
			int tileGid = this->metainfo->getTileGIDAt(tileCoord);

			if (tileGid) {
				Value properties = tmap->getPropertiesForGID(tileGid);

				if (!properties.isNull()) {
					std::string item1 = properties.asValueMap()["Items"].asString();
					if (item1 == "ice") {
						texture = Director::getInstance()->getTextureCache()->addImage("Images/game.png");
						Ice = Sprite::createWithTexture(texture, Rect(0, 40, 20, 20));
						Ice->setPosition(Vec2(j * 20 + 10, i * 20 + 10));
						Ice->setTag(TagNum++);
						IceVector.pushBack(Ice);
						this->addChild(Ice);
						IceTile->removeTileAt(tileCoord);
						metainfo->removeTileAt(tileCoord);
					}
					if (item1 == "finish") {
						texture = Director::getInstance()->getTextureCache()->addImage("Images/game.png");
						Finish = Sprite::createWithTexture(texture, Rect(40, 0, 20, 20));
						Finish->setPosition(Vec2(j * 20 + 10, i * 20 + 10));
						Finish->setTag(TagNum2++);
						FinishVector.pushBack(Finish);
						//this->addChild(Finish);
						//FinishPoint->removeTileAt(tileCoord);
						//metainfo->removeTileAt(tileCoord);
					}
				}
			}
		}
	}
	return true;
}

void SecendScene::createPenguin(Vec2 vector) {
	//man
	texture = Director::getInstance()->getTextureCache()->addImage("Images/game.png");
	Penguin = Sprite::createWithTexture(texture, Rect(20, 20, 20, 20));
	Penguin->setPosition(vector);
	this->addChild(Penguin);
}

void SecendScene::onEnter() {
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SecendScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SecendScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void SecendScene::onExit() {
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}
bool SecendScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	return true;
}


void SecendScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

}

Vec2 SecendScene::tileCoordForPosition(cocos2d::Vec2 position) {
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height;
	return Vec2(x, y);
}

bool SecendScene::setPlayerPosition(Vec2 position, int num) {
	int ice_num = 100;
	Vec2 After2Postion;
	Vec2 IcePostion;
	if (num == 1) {
		After2Postion = position + Vec2(20, 0);
		IcePostion = After2Postion + Vec2(20, 0);
	}
	else if (num == 2) {
		After2Postion = position + Vec2(-20, 0);
		IcePostion = After2Postion + Vec2(-20, 0);
	}
	else if (num == 3) {
		After2Postion = position + Vec2(0, 20);
		IcePostion = After2Postion + Vec2(0, 20);
	}
	else if (num == 4) {
		After2Postion = position + Vec2(0, -20);
		IcePostion = After2Postion + Vec2(0, -20);
	}
	Vec2 tileCoord = this->tileCoordForPosition(After2Postion);
	for (int i = 0; i < IceVector.size(); i++) {
		if (IceVector.at(i)->getPosition().x - 10 <= After2Postion.x && IceVector.at(i)->getPosition().x + 10 >= After2Postion.x &&
			IceVector.at(i)->getPosition().y + 10 >= After2Postion.y && IceVector.at(i)->getPosition().y - 10 <= After2Postion.y) {

			IceMove = setIcePosition(After2Postion, num);
			ice_num = i;
			break;
		}
	}
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

	if (IceMove) {
		//BackPosition 기록
		auto spriteTemp = Sprite::create();
		spriteTemp->setPosition(IceVector.at(ice_num)->getPosition());
		spriteTemp->setTag(IceVector.at(ice_num)->getTag());
		BackPosition.pushBack(spriteTemp);
		BackPosition.pushBack(Penguin);
		//Ice 이동
		IceVector.at(ice_num)->setPosition(IcePostion);
		IceMove = false;
		AfterCheck = 0;
		return true;
	}
	if (ice_num == 100) {
		return true;
	}
	else {
		return false;
	}

}

bool SecendScene::setIcePosition(Vec2 position, int num) {
	Vec2 IcePostion;
	if (num == 1) {
		IcePostion = position + Vec2(20, 0);
	}
	else if (num == 2) {
		IcePostion = position + Vec2(-20, 0);
	}
	else if (num == 3) {
		IcePostion = position + Vec2(0, 20);
	}
	else if (num == 4) {
		IcePostion = position + Vec2(0, -20);
	}

	for (int i = 0; i < IceVector.size(); i++) {
		if (IceVector.at(i)->getPosition().x - 10 <= IcePostion.x && IceVector.at(i)->getPosition().x + 10 >= IcePostion.x &&
			IceVector.at(i)->getPosition().y + 10 >= IcePostion.y && IceVector.at(i)->getPosition().y - 10 <= IcePostion.y) {

			return false;
			break;
		}
	}
	Vec2 tileCoord = this->tileCoordForPosition(IcePostion);
	int tileGid = this->metainfo->getTileGIDAt(tileCoord);
	if (tileGid) {
		Value properties = tmap->getPropertiesForGID(tileGid);
		if (!properties.isNull()) {
			std::string item1 = properties.asValueMap()["Items"].asString();
			if (item1 == "wall") {
				log("wall....");
				AfterCheck = 0;
				return false;
			}
		}
	}
	return true;
}

void SecendScene::Right_button_Action(Ref* pSender) {
	Vec2 playerPos = Penguin->getPosition();
	AfterPosition = playerPos + Vec2(20, 0);
	PenguinMove = setPlayerPosition(playerPos, 1);
	if (PenguinMove) {
		removeChild(Penguin);
		this->createPenguin(AfterPosition);
	}
	FinishCheck();
}

void SecendScene::Left_button_Action(Ref* pSender) {
	Vec2 playerPos = Penguin->getPosition();
	AfterPosition = playerPos + Vec2(-20, 0);
	PenguinMove = setPlayerPosition(playerPos, 2);
	if (PenguinMove) {
		removeChild(Penguin);
		this->createPenguin(AfterPosition);
	}
	FinishCheck();
}

void SecendScene::Up_button_Action(Ref* pSender) {
	Vec2 playerPos = Penguin->getPosition();
	AfterPosition = playerPos + Vec2(0, 20);
	PenguinMove = setPlayerPosition(playerPos, 3);
	if (PenguinMove) {
		removeChild(Penguin);
		this->createPenguin(AfterPosition);
	}
	FinishCheck();
}

void SecendScene::Down_button_Action(Ref* pSender) {
	Vec2 playerPos = Penguin->getPosition();
	AfterPosition = playerPos + Vec2(0, -20);
	PenguinMove = setPlayerPosition(playerPos, 4);
	if (PenguinMove) {
		removeChild(Penguin);
		this->createPenguin(AfterPosition);
	}
	FinishCheck();
}

void SecendScene::Back_button_Action(Ref* pSender) {
	if (!BackPosition.size()) {
		return;
	}
	for (int i = BackPosition.size() - 1; i > BackPosition.size() - 3; i--) {
		if (i == BackPosition.size() - 1) {		//penguin back
			removeChild(Penguin);
			this->createPenguin(BackPosition.at(i)->getPosition());
		}
		else {									//ice back
			for (int m = 0; m < IceVector.size(); m++) {
				if (IceVector.at(m)->getTag() == BackPosition.at(i)->getTag()) {
					IceVector.at(m)->setPosition(BackPosition.at(i)->getPosition());
					break;
				}
			}
		}
	}
}

void SecendScene::Retset_button_Action(Ref* pSender) {
	auto pScene = SecendScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void SecendScene::FinishCheck() {
	int num = 0;
	for (int i = 0; i < FinishVector.size(); i++) {
		for (int m = 0; m < IceVector.size(); m++) {
			if (IceVector.at(m)->getPosition().x - 10 <= FinishVector.at(i)->getPosition().x && IceVector.at(m)->getPosition().x + 10 >= FinishVector.at(i)->getPosition().x &&
				IceVector.at(m)->getPosition().y + 10 >= FinishVector.at(i)->getPosition().y && IceVector.at(m)->getPosition().y - 10 <= FinishVector.at(i)->getPosition().y) {
				num++;
				break;
			}
		}
	}

	if (num == FinishVector.size()) {
		//다음판으로
		auto pScene = ThirdScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
}