#include "FirstScene.h"
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
	sword = false;
	right_sword = false;
	mase = false;
	key = false;
	item = 0;
	winSize2 = Director::getInstance()->getWinSize();

	tmap2 = TMXTiledMap::create("TileMaps/HolygrailTile2.tmx");
	background2 = tmap2->getLayer("Background");
	items2 = tmap2->getLayer("Items2");
	Tree = tmap2->getLayer("Tree");
	metainfo2 = tmap2->getLayer("MetaInfo");
	metainfo2->setVisible(false);
	this->addChild(tmap2, 0, 11);

	auto objects = tmap2->getObjectGroup("Objects");

	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	dragonPosition2 = Vec2(x, y);
	texture = Director::getInstance()->getTextureCache()->addImage("TileMaps/front_man.png");
	this->createDragon2(dragonPosition2);
	createMenubar();
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

	bool bTouch = Resetbar->getBoundingBox().containsPoint(touchPoint);
	if (bTouch) {
		auto pScene = FirstScene::createScene();
		Director::getInstance()->replaceScene(pScene);
		return;
	}


	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = dragon2->getPosition();

	Vec2 diff = touchPoint - playerPos;
	//animation->addSpriteFrameWithTexture(texture, Rect(index * 130, rowIndex * 140, 130, 140));
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			
			texture = Director::getInstance()->getTextureCache()->addImage("TileMaps/right_man.png");
			removeChild(dragon2);
			this->createDragon2(playerPos);
			playerPos.x += tmap2->getTileSize().width;
		}
		else {
			
			texture = Director::getInstance()->getTextureCache()->addImage("TileMaps/left_man.png");
			removeChild(dragon2);
			this->createDragon2(playerPos);
			playerPos.x -= tmap2->getTileSize().width;
		}
	}
	else {
		if (diff.y > 0) {
			
			texture = Director::getInstance()->getTextureCache()->addImage("TileMaps/rear_man.png");
			removeChild(dragon2);
			this->createDragon2(playerPos);
			playerPos.y += tmap2->getTileSize().height;
		}
		else {
			
			texture = Director::getInstance()->getTextureCache()->addImage("TileMaps/front_man.png");
			removeChild(dragon2);
			this->createDragon2(playerPos);
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

void FirstScene::createDragon2(Vec2 vector) {
	animation = Animation::create();
	animation->setDelayPerUnit(0.2f);

	for (int i = 0; i < 3; i++) {
		int index = i % 3;
		int rowIndex = i / 3;

		animation->addSpriteFrameWithTexture(texture, Rect(index * 32, rowIndex * 48, 32, 48));
	}

	dragon2 = Sprite::createWithTexture(texture, Rect(0, 0, 32, 48));
	dragon2->setPosition(vector);
	this->addChild(dragon2);

	animate = Animate::create(animation);
	rep = RepeatForever::create(animate);
	dragon2->runAction(rep);


}

void FirstScene::createMenubar() {
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

	auto statusLabel = LabelTTF::create("Stage2", "", 18);
	statusLabel->setColor(Color3B::WHITE);
	statusLabel->setPosition(Vec2(448, 80));
	addChild(statusLabel);
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
			std::string item1 = properties.asValueMap()["Items"].asString();
			if (item1 == "wall") {
				log("wall....");
				return;
			}
			if (sword) {
				if (item1 == "wolf") {
					item++;
					this->metainfo2->removeTileAt(tileCoord);
					items2->removeTileAt(tileCoord);
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
					this->metainfo2->removeTileAt(tileCoord);
					items2->removeTileAt(tileCoord);
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
					this->metainfo2->removeTileAt(tileCoord);
					items2->removeTileAt(tileCoord);
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
				if (item == 22) {
					if (item1 == "box") {
						this->metainfo2->removeTileAt(tileCoord);
						items2->removeTileAt(tileCoord);
						auto pScene = SecondScene::createScene();
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
				this->metainfo2->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);
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
				this->metainfo2->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);
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
				this->metainfo2->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);
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
				this->metainfo2->removeTileAt(tileCoord);
				items2->removeTileAt(tileCoord);
				log("아이템 획득 !!! key");
			}
		}
	}
	dragon2->setPosition(position);
}
