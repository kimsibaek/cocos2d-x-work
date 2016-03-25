#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	////////////////////
	speed = 10;
	num = 0;
	JumpNum = 0;
	Texture2D *texture = TextureCache::sharedTextureCache()->addImage("Images/player2.png");

	batch = Sprite::createWithTexture(texture, Rect(0, 0, 30, 30));
	batch->setPosition(100, 100);
	batch->setScale(1.5);
	this->addChild(batch);

	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.05);

	for (int i = 0; i < 16; i++)
	{
		animation->addSpriteFrameWithTexture(texture, Rect(i * 30, 0, 30, 30));
		
	}
	Animate *animate = Animate::create(animation);
	RepeatForever *rep = RepeatForever::create(animate);

	batch->runAction(rep);

	auto pMenuItem1 = MenuItemFont::create("Jump!", CC_CALLBACK_1(HelloWorld::doClick1, this));
	pMenuItem1->setColor(Color3B::BLACK);
	pMenuItem1->setPosition(Vec2(240, 100));

	auto pMenu = Menu::create(pMenuItem1, nullptr);
	pMenu->setPosition(Vec2(0, 0));
	this->addChild(pMenu);
	
	return true;
}

void HelloWorld::callEveryFrame(float f) {
	if (num <= 10) {
		speed--;
		num++;
		batch->setPosition(Vec2(100, batch->getPosition().y + speed));
	}
	else if (num >= 10) {
		speed++;
		num++;
		batch->setPosition(Vec2(100, batch->getPosition().y - speed));
		if (num >= 20 && batch->getPosition().y <= 100) {
			num == 0;
			speed = 10;
			JumpNum =0;
			batch->setPosition(Vec2(100, 100));
			//this->unschedule(schedule_selector(HelloWorld::callEveryFrame));
			return;
		}
	}
	
}

void HelloWorld::doClick1(cocos2d::Ref* pSecder) {
	num = 0;
	speed = 10;
	JumpNum++;
	this->schedule(schedule_selector(HelloWorld::callEveryFrame), 0.05f);
	
	
	
	
	
	
	
}

