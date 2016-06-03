#include "HelloWorldScene.h"
#include "GameOver.h"
USING_NS_CC;

#define FIX_POS(_pos, _min, _max) \
if (_pos < _min) \
	_pos = _min; \
else if (_pos > _max) \
	_pos = _max; \

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init())
    {
        return false;
    }

	srand((int)time(nullptr));

	BRICKS_HEIGHT = 4;
	BRICKS_WIDTH = 5;

	texture = Director::getInstance()->getTextureCache()->addImage("Images/white-512x512.png");
	//벽돌 초기화
	this->initializeBricks();
	//공 초기화
	this->initializeBall();
	//패들 초기화
	this->initializePaddle();
	//2초후 게임시작
	this->scheduleOnce(schedule_selector(HelloWorld::startGame), 2.0f);

    return true;
}

HelloWorld::~HelloWorld(void) {
	paddle->release();
	Device::setAccelerometerEnabled(false);
}

void HelloWorld::onEnter() {
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	Device::setAccelerometerEnabled(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	auto listener1 = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

}
void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}

void HelloWorld::onAcceleration(Acceleration* acc, Event* event) {
	auto pDir = Director::getInstance();

	winSize = pDir->getVisibleSize();

	if (paddle == nullptr) {
		return;
	}

	auto ballSize = paddle->getContentSize();
	auto ptNow = paddle->getPosition();
	auto ptTemp = pDir->convertToUI(ptNow);

	ptTemp.x += acc->x*9.81f;
	ptTemp.y -= acc->y*9.81f;

	auto ptNext = pDir->convertToGL(ptTemp);
	FIX_POS(ptNext.x, (ballSize.width / 2.0), (winSize.width - ballSize.width / 2.0));
	FIX_POS(ptNext.y, (ballSize.height / 2.0), (winSize.height - ballSize.height / 2.0));

	paddle->setPosition(ptNext);
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (!isPlaying) {
		return true;
	}

	auto touchPoint = touch->getLocation();
	Rect rect = paddle->getBoundingBox();
	if (rect.containsPoint(touchPoint)) {
		isPaddleTouched = true;
	}
	else {
		isPaddleTouched = false;
	}

}
void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (isPaddleTouched) {
		auto touchPoint = touch->getLocation();

		if (touchPoint.x < 40) {
			touchPoint.x = 40;
		}
		if (touchPoint.x > 280) {
			touchPoint.x = 280;
		}

		Vec2 newLocation = Vec2(touchPoint.x, paddle->getPosition().y);
		paddle->setPosition(newLocation);
	}
}

void HelloWorld::initializeBricks() {
	int count = 0;

	for (int y = 0; y < BRICKS_HEIGHT; y++) {
		for (int x = 0; x < BRICKS_WIDTH; x++) {
			Sprite* bricks = Sprite::createWithTexture(texture, Rect(0, 0, 64, 40));

			switch (count++ % 4) {
			case 0:
				bricks->setColor(Color3B(255, 255, 255));
				break;
			case 1:
				bricks->setColor(Color3B(255, 0, 0));
				break;
			case 2:
				bricks->setColor(Color3B(255, 255, 0));
				break;
			case 3:
				bricks->setColor(Color3B(75, 255, 0));
				break;
			default:
				break;

			}
			bricks->setPosition(Vec2(x * 64 + 32, (y * 40) + 280));
			this->addChild(bricks);
			targets.pushBack(bricks);
		}
	}

}
void HelloWorld::initializeBall() {
	ball = Sprite::createWithTexture(texture, Rect(0, 0, 16, 16));
	ball->setColor(Color3B(0, 255, 255));
	ball->setPosition(Vec2(160, 240));
	this->addChild(ball);
}
void HelloWorld::initializePaddle(){
	paddle = Sprite::createWithTexture(texture, Rect(0, 0, 80, 10));
	paddle->setColor(Color3B(255, 255, 0));
	paddle->setPosition(Vec2(160, 50));
	this->addChild(paddle);
	paddle->retain();
}
void HelloWorld::startGame(float dt) {
	ball->setPosition(Vec2(160, 240));
	ballMovement = Vec2(4, 4);
	if (rand() % 100 < 50) {
		ballMovement.x = -ballMovement.x;
	}
	ballMovement.y = -ballMovement.y;

	isPlaying = true;

	this->schedule(schedule_selector(HelloWorld::gameLogic), 2.0f / 60.0f);
}
void HelloWorld::gameLogic(float dt) {
	ball->setPosition(Vec2(ball->getPosition().x + ballMovement.x, ball->getPosition().y + ballMovement.y));
	bool paddleCollision =	ball->getPosition().y <= paddle->getPosition().y + 13 && 
							ball->getPosition().x >= paddle->getPosition().x - 48 && 
							ball->getPosition().x <= paddle->getPosition().x + 48;
	if (paddleCollision) {
		if (ball->getPosition().y <= paddle->getPosition().y + 13 && ballMovement.y < 0) {
			ball->setPosition(Vec2(ball->getPosition().x, paddle->getPosition().y + 13));
		}
		ballMovement.y = -ballMovement.y;
	}
	bool there_are_solid_bricks = false;

	for (auto &item : targets) {
		Sprite* brick = item;
		if (255 == brick->getOpacity()) {
			there_are_solid_bricks = true;

			Rect rectA = ball->getBoundingBox();
			Rect rectB = brick->getBoundingBox();

			if (rectA.intersectsRect(rectB)) {
				this->processCollision(brick);
			}
		}
	}

	if (!there_are_solid_bricks) {
		isPlaying = false;
		ball->setOpacity(0);

		this->unscheduleAllSelectors();

		log("You win !!!");

		//게임에 이겼다. 새로운 게임 대기 화면
		Scene* pScene = GameOver::createScene();
		Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(1, pScene));
	}

	if (ball->getPosition().x > 312 || ball->getPosition().x < 8) {
		ballMovement.x = -ballMovement.x;
	}
	if (ball->getPosition().y > 450) {
		ballMovement.y = -ballMovement.y;
	}

	if (ball->getPosition().y < (50+5+8)) {
		isPlaying = false;
		ball->setOpacity(0);

		this->unscheduleAllSelectors();
		log("You lose..");
		//게임에 졌다. 새로운 게임 대기 화면
		Scene* pScene = GameOver::createScene();
		Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(1, pScene));
	}
	
}
void HelloWorld::processCollision(Sprite* brick) {
	Vec2 brickPos = brick->getPosition();
	Vec2 ballPos = ball->getPosition();

	if (ballMovement.x > 0 && brick->getPosition().x < ball->getPosition().x) {
		ballMovement.x = -ballMovement.x;
	}
	else if (ballMovement.x < 0 && brick->getPosition().x < ball->getPosition().x) {
		ballMovement.x = -ballMovement.x;
	}

	if (ballMovement.y > 0 && brick->getPosition().y > ball->getPosition().y) {
		ballMovement.y = -ballMovement.y;
	}
	else if (ballMovement.y < 0 && brick->getPosition().y < ball->getPosition().y) {
		ballMovement.y = -ballMovement.y;
	}
	brick->setOpacity(0);
}