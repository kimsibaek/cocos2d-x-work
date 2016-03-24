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
	Texture2D *texture = TextureCache::sharedTextureCache()->addImage("Images/player2.png");

	Sprite* batch = Sprite::createWithTexture(texture, Rect(0, 0, 30, 30));
	batch->setPosition(100, 100);
	batch->setScale(1.5);
	this->addChild(batch);

	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.25);

	for (int i = 0; i < 38; i++)
	{
		if(i < 19)
			animation->addSpriteFrameWithTexture(texture, Rect(i * 30, 0, 30, 30));
		else
			animation->addSpriteFrameWithTexture(texture, Rect((i-19) * 30, 30, 30, 30));
	}
	Animate *animate = Animate::create(animation);
	RepeatForever *rep = RepeatForever::create(animate);

	batch->runAction(rep);
	return true;
}