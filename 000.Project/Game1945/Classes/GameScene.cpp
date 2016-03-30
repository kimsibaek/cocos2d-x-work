#include "GameScene.h"
#include "SimpleAudioEngine.h"

//android effect only support ogg

#if (CC_TARGET_PLATFORM == CC_PLATFOAM_WIN32)
#define MUSIC_FILE		"Music/music.mid"
#elif (CC_TARGET_PLATFORM == CC_PLATFOAM_BLACKBERRY)
#define MUSIC_FILE		"Music/mainMainMusic.ogg"
#else
#define MUSIC_FILE		"Music/mainMainMusic.mp3"
#endif

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
    MenuItemImage *pCloseItem = MenuItemImage::create("Images/CloseNormal.png", "Images/CloseSelected.png", this, menu_selector(GameScene::menuCloseCallback));
    pCloseItem->setPosition( Vec2(Director::getInstance()->getVisibleSize().width - 20, 20) );
	//log("%lf, %lf", Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
    Menu* pMenu = Menu::create(pCloseItem, nullptr);
    pMenu->setPosition(Vec2(0, 0));
    this->addChild(pMenu, 1);

    size_ = Director::getInstance()->getVisibleSize();
	//log("%lf, %lf", Director::sharedDirector()->getWinSize().width, Director::sharedDirector()->getWinSize().height);
    LabelTTF* pLabel = LabelTTF::create("1945", "Thonburi", 34);
	pLabel->setColor(Color3B::RED);
    pLabel->setPosition( Vec2(size_.width / 2, size_.height - 20) );
    this->addChild(pLabel, 1);

    Sprite* pSprite = Sprite::create("Images/bg.png");
    pSprite->setPosition( Vec2(size_.width/2, size_.height/2) );
    this->addChild(pSprite, 0);

    player_ = Sprite::create("Images/airplain_01.png");
    player_->setPosition( Vec2(size_.width/2, 50) );
    this->addChild(player_, 1);
	
	//setTouchEnabled(true);
	
	schedule(schedule_selector(GameScene::tick1));
	schedule(schedule_selector(GameScene::RegenEnemy), 1.0f);
	schedule(schedule_selector(GameScene::Shooting), 0.2f);
	

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//enemy 배열 생성
	//enemy_.begin();

	//missile 배열 생성
	//for (int a = 0; a < MAX_MISSILE; ++a)
	//{
	//	missile_[a].begin();
	//}
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FILE);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);
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
	ActionInterval *move = MoveBy::create(3.f, Vec2(0, -size.height));
	enemy->runAction(move);
	
	//배열에 방금 생성된 적비행기 스프라이트 포인터를 배열 요소로 추가
	enemy_.pushBack(enemy);
}



void GameScene::Shooting(float time)
{
	if (!player_)
		return;
	
	for (int a = 0; a < MAX_MISSILE; ++a)
	{
		auto missile = Sprite::create("Images/missile.png");
		//미사일 2개 생성
		if (a == 0)
		{
			missile->setPosition(Vec2(player_->getPosition().x - 16.f, player_->getPosition().y));
		}
		else if (a == 1)
		{
			missile->setPosition(Vec2(player_->getPosition().x + 16.f, player_->getPosition().y));
		}
		
		addChild(missile);
		
		Size size = Director::sharedDirector()->getWinSize();
		ActionInterval *move = MoveBy::create(0.75f, Vec2(0, size.height));
		missile->runAction(move);
		
		missile_.pushBack(missile);
		
	}
	if (player_) {
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect("Music/fireEffect.mp3");
	}
	else {
		SimpleAudioEngine::getInstance()->stopEffect(m_nSoundId);
	}
}

void GameScene::tick1(float time)
{
	//obj = NULL;
	
	for (int i = 0; i < enemy_.size(); i++) {
		spr = (Sprite*)enemy_.at(i);

		//적 비행기가 화면 아래로 사라졌을 경우 메모리에서 삭제합니다
		if (spr->getPosition().y <= 0)
		{
			//화면(Scene)에 적 비행기 스프라이트를 삭제
			removeChild(spr, false);

			//addObject로 추가했던 스프라이트 포인터를 배열에서 지웁니다
			enemy_.eraseObject(enemy_.at(i));
			continue;
		}
		//모든 미사일 배열을 반복하여 충돌검사
		for (int i = 0; i < missile_.size(); i++) {
			//auto missile = (Sprite*)missile_.at(i);

			//미사일이 화면 위쪽으로 사라졌을 때
			if (missile_.at(i)->getPosition().y >= size_.height)
			{
				//미사일 삭제
				removeChild(missile_.at(i), false);
				missile_.eraseObject(missile_.at(i));
				continue;
			}
			//missile_.at(i)->getBoundingBox();
			//spr->getBoundingBox();
			if (missile_.at(i)->getBoundingBox().intersectsRect(spr->getBoundingBox()))
			{

				//미사일과 적 비행기가 부딪혔을 때
				PutCrashEffect(spr->getPosition());

				//적 비행기 삭제
				removeChild(spr, false);
				enemy_.eraseObject(spr);
				SimpleAudioEngine::getInstance()->playEffect("Music/explodeEffect.mp3");
				//미사일 삭제
				removeChild(missile_.at(i), false);
				missile_.eraseObject(missile_.at(i));
				
			}
		}
		if (player_)
		{
			//intersectsRect함수 리턴값이 충돌하면 true를 리턴

			if (player_->getBoundingBox().intersectsRect(spr->getBoundingBox()))
			{
				//충돌했을때 처리

				//1.폭파 이펙트 출력
				PutCrashEffect(player_->getPosition());
				PutCrashEffect(spr->getPosition());

				//2.적 비행기를 화면에서 없애준다
				SimpleAudioEngine::getInstance()->playEffect("Music/shipDestroyEffect.mp3");
				SimpleAudioEngine::getInstance()->playEffect("Music/explodeEffect.mp3");
				//Scene에서 적비행기 스프라이트를 Remove한다
				removeChild(spr, false);
				enemy_.eraseObject(spr);

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
		if (regenCheckTime_ >= 3)
		{
			//유저 비행기 부활처리
			player_ = Sprite::create("Images/airplain_01.png");
			player_->setPosition(Vec2(size_.width / 2, 50));
			this->addChild(player_, 1);

		}
	}

	//현재 배열의 크기 = 적 비행기 갯수
	//log("Count1 .. %d", enemy_.size());
	//log("%d", enemy_->count());
}

void GameScene::RegenEnemy(float time)
{
	for (int a = 0; a < RANDOM_INT(1, 5); ++a) {
		Size size = Director::sharedDirector()->getWinSize();
		AddEnemy(Vec2(RANDOM_INT(0, (int)size.width), size.height));
	}
}

void GameScene::PutCrashEffect(const cocos2d::Vec2 &pos)
{
	//맨첫번째 스프라이트가 로딩되어 베이스가 된다
	auto *expBase = Sprite::create("Images/exp_01.png");
    expBase->setPosition(pos);
    
	//애니메이션 스프라이트 5프레임을 차례로 등록해줌
    auto *animation = Animation::create();
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
    auto *animate = Animate::create(animation);
	//애니메이션이 끝나면 removeChild를 자동으로 호출하여 메모리 삭제.. 이것도 일종의 액션이다
	CCCallFunc *removeAction = CCCallFunc::create(expBase, callfunc_selector(Node::removeFromParent));
	
	//애니메이션과 리무브액션 2개의 액션을 하나의 시퀀스로 등록후 runAction 실행
    auto *seq = Sequence::create(animate, removeAction, NULL);
	this->addChild(expBase);//씬에 이펙트(베이스 스프라이트)를 추가
    expBase->runAction(seq);//베이스 스프라이트는 애니메이션 시퀀스를 실행한다
	
}


bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (!player_)
		return true;

	Vec2 touchPoint = touch->getLocationInView();
	Vec2 touchGlPoint = Director::sharedDirector()->convertToGL(touchPoint);

	Vec2 playerPos = player_->getPosition();
	distance_ = Vec2(playerPos.x - touchGlPoint.x, playerPos.y - touchGlPoint.y);

	return true;
}
void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (!player_)
		return;

	Vec2 touchPoint = touch->getLocationInView();
	Vec2 touchGlPoint = Director::sharedDirector()->convertToGL(touchPoint);

	Vec2 pos = Vec2(touchGlPoint.x + distance_.x, touchGlPoint.y + distance_.y);

	if (pos.x < 0.f)
	{
		pos.x = 0.f;
		distance_ = Vec2(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}
	else if (pos.x > size_.width)
	{
		pos.x = size_.width;
		distance_ = Vec2(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}

	if (pos.y < 0.f)
	{
		pos.y = 0.f;
		distance_ = Vec2(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}
	else if (pos.y > size_.height)
	{
		pos.y = size_.height;
		distance_ = Vec2(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}

	player_->setPosition(pos);
}
void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
