#include "HelloWorldScene.h"
#include <stdlib.h>
#include <time.h>
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
	if (!Layer::init())
	{
		return false;
	}
	////////////////////
	num = 0;

	srand(time(nullptr));

	CreatePhoto();
	MixingPhoto();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	if (1 <= touchPoint.x && touchPoint.x <= 97) {  //0, 1, 2
		if (195 <= touchPoint.y && touchPoint.y <= 291) {		//0
			if (blank == 1) {									//0->1
				blank = 0;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 0) {
						Photo.at(m)->setPosition(Vec2(49, 146));
						Photo.at(m)->setTag(1);
						break;
					}
				}
			}
			else if (blank == 3) {								//0->3
				blank = 0;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 0) {
						Photo.at(m)->setPosition(Vec2(146, 243));
						Photo.at(m)->setTag(3);
						break;
					}
				}
			}
			else {
				log("이동할 수 없습니다.");
			}
		}
		else if (98 <= touchPoint.y && touchPoint.y <= 194) {	//1
			if (blank == 0) {									//1->0
				blank = 1;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 1) {
						Photo.at(m)->setPosition(Vec2(49, 243));
						Photo.at(m)->setTag(0);
						break;
					}
				}
			}
			else if (blank == 2) {								//1->2
				blank = 1;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 1) {
						Photo.at(m)->setPosition(Vec2(49, 49));
						Photo.at(m)->setTag(2);
						break;
					}
				}
			}
			else if (blank == 4) {								//1->4
				blank = 1;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 1) {
						Photo.at(m)->setPosition(Vec2(146, 146));
						Photo.at(m)->setTag(4);
						break;
					}
				}
			}
			else {
				log("이동할 수 없습니다.");
			}
		}
		else if (1 <= touchPoint.y && touchPoint.y <= 97) {		//2
			if (blank == 1) {									//2->1
				blank = 2;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 2) {
						Photo.at(m)->setPosition(Vec2(49, 146));
						Photo.at(m)->setTag(1);
						break;
					}
				}
			}
			else if (blank == 5) {								//2->5
				blank = 2;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 2) {
						Photo.at(m)->setPosition(Vec2(146, 49));
						Photo.at(m)->setTag(5);
						break;
					}
				}
			}
			else {
				log("이동할 수 없습니다.");
			}
		}
		else {
			return true;
		}
	}
	else if (98 <= touchPoint.x && touchPoint.x <= 194) {		//3, 4, 5
		if (195 <= touchPoint.y && touchPoint.y <= 291) {		//3
			if (blank == 0) {									//3->0
				blank = 3;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 3) {
						Photo.at(m)->setPosition(Vec2(49, 243));
						Photo.at(m)->setTag(0);
						break;
					}
				}
			}
			else if (blank == 4) {								//3->4
				blank = 3;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 3) {
						Photo.at(m)->setPosition(Vec2(146, 146));
						Photo.at(m)->setTag(4);
						break;
					}
				}
			}
			else if (blank == 6) {								//3->6
				blank = 3;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 3) {
						Photo.at(m)->setPosition(Vec2(243, 243));
						Photo.at(m)->setTag(6);
						break;
					}
				}
			}
			else {
				log("이동할 수 없습니다.");
			}
		}
		else if (98 <= touchPoint.y && touchPoint.y <= 194) {	//4
			if (blank == 1) {									//4->1
				blank = 4;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 4) {
						Photo.at(m)->setPosition(Vec2(49, 146));
						Photo.at(m)->setTag(1);
						break;
					}
				}
			}
			else if (blank == 3) {								//4->3
				blank = 4;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 4) {
						Photo.at(m)->setPosition(Vec2(146, 243));
						Photo.at(m)->setTag(3);
						break;
					}
				}
			}
			else if (blank == 5) {								//4->5
				blank = 4;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 4) {
						Photo.at(m)->setPosition(Vec2(146, 49));
						Photo.at(m)->setTag(5);
						break;
					}
				}
			}
			else if (blank == 7) {								//4->7
				blank = 4;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 4) {
						Photo.at(m)->setPosition(Vec2(243, 146));
						Photo.at(m)->setTag(7);
						break;
					}
				}
			}
			else {
				log("이동할 수 없습니다.");
			}
		}
		else if (1 <= touchPoint.y && touchPoint.y <= 97) {		//5
			if (blank == 2) {									//5->2
				blank = 5;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 5) {
						Photo.at(m)->setPosition(Vec2(49, 49));
						Photo.at(m)->setTag(2);
						break;
					}
				}
			}
			else if (blank == 4) {								//5->4
				blank = 5;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 5) {
						Photo.at(m)->setPosition(Vec2(146, 146));
						Photo.at(m)->setTag(4);
						break;
					}
				}
			}
			else if (blank == 8) {								//5->8
				blank = 5;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 5) {
						Photo.at(m)->setPosition(Vec2(243, 49));
						Photo.at(m)->setTag(8);
						break;
					}
				}
			}
			else {
				log("이동할 수 없습니다.");
			}
		}
		else {
			return true;
		}
	}
	else if (195 <= touchPoint.x && touchPoint.x <= 291) {		//6, 7, 8
		if (195 <= touchPoint.y && touchPoint.y <= 291) {		//6
			if (blank == 3) {									//6->3
				blank = 6;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 6) {
						Photo.at(m)->setPosition(Vec2(146, 243));
						Photo.at(m)->setTag(3);
						break;
					}
				}
			}
			else if (blank == 7) {								//6->7
				blank = 6;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 6) {
						Photo.at(m)->setPosition(Vec2(243, 146));
						Photo.at(m)->setTag(7);
						break;
					}
				}
			}
			else {
				log("이동할 수 없습니다.");
			}
		}
		else if (98 <= touchPoint.y && touchPoint.y <= 194) {	//7
			if (blank == 4) {									//7->4
				blank = 7;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 7) {
						Photo.at(m)->setPosition(Vec2(146, 146));
						Photo.at(m)->setTag(4);
						break;
					}
				}
			}
			else if (blank == 6) {								//7->6
				blank = 7;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 7) {
						Photo.at(m)->setPosition(Vec2(243, 243));
						Photo.at(m)->setTag(6);
						break;
					}
				}
			}
			else if (blank == 8) {								//7->8
				blank = 7;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 7) {
						Photo.at(m)->setPosition(Vec2(243, 49));
						Photo.at(m)->setTag(8);
						break;
					}
				}
			}
			else {
				log("이동할 수 없습니다.");
			}
		}
		else if (1 <= touchPoint.y && touchPoint.y <= 97) {		//8
			if (blank == 5) {									//8->5
				blank = 8;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 8) {
						Photo.at(m)->setPosition(Vec2(146, 49));
						Photo.at(m)->setTag(5);
						break;
					}
				}
			}
			else if (blank == 7) {								//8->7
				blank = 8;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 8) {
						Photo.at(m)->setPosition(Vec2(243, 146));
						Photo.at(m)->setTag(7);
						break;
					}
				}
			}
			else {
				log("이동할 수 없습니다.");
			}
		}
		else {
			return true;
		}
	}
	FinishCheck();
	return true;
}

void HelloWorld::FinishCheck() {
	int num = 0;
	for (int i = 0; i < 8; i++) {
		if (Photo.at(i)->getTag() == i) {
			num++;
		}
	}
	if (num == 8) {
		auto sprite = Sprite::create("Images/images.png");
		sprite->setPosition(Vec2(146, 146));
		//sprite->setVisible(false);
		sprite->setScale(1.01);
		addChild(sprite);
		for (int i = 0; i < 8; i++) {
			Photo.at(i)->setVisible(false);
		}
		sprite->setOpacity(0);
		auto myAction = FadeIn::create(1.5f);
		sprite->runAction(myAction);
	}
}

void HelloWorld::CreatePhoto() {
	texture = Director::getInstance()->getTextureCache()->addImage("Images/images.png");   //144x144

	blank = 8;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i+j == 8) {
				break;
			}
			Rect rect = { (float)(i * 96), (float)j * 96, 96, 96 };
			auto sprite = Sprite::createWithTexture(texture, rect);
			sprite->setPosition(Vec2(i * 96 + 48 + i + 1, (2 - j) * 96 + 48 + (2 - j) + 1));
			sprite->setTag(num++);
			Photo.pushBack(sprite);
		}
	}
	for (int i = 0; i < 8; i++) {
		this->addChild(Photo.at(i));

	}
}

void HelloWorld::MixingPhoto() {
	int num = 0;
	for (int mixnum = 0; mixnum < 1000; mixnum++) {
		if (blank == 0) {
			num = rand() % 2;
			if (num == 0) {		//1번선택
				blank = 1;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 1) {
						Photo.at(m)->setPosition(Vec2(49, 243));
						Photo.at(m)->setTag(0);
						break;
					}
				}
			}
			else {				//3번선택
				blank = 3;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 3) {
						Photo.at(m)->setPosition(Vec2(49, 243));
						Photo.at(m)->setTag(0);
						break;
					}
				}
			}
		}
		else if (blank == 1) {
			num = rand() % 3;
			if (num == 0) {				//0번선택
				blank = 0;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 0) {
						Photo.at(m)->setPosition(Vec2(49, 146));
						Photo.at(m)->setTag(1);
						break;
					}
				}
			}
			else if (num == 1) {		//2번선택
				blank = 2;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 2) {
						Photo.at(m)->setPosition(Vec2(49, 146));
						Photo.at(m)->setTag(1);
						break;
					}
				}
			}
			else {						//4번선택
				blank = 4;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 4) {
						Photo.at(m)->setPosition(Vec2(49, 146));
						Photo.at(m)->setTag(1);
						break;
					}
				}
			}
		}
		else if (blank == 2) {
			num = rand() % 2;
			if (num == 0) {		//1번선택
				blank = 1;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 1) {
						Photo.at(m)->setPosition(Vec2(49, 49));
						Photo.at(m)->setTag(2);
						break;
					}
				}
			}
			else {				//5번선택
				blank = 5;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 5) {
						Photo.at(m)->setPosition(Vec2(49, 49));
						Photo.at(m)->setTag(2);
						break;
					}
				}
			}
		}
		else if (blank == 3) {
			num = rand() % 3;
			if (num == 0) {				//0번선택
				blank = 0;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 0) {
						Photo.at(m)->setPosition(Vec2(146, 243));
						Photo.at(m)->setTag(3);
						break;
					}
				}
			}
			else if (num == 1) {		//4번선택
				blank = 4;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 4) {
						Photo.at(m)->setPosition(Vec2(146, 243));
						Photo.at(m)->setTag(3);
						break;
					}
				}
			}
			else {						//6번선택
				blank = 6;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 6) {
						Photo.at(m)->setPosition(Vec2(146, 243));
						Photo.at(m)->setTag(3);
						break;
					}
				}
			}
		}
		else if (blank == 4) {
			num = rand() % 4;
			if (num == 0) {				//1번선택
				blank = 1;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 1) {
						Photo.at(m)->setPosition(Vec2(146, 146));
						Photo.at(m)->setTag(4);
						break;
					}
				}
			}
			else if (num == 1) {		//3번선택
				blank = 3;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 3) {
						Photo.at(m)->setPosition(Vec2(146, 146));
						Photo.at(m)->setTag(4);
						break;
					}
				}
			}
			else if (num == 2) {		//5번선택
				blank = 5;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 5) {
						Photo.at(m)->setPosition(Vec2(146, 146));
						Photo.at(m)->setTag(4);
						break;
					}
				}
			}
			else {						//7번선택
				blank = 7;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 7) {
						Photo.at(m)->setPosition(Vec2(146, 146));
						Photo.at(m)->setTag(4);
						break;
					}
				}
			}
		}
		else if (blank == 5) {
			num = rand() % 3;
			if (num == 0) {				//2번선택
				blank = 2; 
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 2) {
						Photo.at(m)->setPosition(Vec2(146, 49));
						Photo.at(m)->setTag(5);
						break;
					}
				}
			}
			else if (num == 1) {		//4번선택
				blank = 4;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 4) {
						Photo.at(m)->setPosition(Vec2(146, 49));
						Photo.at(m)->setTag(5);
						break;
					}
				}
			}
			else {						//8번선택
				blank = 8;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 8) {
						Photo.at(m)->setPosition(Vec2(146, 49));
						Photo.at(m)->setTag(5);
						break;
					}
				}
			}
		}
		else if (blank == 6) {
			num = rand() % 2;
			if (num == 0) {				//3번선택
				blank = 3;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 3) {
						Photo.at(m)->setPosition(Vec2(243, 243));
						Photo.at(m)->setTag(6);
						break;
					}
				}
			}
			else {						//7번선택
				blank = 7;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 7) {
						Photo.at(m)->setPosition(Vec2(243, 243));
						Photo.at(m)->setTag(6);
						break;
					}
				}
			}
		}
		else if (blank == 7) {
			num = rand() % 3;
			if (num == 0) {				//4번선택
				blank = 4;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 4) {
						Photo.at(m)->setPosition(Vec2(243, 146));
						Photo.at(m)->setTag(7);
						break;
					}
				}
			}
			else if (num == 1) {		//6번선택
				blank = 6;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 6) {
						Photo.at(m)->setPosition(Vec2(243, 146));
						Photo.at(m)->setTag(7);
						break;
					}
				}
			}
			else {						//8번선택
				blank = 8;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 8) {
						Photo.at(m)->setPosition(Vec2(243, 146));
						Photo.at(m)->setTag(7);
						break;
					}
				}
			}
		}
		else if (blank == 8) {
			num = rand() % 2;
			if (num == 0) {		//5번선택
				blank = 5;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 5) {
						Photo.at(m)->setPosition(Vec2(243, 49));
						Photo.at(m)->setTag(8);
						break;
					}
				}
			}
			else {				//7번선택
				blank = 7;
				for (int m = 0; m < 8; m++) {
					if (Photo.at(m)->getTag() == 7) {
						Photo.at(m)->setPosition(Vec2(243, 49));
						Photo.at(m)->setTag(8);
						break;
					}
				}
			}
		}
	}
	
}
