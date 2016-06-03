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

	MenuItemFont::setFontSize(28);

	auto pMenuItem = MenuItemFont::create("Action", CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem, NULL);

	pMenu->alignItemsHorizontally();

	pMenu->setPosition(Vec2(240, 50));

	this->addChild(pMenu);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 200));
	this->addChild(pMan);
    return true;
}

void HelloWorld::doAction(Ref* pSender) {
	//auto myAction = MoveBy::create(2, Vec2(400, 0));
	//auto myAction = MoveTo::create(2, Vec2(400, 0));
	
	//auto myAction = JumpBy::create(2, Vec2(400, 0), 50, 3);
	//auto myAction = JumpTo::create(2, Vec2(400, 0), 50, 3);
	
	//auto myAction = Place::create(Vec2(300, 200));

	//auto myAction = ScaleBy::create(2, 2.0f);
	//auto myAction = ScaleTo::create(2, 2.0f);

	//auto myAction = RotateTo::create(2, 360);
	//auto myAction = RotateTo::create(2, 90);
	//auto myAction = RotateTo::create(2, 180);
	//auto myAction = RotateTo::create(2, 270);

	//auto myAction = Blink::create(2, 5);

	//auto myAction = FadeOut::create(1.5f);
	//auto myAction = FadeIn::create(1.5f);

	//auto myAction = TintTo::create(2, 128, 128, 128);
	//auto myAction = TintBy::create(2, 0, -30, 30);
	
	//pMan->runAction(myAction);
}
