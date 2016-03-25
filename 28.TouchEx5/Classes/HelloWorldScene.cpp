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
	statusLabel = LabelTTF::create("No custom event received!", "", 20);
	statusLabel->setColor(Color3B::BLACK);
	statusLabel->setPosition(Vec2(240, 250));
	addChild(statusLabel);

	auto pMenuItem1 = MenuItemFont::create("Send Custom Event 1", CC_CALLBACK_1(HelloWorld::doClick1, this));
	pMenuItem1->setColor(Color3B::BLACK);
	pMenuItem1->setPosition(Vec2(240, 160));
	
	auto pMenuItem2 = MenuItemFont::create("Send Custom Event 2", CC_CALLBACK_1(HelloWorld::doClick2, this));
	pMenuItem2->setColor(Color3B::BLACK);
	pMenuItem2->setPosition(Vec2(240, 100));

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	pMenu->setPosition(Vec2(0, 0));
	this->addChild(pMenu);

    return true;
}


void HelloWorld::onEnter() {
	Layer::onEnter();

	_listener1 = EventListenerCustom::create("game_custom_event_1", CC_CALLBACK_1(HelloWorld::doEvent1, this));
	_eventDispatcher->addEventListenerWithFixedPriority(_listener1, 1);

	_listener2 = EventListenerCustom::create("game_custom_event_2", CC_CALLBACK_1(HelloWorld::doEvent2, this));
	_eventDispatcher->addEventListenerWithFixedPriority(_listener2, 1);
}
void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(_listener1);
	_eventDispatcher->removeEventListener(_listener2);
}
void HelloWorld::doClick1(cocos2d::Ref* pSecder) {
	static int count = 0;
	++count;
	char* buf = new char[10];
	sprintf(buf, "%d", count);

	EventCustom event("game_custom_event_1");
	event.setUserData(buf);
	_eventDispatcher->dispatchEvent(&event);
}
void HelloWorld::doClick2(cocos2d::Ref* pSecder) {
	static int count = 0;
	++count;
	char* buf = new char[10];
	sprintf(buf, "%d", count);

	EventCustom event("game_custom_event_2");
	event.setUserData(buf);
	_eventDispatcher->dispatchEvent(&event);
}
void HelloWorld::doEvent1(cocos2d::EventCustom* event) {
	std::string str("Custom event 1 received, ");
	char* buf = static_cast<char*>(event->getUserData());
	str += buf;
	str += "times";
	statusLabel->setString(str.c_str());
	delete[] buf;
}
void HelloWorld::doEvent2(cocos2d::EventCustom* event) {
	std::string str("Custom event 2 received, ");
	char* buf = static_cast<char*>(event->getUserData());
	str += buf;
	str += "times";
	statusLabel->setString(str.c_str());
	delete[] buf;
}
