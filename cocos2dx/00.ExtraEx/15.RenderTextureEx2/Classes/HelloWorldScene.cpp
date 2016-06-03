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
	
	winSize = Director::getInstance()->getWinSize();

	m_pTarget = RenderTexture::create(winSize.width, winSize.height, Texture2D::PixelFormat::RGBA8888);
	m_pTarget->retain();
	m_pTarget->setPosition(Vec2(120, 80));
	sprite_2 = Sprite::create("Images/image01.png");
	sprite_2->setPosition(Vec2(240, 160));
	this->addChild(sprite_2);
	sprite_2->addChild(m_pTarget, -1);
	
	MenuItemFont::setFontSize(16);
	item1 = MenuItemFont::create("Save Image", CC_CALLBACK_1(HelloWorld::saveImage, this));
	item1->setColor(Color3B::BLACK);
	item2 = MenuItemFont::create("Clear", CC_CALLBACK_1(HelloWorld::clearImage, this));
	item2->setColor(Color3B::BLACK);
	menu = Menu::create(item1, item2, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(winSize.width - 80, winSize.height - 30));
	this->addChild(menu, 3);

	tableView1 = TableView::create(this, Size(300, 100));
	tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2(90, 0));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	this->addChild(tableView1);
	tableView1->reloadData();
	num = 0;
	
	return true;
}

HelloWorld::~HelloWorld() {
	//m_pTarget->release();
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
	Vec2 start = touch->getLocation();
	Vec2 end = touch->getPreviousLocation();

	m_pTarget->begin();
	sprite_2->visit();
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

	m_pTarget->getSprite();

	char png[20];
	sprintf(png, "image-%d.png", counter);

	m_pTarget->saveToFile(png, Image::Format::PNG, true, nullptr);

	auto image = m_pTarget->newImage();

	auto tex = Director::getInstance()->getTextureCache()->addImage(image, png);
	CC_SAFE_DELETE(image);

	Director::getInstance()->getRenderer()->render();
	log("Image saved %s", png);
	
	counter++;
}

void HelloWorld::clearImage(Ref* sender) {
	m_pTarget->clear(255, 255, 255, 255);
	sprite_2 = Sprite::create("Images/image01.png");
	sprite_2->setPosition(Vec2(240, 160));
	this->addChild(sprite_2);
}

void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell) {
	num = cell->getIdx();
	for (int i = 0; i < sprite_vector.size(); i++) {
		if (cell->getChildByTag(num)->getTag() == sprite_vector.at(i)->getTag()) {
			sprite_vector.at(i)->setPosition(Vec2(0, 10));
		}
		else {
			sprite_vector.at(i)->setPosition(Vec2(0, 0));
		}
	}
	
	//tableCellAtIndex(table, cell->getIdx());
	log("Tag : %d\nCell touched at index : %ld , %d", table->getTag(), cell->getIdx(), cell->getChildByTag(num)->getTag());
}

Size HelloWorld::tableCellSizeForIndex(TableView *table, ssize_t idx) {
	
	return CCSizeMake(60, 60);
}

TableViewCell* HelloWorld::tableCellAtIndex(TableView *table, ssize_t idx) {
	//num = idx;

	char png[25];
	sprintf(png, "Images/crayon_%02d.png", (int)idx+1);
	auto string = String::createWithFormat("%d", idx);
	TableViewCell *cell = table->dequeueCell();
	
	cell = new CustomTableViewCell();
	cell->autorelease();
	sprite_1 = Sprite::create(png);
	sprite_1->setAnchorPoint(Vec2::ZERO); 
	if (num == idx) {
		sprite_1->setPosition(Vec2(0, 10));
	}
	else {
		sprite_1->setPosition(Vec2(0, 0));
	}
	sprite_1->setScale(0.4);
	sprite_1->setTag(idx);
	sprite_vector.pushBack(sprite_1);
	cell->addChild(sprite_1);

	auto label = LabelTTF::create(string->getCString(), "Helvetica", 20.0);
	label->setPosition(Vec2::ZERO);
	label->setAnchorPoint(Vec2::ZERO);
	label->setColor(Color3B::BLACK);
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
