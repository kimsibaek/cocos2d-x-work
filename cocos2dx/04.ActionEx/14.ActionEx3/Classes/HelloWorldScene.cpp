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
	auto pMenuItem = MenuItemFont::create("Action", CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem, NULL);

	pMenu->alignItemsHorizontally();

	pMenu->setPosition(Vec2(240, 50));

	this->addChild(pMenu);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 160));
	this->addChild(pMan);
    return true;
}

void HelloWorld::doAction(Ref* pSender) {
	pMan->removeFromParentAndCleanup(true);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 160));
	this->addChild(pMan);

	//this->ActionSequence(this);
	this->ActionSpawn(this);
	//this->ActionReverse(this);
	//this->ActionRepeat(this);
	//this->ActionRepeatForever(this);
	//this->ActionDelayTime(this);
}

void HelloWorld::ActionSequence(Ref* pSender) {
	auto action = Sequence::create(MoveBy::create(2, Vec2(400, 0)), RotateBy::create(2, 540), nullptr);
	pMan->runAction(action);
}

void HelloWorld::ActionSpawn(Ref* pSender) {
	auto action = Spawn::create(JumpBy::create(4, Vec2(400, 0), 50, 4), RotateBy::create(2, 720), nullptr);
	//pMan->runAction(action);
	auto reverseAction = action->reverse();
	auto myAction = Sequence::create(action, reverseAction, nullptr);
	auto rep2 = RepeatForever::create(myAction);
	pMan->runAction(rep2);
}

void HelloWorld::ActionReverse(Ref* pSender) {
	auto action = MoveBy::create(2, Vec2(400, 0));
	auto reverseAction = action->reverse();
	pMan->runAction(reverseAction);
}

void HelloWorld::ActionRepeat(Ref* pSender) {
	auto myActionForward = MoveBy::create(2, Vec2(400, 0));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep1 = Repeat::create(myAction, 3);
	pMan->runAction(rep1);
}
void HelloWorld::ActionRepeatForever(Ref* pSender) {
	auto myActionForward = MoveBy::create(2, Vec2(400, 0));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep2 = RepeatForever::create(myAction);
	pMan->runAction(rep2);
}

void HelloWorld::ActionDelayTime(Ref* pSender) {
	auto act1 = RotateTo::create(1, 150);
	auto act2 = RotateTo::create(1, 0);
	auto myAction = Sequence::create(act1, DelayTime::create(2), act2, DelayTime::create(1), nullptr);
	auto rep2 = RepeatForever::create(myAction);
	pMan->runAction(rep2);
}