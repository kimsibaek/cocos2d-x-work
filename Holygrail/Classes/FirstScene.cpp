﻿#include "FirstScene.h"
#include "SecondScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

Scene* FirstScene::createScene()
{
    auto scene = Scene::create();
    auto layer = FirstScene::create();
    scene->addChild(layer);
    return scene;
}

bool FirstScene::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 255, 0, 255) ))
    {
        return false;
    }

	winSize2 = Director::getInstance()->getWinSize();

	tmap2 = TMXTiledMap::create("TileMaps/HolygrailTile2.tmx");
	background2 = tmap2->getLayer("Background");
	items2 = tmap2->getLayer("Items2");
	items2->setVisible(true);
	metainfo2 = tmap2->getLayer("MetaInfo");
	metainfo2->setVisible(false);
	this->addChild(tmap2, 0, 11);

	auto objects = tmap2->getObjectGroup("Objects");

	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	dragonPosition2 = Vec2(x, y);

	this->createDragon2();

    return true;
}
void FirstScene::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(FirstScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(FirstScene::onTouchEnded, this);
	//listener->onTouchEnded = CC_CALLBACK_2(FirstScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void FirstScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}
bool FirstScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	//auto touchPoint = touch->getLocation();

	return true;
}


void FirstScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = dragon2->getPosition();

	Vec2 diff = touchPoint - playerPos;
	//animation->addSpriteFrameWithTexture(texture, Rect(index * 130, rowIndex * 140, 130, 140));
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += tmap2->getTileSize().width;

			dragon2->setFlippedX(true);
		}
		else {
			playerPos.x -= tmap2->getTileSize().width;

			dragon2->setFlippedX(false);
		}
	}
	else {
		if (diff.y > 0) {
			playerPos.y += tmap2->getTileSize().height;
		}
		else {
			playerPos.y -= tmap2->getTileSize().height;
		}
	}

	if (playerPos.x <= (tmap2->getMapSize().width * tmap2->getTileSize().width) && playerPos.y <= (tmap2->getMapSize().height* tmap2->getTileSize().height) && playerPos.y >= 0 && playerPos.x >= 0) {
		this->setPlayerPosition2(playerPos);
		//dragon->setPosition(playerPos);
	}

	this->setViewpointCenter2(dragon2->getPosition());

}

void FirstScene::setViewpointCenter2(Vec2 position) {
	int x = MAX(position.x, winSize2.width / 2);
	int y = MAX(position.y, winSize2.height / 2);

	x = MIN(x, (tmap2->getMapSize().width * tmap2->getTileSize().width) - winSize2.width / 2);
	y = MIN(y, (tmap2->getMapSize().height * tmap2->getTileSize().height) - winSize2.height / 2);

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize2.width / 2, winSize2.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;

	this->setPosition(viewPoint);
}

void FirstScene::createDragon2() {
	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/Holygrail.png");

	dragon2 = Sprite::createWithTexture(texture, Rect(0, 0, 32, 48));
	dragon2->setPosition(dragonPosition2);
	this->addChild(dragon2);

	dragon2->setFlippedX(true);

	dragon2->setScale(0.5);

}

Vec2 FirstScene::tileCoordForPosition2(cocos2d::Vec2 position) {
	int x = position.x / tmap2->getTileSize().width;
	int y = ((tmap2->getMapSize().height * tmap2->getTileSize().height) - position.y) / tmap2->getTileSize().height;
	return Vec2(x, y);
}

void FirstScene::setPlayerPosition2(Vec2 position) {
	Vec2 tileCoord = this->tileCoordForPosition2(position);

	int tileGid = this->metainfo2->getTileGIDAt(tileCoord);

	if (tileGid) {
		Value properties = tmap2->getPropertiesForGID(tileGid);

		if (!properties.isNull()) {
			std::string item1 = properties.asValueMap()["Item"].asString();
			if (item1 == "sword") {
				this->metainfo2->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);

				log("아이템 획득 !!! sword");
			}
			if (item1 == "monster") {
				this->metainfo2->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);

				log("아이템 획득 !!! monster");
			}
			if (item1 == "wolf") {
				this->metainfo2->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);

				log("아이템 획득 !!! wolf");
			}
			if (item1 == "water") {
				this->metainfo2->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);

				log("아이템 획득 !!! water");
			}
			if (item1 == "bag") {
				this->metainfo2->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);
				auto pScene = SecondScene::createScene();
				Director::getInstance()->replaceScene(pScene);
				log("아이템 획득 !!! bag");
			}
			if (item1 == "wall") {
				log("Wall...");
				return;
			}
		}
	}
	dragon2->setPosition(position);
}