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
	//-------------------------------------------
	//Type 1 : from Sprite
	//-------------------------------------------
	auto sprite = Sprite::create("Images/grossini_dance_atlas.png");
	auto texture = sprite->getTexture();
	//-------------------------------------------
	//Type 2 : from Texture
	//-------------------------------------------
	auto texture2 = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas.png");
	//-------------------------------------------
	//Type 3 : from BatchNode
	//-------------------------------------------
	auto batch = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 10);
	auto texture3 = batch->getTexture();
	//-------------------------------------------
	
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	for (int i = 0; i < 14; i++) {
		int column = i % 5;
		int row = i / 5;

		animation->addSpriteFrameWithTexture(texture3, Rect(column * 85, row * 121, 85, 121));
	}

	//auto pMan = Sprite::create("Images/grossini_dance_atlas.png", Rect(0, 0, 85, 121));
	auto pMan = Sprite::createWithTexture(texture, Rect(0, 0, 85, 121));
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pMan->runAction(rep);

    return true;
}

