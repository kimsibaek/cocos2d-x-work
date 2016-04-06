#include "HelloWorldScene.h"
#include "CustomTableViewCell.h"

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
	TableView* tableView1 = TableView::create(this, Size(300, 150));
	tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2(90, 0));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	this->addChild(tableView1);
	tableView1->reloadData();
	num = 1;
	auto sprite = Sprite::create("Images/image01.png");
	sprite->setPosition(Vec2(240, 160));
	this->addChild(sprite);

	winSize = Director::getInstance()->getWinSize();

	m_pTarget = RenderTexture::create(sprite->getPosition().x, sprite->getPosition().y, Texture2D::PixelFormat::RGBA8888);
	m_pTarget->retain();
	m_pTarget->setPosition(Vec2(sprite->getPosition().x, sprite->getPosition().y));

	this->addChild(m_pTarget, 1);

	MenuItemFont::setFontSize(16);
	auto item1 = MenuItemFont::create("Save Image", CC_CALLBACK_1(HelloWorld::saveImage, this));
	item1->setColor(Color3B::BLACK);
	auto item2 = MenuItemFont::create("Clear", CC_CALLBACK_1(HelloWorld::clearImage, this));
	item2->setColor(Color3B::BLACK);
	auto menu = Menu::create(item1, item2, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(winSize.width - 80, winSize.height - 30));
	this->addChild(menu, 3);

	return true;
}

HelloWorld::~HelloWorld() {
	m_pTarget->release();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Layer::onExit();
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event* event) {
	auto touch = touches[0];
	if (touch->getLocation().x < 120 || touch->getLocation().x > 360 || touch->getLocation().y < 80 || touch->getLocation().y > 240) {
		return;
	}
	Vec2 start = Vec2(touch->getLocation().x -120, touch->getLocation().y - 80);
	Vec2 end = Vec2(touch->getPreviousLocation().x - 120, touch->getPreviousLocation().y - 80);

	m_pTarget->begin();

	float distance = start.getDistance(end);
	if (distance > 1) {
		int d = (int)distance;
		m_pBrush.clear();
		for (int i = 0; i < d; ++i) {
			sprite_brush = Sprite::create("Images/brush2.png");
			//색깔 체인지
			SelectColor(num);
			m_pBrush.pushBack(sprite_brush);
		}
		for (int i = 0; i < d; i++) {
			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)i / distance;
			m_pBrush.at(i)->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
			m_pBrush.at(i)->setRotation(rand() % 360);
			float r = (float)(rand() % 50 / 50.f) + 0.25f;
			m_pBrush.at(i)->setScale(r);
			m_pBrush.at(i)->visit();
		}
	}
	m_pTarget->end();
}

void HelloWorld::saveImage(Ref* sender) {
	static int counter = 0;

	char png[20];
	sprintf(png, "C:\cocos2d-x-work\image-%d.png", counter);

	m_pTarget->saveToFile(png, Image::Format::PNG, true, nullptr);

	auto image = m_pTarget->newImage();

	auto tex = Director::getInstance()->getTextureCache()->addImage(image, png);
	CC_SAFE_DELETE(image);

	auto sprite = Sprite::createWithTexture(tex);

	sprite->setScale(0.3f);
	sprite->setPosition(Vec2(40, 40));
	sprite->setRotation(counter * 3);
	addChild(sprite);

	Director::getInstance()->getRenderer()->render();
	log("Image saved %s", png);

	counter++;
}

void HelloWorld::clearImage(Ref* sender) {
	//m_pTarget->clear(255, 255, 255, 255);
}

void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell) {
	num = cell->getIdx();
	SelectPosition(num);
	log("Tag : %d\nCell touched at index : %ld", table->getTag(), cell->getIdx());
}

Size HelloWorld::tableCellSizeForIndex(TableView *table, ssize_t idx) {
	
	return CCSizeMake(60, 60);
}

TableViewCell* HelloWorld::tableCellAtIndex(TableView *table, ssize_t idx) {
	//num = idx;
	
	auto string = String::createWithFormat("%ld", idx);

	TableViewCell *cell = table->dequeueCell();

		if (idx == 0) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_1 = Sprite::create("Images/crayon_01.png");
			sprite_1->setAnchorPoint(Vec2::ZERO);
			sprite_1->setPosition(Vec2(0, 0));
			sprite_1->setScale(0.4);
			cell->addChild(sprite_1);
		}
		else if (idx == 1) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_2 = Sprite::create("Images/crayon_02.png");
			sprite_2->setAnchorPoint(Vec2::ZERO);
			sprite_2->setScale(0.4);
			cell->addChild(sprite_2);
		}
		else if (idx == 2) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_3 = Sprite::create("Images/crayon_03.png");
			sprite_3->setAnchorPoint(Vec2::ZERO);
			sprite_3->setScale(0.4);
			cell->addChild(sprite_3);
		}
		else if (idx == 3) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_4 = Sprite::create("Images/crayon_04.png");
			sprite_4->setAnchorPoint(Vec2::ZERO);
			sprite_4->setScale(0.4);
			cell->addChild(sprite_4);
		}
		else if (idx == 4) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_5 = Sprite::create("Images/crayon_05.png");
			sprite_5->setAnchorPoint(Vec2::ZERO);
			sprite_5->setScale(0.4);
			cell->addChild(sprite_5);
		}
		else if (idx == 5) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_6 = Sprite::create("Images/crayon_06.png");
			sprite_6->setAnchorPoint(Vec2::ZERO);
			sprite_6->setScale(0.4);
			cell->addChild(sprite_6);
		}
		else if (idx == 6) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_7 = Sprite::create("Images/crayon_07.png");
			sprite_7->setAnchorPoint(Vec2::ZERO);
			sprite_7->setScale(0.4);
			cell->addChild(sprite_7);
		}
		else if (idx == 7) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_8 = Sprite::create("Images/crayon_08.png");
			sprite_8->setAnchorPoint(Vec2::ZERO);
			sprite_8->setScale(0.4);
			cell->addChild(sprite_8);
		}
		else if (idx == 8) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_9 = Sprite::create("Images/crayon_09.png");
			sprite_9->setAnchorPoint(Vec2::ZERO);
			sprite_9->setScale(0.4);
			cell->addChild(sprite_9);
		}
		else if (idx == 9) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_10 = Sprite::create("Images/crayon_10.png");
			sprite_10->setAnchorPoint(Vec2::ZERO);
			sprite_10->setScale(0.4);
			cell->addChild(sprite_10);
		}
		else if (idx == 10) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_11 = Sprite::create("Images/crayon_11.png");
			sprite_11->setAnchorPoint(Vec2::ZERO);
			sprite_11->setScale(0.4);
			cell->addChild(sprite_11);
		}
		else if (idx == 11) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_12 = Sprite::create("Images/crayon_12.png");
			sprite_12->setAnchorPoint(Vec2::ZERO);
			sprite_12->setScale(0.4);
			cell->addChild(sprite_12);
		}
		else if (idx == 12) {
			cell = new CustomTableViewCell();
			cell->autorelease();
			sprite_13 = Sprite::create("Images/crayon_13.png");
			sprite_13->setAnchorPoint(Vec2::ZERO);
			sprite_13->setScale(0.4);
			cell->addChild(sprite_13);
		}

		auto label = LabelTTF::create(string->getCString(), "Helvetica", 20.0);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);
		cell->addChild(label);
	

	return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(TableView *table) {
	return 13;
}

void HelloWorld::SelectColor(int number) {
	if (number == 0) {
		sprite_brush->setColor(Color3B::RED);
	}
	else if (number == 1) {
		sprite_brush->setColor(Color3B::ORANGE);
	}
	else if (number == 2) {
		sprite_brush->setColor(Color3B::YELLOW);
	}
	else if (number == 3) {
		sprite_brush->setColor(Color3B::GREEN);
	}
	else if (number == 4) {
		sprite_brush->setColor(Color3B::BLUE);
	}
	else if (number == 5) {    //핑크
		sprite_brush->setColor(Color3B(255, 90, 200));
	}
	else if (number == 6) {			//보라
		sprite_brush->setColor(Color3B(255, 0, 255));
	}
	else if (number == 7) {
		sprite_brush->setColor(Color3B::WHITE);
	}
	else if (number == 8) {
		sprite_brush->setColor(Color3B::BLACK);
	}
	else if (number == 9) {
		sprite_brush->setColor(Color3B::GRAY);
	}
	else if (number == 10) {		//갈색
		sprite_brush->setColor(Color3B(128, 0, 0));
	}
	else if (number == 11) {
		sprite_brush->setColor(Color3B(255, 255, 125));
	}
	else if (number == 12) {
		sprite_brush->setColor(Color3B(255, 255, 200));
	}
}

void HelloWorld::SelectPosition(int number) {
	sprite_1->setPosition(Vec2(0, 0));
	sprite_2->setPosition(Vec2(0, 0));
	sprite_3->setPosition(Vec2(0, 0));
	sprite_4->setPosition(Vec2(0, 0));
	sprite_5->setPosition(Vec2(0, 0));
	if (number == 0) {
		sprite_1->setPosition(Vec2(0, 10));
	}
	else if (number == 1) {
		sprite_2->setPosition(Vec2(0, 10));
	}
	else if (number == 2) {
		sprite_3->setPosition(Vec2(0, 10));
	}
	else if (number == 3) {
		sprite_4->setPosition(Vec2(0, 10));
	}
	else if (number == 4) {
		sprite_5->setPosition(Vec2(0, 10));
	}
	else if (number == 5) {    //핑크
		sprite_6->setPosition(Vec2(0, 10));
	}
	else if (number == 6) {			//보라
		sprite_7->setPosition(Vec2(0, 10));
	}
	else if (number == 7) {
		sprite_8->setPosition(Vec2(0, 10));
	}
	else if (number == 8) {
		sprite_9->setPosition(Vec2(0, 10));
	}
	else if (number == 9) {
		sprite_10->setPosition(Vec2(0, 10));
	}
	else if (number == 10) {		//갈색
		sprite_11->setPosition(Vec2(0, 10));
	}
	else if (number == 11) {
		sprite_12->setPosition(Vec2(0, 10));
	}
	else if (number == 12) {
		sprite_13->setPosition(Vec2(0, 10));
	}
}