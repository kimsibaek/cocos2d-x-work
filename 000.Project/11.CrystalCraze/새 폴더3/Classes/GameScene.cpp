#include "GameScene.h"
#include "MainScene.h"
#include "stdafx.h"
#include <vector>
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace CocosDenshion;

//#if (CC_TARGET_PLATFORM == CC_PLATFOAM_ANDROID)
//#define EFFECT_FILE		"Sounds/effect2.ogg"
//#elif (CC_TARGET_PLATFORM == CC_PLATFOAM_MARMALADE)
//#define EFFECT_FILE		"Sounds/effect1.raw"
//#else
//#define EFFECT_FILE		"Sounds/effect1.wav"
//#endif
//
//#if (CC_TARGET_PLATFORM == CC_PLATFOAM_WIN32)
//#define MUSIC_FILE		"Sounds/music.mid"
//#elif (CC_TARGET_PLATFORM == CC_PLATFOAM_BLACKBERRY)
//#define MUSIC_FILE		"Sounds/background.oggw"
//#else
//#define MUSIC_FILE		"Sounds/background.mp3"
//#endif

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init())
    {
        return false;
	}
	gIsGameOver = false;
	gIsDisplayingHint = false;

	gFallingGems = cocos2d::Vector<Sprite_num>(8);
	log("%d", gFallingGems.size());
	gBoard = new int[kNumTotalGems];
	for (int i = 0; i < kNumTotalGems; i++)
	{
		gBoard[i] = -1;
	}
	gNumGemsInColumn = new float[kBoardWidth];
	gTimeSinceAddInColumn = new int[kBoardWidth];
	for (int x = 0; x < kBoardWidth; x++)
	{
		gNumGemsInColumn[x] = 0;
		gTimeSinceAddInColumn[x] = 0;
	}

	gBoardChangedSinceEvaluation = true;
	gPossibleMove = -1;

	//gBoardSprites = Vector<Sprite*>(kNumTotalGems);
	gEndTimerStarted = false;
	gScore = 0;

	

	winSize = Director::getInstance()->getWinSize();

	//바탕화면
	auto pSprite = Sprite::create("Images/background.png");
	pSprite->setPosition(winSize.width / 2, winSize.height / 2);
	pSprite->setZOrder(0);
	pSprite->setScale(0.5);
	this->addChild(pSprite);

	//윗바탕
	auto pSprite1 = Sprite::create("Images/header.png");
	pSprite1->setPosition(winSize.width / 2, winSize.height - 40);
	pSprite1->setScale(0.5f);
	pSprite1->setZOrder(1);
	this->addChild(pSprite1);

	//타이머표시
	gTimer = Sprite::create("Images/timer.png");
	/*gTimer->setPosition(winSize.width / 2, winSize.height - 57);
	gTimer->setScale(0.5f);
	gTimer->setZOrder(2);
	this->addChild(gTimer);*/
	m_pHPProgress = ProgressTimer::create(gTimer);
	m_pHPProgress->setPosition(winSize.width / 2, winSize.height - 57);
	m_pHPProgress->setScale(0.5f);
	m_pHPProgress->setPercentage(100.f);
	m_pHPProgress->setMidpoint(Vec2(0, 0.5));    //끝 지점
	m_pHPProgress->setBarChangeRate(Vec2(1, 0));
	m_pHPProgress->setZOrder(2);
	//m_pHPProgress->setType(kCCProgressTimerTypeBar);

	this->addChild(m_pHPProgress);

	//일시정지
	auto pMenuItem1 = MenuItemImage::create("Images/btn-pause.png", "Images/btn-pause-down.png", CC_CALLBACK_1(GameScene::onPressPause, this));
	pMenuItem1->setScale(0.6);
	pMenuItem1->setZOrder(3);
	pMenuItem1->setPosition(Vec2(20, winSize.height - 20));
	this->addChild(pMenuItem1);

	//점수
	char png[25];
	sprintf(png, "%d", Score_Num);
	label = Label::createWithBMFont("fonts/scorefont.fnt", png, TextHAlignment::RIGHT, 5);
	label->setAnchorPoint(Vec2(1, 0.5));
	label->setScale(1.0f);
	label->setPosition(Vec2(winSize.width-10, winSize.height-20));
	this->addChild(label);
	label->setZOrder(3);
	//onScore();
	

	time_t dNow = time(NULL); // 현재 시각을 초 단위로 얻기
	gStartTime = dNow + kIntroTime;
	gLastMoveTime = dNow;

	gNumConsecutiveGems = 0;
	gIsPowerPlay = false;
	gEndTimerStarted = false;

	gScore = 0;


	//update
	this->schedule(schedule_selector(GameScene::onUpdate), 0.02f);

	setupShimmer();

    return true;
}

void GameScene::setupShimmer()
{
	//바탕화면꾸미기
	/*cc.SpriteFrameCache.getInstance().addSpriteFrames("gamescene/shimmer.plist");

	for (int i = 0; i < 2; i++)
	{
		var sprt = cc.Sprite.createWithSpriteFrameName("gamescene/shimmer/bg-shimmer-" + i + ".png");

		var seqRot = null;
		var seqMov = null;
		var seqSca = null;

		var x;
		var y;
		var rot;

		for (var j = 0; j < 10; j++)
		{
			var time = Math.random() * 10 + 5;
			x = kBoardWidth*kGemSize / 2;
			y = Math.random()*kBoardHeight*kGemSize;
			rot = Math.random() * 180 - 90;
			var scale = Math.random() * 3 + 3;

			var actionRot = cc.EaseInOut.create(cc.RotateTo.create(time, rot), 2);
			var actionMov = cc.EaseInOut.create(cc.MoveTo.create(time, cc.p(x, y)), 2);
			var actionSca = cc.ScaleTo.create(time, scale);

			if (!seqRot)
			{
				seqRot = actionRot;
				seqMov = actionMov;
				seqSca = actionSca;
			}
			else
			{
				seqRot = cc.Sequence.create(seqRot, actionRot);
				seqMov = cc.Sequence.create(seqMov, actionMov);
				seqSca = cc.Sequence.create(seqSca, actionSca);
			}
		}

		x = kBoardWidth*kGemSize / 2;
		y = Math.random()*kBoardHeight*kGemSize;
		rot = Math.random() * 180 - 90;

		sprt.setPosition(x, y);
		sprt.setRotation(rot);

		sprt.setPosition(kBoardWidth*kGemSize / 2, kBoardHeight*kGemSize / 2);
		sprt.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
		sprt.setScale(3);

		gShimmerLayer.addChild(sprt);
		sprt.setOpacity(0);
		sprt.runAction(cc.RepeatForever.create(seqRot));
		sprt.runAction(cc.RepeatForever.create(seqMov));
		sprt.runAction(cc.RepeatForever.create(seqSca));

		sprt.runAction(cc.FadeIn.create(2));
	}*/
}

void GameScene::addScore(int score)
{
	if (gIsPowerPlay) score *= 3;
	gScore += score;
	//보류 :: 점수 표시
	//gScoreLabel.setString("" + gScore);
}

void GameScene::onScore() {
	char png[25];
	sprintf(png, "%d", Score_Num);
	label->setString(png);
}

void GameScene::onPressPause(Ref *pSender) {

}

void GameScene::removeMarkedGems()
{
	// Iterate through the board
	//for (int x = 0; x < kBoardWidth; x++)
	//{
	//	for (int y = 0; y < kBoardHeight; y++)
	//	{
	//		int i = x + y * kBoardWidth;

	//		if (gBoard[i] < -1)
	//		{
	//			// Increase the count for negative crystal types
	//			gBoard[i]++;
	//			if (gBoard[i] == -1)
	//			{
	//				gNumGemsInColumn[x]--;
	//				gBoardChangedSinceEvaluation = true;

	//				// Transform any gem above this to a falling gem
	//				for (int yAbove = y + 1; yAbove < kBoardHeight; yAbove++)
	//				{
	//					int idxAbove = x + yAbove*kBoardWidth;

	//					if (gBoard[idxAbove] < -1)
	//					{
	//						gNumGemsInColumn[x]--;
	//						gBoard[idxAbove] = -1;
	//					}
	//					if (gBoard[idxAbove] == -1) continue;

	//					// The gem is not connected, make it into a falling gem
	//					int gemType = gBoard[idxAbove];
	//					auto gemSprite = gBoardSprites.at(idxAbove);

	//					Sprite_num gem;
	//					gem.gemType = gemType;
	//					gem.sprite = gemSprite;
	//					gem.yPos = yAbove;
	//					gem.ySpeed = 0;
	//					if (gFallingGemsSize[x])	gFallingGems[x].sprite_num = (Sprite_num*)realloc(gFallingGems[x].sprite_num, sizeof(Sprite_num) * (gFallingGemsSize[x] + 1));
	//					else						gFallingGems[x].sprite_num = (Sprite_num*)malloc(sizeof(Sprite_num) * (gFallingGemsSize[x] + 1));

	//					gFallingGems[x].sprite_num[gFallingGemsSize[x]] = gem;
	//					gFallingGemsSize[x]++;

	//					// Remove from board
	//					gBoard[idxAbove] = -1;


	//					//보류 :: ex::mpData.eraseObject(pSprite);
	//					gBoardSprites.erase(idxAbove);
	//					

	//					gNumGemsInColumn[x]--;
	//				}

	//			}
	//		}
	//	}
	//}
}

int GameScene::findMove()
{
	if (!gBoardChangedSinceEvaluation)
	{
		return gPossibleMove;
	}

	// Iterate through all places on the board
	for (int y = 0; y < kBoardHeight; y++)
	{
		for (int x = 0; x < kBoardWidth; x++)
		{
			int idx = x + y*kBoardWidth;
			int gemType = gBoard[idx];

			// Make sure that it is a gem
			if (gemType < 0 || gemType >= 5) continue;

			// Check surrounding tiles
			int numSimilar = 0;

			if (getGemType(x - 1, y) == gemType) numSimilar++;
			if (getGemType(x + 1, y) == gemType) numSimilar++;
			if (getGemType(x, y - 1) == gemType) numSimilar++;
			if (getGemType(x, y + 1) == gemType) numSimilar++;

			if (numSimilar >= 2)
			{
				gPossibleMove = idx;
				return idx;
			}
		}
	}
	gBoardChangedSinceEvaluation = false;
	gPossibleMove = -1;
	return -1;
}

int GameScene::getGemType(int x, int y)
{
	if (x < 0 || x >= kBoardWidth) return -1;
	if (y < 0 || y >= kBoardHeight) return -1;

	return gBoard[x + y*kBoardWidth];
}

void GameScene::createRandomMove()
{
	//Find a random place in the lower part of the board
	int x = rand() % kBoardWidth - 1;
	int y = rand() % kBoardHeight / 2;

	// Make sure it is a gem that we found
	int gemType = gBoard[x + y*kBoardWidth];
	if (gemType == -1 || gemType >= 5) return;

	// Change the color of two surrounding gems
	setGemType(x + 1, y, gemType);
	setGemType(x, y + 1, gemType);

	gBoardChangedSinceEvaluation = true;
}

void GameScene::setGemType(int x, int y, int newType)
{
	// Check bounds
	if (x < 0 || x >= kBoardWidth) return;
	if (y < 0 || y >= kBoardHeight) return;

	// Get the type of the gem
	int idx = x + y*kBoardWidth;
	int gemType = gBoard[idx];

	// Make sure that it is a gem
	if (gemType < 0 || gemType >= 5) return;

	gBoard[idx] = newType;

	// Remove old gem and insert a new one
	this->removeChild(gBoardSprites.at(idx), true);

	char png[25];
	sprintf(png, "Images/%d.png", newType);
	auto gemSprite = Sprite::create(png);
	gemSprite->setScale(0.4f);
	gemSprite->setPosition(x * kGemSize, y * kGemSize);
	gemSprite->setAnchorPoint(Vec2(0, 0));

	this->addChild(gemSprite);
	//보류 :: sprite 교체
	//gBoardSprites.erase(idx);
	gBoardSprites.insert(idx, gemSprite);
	//gBoardSprites.pushBack(gemSprite);

	gBoardChangedSinceEvaluation = true;
}

void GameScene::updatePowerPlay()
{
	bool powerPlay = (gNumConsecutiveGems >= 5);
	if (powerPlay == gIsPowerPlay) return;

	//보류 :: 파티클 생성
	//if (powerPlay)
	//{
	//	// Start power-play
	//	gPowerPlayParticles = cc.ParticleSystem.create("particles/power-play.plist");
	//	gPowerPlayParticles.setAutoRemoveOnFinish(true);
	//	gParticleLayer.addChild(gPowerPlayParticles);

	//	if ('opengl' in sys.capabilities) {

	//		var contentSize = gGameLayer.getContentSize();
	//		gPowerPlayLayer = cc.LayerColor.create(cc.c4b(85, 0, 70, 0), contentSize.width, contentSize.height);

	//		var action = cc.Sequence.create(cc.FadeIn.create(0.25), cc.FadeOut.create(0.25));
	//		gPowerPlayLayer.runAction(cc.RepeatForever.create(action));
	//		gPowerPlayLayer.setBlendFunc(gl.SRC_ALPHA, gl.ONE);

	//		gEffectsLayer.addChild(gPowerPlayLayer);
	//	}

	//}
	//else
	//{
	//	// Stop power-play
	//	if (gPowerPlayParticles)
	//	{
	//		gPowerPlayParticles.stopSystem();

	//		if ('opengl' in sys.capabilities) {
	//			gPowerPlayLayer.stopAllActions();
	//			gPowerPlayLayer.runAction(cc.Sequence.create(cc.FadeOut.create(0.5), cc.CallFunc.create(onRemoveFromParent, this)));
	//		}
	//	}
	//}

	gIsPowerPlay = powerPlay;
}

void GameScene::updateSparkle()
{
	//if (Math.random() > 0.1) return;
	int idx = rand() % kNumTotalGems;
	//보류 ::스파클 생성
	/*auto gemSprite = gBoardSprites.at(idx);
	if (gBoard[idx] < 0 || gBoard[idx] >= 5) return;
	if (!gemSprite) return;

	if (gemSprite.getChildren().length > 0) return;

	sprite = cc.Sprite.createWithSpriteFrameName("crystals/sparkle.png");
	sprite.runAction(cc.RepeatForever.create(cc.RotateBy.create(3, 360)));

	sprite.setOpacity(0);

	sprite.runAction(cc.Sequence.create(
	cc.FadeIn.create(0.5),
	cc.FadeOut.create(2),
	cc.CallFunc.create(onRemoveFromParent, this)));

	sprite.setPosition(kGemSize*(2 / 6), kGemSize*(4 / 6));

	gemSprite.addChild(sprite);*/
}

void GameScene::createGameOver()
{
	//free(gGameOverGems);

	//for (int x = 0; x < kBoardWidth; x++)
	//{
	//	Sprite_num* column = (Sprite_num*)malloc(sizeof(Sprite_num) * gFallingGemsSize[x]);
	//	for (int m = 0; m < gFallingGemsSize[x]; m++) {
	//		column[m] = gFallingGems[x].sprite_num[m];
	//	}
	//	for (int i = 0; i < gFallingGemsSize[x]; i++)
	//	{
	//		Sprite_num gem = column[i];

	//		float ySpeed = ((double)rand() / (RAND_MAX)* 2 - 1)*kGameOverGemSpeed;
	//		float xSpeed = ((double)rand() / (RAND_MAX)* 2 - 1)*kGameOverGemSpeed;

	//		Sprite_num gameOverGem;
	//		gameOverGem.sprite = gem.sprite;
	//		gameOverGem.yPos = gem.yPos;
	//		gameOverGem.xPos = x;
	//		gameOverGem.ySpeed = ySpeed;
	//		gameOverGem.xSpeed = xSpeed;

	//		if (gGameOverGemsSize)	gGameOverGems = (Sprite_num*)realloc(gGameOverGems, sizeof(Sprite_num) * (gGameOverGemsSize + 1));
	//		else					gGameOverGems = (Sprite_num*)malloc(				sizeof(Sprite_num) * (gGameOverGemsSize + 1));

	//		gGameOverGems[gGameOverGemsSize] = gameOverGem;
	//		gGameOverGemsSize++;
	//	}

	//	for (int y = 0; y < kBoardHeight; y++)
	//	{
	//		int i1 = x + y * kBoardWidth;
	//		if (gBoardSprites.at(i1))
	//		{
	//			float ySpeed1 = ((double)rand() / (RAND_MAX)* 2 - 1)*kGameOverGemSpeed;
	//			float xSpeed1 = ((double)rand() / (RAND_MAX)* 2 - 1)*kGameOverGemSpeed;


	//			Sprite_num gameOverGem1;
	//			gameOverGem1.sprite = gBoardSprites.at(i1);
	//			gameOverGem1.yPos = y;
	//			gameOverGem1.xPos = x;
	//			gameOverGem1.ySpeed = ySpeed1;
	//			gameOverGem1.xSpeed = xSpeed1;
	//			//var gameOverGem1 = { sprite: gBoardSprites[i1], xPos : x, yPos : y, ySpeed : ySpeed1, xSpeed : xSpeed1 };

	//			if (gGameOverGemsSize)	gGameOverGems = (Sprite_num*)realloc(gGameOverGems, sizeof(Sprite_num) * (gGameOverGemsSize + 1));
	//			else					gGameOverGems = (Sprite_num*)malloc(				sizeof(Sprite_num) * (gGameOverGemsSize + 1));

	//			gGameOverGems[gGameOverGemsSize] = gameOverGem1;
	//			gGameOverGemsSize++;
	//		}
	//	}
	//}
	////보류 :: 힌트관련
	////gHintLayer.removeAllChildren(true);

	//removeShimmer();
}

void GameScene::removeShimmer()
{
	//보류 :: 잘모름
	/*auto children = gShimmerLayer.getChildren();
	for (int i = 0; i < children.length; i++)
	{
	children[i].runAction(cc.FadeOut.create(1));
	}*/
}

void GameScene::displayHint()
{
	gIsDisplayingHint = true;

	int idx = findMove();
	int x = idx % kBoardWidth;
	int y = idx / kBoardWidth;

	std::vector<int> connected = findConnectedGems(x, y);

	for (int i = 0; i < connected.size(); i++)
	{
		idx = connected.at(i);
		x = idx % kBoardWidth;
		y = idx / kBoardWidth;

		//보류 :: 힌트 표시
		/*var actionFadeIn = cc.FadeIn.create(0.5);
		var actionFadeOut = cc.FadeOut.create(0.5);
		var actionSeq = cc.Sequence.create(actionFadeIn, actionFadeOut);
		var action = cc.RepeatForever.create(actionSeq);

		var hintSprite = cc.Sprite.createWithSpriteFrameName("crystals/hint.png");
		hintSprite.setOpacity(0);
		hintSprite.setPosition(x*kGemSize, y*kGemSize);
		hintSprite.setAnchorPoint(0, 0);
		gHintLayer.addChild(hintSprite);
		hintSprite.runAction(action);*/
	}
}

std::vector<int> GameScene::findConnectedGems_(int x, int y, std::vector<int> arr, int gemType)
{
	// Check for bounds
	if (x < 0 || x >= kBoardWidth) return arr;
	if (y < 0 || y >= kBoardHeight) return arr;

	int idx = x + y*kBoardWidth;

	// Make sure that the gems type match
	log("%d", gBoard[idx]);

	if (gBoard[idx] != gemType) return arr;


	// Check if idx is already visited
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr.at(i) == idx) return arr;
	}

	// Add idx to array
	arr.push_back(idx);

	// Visit neighbours
	arr = findConnectedGems_(x + 1, y, arr, gemType);
	arr = findConnectedGems_(x - 1, y, arr, gemType);
	arr = findConnectedGems_(x, y + 1, arr, gemType);
	arr = findConnectedGems_(x, y - 1, arr, gemType);

	return arr;
}

std::vector<int> GameScene::findConnectedGems(int x, int y)
{
	std::vector<int> connected;
	if (gBoard[x + y*kBoardWidth] <= -1) return connected;

	connected = findConnectedGems_(x, y, connected, gBoard[x + y*kBoardWidth]);

	return connected;
}

void GameScene::updateGameOver()
{
	/*for (int i = 0; i < gGameOverGemsSize; i++)
	{
		Sprite_num gem = gGameOverGems[i];

		gem.xPos = gem.xPos + gem.xSpeed;
		gem.yPos = gem.yPos + gem.ySpeed;
		gem.ySpeed -= kGameOverGemAcceleration;

		gem.sprite->setPosition(gem.xPos*kGemSize, gem.yPos*kGemSize);
	}*/
}

void GameScene::onUpdate(float f) {
	//if (!gIsGameOver)
	//{
	//	removeMarkedGems();

	//	int x;
	//	Sprite* gem;

	//	// Add falling gems
	//	for (x = 0; x < kBoardWidth; x++)
	//	{
	//		if (gNumGemsInColumn[x] + gFallingGems[x].length < kBoardHeight &&
	//			gTimeSinceAddInColumn[x] >= kTimeBetweenGemAdds)
	//		{
	//			// A gem should be added to this column!
	//			var gemType = Math.floor(Math.random() * 5);
	//			var gemSprite = cc.Sprite.createWithSpriteFrameName("crystals/" + gemType + ".png");
	//			gemSprite.setPosition(x * kGemSize, kBoardHeight * kGemSize);
	//			gemSprite.setAnchorPoint(0, 0);

	//			gem = { gemType: gemType, sprite : gemSprite, yPos : kBoardHeight, ySpeed : 0 };
	//			gFallingGems[x].push(gem);

	//			gGameLayer.addChild(gemSprite);

	//			gTimeSinceAddInColumn[x] = 0;
	//		}

	//		gTimeSinceAddInColumn[x]++;
	//	}

	//	// Move falling gems
	//	var gemLanded = false;
	//	for (x = 0; x < kBoardWidth; x++)
	//	{
	//		var column = gFallingGems[x];
	//		var numFallingGems = gFallingGems[x].length;
	//		for (var i = numFallingGems - 1; i >= 0; i--)
	//		{
	//			gem = column[i];

	//			gem.ySpeed += 0.06;
	//			gem.ySpeed *= 0.99;
	//			gem.yPos -= gem.ySpeed;

	//			if (gem.yPos <= gNumGemsInColumn[x])
	//			{
	//				// The gem hit the ground or a fixed gem
	//				if (!gemLanded)
	//				{
	//					gAudioEngine.playEffect("sounds/tap-" + Math.floor(Math.random() * 4) + ".wav");
	//					gemLanded = true;
	//				}

	//				column.splice(i, 1);

	//				// Insert into board
	//				var y = gNumGemsInColumn[x];

	//				if (gBoard[x + y*kBoardWidth] != -1)
	//				{
	//					cc.log("Warning! Overwriting board idx: " + x + y*kBoardWidth + " type: " + gBoard[x + y*kBoardWidth]);
	//				}

	//				gBoard[x + y*kBoardWidth] = gem.gemType;
	//				gBoardSprites[x + y*kBoardWidth] = gem.sprite;

	//				// Update fixed position
	//				gem.sprite.setPosition(x*kGemSize, y*kGemSize);
	//				gNumGemsInColumn[x] ++;

	//				gBoardChangedSinceEvaluation = true;
	//			}
	//			else
	//			{
	//				// Update the falling gems position
	//				gem.sprite.setPosition(x*kGemSize, gem.yPos*kGemSize);
	//			}
	//		}
	//	}

	//	// Check if there are possible moves and no gems falling
	//	var isFallingGems = false;
	//	for (x = 0; x < kBoardWidth; x++)
	//	{
	//		if (gNumGemsInColumn[x] != kBoardHeight)
	//		{
	//			isFallingGems = true;
	//			break;
	//		}
	//	}

	//	if (!isFallingGems)
	//	{
	//		var possibleMove = findMove();
	//		if (possibleMove == -1)
	//		{
	//			// Create a possible move
	//			createRandomMove();
	//		}
	//	}

	//	// Update timer
	//	var currentTime = Date.now();
	//	var elapsedTime = (currentTime - gStartTime) / kTotalGameTime;
	//	var timeLeft = (1 - elapsedTime) * 100;
	//	if (timeLeft < 0) timeLeft = 0;
	//	if (timeLeft > 99.9) timeLeft = 99.9;

	//	gTimer.setPercentage(timeLeft);

	//	// Update consecutive moves / powerplay
	//	if (currentTime - gLastMoveTime > kMaxTimeBetweenConsecutiveMoves)
	//	{
	//		gNumConsecutiveGems = 0;
	//	}
	//	updatePowerPlay();

	//	// Update sparkles
	//	updateSparkle();

	//	// Check if timer sound should be played
	//	if (timeLeft < 6.6 && !gEndTimerStarted)
	//	{
	//		gAudioEngine.playEffect("sounds/timer.wav");
	//		gEndTimerStarted = true;
	//	}

	//	// Check for game over
	//	if (timeLeft == = 0)
	//	{
	//		createGameOver();
	//		this.rootNode.animationManager.runAnimationsForSequenceNamed("Outro");
	//		gIsGameOver = true;
	//		//gAudioEngine.stopAllEffects();
	//		cc.log("stopAllEffects not working!");
	//		gAudioEngine.playEffect("sounds/endgame.wav");
	//		gLastScore = gScore;
	//	}
	//	else if (currentTime - gLastMoveTime > kDelayBeforeHint && !gIsDisplayingHint)
	//	{
	//		displayHint();
	//	}
	//}
	//else
	//{
	//	// It's game over
	//	updateGameOver();
	//}
}

void GameScene::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}

bool GameScene::activatePowerUp(int x, int y)
{
	//// Check for bounds
	//if (x < 0 || x >= kBoardWidth) return;
	//if (y < 0 || y >= kBoardHeight) return;

	bool removedGems = false;

	//int idx = x + y * kBoardWidth;
	////폭탄일때
	//if (gBoard[idx] == kBoardTypePup0)
	//{
	//	// Activate bomb
	//	char wav[25];
	//	sprintf(wav, "sounds/powerup.wav");
	//	m_nSoundId = SimpleAudioEngine::getInstance()->playEffect(wav);
	//	//gAudioEngine.playEffect("sounds/powerup.wav");

	//	removedGems = true;

	//	addScore(2000);

	//	//폭탄sprite 삭제
	//	gBoard[idx] = -kNumRemovalFrames;
	//	this->removeChild(gBoardSprites[idx], true);
	//	gBoardSprites[idx] = null;

	//	// Remove a horizontal line
	//	int idxRemove;
	//	for (int xRemove = 0; xRemove < kBoardWidth; xRemove++)
	//	{
	//		idxRemove = xRemove + y * kBoardWidth;
	//		if (gBoard[idxRemove] >= 0 && gBoard[idxRemove] < 5)
	//		{
	//			gBoard[idxRemove] = -kNumRemovalFrames;
	//			gGameLayer.removeChild(gBoardSprites[idxRemove], true);
	//			gBoardSprites[idxRemove] = null;
	//		}
	//	}

	//	// Remove a vertical line
	//	for (var yRemove = 0; yRemove < kBoardHeight; yRemove++)
	//	{
	//		idxRemove = x + yRemove * kBoardWidth;
	//		if (gBoard[idxRemove] >= 0 && gBoard[idxRemove] < 5)
	//		{
	//			gBoard[idxRemove] = -kNumRemovalFrames;
	//			gGameLayer.removeChild(gBoardSprites[idxRemove], true);
	//			gBoardSprites[idxRemove] = null;
	//		}
	//	}

	//	// Add particle effects
	//	var hp = cc.ParticleSystem.create("particles/taken-hrow.plist");
	//	hp.setPosition(kBoardWidth / 2 * kGemSize + kGemSize / 2, y*kGemSize + kGemSize / 2);
	//	hp.setAutoRemoveOnFinish(true);
	//	gParticleLayer.addChild(hp);

	//	var vp = cc.ParticleSystem.create("particles/taken-vrow.plist");
	//	vp.setPosition(x*kGemSize + kGemSize / 2, kBoardHeight / 2 * kGemSize + kGemSize / 2);
	//	vp.setAutoRemoveOnFinish(true);
	//	gParticleLayer.addChild(vp);

	//	// Add explo anim
	//	var center = cc.p(x*kGemSize + kGemSize / 2, y*kGemSize + kGemSize / 2);

	//	// Horizontal
	//	var sprtH0 = cc.Sprite.createWithSpriteFrameName("crystals/bomb-explo.png");
	//	sprtH0.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
	//	sprtH0.setPosition(center);
	//	sprtH0.setScaleX(5);
	//	sprtH0.runAction(cc.ScaleTo.create(0.5, 30, 1));
	//	sprtH0.runAction(cc.Sequence.create(cc.FadeOut.create(0.5), cc.CallFunc.create(onRemoveFromParent, this)));
	//	gEffectsLayer.addChild(sprtH0);

	//	// Vertical
	//	var sprtV0 = cc.Sprite.createWithSpriteFrameName("crystals/bomb-explo.png");
	//	sprtV0.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
	//	sprtV0.setPosition(center);
	//	sprtV0.setScaleY(5);
	//	sprtV0.runAction(cc.ScaleTo.create(0.5, 1, 30));
	//	sprtV0.runAction(cc.Sequence.create(cc.FadeOut.create(0.5), cc.CallFunc.create(onRemoveFromParent, this)));
	//	gEffectsLayer.addChild(sprtV0);

	//	// Horizontal
	//	var sprtH1 = cc.Sprite.createWithSpriteFrameName("crystals/bomb-explo-inner.png");
	//	sprtH1.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
	//	sprtH1.setPosition(center);
	//	sprtH1.setScaleX(0.5);
	//	sprtH1.runAction(cc.ScaleTo.create(0.5, 8, 1));
	//	sprtH1.runAction(cc.Sequence.create(cc.FadeOut.create(0.5), cc.CallFunc.create(onRemoveFromParent, this)));
	//	gEffectsLayer.addChild(sprtH1);

	//	// Vertical
	//	var sprtV1 = cc.Sprite.createWithSpriteFrameName("crystals/bomb-explo-inner.png");
	//	sprtV1.setRotation(90);
	//	sprtV1.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
	//	sprtV1.setPosition(center);
	//	sprtV1.setScaleY(0.5);
	//	sprtV1.runAction(cc.ScaleTo.create(0.5, 8, 1));
	//	sprtV1.runAction(cc.Sequence.create(cc.FadeOut.create(0.5), cc.CallFunc.create(onRemoveFromParent, this)));
	//	gEffectsLayer.addChild(sprtV1);
	//}

	return removedGems;
}

bool GameScene::removeConnectedGems(int x, int y)
{
	// Check for bounds
	if (x < 0 || x >= kBoardWidth) return false;
	if (y < 0 || y >= kBoardHeight) return false;

	std::vector<int> connected = findConnectedGems(x, y);
	bool removedGems = false;

	if (connected.size() >= 3)
	{
		gBoardChangedSinceEvaluation = true;
		removedGems = true;

		addScore(100 * connected.size());

		int idxPup = -1;
		int pupX;
		int pupY;
		if (connected.size() >= 6)
		{
			// Add power-up
			idxPup = connected.at(rand()%connected.size());
			pupX = idxPup % kBoardWidth;
			pupY = (int)(idxPup / kBoardWidth);
		}

		for (int i = 0; i < connected.size(); i++)
		{
			int idx = connected.at(i);
			int gemX = idx % kBoardWidth;
			int gemY = (int)(idx / kBoardWidth);

			gBoard[idx] = -kNumRemovalFrames;
			gBoardSprites.erase(idx);
			

			// Add particle effect
			//보류 :: 파티클 생성
			/*var particle = cc.ParticleSystem.create("particles/taken-gem.plist");
			particle.setPosition(gemX * kGemSize + kGemSize / 2, gemY*kGemSize + kGemSize / 2);
			particle.setAutoRemoveOnFinish(true);
			gParticleLayer.addChild(particle);*/

			// Add power-up
			//폭탄생성
			if (idx == idxPup)
			{
				gBoard[idx] = kBoardTypePup0;

				auto sprt = Sprite::createWithSpriteFrameName("Images/bomb.png");
				sprt->setPosition(gemX*kGemSize, gemY*kGemSize);
				sprt->setAnchorPoint(Vec2(0, 0));
				sprt->setOpacity(0);
				auto myAction = FadeIn::create(0.4f);
				sprt->runAction(myAction);

				auto sprtGlow = Sprite::createWithSpriteFrameName("Images/bomb-hi.png");
				sprtGlow->setAnchorPoint(Vec2(0, 0));
				sprtGlow->setOpacity(0);
				auto myAction1 = FadeIn::create(0.4f);
				auto myAction2 = FadeOut::create(0.4f);
				auto myAction3 = Sequence::create(myAction1, myAction2, nullptr);
				auto rep = RepeatForever::create(myAction3);
				sprtGlow->runAction(rep);
				sprt->addChild(sprtGlow);
				//sprite 교체
				gBoardSprites.erase(idx);
				gBoardSprites.insert(idx, sprt);
				
				this->addChild(sprt);
			}
			else if (idxPup != -1)
			{
				//보류 :: 이펙트
				
				// Animate effect for power-up
				auto sprtLight = Sprite::createWithSpriteFrameName("Images/bomb-light.png");
				sprtLight->setPosition(gemX*kGemSize + kGemSize / 2, gemY*kGemSize + kGemSize / 2);
				//보류 :: 블라인드
				//sprtLight->setBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				this->addChild(sprtLight);

				auto movAction = MoveTo::create(0.2, Vec2(pupX*kGemSize + kGemSize / 2, pupY*kGemSize + kGemSize / 2));
				
				auto seqAction = Sequence::create(movAction, nullptr);
				onRemoveFromParent(sprtLight->getPosition());
				sprtLight->runAction(seqAction);
			}
		}
	}
	else
	{
		char wav[25];
		sprintf(wav, "sounds/miss.wav");
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect(wav);
		//gAudioEngine.playEffect("sounds/miss.wav");
	}
	time_t dNow = time(NULL); // 현재 시각을 초 단위로 얻기
	gLastMoveTime = dNow;
	//gLastMoveTime = Date.now();

	return removedGems;
}

void GameScene::onRemoveFromParent(Vec2 vec)
{
	log("%f, %f", vec.x, vec.y);
	//this->getParent()->removeChild(node, true);
}

void GameScene::processClick(Vec2 loc){
	//loc.x = loc.x - getPosition.x
	//loc.y = loc.y - getPosition.y
	//터치의 위치를 게임레이어 위치로 변환 
	//loc = cc.pSub(loc, this.gameLayer.getPosition());
	
	int x = (int)(loc.x / kGemSize);
	int y = (int)(loc.y / kGemSize);
	log("%d, %d", x, y);
	if (!gIsGameOver)
	{
		//보류 :: 힌트제거
		//gHintLayer.removeAllChildren(true);
		gIsDisplayingHint = false;

		if (activatePowerUp(x, y) || removeConnectedGems(x, y))
		{
			// Player did a valid move
			auto sound = gNumConsecutiveGems;
			if (sound > 4) sound = 4;
			//보류 :: 효과음
			//gAudioEngine.playEffect("sounds/gem-" + sound + ".wav");

			gNumConsecutiveGems++;
		}
		else
		{
			gNumConsecutiveGems = 0;
		}

		time_t dNow = time(NULL); // 현재 시각을 초 단위로 얻기
		gLastMoveTime = dNow;
		//gLastMoveTime = Date.now();
	}
	//log("processClick");
};

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	processClick(touchPoint);
	//log("onTouchBegan");
	return true;
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

	auto touchPoint = touch->getLocation();
	processClick(touchPoint);
	//log("onTouchEnded");
}