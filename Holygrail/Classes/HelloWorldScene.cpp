#include "HelloWorldScene.h"
#include "FirstScene.h"
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
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	sword = false;
	right_sword = false;
	mase = false;
	key = false;
	item = 0;
	winSize = Director::getInstance()->getWinSize();

	tmap = TMXTiledMap::create("TileMaps/HolygrailTile1.tmx");
	background = tmap->getLayer("Background");
	items = tmap->getLayer("Items");
	items->setVisible(true);
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap, 0, 11);

	auto objects = tmap->getObjectGroup("Objects");

	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	dragonPosition = Vec2(x, y);
	texture = Director::getInstance()->getTextureCache()->addImage("TileMaps/front_man.png");
	this->createDragon(dragonPosition);
	createMenubar();
	return true;
}
void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	//auto touchPoint = touch->getLocation();

	return true;
}


void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	
	auto touchPoint = touch->getLocation();
	
	bool bTouch = Resetbar->getBoundingBox().containsPoint(touchPoint);
	if (bTouch) {
		auto pScene = HelloWorld::createScene();
		Director::getInstance()->replaceScene(pScene);
		return;
	}

	//auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = dragon->getPosition();

	Vec2 diff = touchPoint - playerPos;
	//animation->addSpriteFrameWithTexture(texture, Rect(index * 130, rowIndex * 140, 130, 140));
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			texture = Director::getInstance()->getTextureCache()->addImage("TileMaps/right_man.png");
			removeChild(dragon);
			this->createDragon(playerPos);
			playerPos.x += tmap->getTileSize().width;
		}
		else {
			texture = Director::getInstance()->getTextureCache()->addImage("TileMaps/left_man.png");
			removeChild(dragon);
			this->createDragon(playerPos);
			playerPos.x -= tmap->getTileSize().width;
		}
	}
	else {
		if (diff.y > 0) {
			texture = Director::getInstance()->getTextureCache()->addImage("TileMaps/rear_man.png");
			removeChild(dragon);
			this->createDragon(playerPos);
			playerPos.y += tmap->getTileSize().height;
		}
		else {
			texture = Director::getInstance()->getTextureCache()->addImage("TileMaps/front_man.png");
			removeChild(dragon);
			this->createDragon(playerPos);
			playerPos.y -= tmap->getTileSize().height;
		}
	}

	if (playerPos.x <= (tmap->getMapSize().width * tmap->getTileSize().width) && playerPos.y <= (tmap->getMapSize().height* tmap->getTileSize().height) && playerPos.y >= 0 && playerPos.x >= 0) {
		this->setPlayerPosition(playerPos);
		//dragon->setPosition(playerPos);
	}

	this->setViewpointCenter(dragon->getPosition());

}

void HelloWorld::setViewpointCenter(Vec2 position) {
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	x = MIN(x, (tmap->getMapSize().width * tmap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tmap->getMapSize().height * tmap->getTileSize().height) - winSize.height / 2);

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;

	this->setPosition(viewPoint);
}

void HelloWorld::createDragon(Vec2 vector) {
	//man
	
	animation = Animation::create();
	animation->setDelayPerUnit(0.2f);

	for (int i = 0; i < 3; i++) {
		int index = i % 3;
		int rowIndex = i / 3;

		animation->addSpriteFrameWithTexture(texture, Rect(index * 32, rowIndex * 48, 32, 48));
	}

	dragon = Sprite::createWithTexture(texture, Rect(0, 0, 32, 48));
	dragon->setPosition(vector);
	this->addChild(dragon);

	animate = Animate::create(animation);
	rep = RepeatForever::create(animate);
	dragon->runAction(rep);
}

void HelloWorld::createMenubar() {
	auto Menuber = Sprite::create("TileMaps/Menuber.png");
	Menuber->setPosition(Vec2(448, 160));
	Menuber->setOpacity(128);
	this->addChild(Menuber);

	auto Itembar = Sprite::create("TileMaps/Itembar.png");
	Itembar->setPosition(Vec2(448, 288));
	this->addChild(Itembar);

	Resetbar = Sprite::create("TileMaps/Resetbar.png");
	Resetbar->setPosition(Vec2(448, 32));
	this->addChild(Resetbar);

	auto statusLabel = LabelTTF::create("Stage1", "", 18);
	statusLabel->setColor(Color3B::WHITE);
	statusLabel->setPosition(Vec2(448, 80));
	addChild(statusLabel);
}

Vec2 HelloWorld::tileCoordForPosition(cocos2d::Vec2 position) {
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height;
	return Vec2(x, y);
}

void HelloWorld::setPlayerPosition(Vec2 position) {
	Vec2 tileCoord = this->tileCoordForPosition(position);

	int tileGid = this->metainfo->getTileGIDAt(tileCoord);

	if (tileGid) {
		Value properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull()) {
			std::string item1 = properties.asValueMap()["Items"].asString();
			if (item1 == "wall") {
				log("wall....");
				return;
			}
			if (sword) {
				if (item1 == "wolf") {
					item++;
					this->metainfo->removeTileAt(tileCoord);
					items->removeTileAt(tileCoord);
					log("아이템 획득 !!! wolf");
				}
			}
			else {
				if (item1 == "wolf") {
					log("wolf를 죽이지 못합니다.");
					return;
				}
			}

			if (right_sword) {
				if (item1 == "devil") {
					item++;
					this->metainfo->removeTileAt(tileCoord);
					items->removeTileAt(tileCoord);
					log("아이템 획득 !!! devil");
				}
			}
			else {
				if (item1 == "devil") {
					log("devil을 죽이지 못합니다.");
					return;
				}
			}
			if (mase) {
				if (item1 == "water") {
					item++;
					this->metainfo->removeTileAt(tileCoord);
					items->removeTileAt(tileCoord);
					log("아이템 획득 !!! water");
				}
			}
			else {
				if (item1 == "water") {
					log("water을 죽이지 못합니다.");
					return;
				}
			}
			if (key) {
				if (item == 7) {
					if (item1 == "box") {
						this->metainfo->removeTileAt(tileCoord);
						items->removeTileAt(tileCoord);
						auto pScene = FirstScene::createScene();
						Director::getInstance()->replaceScene(pScene);
						log("아이템 획득 !!! box");
					}
				}
				else {
					log("Item이 부족 합니다.");
					return;
				}
			}
			else {
				if (item1 == "box") {
					log("box를 가지지 못합니다.");
					return;
				}
			}
			if (item1 == "sword") {
				item++;
				sword = true;
				right_sword = false;
				mase = false;
				key = false;
				removeChild(ItemsMenu);
				ItemsMenu = Sprite::create("TileMaps/sword.png");
				ItemsMenu->setPosition(Vec2(448, 288));
				this->addChild(ItemsMenu);

				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);
				log("아이템 획득 !!! sword");
			}
			if (item1 == "right_sword") {
				item++;
				sword = false;
				right_sword = true;
				mase = false;
				key = false;
				removeChild(ItemsMenu);
				ItemsMenu = Sprite::create("TileMaps/right_sword.png");
				ItemsMenu->setPosition(Vec2(448, 288));
				this->addChild(ItemsMenu);
				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);
				log("아이템 획득 !!! right_sword");
			}


			if (item1 == "mase") {
				item++;
				sword = false;
				right_sword = false;
				mase = true;
				key = false;
				removeChild(ItemsMenu);
				ItemsMenu = Sprite::create("TileMaps/mase.png");
				ItemsMenu->setPosition(Vec2(448, 288));
				this->addChild(ItemsMenu);
				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);
				log("아이템 획득 !!! mase");
			}

			if (item1 == "key") {
				item++;
				sword = false;
				right_sword = false;
				mase = false;
				key = true;
				removeChild(ItemsMenu);
				ItemsMenu = Sprite::create("TileMaps/key.png");
				ItemsMenu->setPosition(Vec2(448, 288));
				this->addChild(ItemsMenu);
				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);
				log("아이템 획득 !!! key");
			}
		}
	}
	dragon->setPosition(position);
}
