#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameScene::GameScene() :
regenCheckTime_(-1.f)
{
}

Scene* GameScene::createScene()
{
    Scene *scene = Scene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

    MenuItemImage *pCloseItem = MenuItemImage::create(
                                        "Images/CloseNormal.png",
                                        "Images/CloseSelected.png",
                                        this,
                                        menu_selector(GameScene::menuCloseCallback) );
    pCloseItem->setPosition( ccp(Director::sharedDirector()->getWinSize().width - 20, 20) );

    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition( Vec2(0, 0) );
    this->addChild(pMenu, 1);

    size_ = Director::sharedDirector()->getWinSize();

    LabelTTF* pLabel = LabelTTF::create("1945", "Thonburi", 34);
	pLabel->setColor(Color3B::RED);
    pLabel->setPosition( ccp(size_.width / 2, size_.height - 20) );
    this->addChild(pLabel, 1);

    Sprite* pSprite = Sprite::create("Images/bg.png");
    pSprite->setPosition( ccp(size_.width/2, size_.height/2) );
    this->addChild(pSprite, 0);

    player_ = Sprite::create("Images/airplain_01.png");
    player_->setPosition( ccp(size_.width/2, 50) );
    this->addChild(player_, 1);
	
	setTouchEnabled(true);
	
	schedule(schedule_selector(GameScene::tick1));
	schedule(schedule_selector(GameScene::RegenEnemy), 1.f);
	schedule(schedule_selector(GameScene::Shooting), 0.2f);
	
	//enemy 배열 생성
	enemy_ = Array::create();
	enemy_->retain();

	//missile 배열 생성
	for (int a = 0; a < MAX_MISSILE; ++a)
	{
		missile_[a] = Array::create();
		missile_[a]->retain();
	}

    return true;
}

void GameScene::AddEnemy(const Vec2& position)
{
    Size size = Director::sharedDirector()->getWinSize();

	//적비행기 하나를 Scene에 추가
	enemy = Sprite::create("Images/enemy_01.png");
	enemy->setPosition(position);
	addChild(enemy);
	
	//화면 아래로 내려가는 액션 등록
	ActionInterval *move = MoveBy::create(3.f, ccp(0, -size.height));
	enemy->runAction(move);
	
	//배열에 방금 생성된 적비행기 스프라이트 포인터를 배열 요소로 추가
	enemy_->addObject(enemy);
}



void GameScene::Shooting(float time)
{
	if (!player_)
		return;
	
	for (int a = 0; a < MAX_MISSILE; ++a)
	{
		missile = Sprite::create("Images/missile.png");
		
		if (a == 0)
		{
			missile->setPosition(ccp(player_->getPosition().x - 16.f, player_->getPosition().y));
		}
		else if (a == 1)
		{
			missile->setPosition(ccp(player_->getPosition().x + 16.f, player_->getPosition().y));
		}
		
		addChild(missile);
		
		Size size = Director::sharedDirector()->getWinSize();
		ActionInterval *move = MoveBy::create(0.75f, ccp(0, size.height));
		missile->runAction(move);
		
		missile_[a]->addObject(missile);
	}
}

void GameScene::tick1(float time)
{
	obj = NULL;
	CCARRAY_FOREACH(enemy_, obj)
	{
		//적 비행기 스프라이트를 캐스팅(형변환)하여 얻어옴
		spr = (Sprite*)obj;

		//적 비행기가 화면 아래로 사라졌을 경우 메모리에서 삭제합니다
		if (spr->getPosition().y <= 0)
		{
			//화면(Scene)에 적 비행기 스프라이트를 삭제
			removeChild(spr, false);

			//addObject로 추가했던 스프라이트 포인터를 배열에서 지웁니다
			enemy_->removeObject(spr);
			
		}

		//모든 미사일 배열을 반복하여 충돌검사
		for (a = 0; a < MAX_MISSILE; ++a)
		{
			CCARRAY_FOREACH(missile_[a], obj)
			{
				missile = (Sprite*)obj;

				//미사일이 화면 위쪽으로 사라졌을 때
				if (missile->getPosition().y >= size_.height)
				{
					//미사일 삭제
					removeChild(missile, false);
					missile_[a]->removeObject(missile);
					
				}
				if (missile->getBoundingBox().intersectsRect(spr->getBoundingBox()))
				{
					
					//미사일과 적 비행기가 부딪혔을 때
					PutCrashEffect(spr->getPosition());

					//적 비행기 삭제
					removeChild(spr, false);
					enemy_->removeObject(spr);

					//미사일 삭제
					removeChild(missile, false);
					missile_[a]->removeObject(missile);
					
				}
				
			}
		}

		if (player_)
		{
			//intersectsRect함수 리턴값이 충돌하면 true를 리턴
			
			if (player_->boundingBox().intersectsRect(spr->boundingBox()))
			{
				//충돌했을때 처리

				//1.폭파 이펙트 출력
				PutCrashEffect(player_->getPosition());
				PutCrashEffect(spr->getPosition());

				//2.적 비행기를 화면에서 없애준다

				//Scene에서 적비행기 스프라이트를 Remove한다
				removeChild(spr, false);
				enemy_->removeObject(spr);

				removeChild(player_, false);
				player_ = NULL;

				regenCheckTime_ = 0.f;
			}
			
		}
	}

	//유저 비행기가 죽었을때만 체크하여 부활처리
	if (!player_ && regenCheckTime_ != -1.f)
	{
		//시간을 누적시켜서 3초 이상 경과되었을 때만 부활시킨다
		regenCheckTime_ += time;
		if (regenCheckTime_ >= 3.f)
		{
			//유저 비행기 부활처리
			player_ = Sprite::create("Images/airplain_01.png");
			player_->setPosition(ccp(size_.width / 2, 50));
			this->addChild(player_, 1);
		}
	}

	//현재 배열의 크기 = 적 비행기 갯수
	log("%d", enemy_->count());
}

void GameScene::RegenEnemy(float time)
{
	for (int a = 0; a < RANDOM_INT(1, 5); ++a) {
		Size size = Director::sharedDirector()->getWinSize();
		AddEnemy(ccp(RANDOM_INT(0, (int)size.width), size.height));
	}
}

void GameScene::PutCrashEffect(const cocos2d::Vec2 &pos)
{
	//맨첫번째 스프라이트가 로딩되어 베이스가 된다
	Sprite *expBase = Sprite::create("Images/exp_01.png");
    expBase->setPosition(pos);
    
	//애니메이션 스프라이트 5프레임을 차례로 등록해줌
    Animation *animation = Animation::create();
    animation->addSpriteFrameWithFileName("Images/exp_01.png");
    animation->addSpriteFrameWithFileName("Images/exp_02.png");
    animation->addSpriteFrameWithFileName("Images/exp_03.png");
    animation->addSpriteFrameWithFileName("Images/exp_04.png");
    animation->addSpriteFrameWithFileName("Images/exp_05.png");
    
	//0.1초 간격으로 애니메이션 처리 설정
    animation->setDelayPerUnit(0.1f);
	
	//애니메이션이 끝나고 시작 프레임(1번)으로 돌아간다
    animation->setRestoreOriginalFrame(true);
    
	//에니메이션 생성
    Animate *animate = Animate::create(animation);
	
	//애니메이션이 끝나면 removeChild를 자동으로 호출하여 메모리 삭제.. 이것도 일종의 액션이다
    CCCallFunc *removeAction = CCCallFunc::create(expBase, callfunc_selector(Node::removeFromParent));
	//removeChild(expBase);
	//애니메이션과 리무브액션 2개의 액션을 하나의 시퀀스로 등록후 runAction 실행
    FiniteTimeAction *seq = Sequence::create(animate, NULL);
    this->addChild(expBase);//씬에 이펙트(베이스 스프라이트)를 추가
    expBase->runAction(seq);//베이스 스프라이트는 애니메이션 시퀀스를 실행한다
}
void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



void GameScene::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void GameScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}
bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (!player_)
		return true;

	Vec2 touchPoint = touch->getLocationInView();
	Vec2 touchGlPoint = Director::sharedDirector()->convertToGL(touchPoint);

	Vec2 playerPos = player_->getPosition();
	distance_ = ccp(playerPos.x - touchGlPoint.x, playerPos.y - touchGlPoint.y);

	return true;
}
void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (!player_)
		return;

	Vec2 touchPoint = touch->getLocationInView();
	Vec2 touchGlPoint = Director::sharedDirector()->convertToGL(touchPoint);

	Vec2 pos = ccp(touchGlPoint.x + distance_.x, touchGlPoint.y + distance_.y);

	if (pos.x < 0.f)
	{
		pos.x = 0.f;
		distance_ = ccp(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}
	else if (pos.x > size_.width)
	{
		pos.x = size_.width;
		distance_ = ccp(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}

	if (pos.y < 0.f)
	{
		pos.y = 0.f;
		distance_ = ccp(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}
	else if (pos.y > size_.height)
	{
		pos.y = size_.height;
		distance_ = ccp(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}

	player_->setPosition(pos);
}
void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	
}