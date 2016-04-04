#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255) ))
    {
        return false;
    }
	winSize = Director::getInstance()->getWinSize();

	tmap = TMXTiledMap::create("TileMap/TileRun.tmx");
	tmap->setPosition(Vec2(0, 0));
	background = tmap->getLayer("Background");
	//metainfo = tmap->getLayer("MetaInfo");
	//metainfo->setVisible(false);

	auto myAction3 = MoveBy::create(0.1, Vec2(-32, 0));
	auto rep2 = RepeatForever::create(myAction3);
	tmap->runAction(rep2);

	this->addChild(tmap, 0, 11);
	
	this->createWomen();

	this->schedule(schedule_selector(HelloWorld::tick1), 0.1f);
    return true;
}

void HelloWorld::createWomen() {
	
	Women = CCSprite::create("Images/grossinis_sister1.png");
	Women->setPosition(Vec2(144, 80));
	Women->setScale(0.3);
	this->addChild(Women);
}

Vec2 HelloWorld::tileCoordForPosition(cocos2d::Vec2 position) {
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height;
	return Vec2(x, y);
}


void HelloWorld::tick1(float f) {
	//log("tick1");
	Vec2 playerPos = Women->getPosition();
	
	this->setPlayerPosition(playerPos);
	
	
}

void HelloWorld::setPlayerPosition(Vec2 position) {
	//15번
	Vec2 point = this->background->convertToNodeSpace(position);
	//log("%f", point.x);
	if (point.x > 944) {
		tmap->setPosition(Vec2(0, 0));
	}
	Vec2 tileCoord = this->tileCoordForPosition(Vec2(point.x, point.y-32));

	int tileGid = this->background->getTileGIDAt(tileCoord);
	//log("%d", tileGid);
	if (!tileGid) {
		log("%d", tileGid);
	}
}