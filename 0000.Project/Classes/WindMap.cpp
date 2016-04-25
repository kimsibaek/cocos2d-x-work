#include "WindMap.h"

USING_NS_CC;

Scene* WindMap::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WindMap::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WindMap::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	////////////////////
	BG = Sprite::create("Images/Scene/windmap.png");
	BG->setPosition(Vec2(1006.5, 767.5));
	this->addChild(BG, 1);

	this->setPosition(Vec2(0, 0));

	tmap = TMXTiledMap::create("Images/Scene/WindMap1.tmx");
	tmap->setPosition(Vec2(-31.5, -15.5));
	metainfo = tmap->getLayer("MetaInfo");
	//metainfo->setVisible(false);
	this->addChild(tmap, 2, 11);

	return true;
}

void WindMap::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(WindMap::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(WindMap::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(WindMap::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void WindMap::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}

bool WindMap::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	StartDragPosition = touchPoint;
	return true;
}

void WindMap::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {

	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	EndDragPosition = touchPoint;
	log("BG %f, %f", BG->getPosition().x, BG->getPosition().y);
	log("tmap %f, %f", tmap->getPosition().x, tmap->getPosition().y);
	float x = BG->getPosition().x + (EndDragPosition.x - StartDragPosition.x);
	float y = BG->getPosition().y + (EndDragPosition.y - StartDragPosition.y);
	if (x < -46.5) {
		x = -46.5;
	}
	else if (x > 1006.5) {
		x = 1006.5;
	}
	if (y < -62.5) {
		y = -62.5;
	}
	else if (y > 767.5) {
		y = 767.5;
	}
	BG->setPosition(Vec2(x,y));
	float tx = tmap->getPosition().x + (EndDragPosition.x - StartDragPosition.x);
	float ty = tmap->getPosition().y + (EndDragPosition.y - StartDragPosition.y);
	if (tx < -1053) {
		tx = -1053;
	}
	else if (tx > -31.5) {
		tx = -31.5;
	}
	if (ty < -845) {
		ty = -845;
	}
	else if (ty > -15.5) {
		ty = -15.5;
	}
	tmap->setPosition(Vec2(tx, ty));

	StartDragPosition = EndDragPosition;
}

void WindMap::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);
	Vec2 test = tileCoordForPosition(touchPoint);
	log("%f, %f", test.x, test.y);
}

Vec2 WindMap::tileCoordForPosition(cocos2d::Vec2 position) {
	log("%f, %f", position.x, tmap->getTileSize().width);
	int x = (position.x + 31.5) / tmap->getTileSize().width;
	log("%f, %f, %f", tmap->getMapSize().height, tmap->getTileSize().height, position.y);
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - (position.y + 15.5)) / tmap->getTileSize().height;
	log("%d, %d", x, y);
	return Vec2(x, y);
}

void WindMap::setPlayerPosition(cocos2d::Vec2 position) {
	//Vec2 tileCoord = this->tileCoordForPosition(position);
	////log("%f, %f", tileCoord.x , tileCoord.y);
	//int tileGid = this->metainfo->getTileGIDAt(tileCoord);
	////log("%d", tileGid);
	//if (tileGid) {
	//	Value properties = tmap->getPropertiesForGID(tileGid);

	//	if (!properties.isNull()) {
	//		std::string item1 = properties.asValueMap()["Items"].asString();
	//		if (item1 == "wall") {
	//			log("wall....");
	//			return;
	//		}
	//		if (sword) {
	//			if (item1 == "wolf") {
	//				item++;
	//				this->metainfo->removeTileAt(tileCoord);
	//				items->removeTileAt(tileCoord);
	//				dragon->getBoundingBox().containsPoint(position);
	//				for (int i = 0; i < MonsterVector.size(); i++) {
	//					if (MonsterVector.at(i)->getPosition().x - 16 <= position.x && MonsterVector.at(i)->getPosition().x + 16 >= position.x && MonsterVector.at(i)->getPosition().y + 16 >= position.y && MonsterVector.at(i)->getPosition().y - 16 <= position.y) {
	//						//log("%f, %f, %f, %f", position.x, position.y, MonsterVector.at(i)->getPosition().x, MonsterVector.at(i)->getPosition().y);
	//						log("%d, %f, %f", MonsterVector.at(i)->getTag(), MonsterVector.at(i)->getPosition().x, MonsterVector.at(i)->getPosition().y);

	//						removeChildByTag(MonsterVector.at(i)->getTag());
	//						break;
	//					}
	//				}
	//				log("아이템 획득 !!! wolf");
	//			}
	//		}
	//		else {
	//			if (item1 == "wolf") {
	//				log("wolf를 죽이지 못합니다.");
	//				return;
	//			}
	//		}

	//		if (right_sword) {
	//			if (item1 == "devil") {
	//				item++;
	//				this->metainfo->removeTileAt(tileCoord);
	//				items->removeTileAt(tileCoord);
	//				for (int i = 0; i < MonsterVector.size(); i++) {
	//					if (MonsterVector.at(i)->getPosition().x - 16 <= position.x && MonsterVector.at(i)->getPosition().x + 16 >= position.x && MonsterVector.at(i)->getPosition().y + 16 >= position.y && MonsterVector.at(i)->getPosition().y - 16 <= position.y) {
	//						//log("%f, %f, %f, %f", position.x, position.y, MonsterVector.at(i)->getPosition().x, MonsterVector.at(i)->getPosition().y);
	//						log("%d, %f, %f", MonsterVector.at(i)->getTag(), MonsterVector.at(i)->getPosition().x, MonsterVector.at(i)->getPosition().y);

	//						removeChildByTag(MonsterVector.at(i)->getTag());
	//						break;
	//					}
	//				}
	//				log("아이템 획득 !!! devil");
	//			}
	//		}
	//		else {
	//			if (item1 == "devil") {
	//				log("devil을 죽이지 못합니다.");
	//				return;
	//			}
	//		}
	//		if (mase) {
	//			if (item1 == "water") {
	//				item++;
	//				this->metainfo->removeTileAt(tileCoord);
	//				items->removeTileAt(tileCoord);
	//				for (int i = 0; i < MonsterVector.size(); i++) {
	//					if (MonsterVector.at(i)->getPosition().x - 16 <= position.x && MonsterVector.at(i)->getPosition().x + 16 >= position.x && MonsterVector.at(i)->getPosition().y + 16 >= position.y && MonsterVector.at(i)->getPosition().y - 16 <= position.y) {
	//						//log("%f, %f, %f, %f", position.x, position.y, MonsterVector.at(i)->getPosition().x, MonsterVector.at(i)->getPosition().y);
	//						log("%d, %f, %f", MonsterVector.at(i)->getTag(), MonsterVector.at(i)->getPosition().x, MonsterVector.at(i)->getPosition().y);

	//						removeChildByTag(MonsterVector.at(i)->getTag());
	//						break;
	//					}
	//				}
	//				log("아이템 획득 !!! water");
	//			}
	//		}
	//		else {
	//			if (item1 == "water") {
	//				log("water을 죽이지 못합니다.");
	//				return;
	//			}
	//		}
	//		if (key) {
	//			if (item == 7) {
	//				if (item1 == "box") {
	//					this->metainfo->removeTileAt(tileCoord);
	//					items->removeTileAt(tileCoord);
	//					auto pScene = FirstScene::createScene();
	//					Director::getInstance()->replaceScene(pScene);
	//					log("아이템 획득 !!! box");
	//				}
	//			}
	//			else {
	//				log("Item이 부족 합니다.");
	//				return;
	//			}
	//		}
	//		else {
	//			if (item1 == "box") {
	//				log("box를 가지지 못합니다.");
	//				return;
	//			}
	//		}
	//		if (item1 == "sword") {
	//			item++;
	//			sword = true;
	//			right_sword = false;
	//			mase = false;
	//			key = false;
	//			removeChild(ItemsMenu);
	//			ItemsMenu = Sprite::create("TileMaps/sword.png");
	//			ItemsMenu->setPosition(Vec2(448, 288));
	//			this->addChild(ItemsMenu);

	//			this->metainfo->removeTileAt(tileCoord);
	//			items->removeTileAt(tileCoord);
	//			log("아이템 획득 !!! sword");
	//		}
	//		if (item1 == "right_sword") {
	//			item++;
	//			sword = false;
	//			right_sword = true;
	//			mase = false;
	//			key = false;
	//			removeChild(ItemsMenu);
	//			ItemsMenu = Sprite::create("TileMaps/right_sword.png");
	//			ItemsMenu->setPosition(Vec2(448, 288));
	//			this->addChild(ItemsMenu);
	//			this->metainfo->removeTileAt(tileCoord);
	//			items->removeTileAt(tileCoord);
	//			log("아이템 획득 !!! right_sword");
	//		}


	//		if (item1 == "mase") {
	//			item++;
	//			sword = false;
	//			right_sword = false;
	//			mase = true;
	//			key = false;
	//			removeChild(ItemsMenu);
	//			ItemsMenu = Sprite::create("TileMaps/mase.png");
	//			ItemsMenu->setPosition(Vec2(448, 288));
	//			this->addChild(ItemsMenu);
	//			this->metainfo->removeTileAt(tileCoord);
	//			items->removeTileAt(tileCoord);
	//			log("아이템 획득 !!! mase");
	//		}

	//		if (item1 == "key") {
	//			item++;
	//			sword = false;
	//			right_sword = false;
	//			mase = false;
	//			key = true;
	//			removeChild(ItemsMenu);
	//			ItemsMenu = Sprite::create("TileMaps/key.png");
	//			ItemsMenu->setPosition(Vec2(448, 288));
	//			this->addChild(ItemsMenu);
	//			this->metainfo->removeTileAt(tileCoord);
	//			items->removeTileAt(tileCoord);
	//			log("아이템 획득 !!! key");
	//		}
	//	}
	//}
	//dragon->setPosition(position);
}

