#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "vector"


class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	int kGemSize = 40;
	int kBoardWidth = 8;
	int kBoardHeight = 10;
	int kNumTotalGems = kBoardWidth * kBoardHeight;
	int kTimeBetweenGemAdds = 8;
	int kIntroTime = 1800;
	int kMaxTimeBetweenConsecutiveMoves = 1000;
	int kDelayBeforeHint = 3000;
	float kGameOverGemSpeed = 0.1;
	float kGameOverGemAcceleration = 0.005;
	bool gIsDisplayingHint;
	int gScore;
	int gNumConsecutiveGems;
	int gLastMoveTime;
	int gStartTime;

	bool gEndTimerStarted;
	bool gBoardChangedSinceEvaluation;
	int *gBoard;
	float *gNumGemsInColumn;
	int *gTimeSinceAddInColumn;
	int gPossibleMove;
	bool gIsPowerPlay;
	cocos2d::Vector<cocos2d::Sprite*> gBoardSprites;
	
	//cocos2d::Vector<Sprite_num*> gFallingGems[8];
	int kTotalGameTime = 1000 * 60;
	bool gIsGameOver = false;
	cocos2d::Sprite* gTimer;
	cocos2d::ProgressTimer *m_pHPProgress;


	void setupShimmer();
	void onScore();
	void onPressPause(Ref *pSender);
	void removeMarkedGems();
	int findMove();
	int getGemType(int x, int y);
	void createRandomMove();
	void setGemType(int x, int y, int newType);
	void updatePowerPlay();
	void updateSparkle();
	void createGameOver();
	void removeShimmer();
	void displayHint();
	void GameScene::findConnectedGems_(int x, int y, std::vector<int> arr, int gemType);
	std::vector<int> findConnectedGems(int x, int y);
	void updateGameOver();
	void onUpdate(float f);
	
	

	int Score_Num = 0;
	cocos2d::Label* label;
	cocos2d::Size winSize;
	unsigned int m_nSoundId;
	
	
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__
