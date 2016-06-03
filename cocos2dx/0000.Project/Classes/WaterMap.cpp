#include "WaterMap.h"
#include "pauseScene.h"
#include "MainScene.h"
#include "sqlite3.h"
USING_NS_CC;

Scene* WaterMap::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WaterMap::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool WaterMap::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	////////////////////
	BG = Sprite::create("Images/Scene/watermap.png");
	BG->setPosition(Vec2(1006.5, 767.5));
	this->addChild(BG, 1);

	this->setPosition(Vec2(0, 0));

	tmap = TMXTiledMap::create("Images/Scene/WaterMapTest.tmx");
	tmap->setPosition(Vec2(-33, -16));
	metainfo = tmap->getLayer("MetaInfo");
	//metainfo->setVisible(false);
	this->addChild(tmap, 2, 11);

	MovePositionX = 0;
	MovePositionY = 0;

	pause = Sprite::create("Images/Scene/pause.png");
	pause->setPosition(Vec2(1230, 670));
	pause->setScale(0.4);
	this->addChild(pause, 3);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(WaterMap::doMsgReceived), "TouchStatus", nullptr);

	return true;
}

void WaterMap::doMsgReceived(Ref* obj) {
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

void WaterMap::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(WaterMap::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(WaterMap::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(WaterMap::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void WaterMap::onExit() {
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}

bool WaterMap::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
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

void WaterMap::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	winSize = Director::getInstance()->getWinSize();

	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	EndDragPosition = touchPoint;
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

void WaterMap::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);
	Vec2 test = tileCoordForPosition(touchPoint);
	log("%f, %f", test.x, test.y);
}

Vec2 WaterMap::tileCoordForPosition(cocos2d::Vec2 position) {
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

