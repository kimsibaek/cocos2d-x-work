#include "SecondScene.h"
#include "FirstScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

Scene* SecondScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SecondScene::create();
	scene->addChild(layer);
	return scene;
}

bool SecondScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 255, 0, 255)))
	{
		return false;
	}

	winSize = Director::getInstance()->getWinSize();

	tmap = TMXTiledMap::create("TileMaps/HolygrailTile3.tmx");
	background = tmap->getLayer("Background");
	items2 = tmap->getLayer("Items2");
	items2->setVisible(true);
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap, 0, 11);

	auto objects = tmap->getObjectGroup("Objects");

	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	dragonPosition = Vec2(x, y);

	this->createDragon();

	return true;
}
void SecondScene::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(SecondScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SecondScene::onTouchEnded, this);
	//listener->onTouchEnded = CC_CALLBACK_2(SecondScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void SecondScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}
bool SecondScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	//auto touchPoint = touch->getLocation();

	return true;
}


void SecondScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = dragon->getPosition();

	Vec2 diff = touchPoint - playerPos;
	//animation->addSpriteFrameWithTexture(texture, Rect(index * 130, rowIndex * 140, 130, 140));
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += tmap->getTileSize().width;

			dragon->setFlippedX(true);
		}
		else {
			playerPos.x -= tmap->getTileSize().width;

			dragon->setFlippedX(false);
		}
	}
	else {
		if (diff.y > 0) {
			playerPos.y += tmap->getTileSize().height;
		}
		else {
			playerPos.y -= tmap->getTileSize().height;
		}
	}

	if (playerPos.x <= (tmap->getMapSize().width * tmap->getTileSize().width) && playerPos.y <= (tmap->getMapSize().height* tmap->getTileSize().height) && playerPos.y >= 0 && playerPos.x >= 0) {
		this->setPlayerPosition(playerPos);
		//dragon->setPosition(playerPos);
	}

	this->setViewpointCenter(dragon->getPosition());

}

void SecondScene::setViewpointCenter(Vec2 position) {
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	x = MIN(x, (tmap->getMapSize().width * tmap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tmap->getMapSize().height * tmap->getTileSize().height) - winSize.height / 2);

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;

	this->setPosition(viewPoint);
}

void SecondScene::createDragon() {
	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/Holygrail.png");

	dragon = Sprite::createWithTexture(texture, Rect(0, 0, 32, 48));
	dragon->setPosition(dragonPosition);
	this->addChild(dragon);

	dragon->setFlippedX(true);

	dragon->setScale(0.5);

}

Vec2 SecondScene::tileCoordForPosition(cocos2d::Vec2 position) {
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height;
	return Vec2(x, y);
}

void SecondScene::setPlayerPosition(Vec2 position) {
	Vec2 tileCoord = this->tileCoordForPosition(position);

	int tileGid = this->metainfo->getTileGIDAt(tileCoord);

	if (tileGid) {
		Value properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull()) {
			std::string item1 = properties.asValueMap()["Item"].asString();
			if (item1 == "sword") {
				this->metainfo->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);

				log("아이템 획득 !!! sword");
			}
			if (item1 == "monster") {
				this->metainfo->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);

				log("아이템 획득 !!! monster");
			}
			if (item1 == "wolf") {
				this->metainfo->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);

				log("아이템 획득 !!! wolf");
			}
			if (item1 == "water") {
				this->metainfo->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);

				log("아이템 획득 !!! water");
			}
			if (item1 == "bag") {
				this->metainfo->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);
				auto pScene = HelloWorld::createScene();
				Director::getInstance()->replaceScene(pScene);
				log("아이템 획득 !!! bag");
			}
			if (item1 == "wall") {
				log("Wall...");
				return;
			}
		}
	}
	dragon->setPosition(position);
}
