#include "IntroScene.h"
#include "MainScene.h"
#include <time.h>
#include <string.h>
USING_NS_CC;

Scene* IntroScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IntroScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	////////////////////
	srand(time(NULL));


	CCSprite* BG = CCSprite::create("Images/Scene/BG2.png");
	BG->setPosition(Vec2(640, 360-80));
	BG->setScale(1.6);
	this->addChild(BG);

	auto myAction = MoveTo::create(3, Vec2(640, 360+80));
	//auto myAction2 = FadeTo::create(2.0f, 200);
	//auto myAction3 = Spawn::create(myAction, nullptr);
	BG->runAction(myAction);

	this->scheduleOnce(schedule_selector(IntroScene::myTickInce), 3.0f);
	
	return true;
}

void IntroScene::myTickInce(float f) {
	CCSprite* title = CCSprite::create("Images/Scene/title.png");
	title->setPosition(Vec2(640, 480 + 80));
	this->addChild(title);

	auto myAction1 = MoveTo::create(1.5, Vec2(640, 360+60));
	auto myAction2 = MoveTo::create(1.5, Vec2(640, 360+80));
	auto myAction3 = Sequence::create(myAction1, myAction2, nullptr);
	auto myAction7 = Spawn::create(myAction3, nullptr);
	auto rep1 = RepeatForever::create(myAction7);
	title->runAction(rep1);

	auto pMenuItem1 = MenuItemFont::create("Start Game", CC_CALLBACK_1(IntroScene::doClick, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));
	pMenuItem1->setScale(1.5);
	auto pMenuItem2 = MenuItemFont::create("Option", CC_CALLBACK_1(IntroScene::doClick, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));
	pMenuItem2->setScale(1.5);
	auto pMenuItem3 = MenuItemFont::create("Exit", CC_CALLBACK_1(IntroScene::doClick, this));
	pMenuItem3->setColor(Color3B(0, 0, 0));
	pMenuItem3->setScale(1.5);
	pMenuItem1->setTag(1);
	pMenuItem2->setTag(2);
	pMenuItem3->setTag(3);

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);
	pMenu->setPosition(Vec2(640, 200));
	pMenu->alignItemsVertically();
	pMenu->alignItemsVerticallyWithPadding(30.0f);
	this->addChild(pMenu);

	this->schedule(schedule_selector(IntroScene::tick), 1);

}

void IntroScene::tick(float dt) {
	auto cache = SpriteFrameCache::getInstance();
	int num = rand() % 40;
	int speed = rand() % 5;
	char str1[100];
	char str2[100];
	Vector<SpriteFrame*> animFrames;

	Sprite* sprite;
	

	if (num == 0) {
		cache->addSpriteFramesWithFile("Plist/Person.plist");
		sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
	}
	else if (num == 1) {
		cache->addSpriteFramesWithFile("Plist/Earth1.plist");
		sprite = Sprite::createWithSpriteFrameName("Earth1-1.png");
		sprintf(str1, "Earth1-");
	}
	else if (num == 2) {
		cache->addSpriteFramesWithFile("Plist/Earth2.plist");
		 sprite = Sprite::createWithSpriteFrameName("Earth2-1.png");
		 sprintf(str1, "Earth2-");
	}
	else if (num == 3) {
		cache->addSpriteFramesWithFile("Plist/Earth3.plist");
		 sprite = Sprite::createWithSpriteFrameName("Earth3-1.png");
		 sprintf(str1, "Earth3-");
	}
	else if (num == 4) {
		cache->addSpriteFramesWithFile("Plist/Earth4.plist");
		 sprite = Sprite::createWithSpriteFrameName("Earth4-1.png");
		 sprintf(str1, "Earth4-");
	}
	else if (num == 5) {
		cache->addSpriteFramesWithFile("Plist/Earth5.plist");
		 sprite = Sprite::createWithSpriteFrameName("Earth5-1.png");
		 sprintf(str1, "Earth5-");
	}
	else if (num == 6) {
		cache->addSpriteFramesWithFile("Plist/Earth6.plist");
		 sprite = Sprite::createWithSpriteFrameName("Earth6-1.png");
		 sprintf(str1, "Earth6-");
	}
	else if (num == 7) {
		cache->addSpriteFramesWithFile("Plist/Earth7.plist");
		 sprite = Sprite::createWithSpriteFrameName("Earth7-1.png");
		 sprintf(str1, "Earth7-");
	}
	else if (num == 8) {
		cache->addSpriteFramesWithFile("Plist/Earth8.plist");
		 sprite = Sprite::createWithSpriteFrameName("Earth8-1.png");
		 sprintf(str1, "Earth8-");
	}
	else if (num == 9) {
		cache->addSpriteFramesWithFile("Plist/Earth9.plist");
		 sprite = Sprite::createWithSpriteFrameName("Earth9-1.png");
		 sprintf(str1, "Earth9-");
	}
	else if (num == 10) {
		cache->addSpriteFramesWithFile("Plist/Person.plist");
		sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
	}
	else if (num == 11) {
		cache->addSpriteFramesWithFile("Plist/Fire1.plist");
		sprite = Sprite::createWithSpriteFrameName("Fire1-1.png");
		sprintf(str1, "Fire1-");
	}
	else if (num == 12) {
		cache->addSpriteFramesWithFile("Plist/Fire2.plist");
		sprite = Sprite::createWithSpriteFrameName("Fire2-1.png");
		sprintf(str1, "Fire2-");
	}
	else if (num == 13) {
		cache->addSpriteFramesWithFile("Plist/Fire3.plist");
		sprite = Sprite::createWithSpriteFrameName("Fire3-1.png");
		sprintf(str1, "Fire3-");
	}
	else if (num == 14) {
		cache->addSpriteFramesWithFile("Plist/Fire4.plist");
		sprite = Sprite::createWithSpriteFrameName("Fire4-1.png");
		sprintf(str1, "Fire4-");
	}
	else if (num == 15) {
		cache->addSpriteFramesWithFile("Plist/Fire5.plist");
		sprite = Sprite::createWithSpriteFrameName("Fire5-1.png");
		sprintf(str1, "Fire5-");
	}
	else if (num == 16) {
		cache->addSpriteFramesWithFile("Plist/Fire6.plist");
		sprite = Sprite::createWithSpriteFrameName("Fire6-1.png");
		sprintf(str1, "Fire6-");
	}
	else if (num == 17) {
		cache->addSpriteFramesWithFile("Plist/Fire7.plist");
		sprite = Sprite::createWithSpriteFrameName("Fire7-1.png");
		sprintf(str1, "Fire7-");
	}
	else if (num == 18) {
		cache->addSpriteFramesWithFile("Plist/Fire8.plist");
		sprite = Sprite::createWithSpriteFrameName("Fire8-1.png");
		sprintf(str1, "Fire8-");
	}
	else if (num == 19) {
		cache->addSpriteFramesWithFile("Plist/Fire9.plist");
		sprite = Sprite::createWithSpriteFrameName("Fire9-1.png");
		sprintf(str1, "Fire9-");
	}
	else if (num == 20) {
		cache->addSpriteFramesWithFile("Plist/Person.plist");
		sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
	}
	else if (num == 21) {
		cache->addSpriteFramesWithFile("Plist/Water1.plist");
		sprite = Sprite::createWithSpriteFrameName("Water1-1.png");
		sprintf(str1, "Water1-");
	}
	else if (num == 22) {
		cache->addSpriteFramesWithFile("Plist/Water2.plist");
		sprite = Sprite::createWithSpriteFrameName("Water2-1.png");
		sprintf(str1, "Water2-");
	}
	else if (num == 23) {
		cache->addSpriteFramesWithFile("Plist/Water3.plist");
		sprite = Sprite::createWithSpriteFrameName("Water3-1.png");
		sprintf(str1, "Water3-");
	}
	else if (num == 24) {
		cache->addSpriteFramesWithFile("Plist/Water4.plist");
		sprite = Sprite::createWithSpriteFrameName("Water4-1.png");
		sprintf(str1, "Water4-");
	}
	else if (num == 25) {
		cache->addSpriteFramesWithFile("Plist/Water5.plist");
		sprite = Sprite::createWithSpriteFrameName("Water5-1.png");
		sprintf(str1, "Water5-");
	}
	else if (num == 26) {
		cache->addSpriteFramesWithFile("Plist/Water6.plist");
		sprite = Sprite::createWithSpriteFrameName("Water6-1.png");
		sprintf(str1, "Water6-");
	}
	else if (num == 27) {
		cache->addSpriteFramesWithFile("Plist/Water7.plist");
		sprite = Sprite::createWithSpriteFrameName("Water7-1.png");
		sprintf(str1, "Water7-");
	}
	else if (num == 28) {
		cache->addSpriteFramesWithFile("Plist/Water8.plist");
		sprite = Sprite::createWithSpriteFrameName("Water8-1.png");
		sprintf(str1, "Water8-");
	}
	else if (num == 29) {
		cache->addSpriteFramesWithFile("Plist/Water9.plist");
		sprite = Sprite::createWithSpriteFrameName("Water9-1.png");
		sprintf(str1, "Water9-");
	}
	else if (num == 30) {
		cache->addSpriteFramesWithFile("Plist/Person.plist");
		sprite = Sprite::createWithSpriteFrameName("Person1-1.png");
		sprintf(str1, "Person1-");
	}
	else if (num == 31) {
		cache->addSpriteFramesWithFile("Plist/Wind1.plist");
		sprite = Sprite::createWithSpriteFrameName("Wind1-1.png");
		sprintf(str1, "Wind1-");
	}
	else if (num == 32) {
		cache->addSpriteFramesWithFile("Plist/Wind2.plist");
		sprite = Sprite::createWithSpriteFrameName("Wind2-1.png");
		sprintf(str1, "Wind2-");
	}
	else if (num == 33) {
		cache->addSpriteFramesWithFile("Plist/Wind3.plist");
		sprite = Sprite::createWithSpriteFrameName("Wind3-1.png");
		sprintf(str1, "Wind3-");
	}
	else if (num == 34) {
		cache->addSpriteFramesWithFile("Plist/Wind4.plist");
		sprite = Sprite::createWithSpriteFrameName("Wind4-1.png");
		sprintf(str1, "Wind4-");
	}
	else if (num == 35) {
		cache->addSpriteFramesWithFile("Plist/Wind5.plist");
		sprite = Sprite::createWithSpriteFrameName("Wind5-1.png");
		sprintf(str1, "Wind5-");
	}
	else if (num == 36) {
		cache->addSpriteFramesWithFile("Plist/Wind6.plist");
		sprite = Sprite::createWithSpriteFrameName("Wind6-1.png");
		sprintf(str1, "Wind6-");
	}
	else if (num == 37) {
		cache->addSpriteFramesWithFile("Plist/Wind7.plist");
		sprite = Sprite::createWithSpriteFrameName("Wind7-1.png");
		sprintf(str1, "Wind7-");
	}
	else if (num == 38) {
		cache->addSpriteFramesWithFile("Plist/Wind8.plist");
		sprite = Sprite::createWithSpriteFrameName("Wind8-1.png");
		sprintf(str1, "Wind8-");
	}
	else if (num == 39) {
		cache->addSpriteFramesWithFile("Plist/Wind9.plist");
		sprite = Sprite::createWithSpriteFrameName("Wind9-1.png");
		sprintf(str1, "Wind9-");
	}
	sprite->setPosition(1300, 50);
	this->addChild(sprite);
	for (int i = 1; i < 5; i++) {
		sprintf(str2, "%s%d.png", str1, i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str2);
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	sprite->runAction(rep);

	auto myAction1 = MoveTo::create(speed + 5, Vec2(-80, 50));
	sprite->runAction(myAction1);
}

void IntroScene::doClick(Ref *pSender) {
	auto tItem = (MenuItem *)pSender;

	int i = tItem->getTag();
	log("%d번째 메뉴가 선택되었습니다.", i);
	if (i == 1) {
		auto pScene = MainScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 2) {
		//auto pScene = SecendScene::createScene();
		//Director::getInstance()->replaceScene(pScene);
	}
	else if (i == 3) {
		//auto pScene = SecendScene::createScene();
		//Director::getInstance()->replaceScene(pScene);
	}
	

}